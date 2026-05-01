# CPP09 — C++ Module 09 (42 School)

A collection of three exercises that explore the C++ Standard Template Library (STL) containers and algorithms, focusing on choosing the right container for each problem and understanding algorithmic complexity.

---

## Table of Contents

- [Overview](#overview)
- [Exercises](#exercises)
  - [ex00 — Bitcoin Exchange](#ex00--bitcoin-exchange)
  - [ex01 — Reverse Polish Notation](#ex01--reverse-polish-notation)
  - [ex02 — PmergeMe](#ex02--pmerge-me)
- [Building](#building)
- [Usage](#usage)
- [Key Concepts](#key-concepts)

---

## Overview

Module 09 is the final module of the 42 C++ piscine. It requires using at least **one different STL container per exercise** and prohibits reusing the same container across exercises. The focus is on selecting the right data structure for a given problem and applying classic algorithms with real-world constraints.

---

## Exercises

### ex00 — Bitcoin Exchange

**Program name:** `btc`

Reads a historical Bitcoin price database (CSV) and a list of query dates with amounts, then outputs the value of each amount in USD on the specified date.

#### Files

| File | Description |
|---|---|
| `ex00/src/main.cpp` | Entry point |
| `ex00/src/BitcoinExchange.cpp` | Core logic |
| `ex00/include/BitcoinExchange.hpp` | Class declaration |
| `ex00/data.csv` | Historical BTC price database |

#### Rules

- The database (`data.csv`) contains `date,price` entries from 2009 onward.
- The input file contains lines of the form `date | value`, where `value` is a float between 0 and 1000.
- If the exact date is not found, the closest **earlier** date is used.
- Errors (bad format, out-of-range values, unknown dates) are reported without stopping the program.

#### Container used

`std::map<std::string, float>` — allows `O(log n)` lookup of the closest date using `lower_bound`.

#### Example

```
$> ./btc input.txt
2011-01-03 => 3 = 0.9
2011-01-03 => 2 = 0.6
2011-01-09 => 1 = 0.32
```

---

### ex01 — Reverse Polish Notation

**Program name:** `RPN`

Evaluates a mathematical expression given in Reverse Polish Notation (postfix notation) and prints the result.

#### Files

| File | Description |
|---|---|
| `ex01/src/main.cpp` | Entry point |
| `ex01/src/RPN.cpp` | Evaluation logic |
| `ex01/include/RPN.hpp` | Class declaration |

#### Rules

- Supported operators: `+`, `-`, `*`, `/`.
- Operands are single-digit integers (0–9).
- The expression is passed as a single quoted string argument.
- The program exits with an error message if the expression is invalid.

#### Container used

`std::stack` — naturally models the LIFO stack required by the RPN algorithm.

#### Algorithm

1. Scan tokens left to right.
2. Push numbers onto the stack.
3. On an operator, pop two operands, apply the operator, push the result.
4. The final stack value is the result.

#### Example

```
$> ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
42
$> ./RPN "7 7 * 7 -"
42
$> ./RPN "1 2 * 2 / 2 * 2 4 - +"
0
$> ./RPN "(1 + 1)"
Error
```

---

### ex02 — PmergeMe

**Program name:** `PmergeMe`

Sorts a sequence of positive integers using the **Ford-Johnson** (merge-insert) sorting algorithm with two different STL containers, and prints the time taken by each.

#### Files

| File | Description |
|---|---|
| `ex02/src/main.cpp` | Entry point |
| `ex02/src/PmergeMe.cpp` | Sorting logic |
| `ex02/include/PmergeMe.hpp` | Class declaration |

#### Rules

- The sequence is passed as command-line arguments (positive integers only).
- The algorithm must be applied using **two distinct container types** (e.g., `std::vector` and `std::deque`).
- The program prints the unsorted sequence, the sorted sequence, and the time spent for each container.
- Duplicate values are considered an error.

#### Containers used

- `std::vector<int>` — contiguous memory, cache-friendly for large sequences.
- `std::deque<int>` — double-ended queue, efficient insertions at both ends.

#### Algorithm — Ford-Johnson (Merge-Insert Sort)

The Ford-Johnson algorithm minimises the number of comparisons needed to sort `n` elements:

1. **Pair** adjacent elements and sort each pair (larger element first).
2. **Recursively sort** the sequence of larger elements (the "main chain").
3. **Insert** the smaller elements (the "pend" sequence) into the main chain using binary search, following the order dictated by **Jacobsthal numbers** to minimise comparisons.

#### Example

```
$> ./PmergeMe 3 5 9 7 4
Before: 3 5 9 7 4
After:  3 4 5 7 9
Time to process a range of 5 elements with std::vector : 0.00031 us
Time to process a range of 5 elements with std::deque  : 0.00035 us
```

---

## Building

Each exercise has its own `Makefile` with the standard 42 rules.

```bash
# Build a specific exercise
cd ex00 && make
cd ex01 && make
cd ex02 && make
```

Common Makefile targets:

| Target | Description |
|---|---|
| `make` / `make all` | Compile the program |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and binary |
| `make re` | Rebuild from scratch |

Compilation flags used: `-Wall -Wextra -Werror -std=c++98`

---

## Usage

```bash
# ex00
./btc input.txt

# ex01
./RPN "3 4 + 2 *"

# ex02
./PmergeMe 5 3 1 8 2 9 4 7 6
```

---

## Key Concepts

| Concept | Description |
|---|---|
| **STL Containers** | `std::map`, `std::stack`, `std::vector`, `std::deque` — each chosen to match the problem's access pattern |
| **Iterators & Algorithms** | `lower_bound`, `upper_bound`, binary search for efficient lookups and insertions |
| **Algorithmic Complexity** | Understanding `O(n log n)` sorting vs. naive approaches; Jacobsthal numbers reduce binary search comparisons |
| **Error Handling** | Every exercise validates input and emits meaningful error messages |
| **C++98 Standard** | All code must compile with `-std=c++98`; no C++11 or later features allowed |
