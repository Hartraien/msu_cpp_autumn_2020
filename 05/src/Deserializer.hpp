#ifndef __DESERIALIZER_HPP__
#define __DESERIALIZER_HPP__
#include "SerializerDeserializerCommonIncludes.hpp"

class Deserializer
{

public:
    explicit Deserializer(std::istream &in);
    template <class T>
    Error load(T &object);
    template <class... ArgsT>
    Error operator()(ArgsT &... args);

private:
    Error process();
    template <class T, class... ArgsT>
    Error process(T &arg1, ArgsT &... args);

private:
    std::istream &in_;
};

template <class T>
Error Deserializer::load(T &object)
{
    return object.deserialize(*this);
}

template <class... ArgsT>
Error Deserializer::operator()(ArgsT &... args)
{
    return this->process(args...);
}

template <class T, class... ArgsT>
Error Deserializer::process(T &arg1, ArgsT &... args)
{
    static_assert((std::is_same<T, bool>::value || std::is_same<T, uint64_t>::value), "Wrong type of argument: T is neither bool nor uint64_t");
    std::string res;
    if (!(this->in_ >> res))
    {
        this->in_.clear();
        return Error::CorruptedArchive;
    }
    if (typeid(arg1) == typeid(bool))
    {
        if (res == "true")
        {
            arg1 = true;
        }
        else if (res == "false")
        {
            arg1 = false;
        }
        else
        {
            return Error::CorruptedArchive;
        }
    }
    else if (typeid(arg1) == typeid(uint64_t))
    {
        if (res.find_first_not_of("0123456789") == std::string::npos)
        {
            std::istringstream iss(res);
            iss >> arg1;
        }
        else
        {
            return Error::CorruptedArchive;
        }
    }
    return this->process(args...);
}

#endif // __DESERIALIZER_HPP__