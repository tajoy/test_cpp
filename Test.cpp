#include "Test.h"
#include <iostream>
#include <functional>

Test::Test ( void )
//: hit ( std::bind ( &Test::_hit, this ) )
//    : CM_BIND ( Test, hit )
//     , CM_BIND_N ( Test, say, 1 )
//     , CM_BIND_N ( Test, hit1, 1 )
//     , CM_BIND ( Test, hit2 )
//     , CM_BIND_N ( Test, hit3, 1 )
//     , CM_BIND_N ( Test, add, 2 );

{
}


Test::~Test ( void )
{
}


void Test::_hit()
{
    std::cout << "hit orig" << std::endl;
}

/*
int Test::_say ( std::string text )
{
    std::cout << text << std::endl;
    return 0;
}



void Test::_hit1 ( int n )
{
    std::cout << "hit(" << n << ") orig" << std::endl;
}


int Test::_hit2()
{
    std::cout << "hit orig" << std::endl;
    return 0;
}


int Test::_hit3 ( int n )
{
    std::cout << "hit(" << n << ") orig" << std::endl;
    return 0;
}

int Test::_add ( int n1, int n2 )
{
    std::cout << "add(" << n1 << "," << n2 << ") orig" << std::endl;
    return 0;
}
*/