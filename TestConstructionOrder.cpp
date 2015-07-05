#include <iostream>

using namespace std;

class OBJ1
{
    public:
        OBJ1()
        {
            cout << "OBJ1\n";
        }
};

class OBJ2
{
    public:
        OBJ2()
        {
            cout << "OBJ2\n";
        }
};

class Base1
{
    public:
        Base1()
        {
            cout << "Base1\n";
        }
};

class Base2
{
    public:
        Base2()
        {
            cout << "Base2\n";
        }
};

class Base3
{
    public:
        Base3()
        {
            cout << "Base3\n";
        }
};

class Base4
{
    public:
        Base4()
        {
            cout << "Base4\n";
        }
};

class Derived :
    public Base1,
    virtual public Base2,
    public Base3,
    virtual public Base4
{
    public:
        Derived() : Base4(), Base3(), Base2(),
            Base1(), obj2(), obj1()
        {
            cout << "Derived ok.\n";
        }
    protected:
        OBJ1 obj1;
        OBJ2 obj2;
};

int test_cpp_construction_order()
{
    Derived aa;
    cout << "All is ok.\n";
    return 0;
}