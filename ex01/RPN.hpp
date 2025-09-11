#pragma once

#include <string>
#include <exception>
#include <sstream>
#include <stack>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>

#define ERROR_MSG_PREFIX "RPN: error: "
#define ARGC_ERR         "invalid number of arguments"
#define INVALID_EXPR_ERR "invalid expression"

class RPN {
    public:

        static bool      valid_expression(const std::string& str);
        static long long calculate(const std::string& str);

        struct NoResultException : public std::exception {
            NoResultException();
            virtual const char* what() const throw();
        };

        struct DivisionByZeroException : public std::exception {
            DivisionByZeroException();
            virtual const char* what() const throw();
        };

    private:
        RPN();
        RPN(const RPN&);
        RPN& operator=(const RPN&);
        ~RPN();
};
