#include <DemoClass.h>
#include <DemoStrings.h>
#include <DemoTranslate.h>
#include <iostream>

using namespace DemoTranslate ;

DemoClass::DemoClass(const int& value) {
    m_value = value ;
}

DemoClass::~DemoClass() {}


bool DemoClass::isEqual(DemoClass* other) {
    if (other == NULL) {
        std::cerr << Translate(DemoStrings::ArgumentIsNullInIsEqual) << std::endl ;
        return false ;
    }

    return ((other -> m_value) == m_value) ;
}

bool DemoClass::isDifferent(DemoClass* other) {
    if (other == NULL) {
        std::cerr << Translate(DemoStrings::ArgumentIsNullInIsDifferent) << std::endl ;
        return true ;
    }

    return ((other -> m_value) != m_value) ;
}

bool DemoClass::copy(DemoClass* to) {
    if (to == NULL) {
        std::cerr << Translate(DemoStrings::ArgumentIsNullInCopy) << std::endl ;
        return false ;
    }

    to -> m_value = m_value ;
    return true ;
}
