#include <iostream>
#include "exceptions.h"

template<typename T>
struct node{
public:
    node(T data) : data(data), next(nullptr){}

    node() : data(), next(nullptr){}


    void set_next(node *next_) {
        next = next_;
    }

    node * get_next() {
        return next;
    }

    T get_data() {
        return data;

    }


    void set_data(T data_) {
        data=data_;
    }

private:
    T data;
    node * next;
};


template<typename T>
class stack{
public:
    stack() : head(nullptr){}
    stack(T data) : head(new node<T>(data)){}
    ~stack(){
    }
    bool isEmpty() {
        return head == nullptr;
    }


    void push(T data) {
        if(isEmpty()){
            head = new node<T>(data);
            return;
        }

        node<T> * newelement = new node<T>(head->get_data());
        newelement->set_next(head->get_next());

        head->set_next(newelement);
        head->set_data(data);
    }


    node<T> pop() {
        if(isEmpty()){
            throw UnderflowException();
        }
        node<T> temp = node<T>(head->get_data());
        node<T> * oldhead = head;
        head = head->get_next();
        delete oldhead;
        return temp;
    }

    node<T>* top(){
        return head;
    }

    void empty(){
        while (!isEmpty()){
            pop();
        }
    }

    void print(){
        if(isEmpty()){
            std::cout<<"[ ]"<<std::endl;
            return;
        }
        node<T> * temp = head;
        int i = 1;
        std::cout<<"[ ";
        while (temp->get_next()!= nullptr){
            T data_ = temp->get_data();
            temp=temp->get_next();
            if(i%5 == 0){
                std::cout<<i<<". element: "<<data_<<','<<std::endl;
            }
            else{
                std::cout<<i<<". element: "<<data_;
                if(temp->get_next()!= nullptr){
                    std::cout<<", ";
                }
            }


            i++;

        }
        std::cout<<" ]"<<std::endl;
    }

private:
    node<T>* head;
};

