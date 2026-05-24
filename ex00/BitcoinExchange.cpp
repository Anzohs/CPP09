/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 17:47:20 by hladeiro          #+#    #+#             */
/*   Updated: 2026/05/23 17:47:21 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.h"

static void checkDbName(std::string const &fileName) {
    if (fileName.length() <= 4)
        throw std::runtime_error(DB_NAME_ERROR);
    if (fileName[fileName.length() - 4] != '.' || fileName[fileName.length() - 3] != 'c' || fileName[fileName.length() - 2] != 's' || fileName[fileName.length() - 1] != 'v')
        throw std::runtime_error(DB_NAME_ERROR);
}

BitcoinExchange::BitcoinExchange() : _db(DB_NAME){
    checkDbName(DB_NAME);
    std::string line;
    std::string data;
    std::string value;
    std::fstream f(this->_db, std::ios_base::in);
    if (!f.good())
        throw std::runtime_error(DB_ERROR);
    std::getline(f, line);
    if (line != DB_HEADER)
        throw std::runtime_error(DB_HEADER_MISSING);
    while (std::getline(f, line))
    {
        std::stringstream ss(line);
        while (std::getline(ss, data, ',') && std::getline(ss, value))
        {
            this->_exchange.insert(std::make_pair(data, std::strtof(value.c_str(), NULL)));
        }
    }
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &other): _db(other._db), _exchange(other._exchange){checkDbName(_db);}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &other)
{
    if (this == &other)
        return *this;
    this->_db = other._db;
    this->_exchange = other._exchange;
    checkDbName(_db);
    return *this;
}

float BitcoinExchange::getRate(std::string const &date) {
    std::map<std::string, float>::iterator it = _exchange.lower_bound(date);

    if (it != _exchange.end() && it->first == date)
        return it->second;

    if (it == _exchange.begin())
        throw std::runtime_error("No earlier date available");

    --it;
    return it->second;
}
