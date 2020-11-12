#ifndef __SERIALIZERTESTER_HPP__
#define __SERIALIZERTESTER_HPP__

#include "../src/Serializer.hpp"
#include "../src/Deserializer.hpp"

class SerializerTester
{
public:
    void run_tests();

    void test_serializer();
    void test_serializer_empty();
    void test_deserializer();
    void test_deserializer_failure();
    void test_serial_deserial();
    void test_serializer_several();
    void test_serializer_consecutive();

private:
    class Test_class_empty
    {
    public:
        template <class Serializer>
        Error serialize(Serializer &serializer)
        {
            return serializer();
        }
    };

    class Test_class_small
    {
    public:
        Test_class_small(uint64_t, bool, uint64_t);

        template <class Serializer>
        Error serialize(Serializer &serializer)
        {
            return serializer(a, b, c);
        }

        template <class Deserializer>
        Error deserialize(Deserializer &deserializer)
        {
            return deserializer(a, b, c);
        }

        std::string to_string();

        bool operator==(Test_class_small &) const;

    private:
        uint64_t a;
        bool b;
        uint64_t c;
    };

    class Test_class_large
    {
    public:
        Test_class_large(uint64_t, bool, uint64_t, bool, bool, uint64_t);
        template <class Serializer>
        Error serialize(Serializer &serializer)
        {
            return serializer(a, b, c, d, e, f);
        }

        template <class Deserializer>
        Error deserialize(Deserializer &deserializer)
        {
            return deserializer(a, b, c, d, e, f);
        }

        std::string to_string();

        bool operator==(Test_class_large &) const;

    private:
        uint64_t a;
        bool b;
        uint64_t c;
        bool d;
        bool e;
        uint64_t f;
    };
};
#endif // __SERIALIZERTESTER_HPP__