/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:19:00 by jlara-na          #+#    #+#             */
/*   Updated: 2025/07/30 17:15:27 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include <iostream>
# include <fstream>
# include <sstream>
# include <map>

class BitcoinExchange
{
private:
    std::string                     _input_file;
    std::string                     _csv_file;
    std::map<std::string, double>   _exchangeRates;
public:
    BitcoinExchange(std::string const &input_file, std::string const &csv_file);
    BitcoinExchange(const BitcoinExchange &other);
    ~BitcoinExchange();
    BitcoinExchange &operator=(const BitcoinExchange &other);
    
    void parseCSV();
};

