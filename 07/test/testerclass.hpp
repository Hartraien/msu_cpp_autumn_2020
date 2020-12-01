#ifndef __TESTERCLASS_H__
#define __TESTERCLASS_H__
#include <iostream>
class testerclass
{
public:
    int a = 0;
    testerclass(){};
    testerclass(const testerclass &other)
    {
        a = other.a;
        std::cout << "Copied tester class" << std::endl;
    }

    testerclass &operator=(const testerclass &other)
    {
        a = other.a;
        std::cout << "Operator='ed tester class" << std::endl;
        return *this;
    }
};
#endif // __TESTERCLASS_H__