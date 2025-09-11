/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:05:09 by ana-pper          #+#    #+#             */
/*   Updated: 2025/09/11 16:10:19 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

static int ft_stoi(const std::string& str)
{
    int num = 0;
    std::stringstream ss(str);
    ss >> num;
    return num;
}

bool RPN::valid_expression(const std::string& str)
{
    if (str.empty()) return false;
    for (std::string::size_type i = 0; i < str.size(); ++i)
    {
        char c = str[i];
        if (!std::isdigit(static_cast<unsigned char>(c)) &&
            c!=' ' && c!='+' && c!='-' && c!='*' && c!='/')
            return false;
    }
    return true;
}

long long RPN::calculate(const std::string& str)
{
    std::stringstream postfix(str);
    std::stack<long long> st;
    std::string token;

    while (postfix >> token)
    {
        if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (st.size() < 2)
                throw NoResultException();

            long long right = st.top(); st.pop();
            long long left  = st.top(); st.pop();

            long long result = 0;
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
            st.push(result);
        }
        else
        {
            if (token.size() != 1 || !std::isdigit(static_cast<unsigned char>(token[0])))
                throw NoResultException();

            st.push(static_cast<long long>(ft_stoi(token)));
        }
    }

    if (st.size() != 1)
        throw NoResultException();

    return st.top();
}