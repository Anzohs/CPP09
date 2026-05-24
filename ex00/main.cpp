/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 17:47:24 by hladeiro          #+#    #+#             */
/*   Updated: 2026/05/23 17:47:26 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.h"

static bool isValidDate(const std::string& date)
{
    if (date.length() != 10)
        throw std::runtime_error(BAD_INPUT + date);

    if (date[4] != '-' || date[7] != '-')
        throw std::runtime_error(BAD_INPUT + date);

    for (size_t i = 0; i < date.length(); ++i)
    {
        if (i == 4 || i == 7)
            continue;

        if (!std::isdigit(date[i]))
            throw std::runtime_error(BAD_INPUT + date);;
    }

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (month < 1 || month > 12)
        throw std::runtime_error(BAD_INPUT + date);;

    if (day < 1 || day > 31)
        throw std::runtime_error(BAD_INPUT + date);;

    int daysInMonth[] = {
        31, 28, 31, 30,
        31, 30, 31, 31,
        30, 31, 30, 31
    };

    bool leap =
        (year % 4 == 0 && year % 100 != 0) ||
        (year % 400 == 0);

    if (leap)
        daysInMonth[1] = 29;

    if (day > daysInMonth[month - 1])
        throw std::runtime_error(BAD_INPUT + date);;

    return true;
}

static bool validSeparator(std::string &separator) {
    if (separator.length() != 1 || separator[0] != '|')
        throw std::runtime_error(BAD_INPUT + separator);
    return true;
}

int checkFile(std::fstream& f, std::string fileName) {
    std::string line;
    if (!f.good())
        throw std::runtime_error(AV + fileName);
    std::getline(f, line);
    if (line != FILE_HEADER)
        throw std::runtime_error(HEADER_MISSING);
    return 0;
}

static float parseValue(std::string &value) {
    string parse;
    double val;
    if (value.length() > 4)
        throw std::runtime_error(INVALID_VALUE);
    val = std::strtod(value.c_str(), &parse);
    if (parse == value.c_str())
        throw std::runtime_error(INVALID_VALUE);
    while (*parse == ' ')
        parse++;
    if (*parse != 0)
        throw std::runtime_error(INVALID_VALUE);
    if (val > 1000)
        throw std::runtime_error(SIZE_INTDB);
    if (val < 0)
        throw std::runtime_error(NEG_NB);
    return static_cast<float>(val);
}

InputData getValue(std::string &line) {
    InputData data;

    std::stringstream ss(line);
    std::string valueStr;

    std::getline(ss, data.date, ' ');
    isValidDate(data.date);
    std::getline(ss, data.separator, ' ');
    validSeparator(data.separator);
    std::getline(ss, valueStr);

    data.value = parseValue(valueStr);

    return data;

}

int main(int ac, string *av) {
    if (ac != 2) {
        std::cerr << NO_FILE << std::endl;
        std::cerr << EXAMPLE << std::endl;
        return NO_ARG;
    }
    try {
        std::fstream f(av[1], std::ios_base::in);
        checkFile(f, av[1]);
        BitcoinExchange b;
        std::string line;
        InputData data;
        while (std::getline(f, line)) {
            try {
                data = getValue(line);

                std::cout << data.date
                          << " => "
                          << data.value * b.getRate(data.date)
                          << std::endl;
            }
            catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
