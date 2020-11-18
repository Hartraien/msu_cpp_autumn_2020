#include <iostream>
#include "../src/Formatter.hpp"

//does not implement operator<<
class TestClass
{
};

int main()
{
    TestClass t;
    auto text = format("{0}", t);
    std::cout << text << std::endl;
}
