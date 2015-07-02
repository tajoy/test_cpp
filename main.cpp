#include <stdio.h>
#include <iostream>
//#include "Test.h"

void test ( void )
{

}



int main ( int argc, char** argv )
{
    // auto pTest = new Test();
    std::cout << std::is_same<void, void>().value << std::endl;
    std::cout << std::is_same<int, void>().value << std::endl;
    std::cout << std::is_same<int, int>().value << std::endl;
    //pTest->say ( "hello world!\n" );
    getchar();
    return 0;
}