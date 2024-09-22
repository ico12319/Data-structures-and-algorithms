#include <iostream>
template<class T>

class Node{
public:
    Node* next;
    Node* prev;
    T value;
    
    Node() = delete;
    Node(const T& value);
    void print() const;
    
};
template<class T>
Node<T>::Node(const T& value){
    this->next = nullptr;
    this->prev = nullptr;
    this->value = value;
}

template<class T>
void Node<T>::print() const{
    std::cout<<value<<" ";
}
