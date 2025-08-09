/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:02:41 by jlara-na          #+#    #+#             */
/*   Updated: 2025/08/09 18:11:18 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/PmergeMe.hpp"

int main(int ac, char **av) {
    try{
        if (ac < 2)
            throw (std::runtime_error("Error: Invalid number of arguments"));
        
        PmergeMe    PM(ac, av);
        PM.run();
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}