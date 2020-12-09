#include "ThreadPoolTester.hpp"
#include <chrono>
#include <thread>

std::string func1_non_member()
{
    return "Test string";
}

int func2_non_member()
{
    return 24;
}

int func_sum(int a, int b)
{
    return a + b;
}

std::string func_concat(const std::string &a, const std::string &b)
{
    return a + b;
}

void ThreadPoolTester::test()
{
    std::cout << std::endl;
    this->testConstructor();
    std::cout << std::endl;
    this->testExec();
    std::cout << std::endl;
}

void ThreadPoolTester::testConstructor()
{
    std::cout << "Testing ThreadPool constructors" << std::endl;
    size_t poolSize_zero = 0;
    size_t poolSize_normal = 1;
    size_t poolSize_too_large = tpns::MAX_THREADS + 1;

    bool caughtInvArgEx = false;

    try
    {
        tpns::ThreadPool pool1(poolSize_zero);
    }
    catch (const std::invalid_argument &e)
    {
        caughtInvArgEx = true;
    }

    assert(caughtInvArgEx == true);
    caughtInvArgEx = false;

    try
    {
        tpns::ThreadPool pool2(poolSize_normal);
    }
    catch (const std::invalid_argument &e)
    {
        caughtInvArgEx = true;
    }

    assert(caughtInvArgEx == false);
    caughtInvArgEx = false;

    try
    {
        tpns::ThreadPool pool3(poolSize_too_large);
    }
    catch (const std::invalid_argument &e)
    {
        caughtInvArgEx = true;
    }

    assert(caughtInvArgEx == true);
    caughtInvArgEx = false;

    std::cout << "Successfully tested ThreadPool constructors" << std::endl;
}

void ThreadPoolTester::testExec()
{
    this->testExecNoArgs();
    std::cout << std::endl;
    this->testExecWithArgs();
    std::cout << std::endl;
    this->testExecMemberFunc();
}

void ThreadPoolTester::testExecNoArgs()
{
    std::cout << "Testing ThreadPool::exec with function with no arguments" << std::endl;

    size_t poolSize = 1;
    tpns::ThreadPool pool(poolSize);
    std::string res1 = "";
    int res2 = 0;

    auto task1 = pool.exec(func1_non_member);
    res1 = task1.get();

    assert(res1 == "Test string");

    auto task2 = pool.exec(func2_non_member);
    res2 = task2.get();

    assert(res2 == 24);

    std::cout << "Successfully tested ThreadPool::exec with function with no arguments" << std::endl;
}

void ThreadPoolTester::testExecWithArgs()
{
    std::cout << "Testing ThreadPool::exec with function with arguments" << std::endl;

    size_t poolSize = 1;
    tpns::ThreadPool pool(poolSize);

    std::string str1, str2;
    int int1, int2;
    str1 = "Hello ";
    str2 = "World!";
    int1 = 10;
    int2 = 40;

    auto func_lambda = [](int a, int b) { return a * b; };

    auto task1 = pool.exec(func_sum, int1, int2);
    auto task2 = pool.exec(func_concat, str1, str2);
    auto task3 = pool.exec(func_lambda, int1, int2);

    assert(task1.get() == int1 + int2);
    assert(task2.get() == str1 + str2);
    assert(task3.get() == int1 * int2);

    std::cout << "Successfully tested ThreadPool::exec with function with arguments" << std::endl;
}

void ThreadPoolTester::testExecMemberFunc()
{
    std::cout << "Testing ThreadPool::exec with class member function" << std::endl
              << "-----using lambda function and std::bind (with placeholders)" << std::endl
              << std::endl;

    size_t poolSize = 1;
    tpns::ThreadPool pool(poolSize);
    int res = 0;
    int a = 1;
    std::string str1 = "Hello";

    Helper help;

    auto func_lambda = [&help](int a, std::string b) { return help.func_inner(a, b); };
    auto func_bind = std::bind(&ThreadPoolTester::Helper::func_inner, help, std::placeholders::_1, std::placeholders::_2);

    auto task = pool.exec(func_lambda, a, str1);
    res = task.get();
    assert(res == static_cast<int>(a + str1.length()));

    task = pool.exec(func_bind, a, str1);
    res = task.get();
    assert(res == static_cast<int>(a + str1.length()));

    std::cout << "Successfully tested ThreadPool::exec with class member function" << std::endl
              << "-----using lambda function and std::bind (with placeholders)" << std::endl;
}

int ThreadPoolTester::Helper::func_inner(int a, std::string b)
{
    return a + b.length();
}
