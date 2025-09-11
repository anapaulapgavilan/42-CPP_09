/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:34:12 by ana-pper          #+#    #+#             */
/*   Updated: 2025/09/11 16:01:18 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

static int error_str(const char *msg) {
    std::cerr << msg << "\n";
    return EXIT_FAILURE;
}

static std::string trim(const std::string& s) {
    std::string::size_type a = s.find_first_not_of(" \t\r\n");
    if (a == std::string::npos) return "";
    std::string::size_type b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
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
        if (line.empty()) continue;

        std::size_t pos = line.find('|');
        if (pos == std::string::npos) {
            std::cerr << BAD_INPUT_ERR << line << "\n";
            continue;
        }

        std::string date = trim(line.substr(0, pos));
        std::string val  = trim(line.substr(pos + 1));

        if (date.empty() || val.empty()) {
            std::cerr << BAD_INPUT_ERR << line << "\n";
            continue;
        }

        if (!btc.isDateInCorrectFormat(date) || !btc.isValidDate(date))
            continue;
        if (!btc.isRateInCorrectFormat(val))
            continue;

        float amount = static_cast<float>(std::atof(val.c_str()));
        try {
            float rate   = btc.getRateFromDataBase(date);
            float result = amount * rate;
            std::cout << date
                      << " => " << val
                      << " = " << result
                      << "\n";
        } catch (const std::exception& e) {
            std::cerr << e.what() << "\n";
            continue;
        }
    }
    return EXIT_SUCCESS;
}