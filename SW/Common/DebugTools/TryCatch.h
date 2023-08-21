#ifndef BF943C20_7AE9_4B23_8E55_F33E4532769B
#define BF943C20_7AE9_4B23_8E55_F33E4532769B

#include <iostream>
#include <exception>


#define BEGIN_CHECKED_EXCEPTION() try

#define END_CHECKED_EXCEPTION() catch (const std::exception &e) \
    { \
        PRINT_EXCEPTION_DETAILS() \
        std::cerr << "Exception caught: " << e.what() << std::endl; \
    } \
    catch (...) \
    { \
        PRINT_EXCEPTION_DETAILS() \
        std::cerr << "Unknown exception caught" << std::endl; \
    }

#define PRINT_EXCEPTION_DETAILS() std::cout << "File: " << __FILE__ << std::endl; \
    std::cout << "Function: " << __PRETTY_FUNCTION__ << std::endl; \
    std::cout << "Line: " << __LINE__ << std::endl;


#endif /* BF943C20_7AE9_4B23_8E55_F33E4532769B */
