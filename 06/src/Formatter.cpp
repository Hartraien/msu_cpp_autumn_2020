#include "Formatter.hpp"

Formatter::Formatter(const std::string &str, size_t n_args) : str_(str), n_args_(n_args), str_base_(str)
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
    size_t counter = 1;
    while ((pos_left = str.find_first_of(this->search_symbols_, pos_left)) != std::string::npos)
    {
        if (str[pos_left] == this->end_symbol_[0])
        {
            throw RightBeforeLeftException(this->start_symbol_, this->end_symbol_, this->str_base_pos(this->end_symbol_, counter));
        }
        pos_right = str.find(this->end_symbol_, pos_left);
        if (pos_right == std::string::npos)
        {
            throw NoMatchingRightException(this->start_symbol_, this->end_symbol_, this->str_base_pos(this->start_symbol_, counter));
        }
        std::string substr = str.substr(pos_left + 1, pos_right - pos_left - 1);
        bool sign = true;
        size_t pos_shift = 0;
        if (substr[0] == '-')
        {
            sign = false;
            pos_shift = 1;
        }
        if (substr.substr(pos_shift).find_first_not_of("0123456789") != std::string::npos)
        {
            throw NotaNumberException(substr, this->str_base_pos("{" + substr + "}", 1) + 1);
        }
        size_t val = this->strToSizeT(substr.substr(pos_shift), this->str_base_pos("{" + substr + "}", 1) + 1);
        if (val >= this->n_args_)
        {
            throw TooLargeArgumentException(pos_left + 1, val, this->n_args_);
        }
        if (!sign)
        {
            val = this->n_args_ - val;
        }

        str.erase(pos_left, pos_right - pos_left + 1);
        str.insert(pos_left, insert_values[val]);
        pos_left = pos_left + insert_values[val].length();
        counter += 1;
    }
}

inline size_t Formatter::strToSizeT(const std::string &str, size_t pos)
{
    size_t res = 0;
    int error = sscanf(str.c_str(), "%zu", &res);
    if (error != 1)
    {
        throw NotaNumberException(str, pos);
    }
    return res;
}

size_t Formatter::str_base_pos(const std::string &substr, size_t n)
{
    size_t pos = 0;
    for (size_t i = 0; i < n; i++)
    {
        pos = this->str_base_.find(substr, pos) + substr.length();
    }
    return pos - substr.length();
}
