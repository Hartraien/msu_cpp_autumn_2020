#include <iostream>
#include "testerclass.hpp"
#include "../src/cvector.hpp"

int main()
{
    CVector<testerclass> vec;
    testerclass t;
    t.a = 20;
    vec.push_back(t);
    testerclass b = vec[0];
    std::cout << t.a << " " << b.a << std::endl;
}