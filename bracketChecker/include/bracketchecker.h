#ifndef ADATSZERK_HF01_BRACKETCHECKER_H
#define ADATSZERK_HF01_BRACKETCHECKER_H

#include <string>
#include "stack.h"

/** Written by Márton Kozma, finished at 2023/09/17 **/
class BracketChecker {

public:
    BracketChecker() = default;

    ~BracketChecker(){
        mystack.empty();
    }


    bool checkCorrectness(const std::string& expression);

    static bool is_open_bracket(char c);

    static bool is_closed_bracket(char c);
private:
    stack<char> mystack;

};


#endif //ADATSZERK_HF01_BRACKETCHECKER_H
