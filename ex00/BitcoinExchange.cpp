/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:33:58 by ana-pper          #+#    #+#             */
/*   Updated: 2025/09/11 16:00:33 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

static float ft_stof(const std::string& s) {
    float v = 0.f;
    std::stringstream ss(s);
    ss >> v;
    return v;
}

static std::string trim(const std::string& s) {
    std::string::size_type a = s.find_first_not_of(" \t\r\n");
    if (a == std::string::npos) return "";
    std::string::size_type b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& o) { *this = o; }

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& o) {
    if (this != &o) dataBase = o.dataBase;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::readInternalDataBase(std::ifstream& internal_db) {
    std::string line;

    std::getline(internal_db, line);

    while (std::getline(internal_db, line)) {
        if (line.empty()) continue;
        std::size_t comma = line.find(',');
        if (comma == std::string::npos) continue;

        std::string date = trim(line.substr(0, comma));
        std::string rate = trim(line.substr(comma + 1));
        if (date.empty() || rate.empty()) continue;

        dataBase[date] = ft_stof(rate);
    }
    internal_db.close();
}

float BitcoinExchange::getRateFromDataBase(const std::string& date) const {
    std::map<std::string,float>::const_iterator it = dataBase.lower_bound(date);
    if (it != dataBase.end() && it->first == date)
        return it->second;

    if (it == dataBase.begin())
        throw std::runtime_error(NO_LOWER_DATE_ERR);

    --it;
    return it->second;
}

bool BitcoinExchange::isDateInCorrectFormat(const std::string& date) const {
    if (date.empty()) return false;

    std::size_t h1 = date.find('-');
    std::size_t h2 = date.find('-', h1 == std::string::npos ? 0 : h1 + 1);

    if (h1==std::string::npos || h2==std::string::npos
     || date.find_first_not_of("0123456789-") != std::string::npos)
    {
        std::cerr << BAD_INPUT_ERR << date << "\n";
        return false;
    }
    return true;
}

bool BitcoinExchange::isLeap(int year) {
    return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}

bool BitcoinExchange::isValidDate(const std::string& date) const {
    int year = 0, mon = 0, day = 0;
    char dash1 = 0, dash2 = 0;
    std::istringstream ss(date);
    if (!(ss >> year >> dash1 >> mon >> dash2 >> day) || dash1!='-' || dash2!='-') {
        std::cerr << INCORRECT_DATE_ERR << date << "\n";
        return false;
    }

    if (mon < 1 || mon > 12) {
        std::cerr << INCORRECT_MONTH_ERR << date << "\n";
        return false;
    }

    int mdays = 31;
    if (mon == 2) mdays = isLeap(year) ? 29 : 28;
    else if (mon==4 || mon==6 || mon==9 || mon==11) mdays = 30;

    if (day < 1 || day > mdays) {
        std::cerr << INCORRECT_DAY_ERR << date << "\n";
        return false;
    }
    return true;
}

bool BitcoinExchange::isRateInCorrectFormat(const std::string& s) const
{
    if (s.empty())
    {
        std::cerr << INVALID_RATE_ERR << "\"" << s << "\"\n";
        return false;
    }

    if (s[0] == '-')
    {
        std::cerr << NOT_A_POSITIVE_ERR << "\n";
        return false;
    }

    int dots = 0;
    for (std::string::size_type i = 0; i < s.size(); ++i) {
        if (s[i] == '.') {
            ++dots;
            if (dots > 1) {
                std::cerr << INVALID_RATE_ERR << "\"" << s << "\"\n";
                return false;
            }
        } else if (s[i] < '0' || s[i] > '9') {
            std::cerr << INVALID_RATE_ERR << "\"" << s << "\"\n";
            return false;
        }
    }
    if (s[0] == '.' || s[s.size()-1] == '.') {
        std::cerr << INVALID_RATE_ERR << "\"" << s << "\"\n";
        return false;
    }

    std::stringstream ss(s);
    float rate = 0.f;
    char extra = 0;
    if (!(ss >> rate) || (ss >> extra)) {
        std::cerr << INVALID_RATE_ERR << "\"" << s << "\"\n";
        return false;
    }

    if (rate > 1000.0f)
    {
        std::cerr << TOO_LARGE_ERR << "\n";
        return false;
    }

    return true;
}
