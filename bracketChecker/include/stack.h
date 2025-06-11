#ifndef STACK_H
#define STACK_H

#include "exceptions.h"

/** Written by Márton Kozma, finished at 2023/09/17 **/

template<class T>
class stack{
public:
    stack() : head(0){

    }
    ~stack(){
        empty();
    }

    bool isEmpty();
    bool isFull();
    T pop();
    T top();
    T push(T item);
    void empty();

private:
    static const int buff_size = 1024;
    T arr[buff_size];
    int head;
};



#endif //STACK_H