
#include "BitcoinExchange.hpp"

static int error_str(const char *msg) {
    std::cerr << msg << "\n";
    return EXIT_FAILURE;
}

int main(int argc, char **argv) {
    if (argc != 2)
        return error_str(FILE_OPEN_ERR);

    std::ifstream in(argv[1]);
    if (!in.is_open()) return error_str(FILE_OPEN_ERR);

    std::ifstream db(INTERNAL_DB_FILE);
    if (!db.is_open()) return error_str(INTERNAL_DB_ERR);

    BitcoinExchange btc;
    btc.readInternalDataBase(db);

    std::string line;
    std::getline(in, line);

    while (std::getline(in, line)) 
    {
        std::size_t pos = line.find('|');
        if (pos == std::string::npos || pos+2 >= line.size()) {
            std::cerr << BAD_INPUT_ERR << line << "\n";
            continue;
        }

        std::string date = line.substr(0, pos-1);
        std::string val  = line.substr(pos+2);

        if (!btc.isDateInCorrectFormat(date) || !btc.isValidDate(date))
            continue;
        if (!btc.isRateInCorrectFormat(val))
            continue;

        float amount = std::atof(val.c_str());
        float rate   = btc.getRateFromDataBase(date);
        float result = amount * rate;

        std::cout << date
                  << " => " << val
                  << " = " << result
                  << "\n";
    }
    return EXIT_SUCCESS;
}
