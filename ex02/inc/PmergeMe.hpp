/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:50:16 by jlara-na          #+#    #+#             */
/*   Updated: 2025/08/09 18:06:34 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include <iostream>
# include <sstream>
# include <algorithm>
# include <limits>
# include <vector>
# include <deque>

class PmergeMe
{
    private:
        clock_t _v_time;
        clock_t _d_time;
        std::vector<int> _PMvector;
        std::deque<int> _PMdeque;
        clock_t sortVector();
        clock_t sortDeque();
    public:
        PmergeMe();
        PmergeMe(int ac, char **av);
        PmergeMe(const PmergeMe &other);
        ~PmergeMe();
        PmergeMe &operator=(const PmergeMe &other);
        
        void setPMvector(int ac, char **av);
        void setPMdeque(int ac, char **av);
        void run();
};

//Time to process a range of 3000 elements with std::[..] : 62.14389 us