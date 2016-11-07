#include <mock_assert.h>
#include <geometry/dimensions/Dimension2Di.h>
#include <geometry/points/Point2Di.h>
#include <geometry/dimensions/Dimension3Di.h>

using namespace std ;
using namespace Mind ;


/** @brief  Test allocation of Dimension2D objects. */
static void ftest_allocation() {
    Dimension3Di dim3d1 ;
    assert(dim3d1.getWidth() == 0) ;
    assert(dim3d1.getHeight() == 0) ;
    assert(dim3d1.getDepth() == 0) ;

    Dimension3Di dim3d2(52, 39, 95) ;
    assert(dim3d2.getWidth() == 52) ;
    assert(dim3d2.getHeight() == 39) ;
    assert(dim3d2.getDepth() == 95) ;

    Dimension3Di dim3d3(dim3d2) ;
    assert(dim3d3.getWidth() == 52) ;
    assert(dim3d3.getHeight() == 39) ;
    assert(dim3d3.getDepth() == 95) ;
}

/** @brief  Test scalar operations on Dimension2D objects. */
static void ftest_scalar() {
    const int Width = 685 ;
    const int Height = 241 ;
    const int Depth = 4529 ;
    const int Divisor = 377899 ;
    const int Factor = 597 ;
    Dimension3Di dim3d1(Width, Height, Depth) ;

    /* Divisions */
    Dimension3Di dim3d2 = dim3d1 / Divisor ;
    assert(dim3d2.getWidth() == Width / Divisor) ;
    assert(dim3d2.getHeight() == Height / Divisor) ;
    assert(dim3d2.getDepth() == Depth / Divisor) ;

    dim3d2 /= Divisor ;
    assert(dim3d2.getWidth() == Width / Divisor / Divisor) ;
    assert(dim3d2.getHeight() == Height / Divisor / Divisor) ;
    assert(dim3d2.getDepth() == Depth / Divisor / Divisor) ;

    /* Products */
    Dimension3Di dim3d3 = dim3d1 * Factor ;
    assert(dim3d3.getWidth() == Width * Factor) ;
    assert(dim3d3.getHeight() == Height * Factor) ;
    assert(dim3d3.getDepth() == Depth * Factor) ;

    dim3d3 *= Factor ;
    assert(dim3d3.getWidth() == Width * Factor * Factor) ;
    assert(dim3d3.getHeight() == Height * Factor * Factor) ;
    assert(dim3d3.getDepth() == Depth * Factor * Factor) ;
}

/** @brief  Test Dimension2D operations. */
static void ftest_operation() {
    const int Width1 = 5478 ;
    const int Height1 = 4855 ;
    const int Depth1 = 75 ;
    Dimension3Di dim3d1(Width1, Height1, Depth1) ;

    const int Width2 = 48781 ;
    const int Height2 = 45778 ;
    const int Depth2 = 9765 ;
    Dimension3Di dim3d2(Width2, Height2, Depth2) ;

    const int Width3 = 34 ;
    const int Height3 = 3 ;
    const int Depth3 =4 ;
    Dimension3Di dim3d3(Width3, Height3, Depth3) ;

    /* Addition */
    Dimension3Di dim3d1PLUSd2 = dim3d1 + dim3d2 ;
    assert(dim3d1PLUSd2.getWidth() == Width1 + Width2) ;
    assert(dim3d1PLUSd2.getHeight() == Height1 + Height2) ;
    assert(dim3d1PLUSd2.getDepth() == Depth1 + Depth2) ;

    Dimension3Di dim3d1PLUSd3 = dim3d1 + dim3d3 ;
    assert(dim3d1PLUSd3.getWidth() == Width1 + Width3) ;
    assert(dim3d1PLUSd3.getHeight() == Height1 + Height3) ;
    assert(dim3d1PLUSd3.getDepth() == Depth1 + Depth3) ;

    Dimension3Di dim3d2PLUSd3 = dim3d2 + dim3d3 ;
    assert(dim3d2PLUSd3.getWidth() == Width2 + Width3) ;
    assert(dim3d2PLUSd3.getHeight() == Height2 + Height3) ;
    assert(dim3d2PLUSd3.getDepth() == Depth2 + Depth3) ;

    dim3d2PLUSd3 += dim3d1 ;
    assert(dim3d2PLUSd3.getWidth() == Width2 + Width3 + Width1) ;
    assert(dim3d2PLUSd3.getHeight() == Height2 + Height3 + Height1) ;
    assert(dim3d2PLUSd3.getDepth() == Depth2 + Depth3 + Depth1) ;


    /* Difference */
    Dimension3Di dim3d1MINUSd2 = dim3d1 - dim3d2 ;
    assert(dim3d1MINUSd2.getWidth() == Width1 - Width2) ;
    assert(dim3d1MINUSd2.getHeight() == Height1 - Height2) ;
    assert(dim3d1MINUSd2.getDepth() == Depth1 - Depth2) ;

    Dimension3Di dim3d1MINUSd3 = dim3d1 - dim3d3 ;
    assert(dim3d1MINUSd3.getWidth() == Width1 - Width3) ;
    assert(dim3d1MINUSd3.getHeight() == Height1 - Height3) ;
    assert(dim3d1MINUSd3.getDepth() == Depth1 - Depth3) ;

    Dimension3Di dim3d2MINUSd3 = dim3d2 - dim3d3 ;
    assert(dim3d2MINUSd3.getWidth() == Width2 - Width3) ;
    assert(dim3d2MINUSd3.getHeight() == Height2 - Height3) ;
    assert(dim3d2MINUSd3.getDepth() == Depth2 - Depth3) ;

    dim3d2MINUSd3 -= dim3d1 ;
    assert(dim3d2MINUSd3.getWidth() == Width2 - Width3 - Width1) ;
    assert(dim3d2MINUSd3.getHeight() == Height2 - Height3 - Height1) ;
    assert(dim3d2MINUSd3.getDepth() == Depth2 - Depth3 - Depth1) ;
}

/** @brief  Test equality operator between Dimension3Di. */
static void ftest_equality() {
    const int Width1 = 4575 ;
    const int Height1 = 751 ;
    const int Depth1 = 975 ;
    Dimension3Di dim3d1 = Dimension3Di(Width1, Height1, Depth1) ;
    Dimension3Di dim3d2 = Dimension3Di(Width1, Height1, Depth1) ;
    Dimension3Di dim3d3 = Dimension3Di(dim3d1) ;
    Dimension3Di dim3d4 = Dimension3Di(dim3d2) ;

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

/** @brief  Test inequality operator between Dimension3Di. */
static void ftest_inequality() {
    const int Width1 = 4575 ;
    const int Height1 = 751 ;
    const int Depth1 = 975 ;
    Dimension3Di dim3d1 = Dimension3Di(Width1, Height1, Depth1) ;

    const int Width2 = 4575 ;
    const int Height2 = 777 ;
    const int Depth2 = 975 ;
    Dimension3Di dim3d2 = Dimension3Di(Width2, Height2, Depth2) ;

    const int Width3 = 455 ;
    const int Height3 = 777 ;
    const int Depth3 = 975 ;
    Dimension3Di dim3d3 = Dimension3Di(Width3, Height3, Depth3) ;

    const int Width4 = 4575 ;
    const int Height4 = 751 ;
    const int Depth4 = 97 ;
    Dimension3Di dim3d4 = Dimension3Di(Width4, Height4, Depth4) ;

    const int Width5 = 987 ;
    const int Height5 = 17 ;
    const int Depth5 = 975 ;
    Dimension3Di dim3d5 = Dimension3Di(Width5, Height5, Depth5) ;

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

/** @brief  Test setting values in Dimension3Di. */
static void ftest_setter() {
    Dimension3Di dim3d ;

    int width = 7 ;
    int height = 14 ;
    int depth = 3 ;
    dim3d.set(width, height, depth) ;
    assert(dim3d.getWidth() == width) ;
    assert(dim3d.getHeight() == height) ;
    assert(dim3d.getDepth() == depth) ;

    width = 9 ;
    dim3d.setWidth(width) ;
    assert(dim3d.getWidth() == width) ;
    assert(dim3d.getHeight() == height) ;
    assert(dim3d.getDepth() == depth) ;

    height = 87 ;
    dim3d.setHeight(height) ;
    assert(dim3d.getWidth() == width) ;
    assert(dim3d.getHeight() == height) ;
    assert(dim3d.getDepth() == depth) ;

    depth = 2 ;
    dim3d.setDepth(depth) ;
    assert(dim3d.getWidth() == width) ;
    assert(dim3d.getHeight() == height) ;
    assert(dim3d.getDepth() == depth) ;
}

/** @brief Test conversion from Dimension2D to Dimension3Di and Point2Df. */
static void ftest_cast() {
    {
        const int Width = 897 ;
        const int Height = 5452 ;
        const int Depth = 487 ;
        Dimension3Di dim3d(Width, Height, Depth) ;
        Dimension2Di dim2d = (Dimension2Di) dim3d ;
        assert(dim2d.getWidth() == dim3d.getWidth()) ;
        assert(dim2d.getHeight() == dim3d.getHeight()) ;
    }

    {
        const int Width = 7 ;
        const int Height = 469 ;
        const int Depth = 7487 ;
        Dimension3Di dim3d(Width, Height, Depth) ;
        Point3Di p3d = (Point3Di) dim3d ;
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
