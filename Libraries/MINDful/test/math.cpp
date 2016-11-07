#include <Math.h>
#include <iostream>

using namespace std ;
using namespace Mind ;


/**
 * @brief   Function used to test if a value is positive or null, used by
 *          Math::all_of() in this test. */
bool is_positive(const int& value) {
    return (value > -1) ;
}

/** @brief  Multiply a value by itself to perform a test of Math::foreach(). */
float square(const float& value) {
    return value * value ;
}


int main() {
    cout << "Pi = " << Math::PI << endl ;
    cout << "Pi / 2 = " << Math::PI_HALF << endl ;
    cout << "Pi / 4 = " << Math::PI_QUART << endl ;
    cout << "Pi * 2 = " << Math::PI_TWICE << endl ;
    cout << "Pi.Pi = " << Math::PI_SQUARED << endl ;

    cout << endl ;

    cout << "Perigon angle = " << Math::PERIGON_ANGLE_DEGREE << endl ;
    cout << "Straight angle = " << Math::STRAIGHT_ANGLE_DEGREE << endl ;
    cout << "Right angle = " << Math::RIGHT_ANGLE_DEGREE << endl ;

    cout << endl ;

    cout << "47° = " << Math::to_radian(47) << " radians" << endl ;
    cout << "90° = " << Math::to_radian(90) << " radians" << endl ;
    cout << "123° = " << Math::to_radian(123) << " radians" << endl ;

    cout << "2.146754979953 radians = " << Math::to_degree(2.146754979953) << " degrees" << endl ;
    cout << "0.78539816339745 radians = " << Math::to_degree(0.78539816339745) << " degrees" << endl ;

    cout << endl ;

    cout << "hypot(3, 5) = " << Math::hypot(3, 5) << " =? " << (3*3 + 5*5) << endl ;
    cout << "hypot(2.2, -8.) = " << Math::hypot(2.2, -8.) << " =? " << (2.2*2.2 + -8.*-8.) << endl ;
    cout << "hypot(-9.3, -4.2) = " << Math::hypot(-9.3, -4.2) << " =? " << (-9.3*-9.3 + -4.2*-4.2) << endl ;

    cout << endl ;

    cout << "abs(-15) = " << Math::abs(-15) << endl ;
    cout << "abs(-8.2) = " << Math::abs(-8.2) << endl ;
    cout << "abs(-Pi) = " << Math::abs(-Math::PI) << endl ;
    cout << "abs(-0) = " << Math::abs(-0) << endl ;
    cout << "abs(0) = " << Math::abs(0) << endl ;
    cout << "abs(3.5) = " << Math::abs(3.5) << endl ;
    cout << "abs(95) = " << Math::abs(95) << endl ;

    cout << endl ;

    cout << "max(1,2) = " << Math::max(1,2) << endl ;
    cout << "max(2,1) = " << Math::max(2,1) << endl ;
    cout << "max(2.,1.) = " << Math::max(2.,1.) << endl ;
    cout << "max(0.00001, 0.00001) = " << Math::max(0.00001, 0.00001) << endl ;
    cout << "max(0,-0) = " << Math::max(0,-0) << endl ;
    cout << "max(1,-1) = " << Math::max(1,-1) << endl ;
    cout << "max(-8,-1) = " << Math::max(-8,-1) << endl ;

    int setValues[] = {0,-98,12,95,-8,9} ;
    cout << "max(0,-98,12,95,-8,9) = " << Math::max(setValues, 6) << endl ;

    cout << endl ;

    cout << "min(1,2) = " << Math::min(1,2) << endl ;
    cout << "min(2,1) = " << Math::min(2,1) << endl ;
    cout << "min(2.,1.) = " << Math::min(2.,1.) << endl ;
    cout << "min(0.00001, 0.00001) = " << Math::min(0.00001, 0.00001) << endl ;
    cout << "min(0,-0) = " << Math::min(0,-0) << endl ;
    cout << "min(1,-1) = " << Math::min(1,-1) << endl ;
    cout << "min(-8,-1) = " << Math::min(-8,-1) << endl ;
    cout << "min(0,-98,12,95,-8,9) = " << Math::min(setValues, 6) << endl ;

    cout << endl ;

    vector<float> setValuesMinMax ;
    setValuesMinMax.push_back(-0.00001) ;
    setValuesMinMax.push_back(-3.1) ;
    setValuesMinMax.push_back(-3.01) ;
    setValuesMinMax.push_back(3.20001) ;
    setValuesMinMax.push_back(-0.000007) ;
    setValuesMinMax.push_back(3.2) ;
    pair<float, float> min_and_max = Math::minmax(setValuesMinMax) ;
    cout << "min = " << min_and_max.first << ", max = " << min_and_max.second << endl ;

    cout << endl ;
    cout << endl ;

    cout << "Only positive values..." << endl ;
    vector<int> testValues ;
    testValues.push_back(4) ;
    testValues.push_back(11) ;
    testValues.push_back(5) ;
    testValues.push_back(98) ;
    testValues.push_back(487487484) ;
    testValues.push_back(1) ;
    cout << "All positive ? " << Math::all_of(testValues, is_positive) << endl ;
    cout << "Some positive ? " << Math::any_of(testValues, is_positive) << endl ;
    cout << "None positive ? " << Math::none_of(testValues, is_positive) << endl ;

    cout << endl ;

    cout << "Add a negative value..." << endl ;
    testValues.push_back(-99) ;
    cout << "All positive ? " << Math::all_of(testValues, is_positive) << endl ;
    cout << "Some positive ? " << Math::any_of(testValues, is_positive) << endl ;
    cout << "None positive ? " << Math::none_of(testValues, is_positive) << endl ;

    cout << endl ;

    cout << "Only negative values..." << endl ;
    testValues.clear() ;
    testValues.push_back(-5477) ;
    testValues.push_back(-1) ;
    testValues.push_back(-4) ;
    testValues.push_back(-99) ;
    cout << "All positive ? " << Math::all_of(testValues, is_positive) << endl ;
    cout << "Some positive ? " << Math::any_of(testValues, is_positive) << endl ;
    cout << "None positive ? " << Math::none_of(testValues, is_positive) << endl ;

    cout << endl ;
    cout << endl ;

    vector<float> twiceValues ;
    twiceValues.push_back(2.) ;
    twiceValues.push_back(2.5) ;
    twiceValues.push_back(3.) ;
    twiceValues.push_back(4.) ;
    twiceValues.push_back(10.) ;
    twiceValues.push_back(200.) ;

    cout << "Before..." << endl ;
    for (size_t index = 0 ; index < twiceValues.size() ; index++)
        cout << twiceValues[index] << endl ;

    cout << endl ;
    cout << "Apply SQUARE() function..." << endl ;
    Math::foreach(twiceValues, square) ;

    cout << "After..." << endl ;
    for (size_t index = 0 ; index < twiceValues.size() ; index++)
        cout << twiceValues[index] << endl ;

    return 0 ;
}
