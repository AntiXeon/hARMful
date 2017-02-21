#include <modules/UTDimension3Di.hpp>
#include <geometry/dimensions/Dimension3Di.hpp>
#include <geometry/dimensions/Dimension2Di.hpp>
#include <geometry/points/Point3Di.hpp>
#include <string>
#include <iostream>

using namespace Mind ;

namespace UTMind {
    UTDimension3Di::UTDimension3Di() {}

    UTDimension3Di::~UTDimension3Di() {}

    void UTDimension3Di::allocation() {
        Dimension3Di dim3d1 ;
        check(dim3d1.getWidth() == 0) ;
        check(dim3d1.getHeight() == 0) ;
        check(dim3d1.getDepth() == 0) ;

        Dimension3Di dim3d2(52, 39, 95) ;
        check(dim3d2.getWidth() == 52) ;
        check(dim3d2.getHeight() == 39) ;
        check(dim3d2.getDepth() == 95) ;

        Dimension3Di dim3d3(dim3d2) ;
        check(dim3d3.getWidth() == 52) ;
        check(dim3d3.getHeight() == 39) ;
        check(dim3d3.getDepth() == 95) ;
    }

    void UTDimension3Di::scalarOperations() {
        const int Width = 685 ;
        const int Height = 241 ;
        const int Depth = 4529 ;
        const int Divisor = 377899 ;
        const int Factor = 597 ;
        Dimension3Di dim3d1(Width, Height, Depth) ;

        /* Divisions */
        Dimension3Di dim3d2 = dim3d1 / Divisor ;
        check(dim3d2.getWidth() == Width / Divisor) ;
        check(dim3d2.getHeight() == Height / Divisor) ;
        check(dim3d2.getDepth() == Depth / Divisor) ;

        dim3d2 /= Divisor ;
        check(dim3d2.getWidth() == Width / Divisor / Divisor) ;
        check(dim3d2.getHeight() == Height / Divisor / Divisor) ;
        check(dim3d2.getDepth() == Depth / Divisor / Divisor) ;

        /* Products */
        Dimension3Di dim3d3 = dim3d1 * Factor ;
        check(dim3d3.getWidth() == Width * Factor) ;
        check(dim3d3.getHeight() == Height * Factor) ;
        check(dim3d3.getDepth() == Depth * Factor) ;

        dim3d3 *= Factor ;
        check(dim3d3.getWidth() == Width * Factor * Factor) ;
        check(dim3d3.getHeight() == Height * Factor * Factor) ;
        check(dim3d3.getDepth() == Depth * Factor * Factor) ;
    }

    void UTDimension3Di::dimensionsOperations() {
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
        check(dim3d1PLUSd2.getWidth() == Width1 + Width2) ;
        check(dim3d1PLUSd2.getHeight() == Height1 + Height2) ;
        check(dim3d1PLUSd2.getDepth() == Depth1 + Depth2) ;

        Dimension3Di dim3d1PLUSd3 = dim3d1 + dim3d3 ;
        check(dim3d1PLUSd3.getWidth() == Width1 + Width3) ;
        check(dim3d1PLUSd3.getHeight() == Height1 + Height3) ;
        check(dim3d1PLUSd3.getDepth() == Depth1 + Depth3) ;

        Dimension3Di dim3d2PLUSd3 = dim3d2 + dim3d3 ;
        check(dim3d2PLUSd3.getWidth() == Width2 + Width3) ;
        check(dim3d2PLUSd3.getHeight() == Height2 + Height3) ;
        check(dim3d2PLUSd3.getDepth() == Depth2 + Depth3) ;

        dim3d2PLUSd3 += dim3d1 ;
        check(dim3d2PLUSd3.getWidth() == Width2 + Width3 + Width1) ;
        check(dim3d2PLUSd3.getHeight() == Height2 + Height3 + Height1) ;
        check(dim3d2PLUSd3.getDepth() == Depth2 + Depth3 + Depth1) ;


        /* Difference */
        Dimension3Di dim3d1MINUSd2 = dim3d1 - dim3d2 ;
        check(dim3d1MINUSd2.getWidth() == Width1 - Width2) ;
        check(dim3d1MINUSd2.getHeight() == Height1 - Height2) ;
        check(dim3d1MINUSd2.getDepth() == Depth1 - Depth2) ;

        Dimension3Di dim3d1MINUSd3 = dim3d1 - dim3d3 ;
        check(dim3d1MINUSd3.getWidth() == Width1 - Width3) ;
        check(dim3d1MINUSd3.getHeight() == Height1 - Height3) ;
        check(dim3d1MINUSd3.getDepth() == Depth1 - Depth3) ;

        Dimension3Di dim3d2MINUSd3 = dim3d2 - dim3d3 ;
        check(dim3d2MINUSd3.getWidth() == Width2 - Width3) ;
        check(dim3d2MINUSd3.getHeight() == Height2 - Height3) ;
        check(dim3d2MINUSd3.getDepth() == Depth2 - Depth3) ;

        dim3d2MINUSd3 -= dim3d1 ;
        check(dim3d2MINUSd3.getWidth() == Width2 - Width3 - Width1) ;
        check(dim3d2MINUSd3.getHeight() == Height2 - Height3 - Height1) ;
        check(dim3d2MINUSd3.getDepth() == Depth2 - Depth3 - Depth1) ;
    }

    void UTDimension3Di::equality() {
        const int Width1 = 4575 ;
        const int Height1 = 751 ;
        const int Depth1 = 975 ;
        Dimension3Di dim3d1 = Dimension3Di(Width1, Height1, Depth1) ;
        Dimension3Di dim3d2 = Dimension3Di(Width1, Height1, Depth1) ;
        Dimension3Di dim3d3 = Dimension3Di(dim3d1) ;
        Dimension3Di dim3d4 = Dimension3Di(dim3d2) ;

        check(dim3d1 == dim3d1) ;
        check(dim3d1 == dim3d2) ;
        check(dim3d2 == dim3d1) ;
        check(dim3d1 == dim3d3) ;
        check(dim3d3 == dim3d1) ;
        check(dim3d1 == dim3d4) ;
        check(dim3d4 == dim3d1) ;

        check(dim3d2 == dim3d2) ;
        check(dim3d2 == dim3d3) ;
        check(dim3d3 == dim3d2) ;
        check(dim3d2 == dim3d4) ;
        check(dim3d4 == dim3d2) ;

        check(dim3d3 == dim3d3) ;
        check(dim3d3 == dim3d4) ;
        check(dim3d4 == dim3d3) ;
    }

    void UTDimension3Di::inequality() {
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

        check(dim3d1 != dim3d2) ;
        check(dim3d2 != dim3d1) ;
        check(dim3d1 != dim3d3) ;
        check(dim3d3 != dim3d1) ;
        check(dim3d1 != dim3d4) ;
        check(dim3d4 != dim3d1) ;
        check(dim3d1 != dim3d5) ;
        check(dim3d5 != dim3d1) ;

        check(dim3d2 != dim3d3) ;
        check(dim3d3 != dim3d2) ;
        check(dim3d2 != dim3d4) ;
        check(dim3d4 != dim3d2) ;
        check(dim3d5 != dim3d2) ;
        check(dim3d2 != dim3d5) ;

        check(dim3d3 != dim3d4) ;
        check(dim3d4 != dim3d3) ;
        check(dim3d5 != dim3d3) ;
        check(dim3d3 != dim3d5) ;

        check(dim3d4 != dim3d5) ;
        check(dim3d5 != dim3d4) ;
    }

    void UTDimension3Di::setter() {
        Dimension3Di dim3d ;

        int width = 7 ;
        int height = 14 ;
        int depth = 3 ;
        dim3d.set(width, height, depth) ;
        check(dim3d.getWidth() == width) ;
        check(dim3d.getHeight() == height) ;
        check(dim3d.getDepth() == depth) ;

        width = 9 ;
        dim3d.setWidth(width) ;
        check(dim3d.getWidth() == width) ;
        check(dim3d.getHeight() == height) ;
        check(dim3d.getDepth() == depth) ;

        height = 87 ;
        dim3d.setHeight(height) ;
        check(dim3d.getWidth() == width) ;
        check(dim3d.getHeight() == height) ;
        check(dim3d.getDepth() == depth) ;

        depth = 2 ;
        dim3d.setDepth(depth) ;
        check(dim3d.getWidth() == width) ;
        check(dim3d.getHeight() == height) ;
        check(dim3d.getDepth() == depth) ;
    }

    void UTDimension3Di::cast() {
        // To Dimension2Di.
        {
            const int Width = 897 ;
            const int Height = 5452 ;
            const int Depth = 487 ;
            Dimension3Di dim3d(Width, Height, Depth) ;
            Dimension2Di dim2d = (Dimension2Di) dim3d ;
            check(dim2d.getWidth() == dim3d.getWidth()) ;
            check(dim2d.getHeight() == dim3d.getHeight()) ;
        }
        // To Point3Di.
        {
            const int Width = 7 ;
            const int Height = 469 ;
            const int Depth = 7487 ;
            Dimension3Di dim3d(Width, Height, Depth) ;
            Point3Di p3d = (Point3Di) dim3d ;
            check(p3d.getX() == dim3d.getWidth()) ;
            check(p3d.getY() == dim3d.getHeight()) ;
            check(p3d.getZ() == dim3d.getDepth()) ;
        }
    }
}
