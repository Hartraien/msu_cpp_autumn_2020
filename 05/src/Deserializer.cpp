#include "Deserializer.hpp"

Deserializer::Deserializer(std::istream &in) : in_(in)
{
}

Error Deserializer::process()
{
    return Error::NoError;
}