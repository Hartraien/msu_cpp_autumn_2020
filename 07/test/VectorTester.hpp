#ifndef __VECTORTESTER_H__
#define __VECTORTESTER_H__
#include <iostream>
#include <cassert>
#include <vector>
#include <sstream>
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

    class testerclass_construct
    {
    public:
        testerclass_construct(){};
        testerclass_construct(const testerclass_construct &a)
        {
            std::cout << "copy constructor" << std::endl;
        }

        testerclass_construct &operator=(const testerclass_construct &a)
        {
            std::cout << "copy operator=" << std::endl;
            return *this;
        }

        testerclass_construct(testerclass_construct &&a)
        {
            std::cout << "move constructor" << std::endl;
        }

        testerclass_construct &operator=(testerclass_construct &&a)
        {
            std::cout << "move operator=" << std::endl;
            return *this;
        }
    };

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
        testerclass(const int &a, const int &b, const std::string &c, const testerclass_construct& tc)
        {
            this->a = a;
            this->b = b;
            this->c = c;
        }
    };
};
#endif // __VECTORTESTER_H__