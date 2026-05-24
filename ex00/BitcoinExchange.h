/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 17:46:36 by hladeiro          #+#    #+#             */
/*   Updated: 2026/05/23 17:46:38 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef BITCOINEXCHANGE_H
#define BITCOINEXCHANGE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <stdexcept>
#include <cstdlib>

typedef char* string;
const std::string NO_FILE = "The program need's a file to check the value";
const std::string DB_NAME = "data.csv";
const std::string DB_ERROR = "Error opening the data.csv file";
const std::string EXAMPLE = "Example: ./btc file.txt";
const std::string AV = "Error trying on opening the file: ";
const std::string DB_NAME_ERROR = "The data base from the exchange needs to be a file with extention of .csv";
const std::string NO_EARLY_DATE = "Error: No information before: ";
const std::string BAD_DATE = "Error: bad input => ";
const std::string NEG_NB = "Error: not a positive number.";
const std::string SIZE_INTDB = "Error: too large a number.";
const std::string INVALID_VALUE = "Error: invalid value.";
const std::string FILE_HEADER = "date | value";
const std::string HEADER_MISSING = "The header of the file is missing " + FILE_HEADER;
const std::string DB_HEADER = "date,exchange_rate";
const std::string DB_HEADER_MISSING = "The header of the db is missing " + DB_HEADER;
const std::string BAD_INPUT = "Error: bad input => ";


typedef struct InputData
{
    std::string date;
    std::string separator;
    float       value;
} InputData;

typedef enum errors {
    NO_ARG,
    ERROR_OPENF
} errors;

class BitcoinExchange {
    public:
    BitcoinExchange();
    ~BitcoinExchange();
    BitcoinExchange(BitcoinExchange const &other);
    BitcoinExchange &operator=(BitcoinExchange const &other);
    float getRate(std::string const &date);
    private:
    std::string _db;
    std::map<std::string, float> _exchange;
};


#endif
