#ifndef __marco_h__
#define __marco_h__


#include <string>
#include <sstream>

int test_marco();



void test_log_marco (
    const std::string content,
    const std::string file,
    const int line,
    const std::string function );


template<typename ANY>
std::string AnyToStr ( ANY thing )
{
    std::ostringstream buf;
    buf << thing;
    return buf.str();
}
template<typename ANY, typename ...ANYS>
std::string AnyToStr ( ANY thing, ANYS ...things )
{
    std::ostringstream buf;
    buf << AnyToStr ( thing ) << endl << AnyToStr ( things... );
    return buf.str();
}


#define MYLOG(...) test_log_marco(AnyToStr(__VA_ARGS__), __FILE__, __LINE__, __FUNCTION__)

void test_log();



#endif //__marco_h__
