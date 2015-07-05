
#include "marco.h"
#include <iostream>

using namespace std;

#define M_0 0
#define M_1 M_0+1
#define M_2 M_1+1

int test_marco()
{
    return M_2;
}

void test_log_marco (
    const std::string content,
    const std::string file,
    const int line,
    const std::string function )
{
    cout << function << " in " << file << ":" << line
         << endl
         << content
         << endl;
}




void test_log()
{
    MYLOG ( "test log" );
    MYLOG ( 123 );
    MYLOG ( -456 );
    MYLOG ( 0.0 );
    MYLOG ( -123.456f );
    MYLOG ( true );
    MYLOG ( false );
    MYLOG (
        "hello\n"
        "world!"
    );

    MYLOG ( 123,
            -456,
            0.0,
            -123.456f,
            true,
            false,
            "hello",
            "world!"
          );
}