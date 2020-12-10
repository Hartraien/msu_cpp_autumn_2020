#include "VectorTester.hpp"
void VectorTester::test()
{
    test_constructor();
    test_operatorEQ();
    test_resize_reserve();
    test_elem_operations();
    test_iterators();
}

void VectorTester::test_constructor()
{
    test_default_constructor();
    test_default_value_constructor();
    test_copy_constructor();
    test_move_constructor();
    test_init_list_constructor();
    test_iterator_constructor();
}

void VectorTester::test_operatorEQ()
{
    test_operatorEQ_copy();
    test_operatorEQ_move();
    test_operatorEQ_init_list();
}

void VectorTester::test_resize_reserve()
{
    test_resize();
    test_resize_with_value();
    test_reserve();
}

void VectorTester::test_elem_operations()
{
    test_getter();
    test_setter();
    test_push_back();
    test_pop_back();
    test_emplace_back();
}

void VectorTester::test_iterators()
{
    test_forward_iterator();
    test_reverse_iterator();
}

void VectorTester::test_default_constructor()
{
    std::cout << std::endl
              << "Testing default constructors" << std::endl;

    Vector<int> vec;
    assert(vec.size() == 0);
    assert(vec.capacity() == 6);

    size_t capacity = 60;
    Vector<int> vec2(capacity);
    assert(vec2.size() == 0);
    assert(vec2.capacity() == capacity);

    std::cout << "Successfully tested default constructors" << std::endl
              << std::endl;
}

void VectorTester::test_default_value_constructor()
{
    std::cout << std::endl
              << "Testing constructors with default value" << std::endl;

    size_t capacity = 55;
    int val = 6;
    Vector<int> vec(capacity, val);
    assert(vec.size() == capacity);
    assert(vec.capacity() == capacity);
    for (size_t i = 0; i < capacity; i++)
    {
        assert(vec[i] == val);
    }

    std::cout << "Successfully tested constructors with default value" << std::endl
              << std::endl;
}

void VectorTester::test_copy_constructor()
{
    std::cout << std::endl
              << "Testing copy constructors" << std::endl;

    size_t capacity = 55;
    int val = 6;
    Vector<int> vec1(capacity, val);
    Vector<int> vec2(vec1);
    assert(vec2.size() == vec1.size());
    assert(vec2.capacity() == vec1.capacity());
    for (size_t i = 0; i < capacity; i++)
    {
        assert(vec2[i] == val);
    }

    std::cout << "Successfully tested copy constructors" << std::endl
              << std::endl;
}

void VectorTester::test_move_constructor()
{
    std::cout << std::endl
              << "Testing move constructors" << std::endl;

    size_t capacity = 55;
    int val = 6;
    Vector<int> vec1(capacity, val);
    Vector<int> vec2(std::move(vec1));
    assert(vec2.size() == capacity);
    assert(vec2.capacity() == capacity);
    for (size_t i = 0; i < capacity; i++)
    {
        assert(vec2[i] == val);
    }

    int count = 0;
    assert(vec1.size() == 0);
    assert(vec1.capacity() == 0);
    for (size_t i = 0; i < vec1.size(); i++)
    {
        count++;
        assert(vec1[i] == val);
    }
    assert(count == 0);

    std::cout
        << "Successfully tested move constructors" << std::endl
        << std::endl;
}

void VectorTester::test_init_list_constructor()
{
    std::cout << "Testing init_list constructors" << std::endl
              << std::endl;

    int a[] = {20, 30, 40};
    Vector<int> vec({20, 30, 40});
    assert(vec.size() == 3);
    assert(vec.capacity() == 3);
    for (size_t i = 0; i < 3; i++)
    {
        assert(vec[i] == a[i]);
    }

    std::cout << "Successfully tested init_list constructors" << std::endl
              << std::endl;
}

void VectorTester::test_iterator_constructor()
{
    std::cout << "Testing iterator constructors" << std::endl
              << std::endl;

    std::vector<int> v({10, 20, 30});
    Vector<int> vec(v.begin(), v.end());
    assert(vec.size() == v.size());
    assert(vec.capacity() == v.size());
    for (size_t i = 0; i < v.size(); i++)
    {
        assert(vec[i] == v[i]);
    }

    std::cout << "Successfully tested iterator constructors" << std::endl
              << std::endl;
}

void VectorTester::test_operatorEQ_copy()
{
    std::cout << std::endl
              << "Testing copy operator=" << std::endl;

    size_t capacity = 55;
    int val = 6;
    Vector<int> vec1(capacity, val);
    Vector<int> vec2;
    vec2 = vec1;
    assert(vec2.size() == vec1.size());
    assert(vec2.capacity() == vec1.capacity());
    for (size_t i = 0; i < capacity; i++)
    {
        assert(vec2[i] == val);
    }

    std::cout << "Successfully tested copy operator=" << std::endl
              << std::endl;
}

void VectorTester::test_operatorEQ_move()
{
    std::cout << std::endl
              << "Testing move operator=" << std::endl;

    size_t capacity = 55;
    int val = 6;
    Vector<int> vec1(capacity, val);
    Vector<int> vec2;
    vec2 = std::move(vec1);
    assert(vec2.size() == capacity);
    assert(vec2.capacity() == capacity);
    for (size_t i = 0; i < capacity; i++)
    {
        assert(vec2[i] == val);
    }

    std::cout << "Successfully tested move operator=" << std::endl
              << std::endl;
}

void VectorTester::test_operatorEQ_init_list()
{
    std::cout << "Testing init_list operator=" << std::endl
              << std::endl;

    int a[] = {20, 30, 40};
    Vector<int> vec;
    vec = {20, 30, 40};
    assert(vec.size() == 3);
    assert(vec.capacity() == 3);
    for (size_t i = 0; i < 3; i++)
    {
        assert(vec[i] == a[i]);
    }

    std::cout << "Successfully tested init_list operator=" << std::endl
              << std::endl;
}

void VectorTester::test_resize()
{
    std::cout << "Testing resize" << std::endl
              << std::endl;

    size_t capacity = 10;
    int val = 10;
    Vector<int> vec_def(capacity, val);

    Vector<int> vec(capacity, val);
    Vector<int> vec2(capacity, val);

    vec.resize(capacity / 2);
    assert(vec.size() == capacity / 2);
    assert(vec.capacity() == capacity);
    for (size_t i = 0; i < vec.size(); i++)
    {
        assert(vec[i] == vec_def[i]);
    }

    vec2.resize(capacity * 2);
    assert(vec2.size() == capacity * 2);
    assert(vec2.capacity() == capacity * 2);
    for (size_t i = 0; i < vec_def.size(); i++)
    {
        assert(vec2[i] == vec_def[i]);
    }

    for (size_t i = vec_def.size(); i < vec2.size(); i++)
    {
        assert(vec2[i] == 0);
    }

    std::cout << "Successfully tested resize" << std::endl
              << std::endl;
}

void VectorTester::test_resize_with_value()
{
    std::cout << "Testing resize with value" << std::endl
              << std::endl;

    size_t capacity = 10;
    int val = 1;
    Vector<int> vec_def(capacity, val);

    Vector<int> vec(capacity, val);
    Vector<int> vec2(capacity, val);

    vec.resize(capacity / 2);
    assert(vec.size() == capacity / 2);
    assert(vec.capacity() == capacity);
    for (size_t i = 0; i < vec.size(); i++)
    {
        assert(vec[i] == vec_def[i]);
    }

    vec2.resize(capacity * 2, val);
    assert(vec2.size() == capacity * 2);
    assert(vec2.capacity() == capacity * 2);
    for (size_t i = 0; i < vec.size(); i++)
    {
        assert(vec2[i] == vec_def[i]);
    }
    for (size_t i = vec.size(); i < vec2.size(); i++)
    {
        assert(vec2[i] == val);
    }

    std::cout << "Successfully tested resize with value" << std::endl
              << std::endl;
}

void VectorTester::test_reserve()
{
    std::cout << "Testing reserve" << std::endl
              << std::endl;

    size_t capacity = 10;
    int val = 1;
    Vector<int> vec(capacity, val);
    vec.reserve(capacity - 1);
    assert(vec.size() == capacity);
    assert(vec.capacity() == capacity);

    vec.reserve(capacity * 2);
    assert(vec.size() == capacity);
    assert(vec.capacity() == capacity * 2);

    std::cout << "Successfully tested reserve" << std::endl
              << std::endl;
}

void VectorTester::test_getter()
{
    std::cout << "Testing getter" << std::endl
              << std::endl;

    size_t capacity = 10;
    int val = 1;
    Vector<int> vec(capacity, val);

    for (size_t i = 0; i < vec.size(); i++)
    {
        assert(vec[i] == val);
    }

    int c = 0;

    try
    {
        c = vec[vec.size()];
    }
    catch (const OOBException &e)
    {
        std::string mes = "Index " + std::to_string(vec.size()) + " is out of bounds for vector of size " + std::to_string(vec.size());
        assert(e.what() == mes);
    }

    assert(c == 0);

    std::cout << "Successfully tested getter" << std::endl
              << std::endl;
}

void VectorTester::test_setter()
{
    std::cout << "Testing setter" << std::endl
              << std::endl;

    size_t capacity = 10;
    int val = 1;
    Vector<int> vec(capacity, val);

    for (size_t i = 0; i < vec.size(); i++)
    {
        vec[i] = static_cast<int>(i) + 1;
    }

    for (size_t i = 0; i < vec.size(); i++)
    {
        assert(vec[i] == static_cast<int>(i) + 1);
    }

    try
    {
        vec[vec.size()] = 40;
    }
    catch (const OOBException &e)
    {
        std::string mes = "Index " + std::to_string(vec.size()) + " is out of bounds for vector of size " + std::to_string(vec.size());
        assert(e.what() == mes);
    }

    std::cout << "Successfully tested setter" << std::endl
              << std::endl;
}

void VectorTester::test_push_back()
{
    std::cout << "Testing push_back" << std::endl
              << std::endl;

    size_t capacity = 10;
    int val = 1;
    Vector<int> vec(capacity, val);

    for (size_t i = 0; i < vec.size(); i++)
    {
        vec[i] = i + 1;
    }

    for (size_t i = 0; i < vec.size(); i++)
    {
        assert(vec[i] == static_cast<int>(i) + 1);
    }

    std::cout << "Successfully tested push_back" << std::endl
              << std::endl;
}

void VectorTester::test_pop_back()
{
    std::cout << "Testing pop_back" << std::endl
              << std::endl;
    size_t capacity = 10;
    int val = 1;
    Vector<int> vec(capacity, val);
    Vector<int> vec2;

    for (size_t i = 0; i < vec.size(); i++)
    {
        vec[i] = i + 1;
    }

    for (size_t i = vec.size(); i > 0; i--)
    {
        assert(vec.pop_back() == static_cast<int>(i));
    }

    try
    {
        vec2.pop_back();
    }
    catch (const std::exception &e)
    {
        std::string mes = "Vector is empty, it's impossible to call method pop_back";
        assert(e.what() == mes);
    }

    std::cout << "Successfully tested pop_back" << std::endl
              << std::endl;
}

void VectorTester::test_emplace_back()
{
    std::cout << "Testing emplace_back" << std::endl
              << std::endl;
    size_t capacity = 10;
    Vector<testerclass> vec(capacity);

    int a = 1;
    int b = 2;
    std::string c = "test";

    vec.emplace_back(a, b, c);
    testerclass cl = vec.pop_back();
    assert(cl.a == a);
    assert(cl.b == b);
    assert(cl.c == c);

    std::cout << "Successfully tested emplace_back" << std::endl
              << std::endl;
}

void VectorTester::test_forward_iterator()
{
    std::cout << "Testing begin() and end()" << std::endl
              << std::endl;

    size_t capacity = 10;
    Vector<int> vec(capacity);
    for (size_t i = 0; i < capacity; i++)
    {
        vec.push_back(i + 1);
    }

    int index = 0;
    for (auto i = vec.begin(); i != vec.end(); i++)
    {
        assert(*i == index++ + 1);
    }

    std::cout << "Successfully tested begin() and end()" << std::endl
              << std::endl;
}

void VectorTester::test_reverse_iterator()
{
    std::cout << "Testing rbegin() and rend()" << std::endl
              << std::endl;

    size_t capacity = 10;
    Vector<int> vec(capacity);
    for (size_t i = 0; i < capacity; i++)
    {
        vec.push_back(i + 1);
    }

    int index = vec.size();
    for (auto i = vec.rbegin(); i != vec.rend(); i++)
    {
        assert(*i == index--);
    }

    std::cout << "Successfully tested rbegin() and rend()" << std::endl
              << std::endl;
}
