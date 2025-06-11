#include "stack.h"

/** Written by Márton Kozma, finished at 2023/09/17 **/



/** IMPLEMETATIONS OF TEMPLATE T TYPE **/
template<typename T>


bool stack<T>::isEmpty(){
    return head == 0;

}
template<typename T>

bool stack<T>::isFull() {
    return head==buff_size;
}

template<typename T>

T stack<T>::push(T item) {
    if(isFull()){
        throw OverFlowException();
    }
    arr[head] = item;

    head++;
    return arr[head-1];
}

template<typename T>

T stack<T>::pop(){
    if(isEmpty()){
        throw UnderflowException();
    }

    T popped_element = arr[head-1];
    head--;
    return popped_element;
}

template<typename T>

T stack<T>::top(){
    if(isEmpty()){
        throw UnderflowException();
    }
    return arr[head-1];
}


template<typename T>
void stack<T>::empty(){
    if(isEmpty()){
        return;
    }
    while (!isEmpty()){
        this->pop();
    }

}



/** IMPLEMENTATIONS OF CHAR TYPE **/


template<>

bool stack<char>::isEmpty() {
    return head == 0;
}


//adding item

template<>

char stack<char>::push(char item) {
    if(isFull()){
        throw OverFlowException();
    }
    arr[head] = item;

    head++;
    return arr[head-1];
}

template<>

//removing item
char stack<char>::pop() {
    if(isEmpty()){
        throw UnderflowException();
    }
    char popped_element = arr[head-1];
    head--;
    return popped_element;
}

//get last element
template<>
char stack<char>::top() {
    if(isEmpty()){
        throw UnderflowException();
    }
    return arr[head-1];
}

//erase container content
template<>
void stack<char>::empty(){
    if(isEmpty()){
        return;
    }
    while (!isEmpty()){
        pop();
    }

}





