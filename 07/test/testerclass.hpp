#ifndef __TESTERCLASS_H__
#define __TESTERCLASS_H__
#include <iostream>
class testerclass
{
public:
    int a = 0;
    testerclass(){};
    testerclass(int a, int b, std::string c)
    {
        this->a = a;
        std::cout << "Got arguments: " << std::to_string(a) << " " << std::to_string(b) << " " << c << std::endl;
    }
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
    testerclass(testerclass &&other)
    {
        std::cout << "Moved tester class" << std::endl;
        a = other.a;
        other.a = 0;
    }

    testerclass &operator=(testerclass &&other)
    {
        a = other.a;
        other.a = 0;
        std::cout << "Operator= moved tester class" << std::endl;
        return *this;
    }
    ~testerclass()
    {
        std::cout << "Called destructor for tester class with elem = " << this->a << std::endl;
    }
};

#endif // __TESTERCLASS_H__