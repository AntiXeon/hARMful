#include <simd/SIMDVector.h>
#include <iostream>

#ifdef USE_INTEL_SSE2

using namespace std ;
using namespace Mind ;


void Vector4i_Test() {
    cout << "=== Vector4i TESTS ===" << endl ;

    int32x4_t vecInt32 = SIMD::Vector4i::constant<87, -2, 96, -37>() ;
    float32x4_t vecfZeros = _mm_setzero_ps() ;

    SIMD::Vector4i v1 ;                  v1.print() ;
    SIMD::Vector4i v2(82, 5, -12, 5) ;   v2.print() ;
    SIMD::Vector4i v3(11) ;              v3.print() ;
    SIMD::Vector4i v4(vecInt32) ;        v4.print() ;
    SIMD::Vector4i v5(vecfZeros) ;       v5.print() ;

    cout << endl ;
    cout << "== Min ==" << endl ;
    SIMD::Vector4i vMin = SIMD::Vector4i::min(v2, v4) ;   vMin.print() ;
    vMin = SIMD::Vector4i::min(v2, v3) ;                 vMin.print() ;

    cout << endl ;
    cout << "== Max ==" << endl ;
    SIMD::Vector4i vMax = SIMD::Vector4i::max(v2, v4) ;   vMax.print() ;
    vMax = SIMD::Vector4i::max(v3, v4) ;                 vMax.print() ;

    cout << endl ;
    cout << "== Abs ==" << endl ;
    SIMD::Vector4i vAbs = SIMD::Vector4i::abs(v2) ;       vAbs.print() ;
    vAbs = SIMD::Vector4i::abs(v4) ;                     vAbs.print() ;

    cout << endl ;
    cout << "== Horizontal Add ==" << endl ;
    cout << "V2 : " ; v2.print() ;
    cout << "Sum v2 = " << v2.horizontalAdd() << endl ;
    cout << endl ;
    cout << "V3 : " ; v3.print() ;
    cout << "Sum v3 = " << v3.horizontalAdd() << endl ;

    vecInt32 = v2 ;
    v3 = vecInt32 ;
    cout << "V3 : " ; v3.print() ;

    cout << "Length = " << v3.length() << endl ;
}

void Vector4ui_Test() {
    cout << "=== Vector4ui TESTS ===" << endl ;

    uint32x4_t vecUInt32 = SIMD::Vector4ui::constant<87, 492, 96, 137>() ;
    float32x4_t vecfZeros = _mm_setzero_ps() ;

    SIMD::Vector4ui v1 ;                 v1.print() ;
    SIMD::Vector4ui v2(82, 5, 9812, 5) ; v2.print() ;
    SIMD::Vector4ui v3(11) ;             v3.print() ;
    SIMD::Vector4ui v4(vecUInt32) ;      v4.print() ;
    SIMD::Vector4ui v5(vecfZeros) ;      v5.print() ;

    cout << endl ;
    cout << "== Min ==" << endl ;
    SIMD::Vector4ui vMin = SIMD::Vector4ui::min(v2, v4) ; vMin.print() ;
    vMin = SIMD::Vector4ui::min(v2, v3) ;                vMin.print() ;

    cout << endl ;
    cout << "== Max ==" << endl ;
    SIMD::Vector4ui vMax = SIMD::Vector4ui::max(v2, v4) ; vMax.print() ;
    vMax = SIMD::Vector4ui::max(v3, v4) ;                vMax.print() ;

    cout << endl ;
    cout << "== Horizontal Add ==" << endl ;
    cout << "V2 : " ; v2.print() ;
    cout << "Sum v2 = " << v2.horizontalAdd() << endl ;
    cout << endl ;
    cout << "V3 : " ; v3.print() ;
    cout << "Sum v3 = " << v3.horizontalAdd() << endl ;

    vecUInt32 = v2 ;
    v3 = vecUInt32 ;
    cout << "V3 : " ; v3.print() ;

    cout << "Length = " << v3.length() << endl ;
}

void Vector4f_Test() {
    cout << "=== Vector4f TESTS ===" << endl ;

    float32x4_t vecfZeros = _mm_setzero_ps() ;

    SIMD::Vector4f v1 ;
    SIMD::Vector4f v2(-12.f, 96.54f, 474.23f, -95.3f) ;
    SIMD::Vector4f v3(33.33f) ;
    SIMD::Vector4f v4(vecfZeros) ;

    v4 = SIMD::Vector4f(0.f) ;

    v1.print() ;
    v2.print() ;
    v3.print() ;
    v4.print() ;

    cout << endl ;

    cout << "v2 sum of elements = " << v2.horizontalAdd() << endl ;
    cout << "v3 sum of elements = " << v3.horizontalAdd() << endl ;

    cout << endl ;

//    v2.abs() ; v2.print() ;
    v2.permute<3,2,1,0>() ; v2.print() ;
    v2.changeSign<true, true, false, false>() ; v2.print() ;

    SIMD::Vector4f::Mask maskFTTF(false, true, true, false) ;
    cout << "Add IF: " ; v2.addIf(maskFTTF, v3) ; v2.print() ; cout << endl ;
    cout << "Mul IF: " ; v2.mulIf(maskFTTF, v4) ; v2.print() ; cout << endl ;
    cout << "v2 . v3 = " << v2.dot(v3) << endl ;
    cout << "v2 norm = " << v2.norm() << endl ;

    cout << "Select [v2 v3 v3 v2] " ; SIMD::Vector4f::select(maskFTTF, v3, v2).print() ;
    cout << "Min V2 V3 " ; SIMD::Vector4f::min(v2, v3).print() ;
    cout << "Max V2 V3 " ; SIMD::Vector4f::max(v2, v3).print() ;
    cout << "Sqrt V2 " ; SIMD::Vector4f::sqrt(v2).print() ;
    cout << "Squared V2 " ; SIMD::Vector4f::square(v2).print() ;
    cout << "Fast reciprocal V2 " ; SIMD::Vector4f::fast_recriprocal(v2).print() ;
    cout << "Fast rsqrt V2 " ; SIMD::Vector4f::fast_rsqrt(v2).print() ;
    cout << "Fast sqrt V2 " ; SIMD::Vector4f::fast_sqrt(v2).print() ;
    cout << "V2 * V3 + V2 = " ; SIMD::Vector4f::mul_add(v2, v3, v2).print() ;
    cout << "V3 - V2 * V3 = " ; SIMD::Vector4f::mul_sub(v2, v3, v3).print() ;
    cout << "V3 - V2 * V3 = " ; SIMD::Vector4f::sub_mul(v3, v2, v3).print() ;

    cout << endl ;

    cout << "V2 = " ; v2.print() ; cout << endl ;
    cout << "V3 = " ; v3.print() ; cout << endl ;
    cout << "V4 = " ; v4.print() ; cout << endl ;
    cout << endl ;
    cout << "Is Negative V2 : " ; v2.isNegative().print() ;
    cout << "Is Infinite V3 / V2 : " ; (v3 / v2).isInfinite().print() ;
    cout << "Is NaN V2 / V4 : " ; (v2 / v4).isNaN().print() ;

    cout << endl ;

    AlignedArray4f arrayV1 ;
    Array4f arrayV4 ;
    {
        float tmpV1[] = { -870.45f, 5441.f, -546.454f, -779.f/45.f } ;
        float tmpV4[] = { 0.4f*42.4f, 1.f, 6.f, -9.f/55.f } ;
        arrayV1 = tmpV1 ;
        arrayV4 = tmpV4 ;
    }
    v1.set(arrayV1) ; v1.print() ;
    v4.set(arrayV4) ; v4.print() ;

    AlignedArray4f contentV2 ;
    v2.get(contentV2) ;
    cout << contentV2[0] << endl ;
    cout << contentV2[1] << endl ;
    cout << contentV2[2] << endl ;
    cout << contentV2[3] << endl ;
}

void benchmark() {
    SIMD::Vector4f v1 ;
    for (unsigned int loop = 0 ; loop < 1000000000 ; ++loop) {
        SIMD::Vector4f v2(-12.f, 96.54f, 474.23f, -95.3f) ;
        SIMD::Vector4f v3((float) loop + 3.f) ;

        SIMD::Vector4f v4 = v2 * v3 ;
        Scalar norm = v4.norm() ;
        Scalar dot = v2.dot(v4) ;
        SIMD::Vector4f v5(norm) ;
        SIMD::Vector4f v6 = v4 / norm ;

        v6 = v4 / v5 ;
        v6 = v6 + SIMD::Vector4f::mul_sub(v2, v3, v3) ;
        v6 = v6 - SIMD::Vector4f::mul_add(v4, v3, v2) ;
        v6 = SIMD::Vector4f::sqrt(v6) ;
        v5 = SIMD::Vector4f::square(v5) ;
	    v1 = (v4 * (v6 / v2)) + (v3 - v5) ;
    }

    v1.print() ;
}

void benchmark2() {
    SIMD::Vector4f v1(1.f, 2.f, 6.f, -9.f) ;
    for (int i = 0 ; i < 10000000 ; ++i) {
//        AlignedArray4f v1_values ;
//        v1.get(v1_values) ;
        float* v1_values = v1 ;
        v1_values[0] *= 1.001f ;
        v1_values[1] *= 1.0001f ;
//        v1.set(v1_values) ;
    }
    v1.print() ;
}

int main() {
//   Vector4i_Test() ;
//   cout << endl << endl ;
//   Vector4ui_Test() ;
//   cout << endl << endl ;
//    Vector4f_Test() ;

   // benchmark() ;
   benchmark2() ;

    return 0 ;
} ;

#else

int main() {
    std::cout << "This benchmark is not available on your computer" << std::endl ;
    return 0 ;
}

#endif
