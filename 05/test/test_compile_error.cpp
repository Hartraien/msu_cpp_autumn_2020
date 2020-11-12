#include "../src/Serializer.hpp"
#include "../src/Deserializer.hpp"
#include <sstream>

struct Data
{
    uint64_t a;
    bool b;
    int c;
    template <class Serializer>
    Error serialize(Serializer &serializer)
    {
        return serializer(a, b, c);
    }
};

int main()
{
    Data x{1, true, 2};

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);
}