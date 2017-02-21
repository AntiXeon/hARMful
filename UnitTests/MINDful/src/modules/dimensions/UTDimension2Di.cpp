#include <modules/dimensions/UTDimension2Di.hpp>
#include <geometry/dimensions/Dimension2Di.hpp>
#include <geometry/dimensions/Dimension3Di.hpp>
#include <geometry/points/Point2Di.hpp>
#include <string>
#include <iostream>

using namespace Mind ;

namespace UTMind {
    UTDimension2Di::UTDimension2Di() {}

    UTDimension2Di::~UTDimension2Di() {}

    void UTDimension2Di::allocation() {
        Dimension2Di dim2d1 ;
        check(dim2d1.getWidth() == 0) ;
        check(dim2d1.getHeight() == 0) ;

        Dimension2Di dim2d2(5, 3) ;
        check(dim2d2.getWidth() == 5) ;
        check(dim2d2.getHeight() == 3) ;

        Dimension2Di dim2d3(dim2d2) ;
        check(dim2d3.getWidth() == 5) ;
        check(dim2d3.getHeight() == 3) ;
    }

    void UTDimension2Di::scalarOperations() {
        const int Width = 6 ;
        const int Height = 9 ;
        const int Divisor = 3 ;
        const int Factor = 5 ;
        Dimension2Di dim2d1(Width, Height) ;

        /* Divisions */
        Dimension2Di dim2d2 = dim2d1 / Divisor ;
        check(dim2d2.getWidth() == Width / Divisor) ;
        check(dim2d2.getHeight() == Height / Divisor) ;

        dim2d2 /= Divisor ;
        check(dim2d2.getWidth() == Width / Divisor / Divisor) ;
        check(dim2d2.getHeight() == Height / Divisor / Divisor) ;

        /* Products */
        Dimension2Di dim2d3 = dim2d1 * Factor ;
        check(dim2d3.getWidth() == Width * Factor) ;
        check(dim2d3.getHeight() == Height * Factor) ;

        dim2d3 *= Factor ;
        check(dim2d3.getWidth() == Width * Factor * Factor) ;
        check(dim2d3.getHeight() == Height * Factor * Factor) ;
    }

    void UTDimension2Di::dimensionsOperations() {
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
        check(dim2d1PLUSd2.getWidth() == Width1 + Width2) ;
        check(dim2d1PLUSd2.getHeight() == Height1 + Height2) ;

        Dimension2Di dim2d1PLUSd3 = dim2d1 + dim2d3 ;
        check(dim2d1PLUSd3.getWidth() == Width1 + Width3) ;
        check(dim2d1PLUSd3.getHeight() == Height1 + Height3) ;

        Dimension2Di dim2d2PLUSd3 = dim2d2 + dim2d3 ;
        check(dim2d2PLUSd3.getWidth() == Width2 + Width3) ;
        check(dim2d2PLUSd3.getHeight() == Height2 + Height3) ;

        dim2d2PLUSd3 += dim2d1 ;
        check(dim2d2PLUSd3.getWidth() == Width2 + Width3 + Width1) ;
        check(dim2d2PLUSd3.getHeight() == Height2 + Height3 + Height1) ;


        /* Difference */
        Dimension2Di dim2d1MINUSd2 = dim2d1 - dim2d2 ;
        check(dim2d1MINUSd2.getWidth() == Width1 - Width2) ;
        check(dim2d1MINUSd2.getHeight() == Height1 - Height2) ;

        Dimension2Di dim2d1MINUSd3 = dim2d1 - dim2d3 ;
        check(dim2d1MINUSd3.getWidth() == Width1 - Width3) ;
        check(dim2d1MINUSd3.getHeight() == Height1 - Height3) ;

        Dimension2Di dim2d2MINUSd3 = dim2d2 - dim2d3 ;
        check(dim2d2MINUSd3.getWidth() == Width2 - Width3) ;
        check(dim2d2MINUSd3.getHeight() == Height2 - Height3) ;

        dim2d2MINUSd3 -= dim2d1 ;
        check(dim2d2MINUSd3.getWidth() == Width2 - Width3 - Width1) ;
        check(dim2d2MINUSd3.getHeight() == Height2 - Height3 - Height1) ;
    }

    void UTDimension2Di::equality() {
        const int Width1 = 45755 ;
        const int Height1 = 751445 ;
        Dimension2Di dim2d1 = Dimension2Di(Width1, Height1) ;
        Dimension2Di dim2d2 = Dimension2Di(Width1, Height1) ;
        Dimension2Di dim2d3 = Dimension2Di(dim2d1) ;
        Dimension2Di dim2d4 = Dimension2Di(dim2d2) ;

        check(dim2d1 == dim2d1) ;
        check(dim2d1 == dim2d2) ;
        check(dim2d2 == dim2d1) ;
        check(dim2d1 == dim2d3) ;
        check(dim2d3 == dim2d1) ;
        check(dim2d1 == dim2d4) ;
        check(dim2d4 == dim2d1) ;

        check(dim2d2 == dim2d2) ;
        check(dim2d2 == dim2d3) ;
        check(dim2d3 == dim2d2) ;
        check(dim2d2 == dim2d4) ;
        check(dim2d4 == dim2d2) ;

        check(dim2d3 == dim2d3) ;
        check(dim2d3 == dim2d4) ;
        check(dim2d4 == dim2d3) ;
    }

    void UTDimension2Di::inequality() {
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

        check(dim2d1 != dim2d2) ;
        check(dim2d2 != dim2d1) ;
        check(dim2d1 != dim2d3) ;
        check(dim2d3 != dim2d1) ;
        check(dim2d1 != dim2d4) ;
        check(dim2d4 != dim2d1) ;

        check(dim2d2 != dim2d3) ;
        check(dim2d3 != dim2d2) ;
        check(dim2d2 != dim2d4) ;
        check(dim2d4 != dim2d2) ;

        check(dim2d3 != dim2d4) ;
        check(dim2d4 != dim2d3) ;
    }

    void UTDimension2Di::setter() {
        Dimension2Di dim2d ;

        int width = 7 ;
        int height = 14 ;
        dim2d.set(width, height) ;
        check(dim2d.getWidth() == width) ;
        check(dim2d.getHeight() == height) ;

        width = 9 ;
        dim2d.setWidth(width) ;
        check(dim2d.getWidth() == width) ;
        check(dim2d.getHeight() == height) ;

        height = 87 ;
        dim2d.setHeight(height) ;
        check(dim2d.getWidth() == width) ;
        check(dim2d.getHeight() == height) ;
    }

    void UTDimension2Di::cast() {
        // To Dimension3Di.
        {
            const int Width = 897 ;
            const int Height = 5452 ;
            Dimension2Di dim2d(Width, Height) ;
            Dimension3Di dim3d = (Dimension3Di) dim2d ;
            check(dim3d.getWidth() == dim2d.getWidth()) ;
            check(dim3d.getHeight() == dim2d.getHeight()) ;
            check(dim3d.getDepth() == 0) ;
        }
        // To Point2Di.
        {
            const int Width = 7 ;
            const int Height = 469 ;
            Dimension2Di dim2d(Width, Height) ;
            Point2Di p2d = (Point2Di) dim2d ;
            check(p2d.getX() == dim2d.getWidth()) ;
            check(p2d.getY() == dim2d.getHeight()) ;
        }
    }
}
