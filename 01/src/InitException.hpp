class InitException : public std::exception
{
public:
    InitException(const std::string &message);
    const char *what() const noexcept override;

private:
    std::string message_;
};
