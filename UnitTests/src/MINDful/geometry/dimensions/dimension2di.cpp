#include <mock_assert.h>
#include <geometry/dimensions/Dimension2Di.h>
#include <geometry/points/Point2Di.h>
#include <geometry/dimensions/Dimension3Di.h>

using namespace std ;
using namespace Mind ;


/** @brief  Test allocation of Dimension2D objects. */
static void itest_allocation() {
    Dimension2Di dim2d1 ;
    assert(dim2d1.getWidth() == 0) ;
    assert(dim2d1.getHeight() == 0) ;

    Dimension2Di dim2d2(5, 3) ;
    assert(dim2d2.getWidth() == 5) ;
    assert(dim2d2.getHeight() == 3) ;

    Dimension2Di dim2d3(dim2d2) ;
    assert(dim2d3.getWidth() == 5) ;
    assert(dim2d3.getHeight() == 3) ;
}

/** @brief  Test scalar operations on Dimension2D objects. */
static void itest_scalar() {
    const int Width = 6 ;
    const int Height = 9 ;
    const int Divisor = 3 ;
    const int Factor = 5 ;
    Dimension2Di dim2d1(Width, Height) ;

    /* Divisions */
    Dimension2Di dim2d2 = dim2d1 / Divisor ;
    assert(dim2d2.getWidth() == Width / Divisor) ;
    assert(dim2d2.getHeight() == Height / Divisor) ;

    dim2d2 /= Divisor ;
    assert(dim2d2.getWidth() == Width / Divisor / Divisor) ;
    assert(dim2d2.getHeight() == Height / Divisor / Divisor) ;

    /* Products */
    Dimension2Di dim2d3 = dim2d1 * Factor ;
    assert(dim2d3.getWidth() == Width * Factor) ;
    assert(dim2d3.getHeight() == Height * Factor) ;

    dim2d3 *= Factor ;
    assert(dim2d3.getWidth() == Width * Factor * Factor) ;
    assert(dim2d3.getHeight() == Height * Factor * Factor) ;
}

/** @brief  Test Dimension2D operations. */
static void itest_operation() {
    const int Width1 = 5478 ;
    const int Height1 = 4855 ;
    Dimension2Di dim2d1(Width1, Height1) ;

    const int Width2 = 48781 ;
    const int Height2 = 45778 ;
    Dimension2Di dim2d2(Width2, Height2) ;

    const int Width3 = 34 ;
    const int Height3 = 3 ;
    Dimension2Di dim2d3(Width3, Height3) ;

    /* Addition */
    Dimension2Di dim2d1PLUSd2 = dim2d1 + dim2d2 ;
    assert(dim2d1PLUSd2.getWidth() == Width1 + Width2) ;
    assert(dim2d1PLUSd2.getHeight() == Height1 + Height2) ;

    Dimension2Di dim2d1PLUSd3 = dim2d1 + dim2d3 ;
    assert(dim2d1PLUSd3.getWidth() == Width1 + Width3) ;
    assert(dim2d1PLUSd3.getHeight() == Height1 + Height3) ;

    Dimension2Di dim2d2PLUSd3 = dim2d2 + dim2d3 ;
    assert(dim2d2PLUSd3.getWidth() == Width2 + Width3) ;
    assert(dim2d2PLUSd3.getHeight() == Height2 + Height3) ;

    dim2d2PLUSd3 += dim2d1 ;
    assert(dim2d2PLUSd3.getWidth() == Width2 + Width3 + Width1) ;
    assert(dim2d2PLUSd3.getHeight() == Height2 + Height3 + Height1) ;


    /* Difference */
    Dimension2Di dim2d1MINUSd2 = dim2d1 - dim2d2 ;
    assert(dim2d1MINUSd2.getWidth() == Width1 - Width2) ;
    assert(dim2d1MINUSd2.getHeight() == Height1 - Height2) ;

    Dimension2Di dim2d1MINUSd3 = dim2d1 - dim2d3 ;
    assert(dim2d1MINUSd3.getWidth() == Width1 - Width3) ;
    assert(dim2d1MINUSd3.getHeight() == Height1 - Height3) ;

    Dimension2Di dim2d2MINUSd3 = dim2d2 - dim2d3 ;
    assert(dim2d2MINUSd3.getWidth() == Width2 - Width3) ;
    assert(dim2d2MINUSd3.getHeight() == Height2 - Height3) ;

    dim2d2MINUSd3 -= dim2d1 ;
    assert(dim2d2MINUSd3.getWidth() == Width2 - Width3 - Width1) ;
    assert(dim2d2MINUSd3.getHeight() == Height2 - Height3 - Height1) ;
}

/** @brief  Test equality operator between Dimension2Di. */
static void itest_equality() {
    const int Width1 = 45755 ;
    const int Height1 = 751445 ;
    Dimension2Di dim2d1 = Dimension2Di(Width1, Height1) ;
    Dimension2Di dim2d2 = Dimension2Di(Width1, Height1) ;
    Dimension2Di dim2d3 = Dimension2Di(dim2d1) ;
    Dimension2Di dim2d4 = Dimension2Di(dim2d2) ;

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

/** @brief  Test inequality operator between Dimension2Di. */
static void itest_inequality() {
    const int Width1 = 4575975 ;
    const int Height1 = 757445 ;
    Dimension2Di dim2d1 = Dimension2Di(Width1, Height1) ;

    const int Width2 = 4575975 ;
    const int Height2 = 777445 ;
    Dimension2Di dim2d2 = Dimension2Di(Width2, Height2) ;

    const int Width3 = 455975 ;
    const int Height3 = 777445 ;
    Dimension2Di dim2d3 = Dimension2Di(Width3, Height3) ;

    const int Width4 = 987 ;
    const int Height4 = 17 ;
    Dimension2Di dim2d4 = Dimension2Di(Width4, Height4) ;

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

/** @brief  Test setting values in Dimension2Di. */
static void itest_setter() {
    Dimension2Di dim2d ;

    int width = 7 ;
    int height = 14 ;
    dim2d.set(width, height) ;
    assert(dim2d.getWidth() == width) ;
    assert(dim2d.getHeight() == height) ;

    width = 9 ;
    dim2d.setWidth(width) ;
    assert(dim2d.getWidth() == width) ;
    assert(dim2d.getHeight() == height) ;

    height = 87 ;
    dim2d.setHeight(height) ;
    assert(dim2d.getWidth() == width) ;
    assert(dim2d.getHeight() == height) ;
}

/** @brief Test conversion from Dimension2D to Dimension3Df and Point2Df. */
static void itest_cast() {
    {
        const int Width = 897 ;
        const int Height = 5452 ;
        Dimension2Di dim2d(Width, Height) ;
        Dimension3Di dim3d = (Dimension3Di) dim2d ;
        assert(dim3d.getWidth() == dim2d.getWidth()) ;
        assert(dim3d.getHeight() == dim2d.getHeight()) ;
        assert(dim3d.getDepth() == 0) ;
    }

    {
        const int Width = 7 ;
        const int Height = 469 ;
        Dimension2Di dim2d(Width, Height) ;
        Point2Di p2d = (Point2Di) dim2d ;
        assert(p2d.getX() == dim2d.getWidth()) ;
        assert(p2d.getY() == dim2d.getHeight()) ;
    }
}

int main() {
    itest_allocation() ;
    itest_scalar() ;
    itest_operation() ;
    itest_equality() ;
    itest_inequality() ;
    itest_setter() ;
    itest_cast() ;

    return TestResult ; // Defined in <mock_assert.h>
}
