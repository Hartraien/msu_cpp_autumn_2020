#ifndef __THREADPOOLTESTER_H__
#define __THREADPOOLTESTER_H__
#include <iostream>
#include <cassert>
#include <string>
#include "../src/ThreadPool.hpp"

class ThreadPoolTester
{

public:
    void test();
    void testConstructor();
    void testExec();

    void testExecNoArgs();
    void testExecWithArgs();
    void testExecMemberFunc();

    class Helper
    {
    public:
        int func_inner(int a, std::string b);
    };
};

#endif // __THREADPOOLTESTER_H__