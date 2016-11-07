#include <mock_assert.h>
#include <test_float.h>
#include <geometry/dimensions/Dimension2Df.h>
#include <geometry/points/Point2Df.h>
#include <geometry/dimensions/Dimension3Df.h>

using namespace std ;
using namespace Mind ;

/** @brief  Test allocation of Dimension2D objects. */
static void ftest_allocation() {
    Dimension3Df dim3d1 ;
    assert(dim3d1.getWidth() == 0.f) ;
    assert(dim3d1.getHeight() == 0.f) ;
    assert(dim3d1.getDepth() == 0.f) ;

    Dimension3Df dim3d2(5.2f, 3.9f, 9.5f) ;
    assert(dim3d2.getWidth() == 5.2f) ;
    assert(dim3d2.getHeight() == 3.9f) ;
    assert(dim3d2.getDepth() == 9.5f) ;

    Dimension3Df dim3d3(dim3d2) ;
    assert(dim3d3.getWidth() == 5.2f) ;
    assert(dim3d3.getHeight() == 3.9f) ;
    assert(dim3d3.getDepth() == 9.5f) ;
}

/** @brief  Test scalar operations on Dimension2D objects. */
static void ftest_scalar() {
    const float Width = 6.8975f ;
    const float Height = 2.47441f ;
    const float Depth = 452.4459f ;
    const float Divisor = 3.77487f ;
    const float Factor = 5.97f ;
    Dimension3Df dim3d1(Width, Height, Depth) ;

    /* Divisions */
    Dimension3Df dim3d2 = dim3d1 / Divisor ;
    assert(fclose_to(dim3d2.getWidth(), Width / Divisor)) ;
    assert(fclose_to(dim3d2.getHeight(), Height / Divisor)) ;
    assert(fclose_to(dim3d2.getDepth(), Depth / Divisor)) ;

    dim3d2 /= Divisor ;
    assert(fclose_to(dim3d2.getWidth(), Width / Divisor / Divisor)) ;
    assert(fclose_to(dim3d2.getHeight(), Height / Divisor / Divisor)) ;
    assert(fclose_to(dim3d2.getDepth(), Depth / Divisor / Divisor)) ;

    /* Products */
    Dimension3Df dim3d3 = dim3d1 * Factor ;
    assert(fclose_to(dim3d3.getWidth(), Width * Factor)) ;
    assert(fclose_to(dim3d3.getHeight(), Height * Factor)) ;
    assert(fclose_to(dim3d3.getDepth(), Depth * Factor)) ;

    dim3d3 *= Factor ;
    assert(fclose_to(dim3d3.getWidth(), Width * Factor * Factor)) ;
    assert(fclose_to(dim3d3.getHeight(), Height * Factor * Factor)) ;
    assert(fclose_to(dim3d3.getDepth(), Depth * Factor * Factor)) ;
}

/** @brief  Test Dimension2D operations. */
static void ftest_operation() {
    const float Width1 = 5478.45f ;
    const float Height1 = 4855.48114748786f ;
    const float Depth1 = 75.4f ;
    Dimension3Df dim3d1(Width1, Height1, Depth1) ;

    const float Width2 = 48781.4454544f ;
    const float Height2 = 45778.145f ;
    const float Depth2 = 9765.214f ;
    Dimension3Df dim3d2(Width2, Height2, Depth2) ;

    const float Width3 = 0.34545447995f ;
    const float Height3 = 0.3875487f ;
    const float Depth3 = 0.0471f ;
    Dimension3Df dim3d3(Width3, Height3, Depth3) ;

    /* Addition */
    Dimension3Df dim3d1PLUSd2 = dim3d1 + dim3d2 ;
    assert(fclose_to(dim3d1PLUSd2.getWidth(), Width1 + Width2)) ;
    assert(fclose_to(dim3d1PLUSd2.getHeight(), Height1 + Height2)) ;
    assert(fclose_to(dim3d1PLUSd2.getDepth(), Depth1 + Depth2)) ;

    Dimension3Df dim3d1PLUSd3 = dim3d1 + dim3d3 ;
    assert(fclose_to(dim3d1PLUSd3.getWidth(), Width1 + Width3)) ;
    assert(fclose_to(dim3d1PLUSd3.getHeight(), Height1 + Height3)) ;
    assert(fclose_to(dim3d1PLUSd3.getDepth(), Depth1 + Depth3)) ;

    Dimension3Df dim3d2PLUSd3 = dim3d2 + dim3d3 ;
    assert(fclose_to(dim3d2PLUSd3.getWidth(), Width2 + Width3)) ;
    assert(fclose_to(dim3d2PLUSd3.getHeight(), Height2 + Height3)) ;
    assert(fclose_to(dim3d2PLUSd3.getDepth(), Depth2 + Depth3)) ;

    dim3d2PLUSd3 += dim3d1 ;
    assert(fclose_to(dim3d2PLUSd3.getWidth(), Width2 + Width3 + Width1)) ;
    assert(fclose_to(dim3d2PLUSd3.getHeight(), Height2 + Height3 + Height1)) ;
    assert(fclose_to(dim3d2PLUSd3.getDepth(), Depth2 + Depth3 + Depth1)) ;


    /* Difference */
    Dimension3Df dim3d1MINUSd2 = dim3d1 - dim3d2 ;
    assert(fclose_to(dim3d1MINUSd2.getWidth(), Width1 - Width2)) ;
    assert(fclose_to(dim3d1MINUSd2.getHeight(), Height1 - Height2)) ;
    assert(fclose_to(dim3d1MINUSd2.getDepth(), Depth1 - Depth2)) ;

    Dimension3Df dim3d1MINUSd3 = dim3d1 - dim3d3 ;
    assert(fclose_to(dim3d1MINUSd3.getWidth(), Width1 - Width3)) ;
    assert(fclose_to(dim3d1MINUSd3.getHeight(), Height1 - Height3)) ;
    assert(fclose_to(dim3d1MINUSd3.getDepth(), Depth1 - Depth3)) ;

    Dimension3Df dim3d2MINUSd3 = dim3d2 - dim3d3 ;
    assert(fclose_to(dim3d2MINUSd3.getWidth(), Width2 - Width3)) ;
    assert(fclose_to(dim3d2MINUSd3.getHeight(), Height2 - Height3)) ;
    assert(fclose_to(dim3d2MINUSd3.getDepth(), Depth2 - Depth3)) ;

    dim3d2MINUSd3 -= dim3d1 ;
    assert(fclose_to(dim3d2MINUSd3.getWidth(), Width2 - Width3 - Width1)) ;
    assert(fclose_to(dim3d2MINUSd3.getHeight(), Height2 - Height3 - Height1)) ;
    assert(fclose_to(dim3d2MINUSd3.getDepth(), Depth2 - Depth3 - Depth1)) ;
}

/** @brief  Test equality operator between Dimension3Df. */
static void ftest_equality() {
    const float Width1 = 4575.975f ;
    const float Height1 = 751.445f ;
    const float Depth1 = 975.1746f ;
    Dimension3Df dim3d1 = Dimension3Df(Width1, Height1, Depth1) ;
    Dimension3Df dim3d2 = Dimension3Df(Width1, Height1, Depth1) ;
    Dimension3Df dim3d3 = Dimension3Df(dim3d1) ;
    Dimension3Df dim3d4 = Dimension3Df(dim3d2) ;

    assert(dim3d1 == dim3d1) ;
    assert(dim3d1 == dim3d2) ;
    assert(dim3d2 == dim3d1) ;
    assert(dim3d1 == dim3d3) ;
    assert(dim3d3 == dim3d1) ;
    assert(dim3d1 == dim3d4) ;
    assert(dim3d4 == dim3d1) ;

    assert(dim3d2 == dim3d2) ;
    assert(dim3d2 == dim3d3) ;
    assert(dim3d3 == dim3d2) ;
    assert(dim3d2 == dim3d4) ;
    assert(dim3d4 == dim3d2) ;

    assert(dim3d3 == dim3d3) ;
    assert(dim3d3 == dim3d4) ;
    assert(dim3d4 == dim3d3) ;
}

/** @brief  Test inequality operator between Dimension3Df. */
static void ftest_inequality() {
    const float Width1 = 4575.975f ;
    const float Height1 = 751.445f ;
    const float Depth1 = 975.1746f ;
    Dimension3Df dim3d1 = Dimension3Df(Width1, Height1, Depth1) ;

    const float Width2 = 4575.975f ;
    const float Height2 = 777.445f ;
    const float Depth2 = 975.1746f ;
    Dimension3Df dim3d2 = Dimension3Df(Width2, Height2, Depth2) ;

    const float Width3 = 455.975f ;
    const float Height3 = 777.445f ;
    const float Depth3 = 975.1746f ;
    Dimension3Df dim3d3 = Dimension3Df(Width3, Height3, Depth3) ;

    const float Width4 = 4575.975f ;
    const float Height4 = 751.445f ;
    const float Depth4 = 975.174f ;
    Dimension3Df dim3d4 = Dimension3Df(Width4, Height4, Depth4) ;

    const float Width5 = 987.f ;
    const float Height5 = 17.5f ;
    const float Depth5 = 975.1746f ;
    Dimension3Df dim3d5 = Dimension3Df(Width5, Height5, Depth5) ;

    assert(dim3d1 != dim3d2) ;
    assert(dim3d2 != dim3d1) ;
    assert(dim3d1 != dim3d3) ;
    assert(dim3d3 != dim3d1) ;
    assert(dim3d1 != dim3d4) ;
    assert(dim3d4 != dim3d1) ;
    assert(dim3d1 != dim3d5) ;
    assert(dim3d5 != dim3d1) ;

    assert(dim3d2 != dim3d3) ;
    assert(dim3d3 != dim3d2) ;
    assert(dim3d2 != dim3d4) ;
    assert(dim3d4 != dim3d2) ;
    assert(dim3d5 != dim3d2) ;
    assert(dim3d2 != dim3d5) ;

    assert(dim3d3 != dim3d4) ;
    assert(dim3d4 != dim3d3) ;
    assert(dim3d5 != dim3d3) ;
    assert(dim3d3 != dim3d5) ;

    assert(dim3d4 != dim3d5) ;
    assert(dim3d5 != dim3d4) ;
}

/** @brief  Test setting values in Dimension3Df. */
static void ftest_setter() {
    Dimension3Df dim3d ;

    float width = 7.874f ;
    float height = 14.132f ;
    float depth = 3.14f ;
    dim3d.set(width, height, depth) ;
    assert(dim3d.getWidth() == width) ;
    assert(dim3d.getHeight() == height) ;
    assert(dim3d.getDepth() == depth) ;

    width = 9.465f ;
    dim3d.setWidth(width) ;
    assert(dim3d.getWidth() == width) ;
    assert(dim3d.getHeight() == height) ;
    assert(dim3d.getDepth() == depth) ;

    height = 87.517f ;
    dim3d.setHeight(height) ;
    assert(dim3d.getWidth() == width) ;
    assert(dim3d.getHeight() == height) ;
    assert(dim3d.getDepth() == depth) ;

    depth = 2.698f ;
    dim3d.setDepth(depth) ;
    assert(dim3d.getWidth() == width) ;
    assert(dim3d.getHeight() == height) ;
    assert(dim3d.getDepth() == depth) ;
}

/** @brief Test conversion from Dimension2D to Dimension3Df and Point2Df. */
static void ftest_cast() {
    {
        const float Width = 897.45f ;
        const float Height = 5452.f ;
        const float Depth = 487.4f ;
        Dimension3Df dim3d(Width, Height, Depth) ;
        Dimension2Df dim2d = (Dimension2Df) dim3d ;
        assert(dim2d.getWidth() == dim3d.getWidth()) ;
        assert(dim2d.getHeight() == dim3d.getHeight()) ;
    }

    {
        const float Width = 7.45f ;
        const float Height = 469.198f ;
        const float Depth = 7487.8785f ;
        Dimension3Df dim3d(Width, Height, Depth) ;
        Point3Df p3d = (Point3Df) dim3d ;
        assert(p3d.getX() == dim3d.getWidth()) ;
        assert(p3d.getY() == dim3d.getHeight()) ;
        assert(p3d.getZ() == dim3d.getDepth()) ;
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
