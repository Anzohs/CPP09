#include "PmergeMe.hpp"

int main(int ac, string *av)
{

 if (ac < 2) {
        std::cerr << "Error: No input provided." << std::endl;
        return 1;
    }

    std::vector<int> vec;
    std::deque<int> deq;

    for (int i = 1; i < ac; ++i) {
        int num = std::atoi(av[i]);
        if (num <= 0) {
            std::cerr << "Error: Invalid number." << std::endl;
            return 1;
        }
        vec.push_back(num);
        deq.push_back(num);
    }

    PmergeMe sorter;

    // Medição de tempo para vector
    std::clock_t startVec = std::clock();
    sorter.sortVector(vec);
    std::clock_t endVec = std::clock();
    double durationVec = 1000000.0 * (endVec - startVec) / CLOCKS_PER_SEC;

    // Medição de tempo para deque
    std::clock_t startDeq = std::clock();
    sorter.sortDeque(deq);
    std::clock_t endDeq = std::clock();
    double durationDeq = 1000000.0 * (endDeq - startDeq) / CLOCKS_PER_SEC;

    std::cout << "Before: ";
    for (int i = 1; i < ac; ++i) {
        std::cout << av[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "After (Vector): ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "After (Deque): ";
    for (size_t i = 0; i < deq.size(); ++i) {
        std::cout << deq[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Time to process with vector: " << durationVec << " us" << std::endl;
    std::cout << "Time to process with deque: " << durationDeq << " us" << std::endl;

    return 0;

}
