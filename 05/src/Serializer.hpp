#ifndef __SERIALIZER_HPP__
#define __SERIALIZER_HPP__
#include "SerializerDeserializerCommonIncludes.hpp"

class Serializer
{
public:
    explicit Serializer(std::ostream &out);
    template <class T>
    Error save(T &object);
    template <class... ArgsT>
    Error operator()(ArgsT... args);

private:
    std::string process();
    template <class T, class... ArgsT>
    std::string process(T arg1, ArgsT... args);

private:
    std::ostream &out_;
    inline static const std::string error_string = "!";
    inline static const std::string Separator = " ";
};

template <class T>
Error Serializer::save(T &object)
{
    return object.serialize(*this);
}

template <class... ArgsT>
Error Serializer::operator()(ArgsT... args)
{
    std::string res = this->process(args...);
    if (res.find(this->error_string) == std::string::npos)
    {
        this->out_ << res;
        return Error::NoError;
    }
    else
    {
        return Error::CorruptedArchive;
    }
}

template <class T, class... ArgsT>
std::string Serializer::process(T arg1, ArgsT... args)
{
    static_assert((std::is_same<T, bool>::value || std::is_same<T, uint64_t>::value), "Wrong type of argument: T is neither bool nor uint64_t");
    std::string res = "";
    if (typeid(arg1) == typeid(bool))
    {
        if (arg1 == true)
        {
            res = "true" + this->Separator;
        }
        else
        {
            res = "false" + this->Separator;
        }
    }
    else if (typeid(arg1) == typeid(uint64_t))
    {
        res = std::to_string(arg1) + this->Separator;
    }
    return res + this->process(args...);
}

#endif // __SERIALIZER_HPP__