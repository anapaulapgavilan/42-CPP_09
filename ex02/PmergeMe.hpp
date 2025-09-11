#pragma once

#include <deque>
#include <list>
#include <sys/time.h>
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <deque>
#include <list>
#include <string>
#include <climits>
#include <algorithm>
#include <vector>
#include <limits>

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
        };

        static void generateJacobsthalIndices(int m, std::deque<int>& out);
};
