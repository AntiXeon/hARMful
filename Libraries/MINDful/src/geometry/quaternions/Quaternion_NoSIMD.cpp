#include <geometry/quaternions/Quaternion.hpp>

#ifdef USE_NO_SIMD // for compilations where SSE and NEON are not available
#include <FastMath.hpp>
#include <Math.hpp>

namespace Mind {
    const Scalar Quaternion::Epsilon = 1e-3 ;
    const Quaternion Quaternion::Zero = Quaternion() ;
    const Quaternion Quaternion::Identity = Quaternion(0.f, 0.f, 0.f, 1.f) ;
    const SIMD::Vector4f Quaternion::VectorPartExtractor = SIMD::Vector4f(1.f, 1.f, 1.f, 0.f) ;

    Quaternion::Quaternion():
        Quaternion(
            0.f,
            0.f,
            0.f,
            0.f
        ) {}

    Quaternion::Quaternion(const Quaternion& other):
        Quaternion(
            other.m_values[Axis::X],
            other.m_values[Axis::Y],
            other.m_values[Axis::Z],
            other.m_values[Axis::W]
        ) {}

    Quaternion::Quaternion(
        const Scalar& x,
        const Scalar& y,
        const Scalar& z,
        const Scalar& w
    ) {
        m_values[Axis::X] = x ;
        m_values[Axis::Y] = y ;
        m_values[Axis::Z] = z ;
        m_values[Axis::W] = w ;
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

    Scalar Quaternion::dot(const Quaternion& other) const {
        return (m_values[Axis::X] * other.m_values[Axis::X]) +
                (m_values[Axis::Y] * other.m_values[Axis::Y]) +
                (m_values[Axis::Z] * other.m_values[Axis::Z]) +
                (m_values[Axis::W] * other.m_values[Axis::W]) ;
    }

    Scalar Quaternion::norm() const {
        return std::sqrt(
            (m_values[Axis::X] * m_values[Axis::X]) +
            (m_values[Axis::Y] * m_values[Axis::Y]) +
            (m_values[Axis::Z] * m_values[Axis::Z]) +
            (m_values[Axis::W] * m_values[Axis::W])
        ) ;
    }

    Scalar Quaternion::normalize() {
        Scalar length = norm() ;
        *this *= (1.f / length) ;
        return length ;
    }

    Quaternion Quaternion::inverse() const {
        Scalar squaredLength = this -> dot(*this) ;
        if (squaredLength > 0.f) {
            Scalar invertedSquaredLength = 1.f / squaredLength ;
            return Quaternion(
                -m_values[Axis::X] * invertedSquaredLength,
                -m_values[Axis::Y] * invertedSquaredLength,
                -m_values[Axis::Z] * invertedSquaredLength,
                m_values[Axis::W] * invertedSquaredLength
            ) ;
        }
        else {
            return Quaternion::Zero ;
        }
    }

    Quaternion Quaternion::exp() const {
        Scalar normV = std::sqrt(
            (m_values[Axis::X] * m_values[Axis::X]) +
            (m_values[Axis::Y] * m_values[Axis::Y]) +
            (m_values[Axis::Z] * m_values[Axis::Z])
        ) ;
        Scalar angleSin = std::sin(normV) ;
        Scalar angleCos = std::cos(normV) ;
        Scalar expW = std::exp(m_values[Axis::W]) ;

        Quaternion result ;
        if (std::abs(angleSin) >= Epsilon) {
            Scalar coeff = expW * (angleSin / normV) ;
            result.m_values[Axis::X] = m_values[Axis::X] * coeff ;
            result.m_values[Axis::Y] = m_values[Axis::Y] * coeff ;
            result.m_values[Axis::Z] = m_values[Axis::Z] * coeff ;
        }
        else {
            result.m_values[Axis::X] = 0.f ;
            result.m_values[Axis::Y] = 0.f ;
            result.m_values[Axis::Z] = 0.f ;
        }
        result.m_values[Axis::W] = angleCos * expW ;

        return result ;
    }

    Quaternion Quaternion::ln() const {
        Quaternion unitQuaternion = *this ;
        unitQuaternion.normalize() ;

        Quaternion result ;
        result.m_values[Axis::W] = 0.f ;

        if (std::abs(m_values[Axis::W]) < 1.f) {
            Scalar normV = std::sqrt(
                (unitQuaternion.m_values[Axis::X] * unitQuaternion.m_values[Axis::X]) +
                (unitQuaternion.m_values[Axis::Y] * unitQuaternion.m_values[Axis::Y]) +
                (unitQuaternion.m_values[Axis::Z] * unitQuaternion.m_values[Axis::Z])
            ) ;
            Scalar angle = std::atan2(normV, unitQuaternion.m_values[Axis::W]) ;

            Scalar angleSin = std::sin(angle) ;
            if (std::abs(angleSin) >= Epsilon) {
                Scalar coeff = angle / angleSin ;
                result.m_values[Axis::X] = unitQuaternion.m_values[Axis::X] * coeff ;
                result.m_values[Axis::Y] = unitQuaternion.m_values[Axis::Y] * coeff ;
                result.m_values[Axis::Z] = unitQuaternion.m_values[Axis::Z] * coeff ;
            }
        }
        else {
            result.m_values[Axis::X] = unitQuaternion.m_values[Axis::X] ;
            result.m_values[Axis::Y] = unitQuaternion.m_values[Axis::Y] ;
            result.m_values[Axis::Z] = unitQuaternion.m_values[Axis::Z] ;
        }

        return result ;
    }

    Quaternion Quaternion::slerp(
        const Scalar& time,
        const Quaternion& from,
        const Quaternion& to,
        bool shortestPath
    ) {
        Scalar cos = from.dot(to) ;
        Quaternion usedTo ;

        if ((cos < 0.f) && shortestPath) {
            cos = -cos ;
            usedTo = -to ;
        }
        else {
            usedTo = to ;
        }

        if (std::abs(cos) < (1.f - Epsilon)) {
            // Standard case for SLERP
            Scalar sin = FastMath::sqrt(1.f - (cos * cos)) ;
            Scalar angle = std::atan2(sin, cos) ;
            Scalar invertedSin = 1.f / sin ;
            Scalar coeffFrom = std::sin((1.f - time) * angle) * invertedSin ;
            Scalar coeffTo = std::sin(time * angle) * invertedSin ;
            return (from * coeffFrom) + (usedTo * coeffTo) ;
        }
        else {
            // Two cases here that do not correspond to the standard case:
            // 1. "from" and "to" are very close, so a linerar interpolation can
            //    be done;
            // 2. "from" and "to" are close to be inverse one of the other, so
            //    there is an infinite amount of solution. To solve it, a linear
            //    interpolation is used as well.
            Quaternion result = (from * (1.f - time)) + (usedTo * time) ;
            result.normalize() ;
            return result ;
        }
    }

    Quaternion Quaternion::nlerp(
        const Scalar& time,
        const Quaternion& from,
        const Quaternion& to,
        bool shortestPath
    ) {
        Quaternion usedTo ;
        Quaternion result ;
        Scalar cos = from.dot(to) ;

        if ((cos < 0.f) && shortestPath) {
            usedTo = -to ;
        }
        else {
            usedTo = to ;
        }

        result = from + ((usedTo - from) * time) ;
        result.normalize() ;
        return result ;
    }

    bool Quaternion::closeTo(
        const Quaternion& other,
        const Scalar radiansEpsilon
    ) const {
         Scalar distance = this -> dot(other) ;
         Scalar angle = std::acos((2.f * distance * distance) - 1.f) ;
         return std::abs(angle) <= radiansEpsilon ;
    }

    void Quaternion::swap(Quaternion& other) {
        std::swap(m_values[Axis::X], other.m_values[Axis::X]) ;
        std::swap(m_values[Axis::Y], other.m_values[Axis::Y]) ;
        std::swap(m_values[Axis::Z], other.m_values[Axis::Z]) ;
        std::swap(m_values[Axis::W], other.m_values[Axis::W]) ;
    }

    // From Ken Shoemake's explanations on quaternions.
    // http://www.cs.ucr.edu/~vbz/resources/quatut.pdf
    void Quaternion::from(const Matrix3x3f& matrix) {
        Scalar trace = matrix.trace() ;

        if (trace >= 0.f) {
            Scalar root = std::sqrt(trace + 1.f) ;
            Scalar quartRoot = 0.5f / root ;
            m_values[Axis::X] = (matrix.at(2,1) - matrix.at(1,2)) * quartRoot ;
            m_values[Axis::Y] = (matrix.at(0,2) - matrix.at(2,0)) * quartRoot ;
            m_values[Axis::Z] = (matrix.at(1,0) - matrix.at(0,1)) * quartRoot ;
            m_values[Axis::W] = root * 0.5f ;
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
            Scalar root = matrix.at(iAxis,iAxis) - matrix.at(jAxis,jAxis) - matrix.at(kAxis,kAxis) + 1.f ;
            root = std::sqrt(root) ;
            Scalar quartRoot = 0.5f / root ;
            Scalar* refValues[3] = { &m_values[Axis::X], &m_values[Axis::Y], &m_values[Axis::Z] } ;
            *refValues[iAxis] = root * 0.5f ;
            *refValues[jAxis] = (matrix.at(jAxis,iAxis) - matrix.at(iAxis,jAxis)) * quartRoot ;
            *refValues[kAxis] = (matrix.at(kAxis,iAxis) - matrix.at(iAxis,kAxis)) * quartRoot ;
            m_values[Axis::W] = matrix.at(kAxis,jAxis) - matrix.at(jAxis,kAxis) * quartRoot ;
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

        m_values[Axis::X] = vector.getX() * halfAngleSinus ;
        m_values[Axis::Y] = vector.getY() * halfAngleSinus ;
        m_values[Axis::Z] = vector.getZ() * halfAngleSinus ;
        m_values[Axis::W] = halfAngleCosinus ;
    }

    // From Ken Shoemake's explanations on quaternions.
    // http://www.cs.ucr.edu/~vbz/resources/quatut.pdf
    void Quaternion::to(Matrix3x3f& matrix) {
        Scalar twiceX  = m_values[Axis::X] + m_values[Axis::X] ;
        Scalar twiceY  = m_values[Axis::Y] + m_values[Axis::Y] ;
        Scalar twiceZ  = m_values[Axis::Z] + m_values[Axis::Z] ;
        Scalar x2_x = twiceX * m_values[Axis::X] ;
        Scalar y2_x = twiceY * m_values[Axis::X] ;
        Scalar z2_x = twiceZ * m_values[Axis::X] ;
        Scalar y2_y = twiceY * m_values[Axis::Y] ;
        Scalar z2_y = twiceZ * m_values[Axis::Y] ;
        Scalar z2_z = twiceZ * m_values[Axis::Z] ;
        Scalar x2_w = twiceX * m_values[Axis::W] ;
        Scalar y2_w = twiceY * m_values[Axis::W] ;
        Scalar z2_w = twiceZ * m_values[Axis::W] ;

        matrix.at(0,0, 1.0f - (y2_y + z2_z)) ;
        matrix.at(0,1, y2_x - z2_w) ;
        matrix.at(0,2, z2_x + y2_w) ;
        matrix.at(1,0, y2_x + z2_w) ;
        matrix.at(1,1, 1.0f - (x2_x + z2_z)) ;
        matrix.at(1,2, z2_y - x2_w) ;
        matrix.at(2,0, z2_x - y2_w) ;
        matrix.at(2,1, z2_y + x2_w) ;
        matrix.at(2,2, 1.0f - (x2_x + y2_y)) ;
    }

    void Quaternion::to(Vector3f& vector, Scalar& radAngle) {
        // Get the length of the vector part of the quaternion (x,y,z).
        Scalar squaredLength = (m_values[Axis::X] * m_values[Axis::X]) + (m_values[Axis::Y] * m_values[Axis::Y]) + (m_values[Axis::Z] * m_values[Axis::Z]) ;
        if (squaredLength > 0.f) {
            Scalar invertedLength = 1.f / std::sqrt(squaredLength) ;
            vector.setX(m_values[Axis::X] * invertedLength) ;
            vector.setY(m_values[Axis::Y] * invertedLength) ;
            vector.setZ(m_values[Axis::Z] * invertedLength) ;
            radAngle = 2.f * std::acos(m_values[Axis::W]) ;
        }
        else {
            // Several solution can exist (the angle is 0 % 2xPi radians...).
            vector.setX(1.f) ;
            vector.setY(0.f) ;
            vector.setZ(0.f) ;
            radAngle = 0.f ;
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

    void Quaternion::to(
        Scalar& roll,
        Scalar& pitch,
        Scalar& yaw
    ) {
        Scalar squaredY = m_values[Axis::Y] * m_values[Axis::Y] ;

        // Roll (x-axis rotation).
        Scalar t0 = 2.f * (m_values[Axis::W] * m_values[Axis::X] + m_values[Axis::Y] * m_values[Axis::Z]) ;
        Scalar t1 = 1.f - 2.f * (m_values[Axis::X] * m_values[Axis::X] + squaredY) ;
        roll = std::atan2(t0, t1) ;

        // Pitch (y-axis rotation).
        Scalar t2 = 2.f * (m_values[Axis::W] * m_values[Axis::Y] - m_values[Axis::Z] + m_values[Axis::X]) ;
        if (t2 > 1.f) {
            t2 = 1.f ;
        }
        else if (t2 < -1.f) {
            t2 = -1.f ;
        }
        pitch = std::asin(t2) ;

        // Yaw (z-axis rotation).
        Scalar t3 = 2.f * (m_values[Axis::W] * m_values[Axis::Z] + m_values[Axis::X] * m_values[Axis::Y]) ;
        Scalar t4 = 1.f - 2.f * (squaredY + m_values[Axis::Z] * m_values[Axis::Z]) ;
        yaw = std::atan2(t3, t4) ;
    }

    Scalar Quaternion::operator[](const Axis& axis) const {
        return m_values[axis] ;
    }

    Scalar& Quaternion::operator[](const Axis& axis) {
        return m_values[axis] ;
    }

    Quaternion& Quaternion::operator=(const Quaternion& other) {
        m_values = other.m_values ;
        return *this ;
    }

    Quaternion& Quaternion::operator+=(const Quaternion& other) {
        size_t axes = m_values.size() ;
        for (size_t axis = 0 ; axis < axes ; axis++) {
            m_values[axis] += other.m_values[axis] ;
        }
        return *this ;
    }

    Quaternion Quaternion::operator+(const Quaternion& other) const {
        Quaternion tmp ;

        size_t axes = m_values.size() ;
        for (size_t axis = 0 ; axis < axes ; axis++) {
            tmp.m_values[axis] = m_values[axis] + other.m_values[axis] ;
        }

        return tmp ;
    }

    Quaternion& Quaternion::operator-=(const Quaternion& other) {
        size_t axes = m_values.size() ;
        for (size_t axis = 0 ; axis < axes ; axis++) {
            m_values[axis] -= other.m_values[axis] ;
        }
        return *this ;
    }

    Quaternion Quaternion::operator-(const Quaternion& other) const {
        Quaternion tmp ;

        size_t axes = m_values.size() ;
        for (size_t axis = 0 ; axis < axes ; axis++) {
            tmp.m_values[axis] = m_values[axis] - other.m_values[axis] ;
        }

        return tmp ;
    }

    Quaternion Quaternion::operator-() const {
        Quaternion tmp ;

        size_t axes = m_values.size() ;
        for (size_t axis = 0 ; axis < axes ; axis++) {
            tmp.m_values[axis] = -m_values[axis] ;
        }

        return tmp ;
    }

    Quaternion& Quaternion::operator*=(const Scalar& scalar) {
        size_t axes = m_values.size() ;
        for (size_t axis = 0 ; axis < axes ; axis++) {
            m_values[axis] *= scalar ;
        }
        return *this ;
    }

    Quaternion Quaternion::operator*(const Scalar& scalar) const {
        Quaternion tmp ;

        size_t axes = m_values.size() ;
        for (size_t axis = 0 ; axis < axes ; axis++) {
            tmp.m_values[axis] = m_values[axis] * scalar ;
        }

        return tmp ;
    }

    Quaternion& Quaternion::operator*=(const Quaternion& other) {
        *this = (*this) * other ;
        return *this ;
    }

    Quaternion Quaternion::operator*(const Quaternion& other) const {
        return Quaternion(
            (m_values[Axis::W] * other.m_values[Axis::X]) +
                (m_values[Axis::X] * other.m_values[Axis::W]) +
                (m_values[Axis::Y] * other.m_values[Axis::Z]) -
                (m_values[Axis::Z] * other.m_values[Axis::Y]),
            (m_values[Axis::W] * other.m_values[Axis::Y]) +
                (m_values[Axis::Y] * other.m_values[Axis::W]) +
                (m_values[Axis::Z] * other.m_values[Axis::X]) -
                (m_values[Axis::X] * other.m_values[Axis::Z]),
            (m_values[Axis::W] * other.m_values[Axis::Z]) +
                (m_values[Axis::Z] * other.m_values[Axis::W]) +
                (m_values[Axis::X] * other.m_values[Axis::Y]) -
                (m_values[Axis::Y] * other.m_values[Axis::X]),
            (m_values[Axis::W] * other.m_values[Axis::W]) -
                (m_values[Axis::X] * other.m_values[Axis::X]) -
                (m_values[Axis::Y] * other.m_values[Axis::Y]) -
                (m_values[Axis::Z] * other.m_values[Axis::Z])
        ) ;
    }

    Vector3f Quaternion::operator*(const Vector3f& vec3) const {
        // Implementation from the NVidia SDK.
        Vector3f vecPartQuaternion(
            m_values[Axis::X],
            m_values[Axis::Y],
            m_values[Axis::Z]
        ) ;

        // Cross products of the quaternion vector part with the provided
        // vector.
        Vector3f uv = vecPartQuaternion.cross(vec3) ;
        Vector3f uuv = vecPartQuaternion.cross(uv) ;
        uv *= (2.f * m_values[Axis::W]) ;
        uuv *= 2.f ;

        return vec3 + uv + uuv ;
    }

    bool Quaternion::operator==(const Quaternion& other) const {
        return (m_values[Axis::X] == other.m_values[Axis::X]) &&
                    (m_values[Axis::Y] == other.m_values[Axis::Y]) &&
                    (m_values[Axis::Z] == other.m_values[Axis::Z]) &&
                    (m_values[Axis::W] == other.m_values[Axis::W]) ;
    }

    bool Quaternion::operator!=(const Quaternion& other) const {
        return !(*this == other) ;
    }

    std::ostream& operator<<(std::ostream& s, const Quaternion& p) {
        s << "Quaternion: "
            << p.m_values[Quaternion::Axis::X] << ", "
            << p.m_values[Quaternion::Axis::Y] << ", "
            << p.m_values[Quaternion::Axis::Z] << ", "
            << p.m_values[Quaternion::Axis::W]
        << std::endl ;
        return s ;
    }
}

#endif
