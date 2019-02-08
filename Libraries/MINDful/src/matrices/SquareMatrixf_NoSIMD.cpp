#include <matrices/SquareMatrixf.hpp>
#include <geometry/points/Point4Df.hpp>
#include <Math.hpp>

#ifdef USE_NO_SIMD

namespace Mind {
    const size_t SquareMatrixf::MaximalDataSize = 4 ;

    SquareMatrixf::SquareMatrixf(
        const size_t size,
        const Scalar value
    ) : m_size(size),
        m_defaultValue(value) {
        for (size_t col = 0 ; col < size ; ++col) {
            for (size_t row = 0 ; row < size ; ++row) {
                m_data[row][col] = value ;
            }
        }
    }

    void SquareMatrixf::identity() {
        clearWith(0) ;

        size_t dimension = size() ;
        for (size_t diag = 0 ; diag < dimension ; ++diag) {
            m_data[diag][diag] = 1.f ;
        }
    }

    Scalar SquareMatrixf::trace() const {
        size_t dimension = size() ;
        Scalar trace = 0.f ;
        for (size_t diag = 0 ; diag < dimension ; ++diag) {
            trace += m_data[diag][diag] ;
        }

        return trace ;
    }

    void SquareMatrixf::inverse(SquareMatrixf& result) {
        float coef0 = m_data[2][2] * m_data[3][3] - m_data[3][2] * m_data[2][3] ;
        float coef2 = m_data[1][2] * m_data[3][3] - m_data[3][2] * m_data[1][3] ;
        float coef3 = m_data[1][2] * m_data[2][3] - m_data[2][2] * m_data[1][3] ;

        float coef4 = m_data[2][1] * m_data[3][3] - m_data[3][1] * m_data[2][3] ;
        float coef6 = m_data[1][1] * m_data[3][3] - m_data[3][1] * m_data[1][3] ;
        float coef7 = m_data[1][1] * m_data[2][3] - m_data[2][1] * m_data[1][3] ;

        float coef8 = m_data[2][1] * m_data[3][2] - m_data[3][1] * m_data[2][2] ;
        float coef10 = m_data[1][1] * m_data[3][2] - m_data[3][1] * m_data[1][2] ;
        float coef11 = m_data[1][1] * m_data[2][2] - m_data[2][1] * m_data[1][2] ;

        float coef12 = m_data[2][0] * m_data[3][3] - m_data[3][0] * m_data[2][3] ;
        float coef14 = m_data[1][0] * m_data[3][3] - m_data[3][0] * m_data[1][3] ;
        float coef15 = m_data[1][0] * m_data[2][3] - m_data[2][0] * m_data[1][3] ;

        float coef16 = m_data[2][0] * m_data[3][2] - m_data[3][0] * m_data[2][2] ;
        float coef18 = m_data[1][0] * m_data[3][2] - m_data[3][0] * m_data[1][2] ;
        float coef19 = m_data[1][0] * m_data[2][2] - m_data[2][0] * m_data[1][2] ;

        float coef20 = m_data[2][0] * m_data[3][1] - m_data[3][0] * m_data[2][1] ;
        float coef22 = m_data[1][0] * m_data[3][1] - m_data[3][0] * m_data[1][1] ;
        float coef23 = m_data[1][0] * m_data[2][1] - m_data[2][0] * m_data[1][1] ;

        Point4Df fac0(coef0, coef0, coef2, coef3) ;
        Point4Df fac1(coef4, coef4, coef6, coef7) ;
        Point4Df fac2(coef8, coef8, coef10, coef11) ;
        Point4Df fac3(coef12, coef12, coef14, coef15) ;
        Point4Df fac4(coef16, coef16, coef18, coef19) ;
        Point4Df fac5(coef20, coef20, coef22, coef23) ;

        Point4Df vec0(m_data[1][0], m_data[0][0], m_data[0][0], m_data[0][0]) ;
        Point4Df vec1(m_data[1][1], m_data[0][1], m_data[0][1], m_data[0][1]) ;
        Point4Df vec2(m_data[1][2], m_data[0][2], m_data[0][2], m_data[0][2]) ;
        Point4Df vec3(m_data[1][3], m_data[0][3], m_data[0][3], m_data[0][3]) ;

        Point4Df inv0 = Point4Df::mul(vec1, fac0) - Point4Df::mul(vec2, fac1) + Point4Df::mul(vec3, fac2) ;
        Point4Df inv1 = Point4Df::mul(vec0, fac0) - Point4Df::mul(vec2, fac3) + Point4Df::mul(vec3, fac4) ;
        Point4Df inv2 = Point4Df::mul(vec0, fac1) - Point4Df::mul(vec1, fac3) + Point4Df::mul(vec3, fac5) ;
        Point4Df inv3 = Point4Df::mul(vec0, fac2) - Point4Df::mul(vec1, fac4) + Point4Df::mul(vec2, fac5) ;

        Point4Df signA(+1, -1, +1, -1) ;
        Point4Df signB(-1, +1, -1, +1) ;
        result.m_data[0] = Point4Df::mul(inv0, signB).toArray() ;
        result.m_data[1] = Point4Df::mul(inv1, signA).toArray() ;
        result.m_data[2] = Point4Df::mul(inv2, signB).toArray() ;
        result.m_data[3] = Point4Df::mul(inv3, signA).toArray() ;

        Point4Df resultRow0(result[0][0], result[1][0], result[2][0], result[3][0]) ;
        Point4Df thisRow0(m_data[0][0], m_data[1][0], m_data[2][0], m_data[3][0]) ;

        Point4Df dot0 = Point4Df::mul(thisRow0, resultRow0) ;
        float dot1 = (dot0.get(Point4Df::X) + dot0.get(Point4Df::Y)) + (dot0.get(Point4Df::Z) + dot0.get(Point4Df::W)) ;

        float oneOverDeterminant = -1.f / dot1 ;

        for(size_t x = 0 ; x < m_size ; ++x) {
            for(size_t y = 0 ; y < m_size ; ++y) {
                result[x][y] *= oneOverDeterminant ;
            }
        }
    }

    size_t SquareMatrixf::size() const {
        return m_size ;
    }

    bool SquareMatrixf::operator==(const SquareMatrixf& other) const {
        if (this != &other) {
            if (size() != other.size()) {
                return false ;
            }

            for (size_t row = 0; row < m_size; ++row) {
                for (size_t col = 0; col < m_size; ++col) {
                    if (m_data[row][col] != other.m_data[row][col]) {
                        return false ;
                    }
                }
            }

            return true ;
        }

        return true ;
    }

    bool SquareMatrixf::operator!=(const SquareMatrixf& other) const {
        return !(*this == other) ;
    }

    std::ostream& operator<<(std::ostream& s, const SquareMatrixf& p) {
        s << "SquareMatrixf: " << std::endl ;
            size_t size = p.size() ;
            for (unsigned int row = 0 ; row < size ; ++row) {
                s << "{ " ;
                for (unsigned int col = 0 ; col < size ; ++col) {
                    s << p.m_data[row][col] << " ; " ;
                }
                s << "}" << std::endl ;
            }
        s << std::endl ;
        return s ;
    }

    void SquareMatrixf::clearWith(const Scalar value) {
        for (size_t col = 0 ; col < MaximalDataSize ; ++col) {
            for (size_t row = 0 ; row < MaximalDataSize ; ++row) {
                m_data[row][col] = value ;
            }
        }
    }

    void SquareMatrixf::getData(Scalar* output) {
        size_t outputIndex = 0 ;
        for (size_t row = 0 ; row < m_size ; ++row) {
            output[outputIndex]     = m_data[row][0] ;
            output[outputIndex + 1] = m_data[row][1] ;
            output[outputIndex + 2] = m_data[row][2] ;
            output[outputIndex + 3] = m_data[row][3] ;
            outputIndex += MaximalDataSize ;
        }
    }
} ;

#endif
