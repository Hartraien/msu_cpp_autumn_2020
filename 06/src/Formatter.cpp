#include "Formatter.hpp"

Formatter::Formatter(const std::string &str, size_t n_args) : str_(str), n_args_(n_args)
{
}

void Formatter::argsToVectorImpl(std::vector<std::string> &)
{
    return;
}

void Formatter::insert(const std::vector<std::string> &insert_values)
{
    std::string &str = this->str_;
    size_t pos_left = 0;
    size_t pos_right = 0;
    while ((pos_left = str.find_first_of(this->search_symbols_, pos_left)) != std::string::npos)
    {
        if (str[pos_left] == this->end_symbol_[0])
        {
            //TODO
            throw std::runtime_error(this->end_symbol_ + " appears before " + this->start_symbol_ + " at index " + std::to_string(pos_left));
        }
        pos_right = str.find(this->end_symbol_, pos_left);
        if (pos_right == std::string::npos)
        {
            //TODO
            throw std::runtime_error("No matching " + this->end_symbol_ + " for " + this->start_symbol_ + " at index " + std::to_string(pos_left));
        }
        std::cout << pos_left << " " << pos_right;
        std::string substr = str.substr(pos_left + 1, pos_right - pos_left - 1);
        std::cout << " " << substr;
        bool sign = true;
        size_t pos_shift = 0;
        if (substr[0] == '-')
        {
            sign = false;
            pos_shift = 1;
        }
        size_t val = this->strToSizeT(substr.substr(pos_shift));
        std::cout << " " << val << std::endl;
        if (val > this->n_args_)
        {
            //TODO custom exception
        }
        if (!sign)
        {
            val = this->n_args_ - val;
        }

        str.erase(pos_left, pos_right - pos_left + 1);
        str.insert(pos_left, insert_values[val]);
        pos_left = pos_left + insert_values[val].length();
    }
}

inline size_t Formatter::strToSizeT(const std::string &str)
{
    size_t res = 0;
    int error = sscanf(str.c_str(), "%zu", &res);
    if (error != 1)
    {
        //TODO custom exception
    }
    return res;
}
