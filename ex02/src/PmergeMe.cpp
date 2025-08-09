/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:50:13 by jlara-na          #+#    #+#             */
/*   Updated: 2025/08/09 18:13:20 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/PmergeMe.hpp"


PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(int ac, char **av) {
    clock_t time;
    for (int i = 1; i < ac; i++) {
        const std::string& s = av[i];

        for (size_t j = 0; j < s.size(); ++j) {
            if (!isdigit(s[j]))
                throw std::runtime_error("Error: Invalid character in input: (" + s + ")");
        }
        
        std::istringstream iss(s);
        long num;

        iss >> num;
        if (num < 0 || num > std::numeric_limits<int>::max())
            throw std::runtime_error("Error: Number out of range: (" + s + ")");
        time = clock();
        _PMvector.push_back(static_cast<int>(num));
        _v_time = (clock() - time) / CLOCKS_PER_SEC * 1000000.0;
        time = clock();
        _PMdeque.push_back(static_cast<int>(num));
        _d_time = (clock() - time) / CLOCKS_PER_SEC * 1000000.0;
    }

    std::vector<int> v_copy = _PMvector;

    std::sort(v_copy.begin(), v_copy.end());

    for (size_t i = 1; i < v_copy.size(); ++i) {
        if (v_copy[i] == v_copy[i - 1])
            throw std::runtime_error("Error: Duplicate value found");
    }
    std::cout << _d_time << " <- d_time / v_time -> " << _v_time << std::endl; 
}

PmergeMe::PmergeMe(const PmergeMe &other): _PMvector(other._PMvector), _PMdeque(other._PMdeque){}

PmergeMe::~PmergeMe(){}

PmergeMe &PmergeMe::operator=(const PmergeMe &other){
    if (this != &other){

    }
    return (*this);
}

void PmergeMe::setPMvector(int ac, char **av){
    for (int i = 1; i < ac; i++) {
        const std::string& s = av[i];

        for (size_t j = 0; j < s.size(); ++j) {
            if (!isdigit(s[j]))
                throw std::runtime_error("Error: Invalid character in input: (" + s + ")");
        }
        
        std::istringstream iss(s);
        long num;

        iss >> num;
        if (num < 0 || num > std::numeric_limits<int>::max())
            throw std::runtime_error("Error: Number out of range: (" + s + ")");
        _PMvector.push_back(static_cast<int>(num));
    }
}

void PmergeMe::setPMdeque(int ac, char **av){
    
    for (int i = 1; i < ac; i++) {
        const std::string& s = av[i];

        for (size_t j = 0; j < s.size(); ++j) {
            if (!isdigit(s[j]))
                throw std::runtime_error("Error: Invalid character in input: (" + s + ")");
        }
        
        std::istringstream iss(s);
        long num;

        iss >> num;
        if (num < 0 || num > std::numeric_limits<int>::max())
            throw std::runtime_error("Error: Number out of range: (" + s + ")");
        _PMdeque.push_back(static_cast<int>(num));
    }
}

void insertionSortVector(std::vector<int>& v, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int key = v[i];
        int j = i - 1;
        while (j >= left && v[j] > key) {
            v[j + 1] = v[j];
            --j;
        }
        v[j + 1] = key;
    }
}

void mergeVector(std::vector<int>& v, int left, int mid, int right) {
    std::vector<int> leftPart(v.begin() + left, v.begin() + mid + 1);
    std::vector<int> rightPart(v.begin() + mid + 1, v.begin() + right + 1);

    size_t i = 0, j = 0;
    int k = left;
    while (i < leftPart.size() && j < rightPart.size()) {
        if (leftPart[i] <= rightPart[j])
            v[k++] = leftPart[i++];
        else
            v[k++] = rightPart[j++];
    }
    while (i < leftPart.size()) v[k++] = leftPart[i++];
    while (j < rightPart.size()) v[k++] = rightPart[j++];
}

void FJ_v_sort(std::vector<int>& v, int left, int right) {
    if (right - left <= 10) {
        insertionSortVector(v, left, right);
        return;
    }
    int mid = (left + right) / 2;
    FJ_v_sort(v, left, mid);
    FJ_v_sort(v, mid + 1, right);
    mergeVector(v, left, mid, right);
}

void insertionSortDeque(std::deque<int>& d, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int key = d[i];
        int j = i - 1;
        while (j >= left && d[j] > key) {
            d[j + 1] = d[j];
            --j;
        }
        d[j + 1] = key;
    }
}

void mergeDeque(std::deque<int>& d, int left, int mid, int right) {
    std::deque<int> leftPart(d.begin() + left, d.begin() + mid + 1);
    std::deque<int> rightPart(d.begin() + mid + 1, d.begin() + right + 1);

    size_t i = 0, j = 0;
    int k = left;
    while (i < leftPart.size() && j < rightPart.size()) {
        if (leftPart[i] <= rightPart[j])
            d[k++] = leftPart[i++];
        else
            d[k++] = rightPart[j++];
    }
    while (i < leftPart.size()) d[k++] = leftPart[i++];
    while (j < rightPart.size()) d[k++] = rightPart[j++];
}

void FJ_d_sort(std::deque<int>& d, int left, int right) {
    if (right - left <= 10) {
        insertionSortDeque(d, left, right);
        return;
    }
    int mid = (left + right) / 2;
    FJ_d_sort(d, left, mid);
    FJ_d_sort(d, mid + 1, right);
    mergeDeque(d, left, mid, right);
}

clock_t PmergeMe::sortVector(){
    if (_PMvector.size() <= 1)
        return 0;
    clock_t v_start_t = clock();
    FJ_v_sort(_PMvector, 0, static_cast<int>(_PMvector.size() - 1));
    clock_t v_end_t = clock();
    double vecTime = (double)(v_end_t - v_start_t) / CLOCKS_PER_SEC * 1000000.0;
    return (vecTime);
}

clock_t PmergeMe::sortDeque(){
    if (_PMdeque.size() <= 1)
        return 0;
    clock_t d_start_t = clock();
    FJ_d_sort(_PMdeque, 0, static_cast<int>(_PMdeque.size() - 1));
    clock_t d_end_t = clock();
    double deqTime = (double)(d_end_t - d_start_t) / CLOCKS_PER_SEC * 1000000.0;
    return (deqTime);
}

void    PmergeMe::run(){
    std::cout << "Before:  ";
    for (size_t i = 0; i < _PMvector.size(); i++) {
        std::cout << _PMvector[i] << " ";
    }
    std::cout << std::endl;
    
    _v_time += sortVector();
    _d_time += sortDeque();
    
    std::cout << "After:   ";
    for (size_t i = 0; i < _PMvector.size(); i++) {
        std::cout << _PMvector[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Time to process a range of " << _PMvector.size() << " elements with std::vector : " << _v_time << "us" << std::endl;
    std::cout << "Time to process a range of " << _PMdeque.size() << " elements with std::deque : " << _d_time << "us" << std::endl;
}