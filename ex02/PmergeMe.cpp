/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:14:28 by ana-pper          #+#    #+#             */
/*   Updated: 2025/09/11 16:38:23 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void PmergeMe::generateJacobsthalIndices(int m, std::deque<int>& out) {
    out.clear();
    if (m < 3) return;
    long long prev2 = 1;
    long long prev1 = 1;
    while (true) {
        long long jval = prev1 + 2 * prev2;
        if (jval > m) break;
        out.push_back(static_cast<int>(jval));
        prev2 = prev1;
        prev1 = jval;
    }
}

void PmergeMe::sortDeque(std::deque<int>& deq) {
    const size_t n = deq.size();
    if (n < 2) return;
    if (n == 2) { if (deq[0] > deq[1]) std::swap(deq[0], deq[1]); return; }

    bool hasStraggler = (deq.size() % 2 != 0);
    int straggler = 0;
    if (hasStraggler) { straggler = deq.back(); deq.pop_back(); }

    std::deque<PairInt> pairs;
    while (deq.size() >= 2) {
        int a = deq.front(); deq.pop_front();
        int b = deq.front(); deq.pop_front();
        if (a < b) pairs.push_back(PairInt(b, a));
        else       pairs.push_back(PairInt(a, b));
    }

    for (size_t i = 1; i < pairs.size(); ++i) {
        PairInt key = pairs[i];
        size_t j = i;
        while (j > 0 && pairs[j-1].big > key.big) {
            pairs[j] = pairs[j-1];
            --j;
        }
        pairs[j] = key;
    }

    std::deque<int> mainChain, pend;
    for (size_t k = 0; k < pairs.size(); ++k) {
        mainChain.push_back(pairs[k].big);
        pend.push_back(pairs[k].small);
    }

    if (!pend.empty()) mainChain.push_front(pend.front());

    std::deque<int> jacob;
    generateJacobsthalIndices(static_cast<int>(pend.size()), jacob);

    int m = static_cast<int>(pend.size());
    if (m > 0) {
        std::vector<bool> used(m + 1, false);
        used[1] = true;

        for (size_t t = 0; t < jacob.size(); ++t) {
            int jIndex = jacob[t];
            if (jIndex <= m && !used[jIndex]) {
                int v = pend[jIndex - 1];
                std::deque<int>::iterator pos = std::upper_bound(mainChain.begin(), mainChain.end(), v);
                mainChain.insert(pos, v);
                used[jIndex] = true;

                if (jIndex - 1 >= 1 && !used[jIndex - 1]) {
                    int w = pend[jIndex - 2];
                    pos = std::upper_bound(mainChain.begin(), mainChain.end(), w);
                    mainChain.insert(pos, w);
                    used[jIndex - 1] = true;
                }
            }
        }
        for (int idx = m; idx >= 1; --idx) {
            if (!used[idx]) {
                int value = pend[idx - 1];
                std::deque<int>::iterator pos = std::upper_bound(mainChain.begin(), mainChain.end(), value);
                mainChain.insert(pos, value);
                used[idx] = true;
            }
        }
    }

    if (hasStraggler) {
        std::deque<int>::iterator pos = std::upper_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(pos, straggler);
    }

    deq.assign(mainChain.begin(), mainChain.end());
}

void PmergeMe::sortList(std::list<int>& lst) {
    const size_t n = lst.size();
    if (n < 2) return;
    if (n == 2) {
        std::list<int>::iterator it = lst.begin();
        int a = *it; ++it; int b = *it;
        if (a > b) { lst.clear(); lst.push_back(b); lst.push_back(a); }
        return;
    }

    bool hasStraggler = (lst.size() % 2 != 0);
    int straggler = 0;
    if (hasStraggler) { straggler = lst.back(); lst.pop_back(); }

    std::deque<PairInt> pairs;
    while (lst.size() >= 2) {
        int a = lst.front(); lst.pop_front();
        int b = lst.front(); lst.pop_front();
        if (a < b) pairs.push_back(PairInt(b, a));
        else       pairs.push_back(PairInt(a, b));
    }

    for (size_t i = 1; i < pairs.size(); ++i) {
        PairInt key = pairs[i];
        size_t j = i;
        while (j > 0 && pairs[j-1].big > key.big) {
            pairs[j] = pairs[j-1];
            --j;
        }
        pairs[j] = key;
    }

    std::list<int> mainChain;
    std::deque<int> pend;
    for (size_t k = 0; k < pairs.size(); ++k) {
        mainChain.push_back(pairs[k].big);
        pend.push_back(pairs[k].small);
    }
    if (!pend.empty()) mainChain.push_front(pend.front());

    std::deque<int> jacob;
    generateJacobsthalIndices(static_cast<int>(pend.size()), jacob);

    int m = static_cast<int>(pend.size());
    if (m > 0) {
        std::vector<bool> used(m + 1, false);
        used[1] = true;

        for (size_t t = 0; t < jacob.size(); ++t) {
            int jIndex = jacob[t];
            if (jIndex <= m && !used[jIndex]) {
                int v = pend[jIndex - 1];
                std::list<int>::iterator pos = std::upper_bound(mainChain.begin(), mainChain.end(), v);
                mainChain.insert(pos, v);
                used[jIndex] = true;

                if (jIndex - 1 >= 1 && !used[jIndex - 1]) {
                    int w = pend[jIndex - 2];
                    pos = std::upper_bound(mainChain.begin(), mainChain.end(), w);
                    mainChain.insert(pos, w);
                    used[jIndex - 1] = true;
                }
            }
        }
        for (int idx = m; idx >= 1; --idx) {
            if (!used[idx]) {
                int value = pend[idx - 1];
                std::list<int>::iterator pos = std::upper_bound(mainChain.begin(), mainChain.end(), value);
                mainChain.insert(pos, value);
                used[idx] = true;
            }
        }
    }

    if (hasStraggler) {
        std::list<int>::iterator pos = std::upper_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(pos, straggler);
    }

    lst.assign(mainChain.begin(), mainChain.end());
}

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &other) { (void)other; }
PmergeMe &PmergeMe::operator=(const PmergeMe &other) { (void)other; return *this; }
PmergeMe::~PmergeMe() {}