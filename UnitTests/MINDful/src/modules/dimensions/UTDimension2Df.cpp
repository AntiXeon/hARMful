#include <modules/dimensions/UTDimension2Df.hpp>
#include <geometry/dimensions/Dimension2Df.hpp>
#include <geometry/dimensions/Dimension3Df.hpp>
#include <geometry/points/Point2Df.hpp>
#include <string>
#include <iostream>

using namespace Mind ;

namespace UTMind {
    UTDimension2Df::UTDimension2Df() {}

    UTDimension2Df::~UTDimension2Df() {}

    void UTDimension2Df::allocation() {
        Dimension2Df dim2d1 ;
        check(dim2d1.getWidth() == 0.f) ;
        check(dim2d1.getHeight() == 0.f) ;

        Dimension2Df dim2d2(5.2f, 3.9f) ;
        check(dim2d2.getWidth() == 5.2f) ;
        check(dim2d2.getHeight() == 3.9f) ;

        Dimension2Df dim2d3(dim2d2) ;
        check(dim2d3.getWidth() == 5.2f) ;
        check(dim2d3.getHeight() == 3.9f) ;
    }

    void UTDimension2Df::scalarOperations() {
        const float Width = 6.8975f ;
        const float Height = 2.47441f ;
        const float Divisor = 3.77487f ;
        const float Factor = 5.97f ;
        Dimension2Df dim2d1(Width, Height) ;

        /* Divisions */
        Dimension2Df dim2d2 = dim2d1 / Divisor ;
        check(compare(dim2d2.getWidth(), Width / Divisor)) ;
        check(compare(dim2d2.getHeight(), Height / Divisor)) ;

        dim2d2 /= Divisor ;
        check(compare(dim2d2.getWidth(), Width / Divisor / Divisor)) ;
        check(compare(dim2d2.getHeight(), Height / Divisor / Divisor)) ;

        /* Products */
        Dimension2Df dim2d3 = dim2d1 * Factor ;
        check(compare(dim2d3.getWidth(), Width * Factor)) ;
        check(compare(dim2d3.getHeight(), Height * Factor)) ;

        dim2d3 *= Factor ;
        check(compare(dim2d3.getWidth(), Width * Factor * Factor)) ;
        check(compare(dim2d3.getHeight(), Height * Factor * Factor)) ;
    }

    void UTDimension2Df::dimensionsOperations() {
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
        check(compare(dim2d1PLUSd2.getWidth(), Width1 + Width2)) ;
        check(compare(dim2d1PLUSd2.getHeight(), Height1 + Height2)) ;

        Dimension2Df dim2d1PLUSd3 = dim2d1 + dim2d3 ;
        check(compare(dim2d1PLUSd3.getWidth(), Width1 + Width3)) ;
        check(compare(dim2d1PLUSd3.getHeight(), Height1 + Height3)) ;

        Dimension2Df dim2d2PLUSd3 = dim2d2 + dim2d3 ;
        check(compare(dim2d2PLUSd3.getWidth(), Width2 + Width3)) ;
        check(compare(dim2d2PLUSd3.getHeight(), Height2 + Height3)) ;

        dim2d2PLUSd3 += dim2d1 ;
        check(compare(dim2d2PLUSd3.getWidth(), Width2 + Width3 + Width1)) ;
        check(compare(dim2d2PLUSd3.getHeight(), Height2 + Height3 + Height1)) ;

        /* Difference */
        Dimension2Df dim2d1MINUSd2 = dim2d1 - dim2d2 ;
        check(compare(dim2d1MINUSd2.getWidth(), Width1 - Width2)) ;
        check(compare(dim2d1MINUSd2.getHeight(), Height1 - Height2)) ;

        Dimension2Df dim2d1MINUSd3 = dim2d1 - dim2d3 ;
        check(compare(dim2d1MINUSd3.getWidth(), Width1 - Width3)) ;
        check(compare(dim2d1MINUSd3.getHeight(), Height1 - Height3)) ;

        Dimension2Df dim2d2MINUSd3 = dim2d2 - dim2d3 ;
        check(compare(dim2d2MINUSd3.getWidth(), Width2 - Width3)) ;
        check(compare(dim2d2MINUSd3.getHeight(), Height2 - Height3)) ;

        dim2d2MINUSd3 -= dim2d1 ;
        check(compare(dim2d2MINUSd3.getWidth(), Width2 - Width3 - Width1)) ;
        check(compare(dim2d2MINUSd3.getHeight(), Height2 - Height3 - Height1)) ;
    }

    void UTDimension2Df::equality() {
        const float Width1 = 4575.975f ;
        const float Height1 = 751.445f ;
        Dimension2Df dim2d1 = Dimension2Df(Width1, Height1) ;
        Dimension2Df dim2d2 = Dimension2Df(Width1, Height1) ;
        Dimension2Df dim2d3 = Dimension2Df(dim2d1) ;
        Dimension2Df dim2d4 = Dimension2Df(dim2d2) ;

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

    void UTDimension2Df::inequality() {
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

    void UTDimension2Df::setter() {
        Dimension2Df dim2d ;

        float width = 7.874f ;
        float height = 14.132f ;
        dim2d.set(width, height) ;
        check(dim2d.getWidth() == width) ;
        check(dim2d.getHeight() == height) ;

        width = 9.465f ;
        dim2d.setWidth(width) ;
        check(dim2d.getWidth() == width) ;
        check(dim2d.getHeight() == height) ;

        height = 87.517f ;
        dim2d.setHeight(height) ;
        check(dim2d.getWidth() == width) ;
        check(dim2d.getHeight() == height) ;
    }

    void UTDimension2Df::cast() {
        // To Dimension3Df.
        {
            const float Width = 897.45f ;
            const float Height = 5452.f ;
            Dimension2Df dim2d(Width, Height) ;
            Dimension3Df dim3d = (Dimension3Df) dim2d ;
            check(dim3d.getWidth() == dim2d.getWidth()) ;
            check(dim3d.getHeight() == dim2d.getHeight()) ;
            check(dim3d.getDepth() == 0.f) ;
        }
        // To Point2Df.
        {
            const float Width = 7.45f ;
            const float Height = 469.198f ;
            Dimension2Df dim2d(Width, Height) ;
            Point2Df p2d = (Point2Df) dim2d ;
            check(p2d.getX() == dim2d.getWidth()) ;
            check(p2d.getY() == dim2d.getHeight()) ;
        }
    }
}
