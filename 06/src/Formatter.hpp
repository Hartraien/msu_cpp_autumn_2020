#ifndef __FORMATTER_HPP__
#define __FORMATTER_HPP__
#include <string>
#include <sstream>
#include <vector>
#include "./exc/NotaNumber.hpp"
#include "./exc/WrongTemplateString.hpp"
#include "./exc/TooLargeArgument.hpp"

class Formatter
{
public:
    Formatter(const std::string &, size_t);
    template <class... ArgsT>
    std::string process(const ArgsT &...);

private:
    template <class T, class... ArgsT>
    void argsToVectorImpl(std::vector<std::string> &, const T &, const ArgsT &...);
    void argsToVectorImpl(std::vector<std::string> &);

    template <class... ArgsT>
    std::vector<std::string> argsToVector(const ArgsT &...);

    void insert(const std::vector<std::string> &);

    inline size_t strToSizeT(const std::string &, size_t);

    template <class T>
    std::string to_string(const T &);

    size_t str_base_pos(const std::string&, size_t);

private:
    const std::string start_symbol_ = "{";
    const std::string end_symbol_ = "}";
    const std::string search_symbols_ = this->start_symbol_ + this->end_symbol_;

    std::string str_;
    size_t n_args_;
    std::string str_base_;
};

template <class... ArgsT>
std::string Formatter::process(const ArgsT &... args)
{
    std::vector<std::string> insert_values = this->argsToVector(args...);
    this->insert(insert_values);
    return this->str_;
}

template <class T, class... ArgsT>
void Formatter::argsToVectorImpl(std::vector<std::string> &vect, const T &arg1, const ArgsT &... args)
{
    vect.push_back(this->to_string(arg1));
    this->argsToVectorImpl(vect, args...);
}

template <class... ArgsT>
std::vector<std::string> Formatter::argsToVector(const ArgsT &... args)
{
    std::vector<std::string> res;
    res.reserve(this->n_args_);
    this->argsToVectorImpl(res, args...);
    return res;
}

template <class T>
std::string Formatter::to_string(const T &arg)
{
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

template <class... ArgsT>
std::string format(const std::string &str, const ArgsT &... args)
{
    Formatter f(str, sizeof...(args));
    return f.process(args...);
}

#endif // __FORMATTER_HPP__