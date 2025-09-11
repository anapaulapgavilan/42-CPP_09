/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:05:02 by ana-pper          #+#    #+#             */
/*   Updated: 2025/09/11 16:10:38 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

static int print_error()
{
    std::cerr << "Error" << std::endl;
    return EXIT_FAILURE;
}

int main(int argc, char** argv)
{
    if (argc != 2)
        return print_error();

    std::string expr(argv[1]);
    if (!RPN::valid_expression(expr))
        return print_error();

    try 
    {
        long long result = RPN::calculate(expr);
        std::cout << result << std::endl;
    }
    catch (const std::exception&)
    {
        return print_error();
    }

    return EXIT_SUCCESS;
}