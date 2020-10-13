#include <iostream>
#include <memory>
#include "AllocatorTester.hpp"

int main(int argc, char **argv)
{
    std::unique_ptr<AllocatorTester> allocatorTester(new AllocatorTester);
    allocatorTester->test_makeAllocator();
    allocatorTester->test_alloc();
    allocatorTester->test_reset();
    std::cout << "Tested everything successfully" << std::endl;
}