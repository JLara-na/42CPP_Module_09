/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:27:19 by jlara-na          #+#    #+#             */
/*   Updated: 2025/08/05 17:39:32 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RPN.hpp"

RPN::RPN(){}

RPN::RPN(std::string input) : _operation(input){}

RPN::RPN(const RPN &other) : _operation(other._operation){}

RPN::~RPN(){}

RPN &RPN::operator=(const RPN &other){
    if (this != &other)
            this->_operation = other._operation;
    return(*this);
}

void RPN::setOperation(const std::string &input){
    _operation = input;
}

bool isNumber(const std::string& s) {
    for (size_t i = 0; i < s.length(); ++i) {
        if (!std::isdigit(s[i]))
            return false;
    }
    return true;
}

void RPN::printResult(){
    std::stack<double> stack;
    std::istringstream iss(_operation);
    std::string token;

    while (iss >> token) {
        if (token.length() != 1 && isNumber(token))
                throw std::runtime_error("Error: number greater than 10");
        if (token.length() != 1 && !isNumber(token))
                throw std::runtime_error("Error: Only numbers and operators");
        if (std::string("+-*/").find(token) != std::string::npos) {
            if (stack.size() < 2)
                throw std::runtime_error("Error: not enough operands for operation");
            double y = stack.top();
            stack.pop();
            double x = stack.top();
            stack.pop();

            if (token == "+")
                stack.push(x + y);
            else if (token == "-")
                stack.push(x - y);
            else if (token == "*")
                stack.push(x * y);
            else if (token == "/") {
                if (y == 0)
                    throw std::runtime_error("Error: division by zero");
                stack.push(x / y);
            }
        }
        else {
            if (!std::isdigit(token[0]))
                throw std::runtime_error("Error: Only numbers and operators");
            std::stringstream ss(token);
            double value;
            ss >> value;
            stack.push(value);
        }
    }
    if (stack.size() != 1)
        throw std::runtime_error("Error: malformed expression");
    std::cout << stack.top() << std::endl;
}