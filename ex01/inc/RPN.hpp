/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:27:09 by jlara-na          #+#    #+#             */
/*   Updated: 2025/08/05 17:34:42 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include <iostream>
# include <sstream>
# include <stack>

class RPN
{
    private:
        std::string _operation;
    public:
        RPN();
        RPN(std::string input);
        RPN(const RPN &other);
        ~RPN();
        RPN &operator=(const RPN &other);

        void setOperation(const std::string &input);
        void printResult();
};