#pragma once
#include <iostream>

template<class T>
class Node{
public:
    T value;
    Node<T>* next;
    Node<T>* prev;

    Node() = delete;
    Node(const T& value);
    void print() const;
};

template<class T>
Node<T>::Node(const T& value){
    this->value = value;
    this->next = nullptr;
    this->prev = nullptr;
}

template<class T>
void Node<T>::print() const{
    std::cout<<value<<" ";
}
