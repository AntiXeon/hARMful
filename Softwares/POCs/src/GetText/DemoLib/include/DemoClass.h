#ifndef __DEMO_CLASS__
#define __DEMO_CLASS__


class DemoClass {

    private:
        int m_value ;


    public:
        DemoClass(const int& value) ;
        virtual ~DemoClass() ;

        bool isEqual(DemoClass* other) ;
        bool isDifferent(DemoClass* other) ;
        bool copy(DemoClass* to) ;

} ;


#endif
