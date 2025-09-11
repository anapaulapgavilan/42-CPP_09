#include "PmergeMe.hpp"

void PmergeMe::generateJacobsthalIndices(int m, std::deque<int>& out) {
    out.clear();
    // Jacobsthal sequence generation: J0=0, J1=1, J2=1, then Jn = J(n-1) + 2*J(n-2)
    // Generate Jacobsthal numbers from J3 upward until exceeding m
    if (m < 3) {
        return;
    }
    long long prev2 = 1, prev1 = 1; 
    long long jval;
    // J3 and onward:
    while (true) {
        jval = prev1 + 2 * prev2;
        if (jval > m) break;
        out.push_back((int)jval);
        prev2 = prev1;
        prev1 = jval;
    }
}

void PmergeMe::sortDeque(std::deque<int>& deq) {
    // If 0 or 1 elements, already sorted
    size_t n = deq.size();
    if (n < 2) {
        return;
    }
    if (n == 2) {
        if (deq[0] > deq[1]) {
            int tmp = deq[0];
            deq[0] = deq[1];
            deq[1] = tmp;
        }
        return;
    }
    // Separate straggler if count is odd
    bool hasStraggler = (deq.size() % 2 != 0);
    int straggler = 0;
    if (hasStraggler) {
        straggler = deq.back();
        deq.pop_back();
    }
    // Pair up the remaining elements
    std::deque<PairInt> pairs;
    while (deq.size() >= 2) {
        int first = deq.front();
        deq.pop_front();
        int second = deq.front();
        deq.pop_front();
        if (first < second) {
            pairs.push_back(PairInt(second, first));
        } else {
            pairs.push_back(PairInt(first, second));
        }
    }
    // Sort the pairs by the larger value (big) using insertion sort
    for (size_t i = 1; i < pairs.size(); ++i) {
        PairInt key = pairs[i];
        size_t j = i;
        while (j > 0 && pairs[j-1].big > key.big) {
            pairs[j] = pairs[j-1];
            --j;
        }
        pairs[j] = key;
    }
    // Build the main chain (sorted bigs) and pend (smalls) sequences
    std::deque<int> mainChain;
    std::deque<int> pend;
    for (size_t k = 0; k < pairs.size(); ++k) {
        mainChain.push_back(pairs[k].big);
        pend.push_back(pairs[k].small);
    }
    // Insert the first small element at the beginning of mainChain
    if (!pend.empty()) {
        mainChain.push_front(pend.front());
        // Mark index 1 as used (but do not remove from pend to preserve indexing)
    }
    // Generate Jacobsthal sequence indices for insertion order
    std::deque<int> jacob;
    generateJacobsthalIndices(pend.size(), jacob);
    // Mark used indices (1-indexed) for pend; index 1 is already used
    int m = (int)pend.size();
    if (m > 0) {
        std::vector<bool> used(m + 1, false);
        used[1] = true;
        // Insert elements at Jacobsthal sequence positions (and their predecessors)
        for (size_t t = 0; t < jacob.size(); ++t) {
            int jIndex = jacob[t];
            if (jIndex <= m && !used[jIndex]) {
                int valJ = pend[jIndex - 1];
                std::deque<int>::iterator pos = std::upper_bound(mainChain.begin(), mainChain.end(), valJ);
                mainChain.insert(pos, valJ);
                used[jIndex] = true;
                if (jIndex - 1 >= 1 && !used[jIndex - 1]) {
                    int valJm1 = pend[jIndex - 2];
                    pos = std::upper_bound(mainChain.begin(), mainChain.end(), valJm1);
                    mainChain.insert(pos, valJm1);
                    used[jIndex - 1] = true;
                }
            }
        }
        // Insert any remaining small elements in descending order of their indices
        for (int idx = m; idx >= 1; --idx) {
            if (!used[idx]) {
                int value = pend[idx - 1];
                std::deque<int>::iterator pos = std::upper_bound(mainChain.begin(), mainChain.end(), value);
                mainChain.insert(pos, value);
                used[idx] = true;
            }
        }
    }
    // Insert the straggler (unpaired element) into the sorted main chain
    if (hasStraggler) {
        std::deque<int>::iterator pos = std::upper_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(pos, straggler);
    }
    // Transfer the sorted sequence back to the original deque
    deq.assign(mainChain.begin(), mainChain.end());
}

void PmergeMe::sortList(std::list<int>& lst) {
    // If 0 or 1 elements, already sorted
    size_t n = lst.size();
    if (n < 2) {
        return;
    }
    if (n == 2) {
        std::list<int>::iterator it = lst.begin();
        int a = *it;
        int b = *(++it);
        if (a > b) {
            // Swap the two elements
            lst.clear();
            lst.push_back(b);
            lst.push_back(a);
        }
        return;
    }
    // Separate straggler if count is odd
    bool hasStraggler = (lst.size() % 2 != 0);
    int straggler = 0;
    if (hasStraggler) {
        straggler = lst.back();
        lst.pop_back();
    }
    // Pair up the remaining elements
    std::deque<PairInt> pairs;
    while (lst.size() >= 2) {
        int first = lst.front();
        lst.pop_front();
        int second = lst.front();
        lst.pop_front();
        if (first < second) {
            pairs.push_back(PairInt(second, first));
        } else {
            pairs.push_back(PairInt(first, second));
        }
    }
    // Sort pairs by the larger value using insertion sort
    for (size_t i = 1; i < pairs.size(); ++i) {
        PairInt key = pairs[i];
        size_t j = i;
        while (j > 0 && pairs[j-1].big > key.big) {
            pairs[j] = pairs[j-1];
            --j;
        }
        pairs[j] = key;
    }
    // Build main chain (list of bigs) and pend (deque of smalls)
    std::list<int> mainChain;
    std::deque<int> pend;
    for (size_t k = 0; k < pairs.size(); ++k) {
        mainChain.push_back(pairs[k].big);
        pend.push_back(pairs[k].small);
    }
    // Insert the first small element at the beginning of mainChain
    if (!pend.empty()) {
        mainChain.push_front(pend.front());
    }
    // Generate Jacobsthal sequence indices
    std::deque<int> jacob;
    generateJacobsthalIndices(pend.size(), jacob);
    // Mark used indices and perform insertion according to sequence
    int m = (int)pend.size();
    if (m > 0) {
        std::vector<bool> used(m + 1, false);
        used[1] = true;
        for (size_t t = 0; t < jacob.size(); ++t) {
            int jIndex = jacob[t];
            if (jIndex <= m && !used[jIndex]) {
                int valJ = pend[jIndex - 1];
                std::list<int>::iterator pos = std::upper_bound(mainChain.begin(), mainChain.end(), valJ);
                mainChain.insert(pos, valJ);
                used[jIndex] = true;
                if (jIndex - 1 >= 1 && !used[jIndex - 1]) {
                    int valJm1 = pend[jIndex - 2];
                    pos = std::upper_bound(mainChain.begin(), mainChain.end(), valJm1);
                    mainChain.insert(pos, valJm1);
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
    // Insert straggler into main chain
    if (hasStraggler) {
        std::list<int>::iterator pos = std::upper_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(pos, straggler);
    }
    // Transfer sorted sequence back to the original list
    lst.assign(mainChain.begin(), mainChain.end());
}

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &other) { (void)other; }
PmergeMe &PmergeMe::operator=(const PmergeMe &other) { (void)other; return *this; }
PmergeMe::~PmergeMe() {}
