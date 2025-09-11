#include "PmergeMe.hpp"

int main(int argc, char** argv) {
    
    if (argc < 2) {
        std::cerr << "Error: Bad arguments" << std::endl;
        return 1;
    }

    std::deque<int> deq;
    std::list<int> lst;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.empty()) {
            std::cerr << "Error: empty argument" << std::endl;
            return 1;
        }
        for (size_t j = 0; j < arg.size(); ++j) {
            if (!std::isdigit(arg[j])) {
                std::cerr << "Error: contains non-digit characters" << std::endl;
                return 1;
            }
        }
        long value = std::strtol(arg.c_str(), NULL, 10);
        if (value <= 0 || value > INT_MAX) {
            std::cerr << "Error: Is outside of INT limits" << std::endl;
            return 1;
        }
        deq.push_back(static_cast<int>(value));
        lst.push_back(static_cast<int>(value));
    }

    std::cout << "Before: ";
    for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it) {
        std::cout << *it;
        if (it + 1 != deq.end()) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;

    timeval start, end;
    gettimeofday(&start, NULL);
    PmergeMe::sortDeque(deq);
    gettimeofday(&end, NULL);
    long long timeDeque = (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);

    gettimeofday(&start, NULL);
    PmergeMe::sortList(lst);
    gettimeofday(&end, NULL);
    long long timeList = (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);

    std::cout << "After (deque): ";
    for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it) {
        std::cout << *it;
        if (it + 1 != deq.end()) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;

    std::cout << "After (list) : ";
    for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
    {
        std::cout << *it;
        std::list<int>::iterator next = it;  ++next;
        if (next != lst.end()) std::cout << ' ';
    }
    std::cout << '\n';

    std::cout << "Time to process a range of " << deq.size() 
              << " elements with std::deque container: " << timeDeque << " us" << std::endl;
    std::cout << "Time to process a range of " << deq.size() 
              << " elements with std::list container: " << timeList << " us" << std::endl;

    return 0;
}
