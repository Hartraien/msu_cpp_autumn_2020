#ifndef __VECTORTESTER_H__
#define __VECTORTESTER_H__
#include <iostream>
#include <cassert>
#include <vector>
#include "../src/Vector.hpp"

class VectorTester
{
public:
    void test();

    void test_constructor();
    void test_operatorEQ();
    void test_resize_reserve();
    void test_elem_operations();
    void test_iterators();

    void test_default_constructor();
    void test_default_value_constructor();
    void test_copy_constructor();
    void test_move_constructor();
    void test_init_list_constructor();
    void test_iterator_constructor();

    void test_operatorEQ_copy();
    void test_operatorEQ_move();
    void test_operatorEQ_init_list();

    void test_resize();
    void test_resize_with_value();
    void test_reserve();

    void test_getter();
    void test_setter();
    void test_push_back();
    void test_pop_back();
    void test_emplace_back();

    void test_forward_iterator();
    void test_reverse_iterator();

    class testerclass
    {
    public:
        int a = 0;
        int b = 0;
        std::string c;
        testerclass()
        {
            a = 0;
            b = 0;
            c = "";
        };
        testerclass(int a, int b, std::string c)
        {
            this->a = a;
            this->b = b;
            this->c = c;
        }
    };
};
#endif // __VECTORTESTER_H__