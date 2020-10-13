#include <iostream>
#include <memory>
#include "../test/AllocatorTester.hpp"

int main(int argc, char **argv)
{
    std::unique_ptr<AllocatorTester> allocatorTester(new AllocatorTester);
    allocatorTester->test_makeAllocator();
    allocatorTester->test_alloc();
    allocatorTester->test_reset();
    std::cout <<std::endl << "All tests were passed successfully" << std::endl;
}