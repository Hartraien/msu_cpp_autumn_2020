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
    //Constructor that saves the copy of format string and number of variadic arguments
    Formatter(const std::string &, size_t);

    // converts all variadic arguments to their string representation
    // and inserts them into format string
    template <class... ArgsT>
    std::string process(const ArgsT &...);

private:
    //converts each argument in varidic arguments to string and stores the result in vector
    template <class T, class... ArgsT>
    void argsToVectorImpl(std::vector<std::string> &, const T &, const ArgsT &...);

    // End of recursive function
    void argsToVectorImpl(std::vector<std::string> &);

    // creates vector to store string representations of each variadic argument
    template <class... ArgsT>
    std::vector<std::string> argsToVector(const ArgsT &...);

    //inserts string representations of each variadic argument into their corresponding places
    void insert(const std::vector<std::string> &);

    // Converts string within braces into size_t number of argument
    inline size_t strToSizeT(const std::string &, size_t);

    // converts argument of template class T to string using stringsream
    template <class T>
    std::string to_string(const T &);

    // find position of substring in unedited format string
    // used in exceptions
    size_t str_base_pos(const std::string &, size_t);

private:
    const std::string start_symbol_ = "{";
    const std::string end_symbol_ = "}";
    const std::string search_symbols_ = this->start_symbol_ + this->end_symbol_;

    //string that is to be formated
    std::string str_;
    // number of variadic arguments
    size_t n_args_;
    // copy of format string, used for exceptions
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