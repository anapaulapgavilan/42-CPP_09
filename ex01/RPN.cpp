#include "RPN.hpp"

bool RPN::valid_expression(const std::string& str)
{
    if (str.empty()) return false;
    for (size_t i = 0; i < str.size(); ++i)
    {
        char c = str[i];
        if (!std::isdigit(c) && c!=' ' && c!='+' && c!='-' && c!='*' && c!='/')
            return false;
    }
    return true;
}

static int ft_stoi(const std::string& str)
{
    int num;
    std::stringstream ss(str);
    ss >> num;
    return num;
}

long long RPN::calculate(const std::string& str)
{
    std::stringstream postfix(str);
    std::stack<int>     temp;
    std::string         token;

    while (postfix >> token)
    {
        if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (temp.size() < 2)
                throw NoResultException();

            int right = temp.top(); temp.pop();
            int left  = temp.top(); temp.pop();

            int result = 0;
            switch (token[0])
            {
                case '+': result = left + right; break;
                case '-': result = left - right; break;
                case '*': result = left * right; break;
                case '/':
                    if (right == 0)
                        throw DivisionByZeroException();
                    result = left / right;
                    break;
            }
            temp.push(result);
        }
        else
        {
            temp.push(ft_stoi(token));
        }
    }

    if (temp.size() != 1)
        throw NoResultException();

    return temp.top();
}

RPN::NoResultException::NoResultException() {}

RPN::DivisionByZeroException::DivisionByZeroException() {}

const char* RPN::NoResultException::what() const throw()
{
    return "RPN exception: No result. Wrongly formatted expression";
}

const char* RPN::DivisionByZeroException::what() const throw()
{
    return "RPN exception: division by zero";
}
