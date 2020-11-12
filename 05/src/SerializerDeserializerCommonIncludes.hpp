#ifndef __SERIALIZERDESERIALIZERCOMMONINCLUDES_HPP__
#define __SERIALIZERDESERIALIZERCOMMONINCLUDES_HPP__

#include <iostream>
#include <cstdint>
#include <typeinfo>
#include <string>
#include <type_traits>

enum class Error
{
    NoError,
    CorruptedArchive
};
#endif // __SERIALIZERDESERIALIZERCOMMONINCLUDES_HPP__