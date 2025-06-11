#ifndef EXCEPTIONS_H
#define  EXCEPTIONS_H

#include <exception>

/** Written by Márton Kozma, finished at 2023/09/17 **/

class OverFlowException : public std::exception{
    const char * what() const noexcept override{
        return "Exceeded allocated buffer size. Overlfow error";
    }

};

class UnderflowException : public std::exception{
    const char * what() const noexcept override{
        return "No initialized items remaining. Underflow error";
    }
};


#endif