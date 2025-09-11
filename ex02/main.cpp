/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:14:20 by ana-pper          #+#    #+#             */
/*   Updated: 2025/09/11 16:35:40 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

static int print_error() {
    std::cerr << "Error" << std::endl;
    return 1;
}

static bool is_all_digits(const std::string& s) {
    if (s.empty()) return false;
    for (std::string::size_type i = 0; i < s.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(s[i]);
        if (!std::isdigit(c)) return false;
    }
    return true;
}

int main(int argc, char** argv) {
    if (argc < 2) return print_error();

    std::deque<int> deq;
    std::list<int>  lst;

    // Parseo y validación: enteros positivos en rango int
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (!is_all_digits(arg)) return print_error();

        long v = std::strtol(arg.c_str(), NULL, 10);
        if (v <= 0 || v > INT_MAX) return print_error();

        deq.push_back(static_cast<int>(v));
        lst.push_back(static_cast<int>(v));
    }

    // Before
    std::cout << "Before: ";
    for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it) {
        std::cout << *it;
        if (it + 1 != deq.end()) std::cout << ' ';
    }
    std::cout << std::endl;

    // Tiempos (μs)
    timeval t0, t1;

    gettimeofday(&t0, NULL);
    PmergeMe::sortDeque(deq);
    gettimeofday(&t1, NULL);
    long long timeDeque = (t1.tv_sec - t0.tv_sec) * 1000000LL + (t1.tv_usec - t0.tv_usec);

    gettimeofday(&t0, NULL);
    PmergeMe::sortList(lst);
    gettimeofday(&t1, NULL);
    long long timeList = (t1.tv_sec - t0.tv_sec) * 1000000LL + (t1.tv_usec - t0.tv_usec);

    // After (una sola línea, como pide el subject; usamos el resultado de deque)
    std::cout << "After: ";
    for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it) {
        std::cout << *it;
        if (it + 1 != deq.end()) std::cout << ' ';
    }
    std::cout << std::endl;

    // Líneas de tiempo (con nombre del contenedor)
    std::cout << "Time to process a range of " << deq.size()
              << " elements with std::deque : " << timeDeque << " us" << std::endl;

    std::cout << "Time to process a range of " << lst.size()
              << " elements with std::list  : " << timeList  << " us" << std::endl;

    return 0;
}