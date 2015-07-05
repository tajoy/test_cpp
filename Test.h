#ifndef __Test_h__
#define __Test_h__


/*#include "CallableMod.h"*/
#include <string>

class Test
{
    public:
        Test ( void );
        virtual ~Test ( void );
//     public:
//         CallableMod<void> hit;
    protected:
        void _hit();



        //CM_DEF ( hit, void, );
//         CM_DEF ( hit1, void, int );
//         CM_DEF ( hit2, int, void );
//         CM_DEF ( hit3, int, int );
//         CM_DEF ( say, int, std::string );
//         CM_DEF ( add, int, int, int );

};



#endif // __Test_h__
