#pragma once

#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>

#define BAD_INPUT_ERR           "Error: bad input => "
#define INCORRECT_DATE_ERR      "Error: incorrect date => "
#define YEAR_NOT_ON_DB_ERR      "Error: year is not at the database => "
#define INCORRECT_MONTH_ERR     "Error: incorrect month => "
#define INCORRECT_DAY_ERR       "Error: incorrect day => "
#define INVALID_RATE_ERR        "Error: invalid rate => "
#define NOT_A_POSITIVE_ERR      "Error: not a positive number."
#define TOO_LARGE_ERR           "Error: too large a number."
#define FILE_OPEN_ERR           "Error: could not open file"
#define INTERNAL_DB_FILE        "./data.csv"
#define INTERNAL_DB_ERR         "Error: fatal: could not open internal database file"

class BitcoinExchange {

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        void readInternalDataBase(std::ifstream& internal_db);
        float getRateFromDataBase(const std::string& date) const;

        bool isDateInCorrectFormat(const std::string& date) const;
        bool isValidDate(const std::string& date) const;
        bool isRateInCorrectFormat(const std::string &rate_str);

    private:
        std::map<std::string, float> dataBase;
};
