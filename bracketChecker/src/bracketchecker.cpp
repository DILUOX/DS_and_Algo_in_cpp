#include "bracketchecker.h"
#include "iostream"

/** Written by Márton Kozma, finished at 2023/09/17 **/


bool BracketChecker::checkCorrectness(const std::string& expression) {


    bool correct = true;

    for(char current : expression) //iterating through expression
    {
        if(!correct){
            break;
        }

        /** OPEN BRACKET FOUND **/
        if(is_open_bracket(current)){     //pushing open brackets into stack
            mystack.push(current);
        }

        /** CLOSED BRACKET FOUND    **/
        if(is_closed_bracket(current))
        {
            if(mystack.isEmpty()) {     //if the stack is empty it means that the current closing bracket doesn't have an open bracket pair
                correct = false;
                break;
            }
            char top = mystack.pop();   //getting the last bracket while deleting it

            switch(current)
            {
                //if the current closed bracket doesn't have a matching open bracket then the expression is invalid
                case ')':
                    if (top != '(') correct = false;
                    break;
                case ']':
                    if (top != '[') correct = false;
                    break;
                case '}':
                    if (top != '{') correct = false;
                    break;
                default:
                    std::cout << "Is not a bracket!" << std::endl;
                    break;

            }
        }
    }
    //if the expression is correct then all the brackets were examined and deleted from the stack
    if(!mystack.isEmpty()){
        correct = false;
        mystack.empty();        //deleting garbage from stack
    }

    return correct;
}

//checking open bracket types
bool BracketChecker::is_open_bracket(char c) {
    return c == '(' || c == '{' || c == '[';
}

//checking closed bracket types
bool BracketChecker::is_closed_bracket(char c) {
    return c == ')' || c == '}' || c == ']';
}



