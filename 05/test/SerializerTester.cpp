#include <sstream>
#include <cassert>
#include "SerializerTester.hpp"

std::string SerializerTester::Test_class_small::to_string()
{
    std::string res = "";
    res += std::to_string(a) + " ";
    if (b)
    {
        res += "true ";
    }
    else
    {
        res += "false ";
    }
    res += std::to_string(c) + " ";
    return res;
}

bool SerializerTester::Test_class_small::operator==(Test_class_small &other) const
{
    return (this->a == other.a) && (this->b == other.b) && (this->c == other.c);
}

SerializerTester::Test_class_large::Test_class_large(uint64_t a, bool b, uint64_t c, bool d, bool e, uint64_t f)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    this->e = e;
    this->f = f;
}

std::string SerializerTester::Test_class_large::to_string()
{
    std::string res = "";
    res += std::to_string(a) + " ";
    if (b)
    {
        res += "true ";
    }
    else
    {
        res += "false ";
    }
    res += std::to_string(c) + " ";
    if (d)
    {
        res += "true ";
    }
    else
    {
        res += "false ";
    }
    if (e)
    {
        res += "true ";
    }
    else
    {
        res += "false ";
    }
    res += std::to_string(f) + " ";
    return res;
}

bool SerializerTester::Test_class_large::operator==(Test_class_large &other) const
{
    return (this->a == other.a) && (this->b == other.b) && (this->c == other.c) && (this->d == other.d) && (this->d == other.d) && (this->d == other.d);
}

void SerializerTester::test_serializer()
{
    std::cout << "Testing serializer" << std::endl;
    std::stringstream stream;

    Test_class_small ex1(1, true, 4);
    std::string ex1_serial = "1 true 4 ";

    Serializer serializer(stream);
    serializer.save(ex1);
    assert(ex1_serial == stream.str());
    std::cout << "Successfully tested serializer" << std::endl
              << std::endl;
}

void SerializerTester::test_serializer_empty()
{
    std::cout << "Testing serializer for class without fields" << std::endl;
    std::stringstream stream;

    Test_class_empty ex_empt;
    std::string ex_empt_serial = "";

    Serializer serializer(stream);
    Error err = serializer.save(ex_empt);
    assert(err == Error::NoError);

    assert(ex_empt_serial == stream.str());
    std::cout << "Successfully tested serializer for class without fields" << std::endl
              << std::endl;
}

void SerializerTester::test_deserializer()
{
    std::cout << "Testing deserializer (correct arguments)" << std::endl;
    std::stringstream stream;

    Test_class_small ex1(0, false, 0);
    std::string ex1_deserial = "1 true 4 ";

    stream << ex1_deserial;

    Deserializer deserializer(stream);
    Error err = deserializer.load(ex1);

    assert(err == Error::NoError);
    assert(ex1_deserial == ex1.to_string());
    std::cout << "Successfully tested deserializer for case of correct arguments" << std::endl
              << std::endl;
}

void SerializerTester::test_deserializer_failure()
{
    std::cout << "Testing deserializer (incorrect arguments)" << std::endl;
    std::stringstream stream;

    Test_class_small ex1(0, false, 0);
    std::string ex1_deserial = "a true 4 ";
    std::string ex1_values = "0 false 0 ";

    stream << ex1_deserial;

    Deserializer deserializer(stream);
    Error err = deserializer.load(ex1);

    assert(err == Error::CorruptedArchive);
    assert(ex1_values == ex1.to_string());
    std::cout << "Successfully tested deserializer for case of incorrect arguments" << std::endl
              << std::endl;
}

void SerializerTester::test_serial_deserial()
{
    std::cout << "Testing serialization and subsequent deserialization" << std::endl;

    std::stringstream stream;

    Test_class_small ex1(1, true, 4);

    Serializer serializer(stream);
    serializer.save(ex1);

    Test_class_small ex2(0, false, 0);

    Deserializer deserializer(stream);
    Error err = deserializer.load(ex2);

    assert(err == Error::NoError);
    assert(ex1 == ex2);
    std::cout << "Successfully tested serialization and subsequent deserialization" << std::endl
              << std::endl;
}

void SerializerTester::test_serializer_several()
{
    std::cout << "Testing serialization and subsequent deserialization of two objects at once" << std::endl;
    std::cout << "Order of calls:" << std::endl;
    std::cout << "------"
              << "serialize(first)" << std::endl;
    std::cout << "------"
              << "serialize(second)" << std::endl;
    std::cout << "------"
              << "deserialize(first)" << std::endl;
    std::cout << "------"
              << "deserialize(second)" << std::endl;

    std::stringstream stream;

    Test_class_small ex1_in(1, true, 4);
    Test_class_small ex2_in(22, true, 4);

    Serializer serializer(stream);
    serializer.save(ex1_in);
    serializer.save(ex2_in);

    Test_class_small ex1_out(0, false, 0);
    Test_class_small ex2_out(0, false, 0);

    Deserializer deserializer(stream);

    Error err_1 = deserializer.load(ex1_out);

    Error err_2 = deserializer.load(ex2_out);

    assert(err_1 == Error::NoError);
    assert(ex1_in == ex1_out);
    assert(err_2 == Error::NoError);
    assert(ex2_in == ex2_out);
    std::cout << "Successfully tested serialization and subsequent deserialization of two objects at once" << std::endl
              << std::endl;
}

void SerializerTester::test_serializer_consecutive()
{
    std::cout << "Testing serialization and subsequent deserialization of two objects consequentially from same stream" << std::endl;
    std::cout << "Order of calls:" << std::endl;
    std::cout << "------"
              << "serialize(first)" << std::endl;
    std::cout << "------"
              << "deserialize(first)" << std::endl;
    std::cout << "------"
              << "serialize(second)" << std::endl;
    std::cout << "------"
              << "deserialize(second)" << std::endl;
    std::stringstream stream;

    Test_class_small ex1_in(1, true, 4);
    Test_class_large ex2_in(22, true, 4, false, true, 100);

    Test_class_small ex1_out(0, false, 0);
    Test_class_large ex2_out(0, false, 0, false, false, 0);

    Serializer serializer(stream);
    Deserializer deserializer(stream);
    serializer.save(ex1_in);

    Error err_1 = deserializer.load(ex1_out);

    serializer.save(ex2_in);

    Error err_2 = deserializer.load(ex2_out);

    assert(err_1 == Error::NoError);
    assert(ex1_in == ex1_out);
    assert(err_2 == Error::NoError);
    assert(ex2_in == ex2_out);
    std::cout << "Successfully tested serialization and subsequent deserialization of two objects consequentially from same stream" << std::endl
              << std::endl;
}

SerializerTester::Test_class_small::Test_class_small(uint64_t a, bool b, uint64_t c)
{
    this->a = a;
    this->b = b;
    this->c = c;
}

void SerializerTester::run_tests()
{
    this->test_serializer();
    this->test_serializer_empty();
    this->test_deserializer();
    this->test_deserializer_failure();
    this->test_serial_deserial();
    this->test_serializer_several();
    this->test_serializer_consecutive();

    std::cout << "Command to test that wrong types (not uint64_t and not bool) of serializer arguments lead to compile error" << std::endl;
    std::cout << "\"make test_compile_error\" (without quotes)" << std::endl;
}
