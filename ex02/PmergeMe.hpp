#ifndef PMERGEME_HPP
#define PMERGEME_HPP


typedef char* string;

#include <vector>
#include <deque>
#include <iostream>
#include <iterator>

class PmergeMe {
public:
    PmergeMe();
    ~PmergeMe();

    void sortVector(std::vector<int>& vec);
    void sortDeque(std::deque<int>& deq);

private:
    void mergeInsertionSortVector(std::vector<int>& vec, int left, int right);
    void mergeInsertionSortDeque(std::deque<int>& deq, int left, int right);
    void insertionSortVector(std::vector<int>& vec, int left, int right);
    void insertionSortDeque(std::deque<int>& deq, int left, int right);
    void insertIntoVector(std::vector<int>& vec, int start, int end);
    void insertIntoDeque(std::deque<int>& deq, int start, int end);

    static const int THRESHOLD = 10; // Limite para usar Insertion Sort
};

#endif
