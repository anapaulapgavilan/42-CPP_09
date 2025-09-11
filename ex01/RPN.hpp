/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:05:15 by ana-pper          #+#    #+#             */
/*   Updated: 2025/09/11 16:09:29 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <exception>
#include <sstream>
#include <stack>
#include <cctype>
#include <cstdlib>
#include <iostream>

class RPN {
    public:
        static bool      valid_expression(const std::string& str);
        static long long calculate(const std::string& str);

        struct NoResultException : public std::exception {
            NoResultException() {}
            virtual const char* what() const throw() { return "Error"; }
        };

        struct DivisionByZeroException : public std::exception {
            DivisionByZeroException() {}
            virtual const char* what() const throw() { return "Error"; }
        };

    private:
        RPN();
        RPN(const RPN&);
        RPN& operator=(const RPN&);
        ~RPN();
};

#endif