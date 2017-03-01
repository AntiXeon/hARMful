#include <geometry/quaternions/Quaternion.hpp>

#ifdef USE_SIMD // for compilations where SSE or NEON are available
#include <FastMath.hpp>
#include <Math.hpp>

namespace Mind {
    const Quaternion Quaternion::Zero = Quaternion() ;
    const Quaternion Quaternion::Identity = Quaternion(0.f, 0.f, 0.f, 1.f) ;

    Quaternion::Quaternion() {
        m_values = SIMD::Vector4f(0.f, 0.f, 0.f, 0.f) ;
    }

    Quaternion::Quaternion(const Quaternion& other) : m_values(other.m_values) {}

    Quaternion::Quaternion(const SIMD::Vector4f& values) : m_values(values) {}

    Quaternion::Quaternion(
        const Scalar& x,
        const Scalar& y,
        const Scalar& z,
        const Scalar& w
    ) {
        m_values = SIMD::Vector4f(x, y, z, w) ;
    }

    Quaternion::Quaternion(const Matrix3x3f& matrix) {
        from(matrix) ;
    }

    Quaternion::Quaternion(const Vector3f& vector, const Scalar& radAngle) {
        from(vector, radAngle) ;
    }

    Quaternion::Quaternion(
        const Vector3f& xAxis,
        const Vector3f& yAxis,
        const Vector3f& zAxis
    ) {
        from(xAxis, yAxis, zAxis) ;
    }

    Quaternion::~Quaternion() {}

    Scalar Quaternion::dot(const Quaternion& other) {
        return m_values.dot(other.m_values) ;
    }

    Scalar Quaternion::norm() {
        return m_values.dot(m_values) ;
    }

    void Quaternion::swap(Quaternion& other) {
        std::swap(m_values, other.m_values) ;
    }

    // From Ken Shoemake's explanations on quaternions.
    // http://www.cs.ucr.edu/~vbz/resources/quatut.pdf
    void Quaternion::from(const Matrix3x3f& matrix) {
        const int QuaternionSize = SIMD::Vector4f::size() ;
        Scalar quaternionValues[QuaternionSize] ;
        Scalar trace = matrix.trace() ;

        if (trace >= 0.f) {
            Scalar root = FastMath::sqrt(trace + 1.f) ;
            Scalar quartRoot = 0.5f / root ;

            m_values = SIMD::Vector4f(
                matrix.at(2,1) - matrix.at(1,2),
                matrix.at(0,2) - matrix.at(2,0),
                matrix.at(1,0) - matrix.at(0,1),
                0.5f
            ) ;

            // Multiply the values of the quaternion by their corresponding root
            // or [1/4 root].
            SIMD::Vector4f factorsSIMD(
                quartRoot,
                quartRoot,
                quartRoot,
                root
            ) ;

            m_values = m_values * factorsSIMD ;
        }
        else {
            // Shuffle axes according to the values on the diagonal of the
            // matrix.
            static Axis axes[3] = { Axis::Y, Axis::Z, Axis::X } ;
            Axis iAxis = Axis::X ;
            if (matrix.at(Axis::Y, Axis::Y) > matrix.at(iAxis, iAxis)) {
                iAxis = Axis::Y ;
            }

            if (matrix.at(Axis::Z, Axis::Z) > matrix.at(iAxis, iAxis)) {
                iAxis = Axis::Z ;
            }
            Axis jAxis = axes[iAxis] ;
            Axis kAxis = axes[jAxis] ;

            // Set the values according to the axis shuffle.
            // This avoids many possible cases with quite the same code.
            Scalar* refValues[] = {
                &quaternionValues[Axis::X],
                &quaternionValues[Axis::Y],
                &quaternionValues[Axis::Z]
            } ;

            Scalar root = matrix.at(iAxis,iAxis) - matrix.at(jAxis,jAxis) - matrix.at(kAxis,kAxis) + 1.f ;
            root = FastMath::sqrt(root) ;
            Scalar quartRoot = 0.5f / root ;
            *refValues[iAxis] = 0.5f ;
            *refValues[jAxis] = matrix.at(jAxis,iAxis) - matrix.at(iAxis,jAxis) ;
            *refValues[kAxis] = matrix.at(kAxis,iAxis) - matrix.at(iAxis,kAxis) ;
            quaternionValues[Axis::W] = matrix.at(kAxis,jAxis) - matrix.at(jAxis,kAxis) ;

            m_values = SIMD::Vector4f(
                quaternionValues[Axis::X],
                quaternionValues[Axis::Y],
                quaternionValues[Axis::Z],
                quaternionValues[Axis::W]
            ) ;

            // Multiply the values of the quaternion by their corresponding root
            // or [1/4 root].
            Scalar factors[4] ;
            factors[iAxis] = root ;
            factors[jAxis] = quartRoot ;
            factors[kAxis] = quartRoot ;
            factors[Axis::W] = quartRoot ;

            SIMD::Vector4f factorsSIMD(
                factors[Axis::X],
                factors[Axis::Y],
                factors[Axis::Z],
                factors[Axis::W]
            ) ;

            m_values = m_values * factorsSIMD ;
        }
    }

    void Quaternion::from(
        const Vector3f& xAxis,
        const Vector3f& yAxis,
        const Vector3f& zAxis
    ) {
        // Convert the vector to a rotation matrix, used then to generate the
        // quaternion values.
        Matrix3x3f rotationMatrix ;

        Array4f xAxisArray ;
        xAxis.getCoordinates(xAxisArray) ;
        Array4f yAxisArray ;
        yAxis.getCoordinates(yAxisArray) ;
        Array4f zAxisArray ;
        zAxis.getCoordinates(zAxisArray) ;

        for (size_t column = 0 ; column < 3 ; ++column) {
            rotationMatrix.at(0, column) = xAxisArray[column] ;
            rotationMatrix.at(1, column) = yAxisArray[column] ;
            rotationMatrix.at(2, column) = zAxisArray[column] ;
        }

        from(rotationMatrix) ;
    }

    // From Ken Shoemake's explanations on quaternions.
    // http://www.cs.ucr.edu/~vbz/resources/quatut.pdf
    void Quaternion::from(const Vector3f& vector, const Scalar& radAngle) {
        Scalar halfAngle = radAngle * 0.5f ;
        Scalar halfAngleSinus = std::sin(halfAngle) ;
        Scalar halfAngleCosinus = std::cos(halfAngle) ;

        m_values = SIMD::Vector4f(
            halfAngleSinus,
            halfAngleSinus,
            halfAngleSinus,
            halfAngleCosinus
        ) ;

        // Multiply only the vector part of the quaternion with the provided
        // vector.
        SIMD::Vector4f::Mask maskMul(true, true, true, false) ;
        SIMD::Vector4f tmp(vector.getX(), vector.getY(), vector.getZ(), 0.f) ;
        m_values.mulIf(maskMul, tmp) ;
    }

    // From Ken Shoemake's explanations on quaternions.
    // http://www.cs.ucr.edu/~vbz/resources/quatut.pdf
    void Quaternion::to(Matrix3x3f& matrix) {
        float* valueArray = m_values ;
        auto twiceValues = m_values + m_values ;
        float* twiceValuesX = twiceValues * SIMD::Vector4f(valueArray[Axis::X]) ;
        float* twiceValuesY = twiceValues * SIMD::Vector4f(valueArray[Axis::Y]) ;
        float* twiceValuesZ = twiceValues * SIMD::Vector4f(valueArray[Axis::Z]) ;
        float* twiceValuesW = twiceValues * SIMD::Vector4f(valueArray[Axis::W]) ;

        matrix.at(0,0, 1.f - (twiceValuesY[Axis::Y] + twiceValuesZ[Axis::Z])) ;
        matrix.at(0,1, twiceValuesX[Axis::Y] - twiceValuesW[Axis::Z]) ;
        matrix.at(0,2, twiceValuesX[Axis::W] + twiceValuesW[Axis::Y]) ;

        matrix.at(1,0, twiceValuesX[Axis::Y] + twiceValuesW[Axis::Z]) ;
        matrix.at(1,1, 1.f - (twiceValuesX[Axis::X] + twiceValuesZ[Axis::Z])) ;
        matrix.at(1,2, twiceValuesY[Axis::Z] - twiceValuesW[Axis::X]) ;

        matrix.at(2,0, twiceValuesX[Axis::Z] - twiceValuesW[Axis::Y]) ;
        matrix.at(2,1, twiceValuesY[Axis::Z] + twiceValuesW[Axis::X]) ;
        matrix.at(2,2, 1.f - (twiceValuesX[Axis::X] + twiceValuesY[Axis::Y])) ;
    }

    void Quaternion::to(Vector3f& vector, Scalar& radAngle) {
        // Get the length of the vector part of the quaternion (x,y,z).
        float* valueArray = m_values ;
        SIMD::Vector4f tmp(
            valueArray[Axis::X],
            valueArray[Axis::Y],
            valueArray[Axis::Z],
            0.f
        ) ;

        Scalar squaredLength = (m_values * tmp).horizontalAdd() ;

        if (squaredLength > 0.) {
            // A unique solution exists.
            radAngle = 2.f * std::acos(valueArray[Axis::W]) ;
            SIMD::Vector4f squaredLengthVec(squaredLength) ;
            auto invLength = SIMD::Vector4f::fast_rsqrt(squaredLengthVec) ;
            auto vectorValues = tmp * invLength ;
            float* vectorValuesPtr = vectorValues ;
            vector.set(
                vectorValuesPtr[Axis::X],
                vectorValuesPtr[Axis::Y],
                vectorValuesPtr[Axis::Z]
            ) ;
        }
        else {
            // Several solution can exist (the angle is 0 % 2xPi radians...).
            radAngle = 0._rad ;
            vector.set(1.f, 0.f, 0.f) ;
        }
    }

    void Quaternion::to(
        Vector3f& xAxis,
        Vector3f& yAxis,
        Vector3f& zAxis
    ) {
        Matrix3x3f rotationMatrix ;
        to(rotationMatrix) ;

        xAxis.set(
            rotationMatrix.at(0,0),
            rotationMatrix.at(1,0),
            rotationMatrix.at(2,0)
        ) ;

        yAxis.set(
            rotationMatrix.at(0,1),
            rotationMatrix.at(1,1),
            rotationMatrix.at(2,1)
        ) ;

        zAxis.set(
            rotationMatrix.at(0,2),
            rotationMatrix.at(1,2),
            rotationMatrix.at(2,2)
        ) ;
    }

    Scalar Quaternion::operator[](const Axis& axis) const {
        float* valuesArray = m_values ;
        return valuesArray[axis] ;
    }

    Scalar& Quaternion::operator[](const Axis& axis) {
        float* valuesArray = m_values ;
        return valuesArray[axis] ;
    }

    Quaternion& Quaternion::operator=(const Quaternion& other) {
        m_values = other.m_values ;
        return *this ;
    }

    Quaternion& Quaternion::operator+=(const Quaternion& other) {
        m_values += other.m_values ;
        return *this ;
    }

    Quaternion Quaternion::operator+(const Quaternion& other) const {
        auto copyValues = m_values ;
        return Quaternion(copyValues + other.m_values) ;
    }

    Quaternion& Quaternion::operator-=(const Quaternion& other) {
        m_values -= other.m_values ;
        return *this ;
    }

    Quaternion Quaternion::operator-(const Quaternion& other) const {
        auto copyValues = m_values ;
        return Quaternion(copyValues - other.m_values) ;
    }

    Quaternion& Quaternion::operator*=(const Scalar& scalar) {
        m_values *= scalar ;
        return *this ;
    }

    Quaternion Quaternion::operator*(const Scalar& scalar) const {
        return Quaternion(m_values * scalar) ;
    }

    Quaternion& Quaternion::operator*=(const Quaternion& other) {
        Scalar newX ;
        Scalar newY ;
        Scalar newZ ;
        Scalar newW ;

        // Compute new X value of the curent Quaternion.
        // (w * other.w) - (x * other.x) - (y * other.y) - (z * other.z)
        {
            auto changedSignOtherX = other.m_values ;
            changedSignOtherX.changeSign<false, false, false, true>() ;
            newX = (m_values * changedSignOtherX).horizontalSub() ;
        }

        // Compute new Y value of the curent Quaternion.
        // (w * other.x) + (x * other.w) + (y * other.z) - (z * other.y)
        {
            auto permuteOtherY = other.m_values ;
            permuteOtherY.permute<1,0,3,2>() ;
            permuteOtherY.changeSign<false, false, false, true>() ;
            newY = (m_values * permuteOtherY).horizontalAdd() ;
        }

        // Compute new Z value of the curent Quaternion.
        // (w * other.y) + (y * other.w) + (z * other.x) - (x * other.z)
        {
            auto permuteOtherZ = other.m_values ;
            permuteOtherZ.permute<2,0,3,1>() ;
            permuteOtherZ.changeSign<false, false, false, true>() ;
            newZ = (m_values * permuteOtherZ).horizontalAdd() ;
        }

        // Compute new W value of the curent Quaternion.
        // (w * other.z) + (z * other.w) + (x * other.y) - (y * other.x)
        {
            auto permuteOtherW = other.m_values ;
            permuteOtherW.permute<3,2,0,1>() ;
            permuteOtherW.changeSign<false, false, false, true>() ;
            newW = (m_values * permuteOtherW).horizontalAdd() ;
        }

        m_values = SIMD::Vector4f(newX, newY, newZ, newW) ;
        return *this ;
    }

    Quaternion Quaternion::operator*(const Quaternion& other) const {
        Quaternion tmp(*this) ;
        tmp *= other ;
        return tmp ;
    }

    bool Quaternion::operator==(const Quaternion& /*other*/) const {
        // return m_values == other.m_values ;
        return false ;
    }

    bool Quaternion::operator!=(const Quaternion& /*other*/) const {
        // return m_values != other.m_values ;
        return false ;
    }
}

#endif
