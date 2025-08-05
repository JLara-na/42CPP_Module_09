/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:19:03 by jlara-na          #+#    #+#             */
/*   Updated: 2025/08/05 17:48:08 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(std::string const &csv_file, std::string const &input_file) : _input_file(input_file), _csv_file(csv_file)
{
    std::ifstream iFileStream (_input_file.c_str());
    
    if (!iFileStream.is_open())
        throw (std::runtime_error("Error: could not open: " + _input_file));

    std::ifstream csvFileStream(_csv_file.c_str());
    
    if (!csvFileStream.is_open())
        throw (std::runtime_error("Error: could not open: " + _csv_file));
    parseCSV();
    parseInput();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _input_file(other._input_file), _csv_file(other._csv_file), _exchangeRates(other._exchangeRates){}

BitcoinExchange::~BitcoinExchange(){}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other){
    if (this != &other){
        this->_input_file = other._input_file;
        this->_csv_file = other._csv_file;
        this->_exchangeRates = other._exchangeRates;
    }
    return(*this);
}

bool check_valueStr(std::string value){
    if (value.empty())
        return false;

    std::istringstream iss(value);
    
    double d;
    char c;
    if (!(iss >> d))
        return false;
    if (iss >> c)
        return false;
    return true;
}

bool isLeapYear(int year){
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

bool check_dateStr(std::string date){
    if (date.empty())
        return false;
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    std::string yearStr = date.substr(0, 4);
    std::string monthStr = date.substr(5, 2);
    std::string dayStr = date.substr(8, 2);

    for (size_t i = 0; i < 4; ++i)
        if (!std::isdigit(yearStr[i]))
            return false;
    for (size_t i = 0; i < 2; ++i)
        if (!std::isdigit(monthStr[i]) || !std::isdigit(dayStr[i]))
            return false;

    int year = atoi(yearStr.c_str());
    int month = atoi(monthStr.c_str());
    int day = atoi(dayStr.c_str());

    if (month < 1 || month > 12)
        return false;

    int maxDay = 31;
    if (month == 2) {
        maxDay = isLeapYear(year) ? 29 : 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        maxDay = 30;
    }
    if (day < 1 || day > maxDay)
        return false;
    return true;
}

void trimInPlace(std::string &str) {
    size_t start = 0;
    while (start < str.length() && std::isspace(str[start]))
        ++start;

    size_t end = str.length();
    while (end > start && std::isspace(str[end - 1]))
        --end;

    str = str.substr(start, end - start);
}

void BitcoinExchange::parseCSV(){
    std::ifstream   csvFileStream(_csv_file.c_str());
    std::string     line;
    std::string     firstline;
    
    if (!std::getline(csvFileStream, line)) //header skip
        throw (std::runtime_error("Error: csv file empty"));
    firstline = line;  
    line.clear();
    while (std::getline(csvFileStream, line)){
        if (line.empty())
                continue ;
        std::stringstream   strStream(line);
        std::string date;
        std::string valueStr;
        if(std::getline(strStream, date, ',') && std::getline(strStream, valueStr)){
            if (line.empty() || valueStr.empty())
                throw (std::runtime_error("Error: missing date or value at csv file"));
            trimInPlace(date);
            trimInPlace(valueStr);
            if (check_valueStr(valueStr) && check_dateStr(date)){
                double value = std::atof(valueStr.c_str());
                if (value < 0)
                    throw (std::runtime_error("Error: bad csv value format: negative exchange rate: (" + valueStr + ")"));
                _exchangeRates[date] = value;
            }
            else
                throw (std::runtime_error("Error: bad csv value format: (" + date + ") (" + valueStr + ")"));
        }
        else
            throw (std::runtime_error("Error: bad csv file format: (" + line + ")"));
    }
    if (line == firstline)
                throw (std::runtime_error("Error: csv file has no values"));
}

void BitcoinExchange::exchangeBitcoins(std::string inputDate, double inputValue){
    std::map<std::string, double>::const_iterator itCSV = _exchangeRates.lower_bound(inputDate);
    
    if (itCSV == _exchangeRates.end()) {
        --itCSV;
    }
    else if (itCSV->first != inputDate){
        if (itCSV != _exchangeRates.begin()){
            --itCSV;
        }
        else{
            std::cerr << "Error: no available exchange rate before (" << inputDate << ") using (" << itCSV->first << ")" << std::endl;
        }
    }
    double rate = itCSV->second;
    double result = inputValue * rate;

    std::cout << inputDate << " => " << inputValue << " * " << rate << " = " << result << std::endl;

}

void BitcoinExchange::parseInput(){
    std::ifstream   inputFileStream(_input_file.c_str());
    std::string     line;
    std::string     firstline;
    
    if (!std::getline(inputFileStream, line)) //header skip
        throw (std::runtime_error("Error: input file empty"));
    firstline = line;
    line.clear();
    while (std::getline(inputFileStream, line)){
        if (line.empty())
                continue;
        std::stringstream   strStream(line);
        std::string date;
        std::string valueStr;
        if(std::getline(strStream, date, '|') && std::getline(strStream, valueStr)){
            if (line.empty() || valueStr.empty())
                throw (std::runtime_error("Error: missing date or value at input file"));
            trimInPlace(date);
            trimInPlace(valueStr);
            if (check_valueStr(valueStr) && check_dateStr(date)){
                double value = std::atof(valueStr.c_str());
                if (value > 1000.0)
                    std::cerr << "Error: bad input value format: too large a number: (" + valueStr + ")" << std::endl;
                else if (value < 0)
                    std::cerr << "Error: bad input value format: not a positive number: (" + valueStr + ")" << std::endl;
                else 
                    exchangeBitcoins(date, value);
            }
            else
                std::cerr << "Error: bad input value format: (" + date + ") (" + valueStr + ")" << std::endl;
        }
        else
            std::cerr << "Error: bad input file format: (" + line + ")" << std::endl;
    }
    if (line == firstline)
                throw (std::runtime_error("Error: input file has no values"));
}
