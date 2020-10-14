#include <cassert>
#include <exception>
#include <string>
#include <iostream>
#include <memory>

#include "../test/AllocatorTester.hpp"
#include "../src/Allocator.hpp"

void AllocatorTester::test_makeAllocator()
{
    std::cout << std::endl
              << std::endl
              << "Testing makeAllocator method" << std::endl
              << std::endl
              << std::endl;
    std::unique_ptr<Allocator> allocator1 = std::make_unique<Allocator>();

    std::string exceptionText;

    try
    {
        allocator1->makeAllocator(0);
    }
    catch (const std::exception &e)
    {
        exceptionText = e.what();
    }

    assert(exceptionText == "Received non-positive maxSize argument");
    std::cout << "Successfully tested for first time call of makeAllocator with maxSize == 0 argument" << std::endl;

    size_t size = 1000;
    allocator1->makeAllocator(size);
    assert(allocator1->getCapacity() == size);
    assert(allocator1->getRemainder() == size);

    std::cout << "Successfully tested for first time call of makeAllocator with maxSize == 1000 argument" << std::endl;

    size_t size2 = 500;
    allocator1->makeAllocator(size2);
    assert(allocator1->getCapacity() == size);
    assert(allocator1->getRemainder() == size);

    std::cout << "Successfully tested for second call of makeAllocator with maxSize == 500 argument" << std::endl;
}

void AllocatorTester::test_alloc()
{
    std::cout << std::endl
              << std::endl
              << "Testing alloc method" << std::endl
              << std::endl
              << std::endl;

    const std::string noException = "No exception";
    size_t size = 1000;
    std::unique_ptr<Allocator> allocator1 = std::make_unique<Allocator>();

    std::string exceptionTextAlloc;
    std::string expectedExceptionTextAlloc = "Allocator is not initiated, call makeAllocator before calling alloc";
    try
    {
        allocator1->alloc(1);
    }
    catch (const std::exception &e)
    {
        exceptionTextAlloc = e.what();
    }
    assert(exceptionTextAlloc == expectedExceptionTextAlloc);

    std::cout << "Successfully tested alloc() method for exception throwing when calling before makeAllocator" << std::endl;

    allocator1->makeAllocator(size);

    size_t nullSize = 0;

    expectedExceptionTextAlloc = "Received non-positive size argument";
    try
    {
        allocator1->alloc(nullSize);
    }
    catch (const std::exception &e)
    {
        exceptionTextAlloc = e.what();
    }
    assert(exceptionTextAlloc == expectedExceptionTextAlloc);
    std::cout << "Successfully tested alloc() method for size == 0" << std::endl;

    char *firstPointer = nullptr;
    size_t size1 = 100;
    firstPointer = allocator1->alloc(size1);
    assert(firstPointer != nullptr);
    std::cout << "Successfully tested memory allocation" << std::endl;

    std::string exceptionText = noException;
    char letter1 = 'a';
    try
    {
        firstPointer[0] = letter1;
    }
    catch (const std::exception &e)
    {
        exceptionText = e.what();
    }

    assert(exceptionText == noException);
    std::cout << "Successfully tested writing to allocated memory" << std::endl;

    exceptionText = noException;
    char result;
    try
    {
        result = firstPointer[0];
    }
    catch (const std::exception &e)
    {
        exceptionText = e.what();
    }
    assert(exceptionText == noException);
    assert(result == letter1);

    std::cout << "Successfully tested reading from allocated memory" << std::endl;
    char *secondPointer = nullptr;

    secondPointer = allocator1->alloc(size1);
    assert(secondPointer != nullptr);
    assert(secondPointer != firstPointer);

    std::cout << "Successfully tested second allocation within bounds" << std::endl;

    char *thirdpointer = allocator1->alloc(size);
    assert(thirdpointer == nullptr);
    std::cout << "Successfully tested allocation outside of bounds" << std::endl;
}

void AllocatorTester::test_reset()
{
    std::cout << std::endl
              << std::endl
              << "Testing reset method" << std::endl
              << std::endl
              << std::endl;

    size_t maxSize = 1000;
    size_t size1 = 100;
    size_t size2 = 200;
    std::unique_ptr<Allocator> allocator = std::make_unique<Allocator>();

    std::string exceptionTextReset;
    std::string expectedExceptionTextReset = "Allocator is not initiated, call makeAllocator before calling reset";
    try
    {
        allocator->reset();
    }
    catch (const std::exception &e)
    {
        exceptionTextReset = e.what();
    }
    assert(exceptionTextReset == expectedExceptionTextReset);

    std::cout << "Successfully tested reset() method for exception throwing when calling before makeAllocator" << std::endl;

    allocator->makeAllocator(maxSize);

    char *firstPointer = allocator->alloc(size1);
    allocator->reset();
    char *secondPointer = allocator->alloc(size2);
    assert(firstPointer == secondPointer);
    std::cout << "Successfully tested reset() method" << std::endl;
}
