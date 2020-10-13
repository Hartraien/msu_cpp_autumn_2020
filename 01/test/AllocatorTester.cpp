#include <cassert>
#include <exception>
#include <string>
#include <limits>
#include <iostream>
#include <memory>

#include "AllocatorTester.hpp"
#include "../src/Allocator.hpp"

void AllocatorTester::test_makeAllocator()
{
    std::unique_ptr<Allocator> allocator1(new Allocator());

    std::string exceptionText;

    try
    {
        allocator1->makeAllocator(0);
    }
    catch (const std::exception &e)
    {
        exceptionText = e.what();
    }

    assert(exceptionText == "received non-positive maxSize argument: 0");
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

    size_t maxSize = std::numeric_limits<std::size_t>::max();
    std::unique_ptr<Allocator> allocator2(new Allocator());
    allocator2->makeAllocator(maxSize);
    assert(allocator2->getCapacity() == maxSize);
    assert(allocator2->getRemainder() == maxSize);

    std::cout << "Successfully tested for first time call of makeAllocator with maxSize == std::numeric_limits<std::size_t>::max() argument" << std::endl;
}

void AllocatorTester::test_alloc()
{
    const std::string noException = "No exception";
    size_t size = 1000;
    std::unique_ptr<Allocator> allocator1(new Allocator(size));

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

    std::cout << "Successfully tested alloc() method for exception throwing" << std::endl;

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
    char letter2 = 'b';
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
    size_t maxSize = 1000;
    size_t size1 = 100;
    size_t size2 = 200;
    std::unique_ptr<Allocator> allocator(new Allocator());

    std::string exceptionTextReset;
    std::string expectedExceptionTextReset = "Allocator is not initiated, call makeAllocator before calling alloc";
    try
    {
        allocator->reset();
    }
    catch (const std::exception &e)
    {
        exceptionTextReset = e.what();
    }
    assert(exceptionTextReset == expectedExceptionTextReset);

    std::cout << "Successfully tested reset() method for exception throwing" << std::endl;

    allocator->makeAllocator(maxSize);

    char *firstPointer = allocator->alloc(size1);
    allocator->reset();
    char *secondPointer = allocator->alloc(size2);
    assert(firstPointer == secondPointer);
    std::cout << "Successfully tested reset() method" << std::endl;
}
