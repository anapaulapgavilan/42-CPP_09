#include "RPN.hpp"

static int error_str(const std::string& msg)
{
    std::cerr << ERROR_MSG_PREFIX << msg << std::endl;
    return EXIT_FAILURE;
}

int main(int argc, char** argv)
{
    if (argc != 2)
        return error_str(ARGC_ERR);

    std::string str(argv[1]);
    if (!RPN::valid_expression(str))
        return error_str(INVALID_EXPR_ERR);

    try 
    {
        long long result = RPN::calculate(str);
        std::cout << result << std::endl;
    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
