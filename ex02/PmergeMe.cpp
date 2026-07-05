#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

void PmergeMe::sortVector(std::vector<int>& vec) {
    if (vec.size() <= 1) return;
    if (vec.size() < THRESHOLD) {
        insertionSortVector(vec, 0, vec.size() - 1);
    } else {
        mergeInsertionSortVector(vec, 0, vec.size() - 1);
    }
}

void PmergeMe::sortDeque(std::deque<int>& deq) {
    if (deq.size() <= 1) return;
    if (deq.size() < THRESHOLD) {
        insertionSortDeque(deq, 0, deq.size() - 1);
    } else {
        mergeInsertionSortDeque(deq, 0, deq.size() - 1);
    }
}

void PmergeMe::mergeInsertionSortVector(std::vector<int>& vec, int left, int right) {
    if (right - left + 1 < THRESHOLD) {
        insertionSortVector(vec, left, right);
        return;
    }

    if (right - left < 1) return;

    int mid = left + (right - left) / 2;
    mergeInsertionSortVector(vec, left, mid);
    mergeInsertionSortVector(vec, mid + 1, right);

    // Inserção dos elementos menores com busca binária
    insertIntoVector(vec, left, right);
}

void PmergeMe::mergeInsertionSortDeque(std::deque<int>& deq, int left, int right) {
    if (right - left + 1 < THRESHOLD) {
        insertionSortDeque(deq, left, right);
        return;
    }

    if (right - left < 1) return;

    int mid = left + (right - left) / 2;
    mergeInsertionSortDeque(deq, left, mid);
    mergeInsertionSortDeque(deq, mid + 1, right);

    // Inserção dos elementos menores com busca binária
    insertIntoDeque(deq, left, right);
}

void PmergeMe::insertionSortVector(std::vector<int>& vec, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int key = vec[i];
        int j = i - 1;
        while (j >= left && vec[j] > key) {
            vec[j + 1] = vec[j];
            --j;
        }
        vec[j + 1] = key;
    }
}

void PmergeMe::insertionSortDeque(std::deque<int>& deq, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int key = deq[i];
        int j = i - 1;
        while (j >= left && deq[j] > key) {
            deq[j + 1] = deq[j];
            --j;
        }
        deq[j + 1] = key;
    }
}

void PmergeMe::insertIntoVector(std::vector<int>& vec, int start, int end) {
    for (int i = start + 1; i <= end; ++i) {
        int key = vec[i];
        int j = i - 1;
        while (j >= start && vec[j] > key) {
            vec[j + 1] = vec[j];
            --j;
        }
        vec[j + 1] = key;
    }
}

void PmergeMe::insertIntoDeque(std::deque<int>& deq, int start, int end) {
    for (int i = start + 1; i <= end; ++i) {
        int key = deq[i];
        int j = i - 1;
        while (j >= start && deq[j] > key) {
            deq[j + 1] = deq[j];
            --j;
        }
        deq[j + 1] = key;
    }
}
