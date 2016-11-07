#include <mock_assert.h>
#include <test_float.h>
#include <geometry/dimensions/Dimension2Df.h>
#include <geometry/points/Point2Df.h>
#include <geometry/dimensions/Dimension3Df.h>

using namespace std ;
using namespace Mind ;

/** @brief  Test allocation of Dimension2D objects. */
static void ftest_allocation() {
    Dimension2Df dim2d1 ;
    assert(dim2d1.getWidth() == 0.f) ;
    assert(dim2d1.getHeight() == 0.f) ;

    Dimension2Df dim2d2(5.2f, 3.9f) ;
    assert(dim2d2.getWidth() == 5.2f) ;
    assert(dim2d2.getHeight() == 3.9f) ;

    Dimension2Df dim2d3(dim2d2) ;
    assert(dim2d3.getWidth() == 5.2f) ;
    assert(dim2d3.getHeight() == 3.9f) ;
}

/** @brief  Test scalar operations on Dimension2D objects. */
static void ftest_scalar() {
    const float Width = 6.8975f ;
    const float Height = 2.47441f ;
    const float Divisor = 3.77487f ;
    const float Factor = 5.97f ;
    Dimension2Df dim2d1(Width, Height) ;

    /* Divisions */
    Dimension2Df dim2d2 = dim2d1 / Divisor ;
    assert(fclose_to(dim2d2.getWidth(), Width / Divisor)) ;
    assert(fclose_to(dim2d2.getHeight(), Height / Divisor)) ;

    dim2d2 /= Divisor ;
    assert(fclose_to(dim2d2.getWidth(), Width / Divisor / Divisor)) ;
    assert(fclose_to(dim2d2.getHeight(), Height / Divisor / Divisor)) ;

    /* Products */
    Dimension2Df dim2d3 = dim2d1 * Factor ;
    assert(fclose_to(dim2d3.getWidth(), Width * Factor)) ;
    assert(fclose_to(dim2d3.getHeight(), Height * Factor)) ;

    dim2d3 *= Factor ;
    assert(fclose_to(dim2d3.getWidth(), Width * Factor * Factor)) ;
    assert(fclose_to(dim2d3.getHeight(), Height * Factor * Factor)) ;
}

/** @brief  Test Dimension2D operations. */
static void ftest_operation() {
    const float Width1 = 5478.45f ;
    const float Height1 = 4855.48114748786f ;
    Dimension2Df dim2d1(Width1, Height1) ;

    const float Width2 = 48781.4454544f ;
    const float Height2 = 45778.145f ;
    Dimension2Df dim2d2(Width2, Height2) ;

    const float Width3 = 0.34545447995f ;
    const float Height3 = 0.3875487f ;
    Dimension2Df dim2d3(Width3, Height3) ;

    /* Addition */
    Dimension2Df dim2d1PLUSd2 = dim2d1 + dim2d2 ;
    assert(fclose_to(dim2d1PLUSd2.getWidth(), Width1 + Width2)) ;
    assert(fclose_to(dim2d1PLUSd2.getHeight(), Height1 + Height2)) ;

    Dimension2Df dim2d1PLUSd3 = dim2d1 + dim2d3 ;
    assert(fclose_to(dim2d1PLUSd3.getWidth(), Width1 + Width3)) ;
    assert(fclose_to(dim2d1PLUSd3.getHeight(), Height1 + Height3)) ;

    Dimension2Df dim2d2PLUSd3 = dim2d2 + dim2d3 ;
    assert(fclose_to(dim2d2PLUSd3.getWidth(), Width2 + Width3)) ;
    assert(fclose_to(dim2d2PLUSd3.getHeight(), Height2 + Height3)) ;

    dim2d2PLUSd3 += dim2d1 ;
    assert(fclose_to(dim2d2PLUSd3.getWidth(), Width2 + Width3 + Width1)) ;
    assert(fclose_to(dim2d2PLUSd3.getHeight(), Height2 + Height3 + Height1)) ;


    /* Difference */
    Dimension2Df dim2d1MINUSd2 = dim2d1 - dim2d2 ;
    assert(fclose_to(dim2d1MINUSd2.getWidth(), Width1 - Width2)) ;
    assert(fclose_to(dim2d1MINUSd2.getHeight(), Height1 - Height2)) ;

    Dimension2Df dim2d1MINUSd3 = dim2d1 - dim2d3 ;
    assert(fclose_to(dim2d1MINUSd3.getWidth(), Width1 - Width3)) ;
    assert(fclose_to(dim2d1MINUSd3.getHeight(), Height1 - Height3)) ;

    Dimension2Df dim2d2MINUSd3 = dim2d2 - dim2d3 ;
    assert(fclose_to(dim2d2MINUSd3.getWidth(), Width2 - Width3)) ;
    assert(fclose_to(dim2d2MINUSd3.getHeight(), Height2 - Height3)) ;

    dim2d2MINUSd3 -= dim2d1 ;
    assert(fclose_to(dim2d2MINUSd3.getWidth(), Width2 - Width3 - Width1)) ;
    assert(fclose_to(dim2d2MINUSd3.getHeight(), Height2 - Height3 - Height1)) ;
}

/** @brief  Test equality operator between Dimension2Df. */
static void ftest_equality() {
    const float Width1 = 4575.975f ;
    const float Height1 = 751.445f ;
    Dimension2Df dim2d1 = Dimension2Df(Width1, Height1) ;
    Dimension2Df dim2d2 = Dimension2Df(Width1, Height1) ;
    Dimension2Df dim2d3 = Dimension2Df(dim2d1) ;
    Dimension2Df dim2d4 = Dimension2Df(dim2d2) ;

    assert(dim2d1 == dim2d1) ;
    assert(dim2d1 == dim2d2) ;
    assert(dim2d2 == dim2d1) ;
    assert(dim2d1 == dim2d3) ;
    assert(dim2d3 == dim2d1) ;
    assert(dim2d1 == dim2d4) ;
    assert(dim2d4 == dim2d1) ;

    assert(dim2d2 == dim2d2) ;
    assert(dim2d2 == dim2d3) ;
    assert(dim2d3 == dim2d2) ;
    assert(dim2d2 == dim2d4) ;
    assert(dim2d4 == dim2d2) ;

    assert(dim2d3 == dim2d3) ;
    assert(dim2d3 == dim2d4) ;
    assert(dim2d4 == dim2d3) ;
}

/** @brief  Test inequality operator between Dimension2Df. */
static void ftest_inequality() {
    const float Width1 = 4575.975f ;
    const float Height1 = 751.445f ;
    Dimension2Df dim2d1 = Dimension2Df(Width1, Height1) ;

    const float Width2 = 4575.975f ;
    const float Height2 = 777.445f ;
    Dimension2Df dim2d2 = Dimension2Df(Width2, Height2) ;

    const float Width3 = 455.975f ;
    const float Height3 = 777.445f ;
    Dimension2Df dim2d3 = Dimension2Df(Width3, Height3) ;

    const float Width4 = 987.f ;
    const float Height4 = 17.5f ;
    Dimension2Df dim2d4 = Dimension2Df(Width4, Height4) ;

    assert(dim2d1 != dim2d2) ;
    assert(dim2d2 != dim2d1) ;
    assert(dim2d1 != dim2d3) ;
    assert(dim2d3 != dim2d1) ;
    assert(dim2d1 != dim2d4) ;
    assert(dim2d4 != dim2d1) ;

    assert(dim2d2 != dim2d3) ;
    assert(dim2d3 != dim2d2) ;
    assert(dim2d2 != dim2d4) ;
    assert(dim2d4 != dim2d2) ;

    assert(dim2d3 != dim2d4) ;
    assert(dim2d4 != dim2d3) ;
}

/** @brief  Test setting values in Dimension2Df. */
static void ftest_setter() {
    Dimension2Df dim2d ;

    float width = 7.874f ;
    float height = 14.132f ;
    dim2d.set(width, height) ;
    assert(dim2d.getWidth() == width) ;
    assert(dim2d.getHeight() == height) ;

    width = 9.465f ;
    dim2d.setWidth(width) ;
    assert(dim2d.getWidth() == width) ;
    assert(dim2d.getHeight() == height) ;

    height = 87.517f ;
    dim2d.setHeight(height) ;
    assert(dim2d.getWidth() == width) ;
    assert(dim2d.getHeight() == height) ;
}

/** @brief Test conversion from Dimension2D to Dimension3Df and Point2Df. */
static void ftest_cast() {
    {
        const float Width = 897.45f ;
        const float Height = 5452.f ;
        Dimension2Df dim2d(Width, Height) ;
        Dimension3Df dim3d = (Dimension3Df) dim2d ;
        assert(dim3d.getWidth() == dim2d.getWidth()) ;
        assert(dim3d.getHeight() == dim2d.getHeight()) ;
        assert(dim3d.getDepth() == 0.f) ;
    }

    {
        const float Width = 7.45f ;
        const float Height = 469.198f ;
        Dimension2Df dim2d(Width, Height) ;
        Point2Df p2d = (Point2Df) dim2d ;
        assert(p2d.getX() == dim2d.getWidth()) ;
        assert(p2d.getY() == dim2d.getHeight()) ;
    }
}

int main() {
    ftest_allocation() ;
    ftest_scalar() ;
    ftest_operation() ;
    ftest_equality() ;
    ftest_inequality() ;
    ftest_setter() ;
    ftest_cast() ;

    return TestResult ; // Defined in <mock_assert.h>
}
