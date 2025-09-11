#include "BitcoinExchange.hpp"

static float ft_stof(const std::string& s) {
    float v; std::stringstream ss(s); ss >> v; return v;
}

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& o) { *this = o; }

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& o) {
    dataBase = o.dataBase; return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::readInternalDataBase(std::ifstream& internal_db) {
    std::string line;
    
    std::getline(internal_db, line);

    while (std::getline(internal_db, line)) {
        std::size_t comma = line.find(',');
        std::string date = line.substr(0, comma);
        std::string rate = line.substr(comma + 1);
        dataBase[date] = ft_stof(rate);
    }
    internal_db.close();
}

float BitcoinExchange::getRateFromDataBase(const std::string& date) const {
    std::map<std::string,float>::const_iterator it = dataBase.lower_bound(date);
    if (it != dataBase.end() && it->first == date)
        return it->second;
    if (it == dataBase.begin())
        return it->second;
    --it;
    return it->second;
}

bool BitcoinExchange::isDateInCorrectFormat(const std::string& date) const {
    if (date.empty()) return false;

    std::size_t h1 = date.find('-');
    std::size_t h2 = date.find('-', h1+1);
    
    if (h1==std::string::npos || h2==std::string::npos
     || date.find_first_not_of("0123456789-")!=std::string::npos)
    {
        std::cerr << BAD_INPUT_ERR << date << "\n";
        return false;
    }
    return true;
}

bool BitcoinExchange::isValidDate(const std::string& date) const {
    int year, mon, day; char dash;
    std::istringstream ss(date);
    if (!(ss >> year >> dash >> mon >> dash >> day)) {
        std::cerr << INCORRECT_DATE_ERR << date << "\n";
        return false;
    }
    if (year < 2009 || year > 2022) {
        std::cerr << YEAR_NOT_ON_DB_ERR << date << "\n";
        return false;
    }
    if (mon < 1 || mon > 12) {
        std::cerr << INCORRECT_MONTH_ERR << date << "\n";
        return false;
    }
    if (day < 1 || day > 31
     || (day>28 && mon==2)
     || (day==31 && (mon==4||mon==6||mon==9||mon==11)))
    {
        std::cerr << INCORRECT_DAY_ERR << date << "\n";
        return false;
    }
    return true;
}

bool BitcoinExchange::isRateInCorrectFormat(const std::string& s)
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

    if (s.find_first_not_of("0123456789.") != std::string::npos
        || s.front() == '.' || s.back() == '.')
    {
        std::cerr << INVALID_RATE_ERR << "\"" << s << "\"\n";
        return false;
    }
    float rate = ft_stof(s);
    if (rate > 1000.0f)
    {
        std::cerr << TOO_LARGE_ERR << "\n";
        return false;
    }

    return true;
}
