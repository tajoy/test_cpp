#ifndef __CallableMod_h__
#define __CallableMod_h__



#include <deque>
#include <functional>
#include <iostream>


template<typename TRET, typename ...TARGS>
class CallableMod
{
    public:
        CallableMod ( std::function<TRET ( TARGS... ) > func )
        {
            m_qcFunc.clear();
            m_qcFunc.push_back ( func );
        }

        virtual ~CallableMod ( void )
        {

        }

        TRET operator() ( TARGS... args )
        {
            m_qTRet.clear();
            for ( auto it : m_qcFunc ) {


                TRET ret = it ( args ... );


                m_qTRet.push_back ( ret );
            }

            if ( std::is_same<TRET, void>().value ) {
                m_qTRet.back()
            } else {
                return m_qTRet.back();
            }
        }

        void pushBefore ( std::function<TRET ( TARGS... ) > func )
        {
            m_qcFunc.push_back ( func );
        }

        void pushAfter ( std::function<TRET ( TARGS... ) > func )
        {
            m_qcFunc.push_front ( func );
        }

        int getCount()
        {
            return m_qcFunc.size();
        }

        TRET getRet ( int index )
        {

            if ( std::is_same<TRET, void>().value ) return;
            else {
                if ( m_qTRet.size() >= index || index < 0 ) {
                    TRET ret;
                    return ret;
                }
                return m_qTRet.at ( index );
            }
        }


    private:
        std::deque< std::function< TRET ( TARGS... ) > > m_qcFunc;
        std::deque< TRET > m_qTRet;
};

template<typename TRET>
class CallableMod : public CallableMod<TRET, void>
{
    public:
        CallableMod ( std::function<TRET ( void ) > func )
        {
            m_qcFunc.clear();
            m_qcFunc.push_back ( func );
        }
        TRET operator() ()
        {
            m_qTRet.clear();
            for ( auto it : m_qcFunc ) {
                TRET ret = it();
                m_qTRet.push_back ( ret );
            }
            return m_qTRet.back();
        }
};



#define CM_DEF(funname, rettype, ... ) \
    public: CallableMod<rettype, __VA_ARGS__> funname; \
    protected: rettype _##funname(__VA_ARGS__);

#define CM_BIND_N(classname, funname, countargs) \
    funname(std::bind(&classname::_##funname, this, std::placeholders::_##countargs))

#define CM_BIND(classname, funname) \
    funname(std::bind(&classname::_##funname, this))


void test_cm ( void )
{
    // auto pTest = new Test();
    std::cout << std::is_same<void, void>().value << std::endl;
    std::cout << std::is_same<int, void>().value << std::endl;
    std::cout << std::is_same<int, int>().value << std::endl;
    //pTest->say ( "hello world!\n" );
}

#endif // __CallableMod_h__
