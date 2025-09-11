/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:16:46 by ana-pper          #+#    #+#             */
/*   Updated: 2025/09/11 16:35:38 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <list>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <string>
#include <climits>
#include <cstdlib>
#include <sys/time.h>
#include <cctype>

class PmergeMe 
{
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        static void sortDeque(std::deque<int>& deq);
        static void sortList(std::list<int>& lst);

    private:
        struct PairInt {
            int big;
            int small;
            PairInt(int a, int b) : big(a), small(b) {}
            PairInt() : big(0), small(0) {}
        };

        static void generateJacobsthalIndices(int m, std::deque<int>& out);
};

#endif