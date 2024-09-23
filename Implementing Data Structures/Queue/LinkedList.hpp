#pragma once
#include "Node.hpp"

template<class T>
class LinkedList{
private:
    Node<T>* head;
    Node<T>* tail;
    
    void destroy();
    
public:
    LinkedList();
    ~LinkedList();
    void addFirst(const T& value);
    void addLast(const T& value);
    void removeFirst();
    void removeLast();
    void print() const;
    const T& getHeadValue() const;
    const T& getTailValue() const;
};

template<class T>
LinkedList<T>::LinkedList(){
    this->head = nullptr;
    this->tail = nullptr;
}

template<class T>
LinkedList<T>::~LinkedList(){
    destroy();
}

template<class T>
void LinkedList<T>::destroy(){
    Node<T>* curr = head;
    while(curr != nullptr){
        Node<T>* next = curr->next;
        delete curr;
        curr = next;
    }
    head = nullptr;
    tail = nullptr;
}

template<class T>
void LinkedList<T>::print() const{
    Node<T>* curr = head;
    while(curr != nullptr){
        curr->print();
        curr = curr->next;
    }
}

template<class T>
void LinkedList<T>::addFirst(const T& value){
    Node<T>* newHead = new Node(value);
    if(head == nullptr){
        head = tail = newHead;
    }
    else{
        newHead->next = head;
        head->prev = newHead;
        head = newHead;
    }
}

template<class T>
void LinkedList<T>::addLast(const T& value){
    Node<T>* newTail = new Node(value);
    if(tail == nullptr){
        head = tail = newTail;
    }
    else{
        newTail->prev = tail;
        tail->next = newTail;
        tail = newTail;
    }
}

template<class T>
void LinkedList<T>::removeFirst(){
    Node<T>* oldHead = head;
    head = head->next;
    if(head != nullptr){
        head->prev = nullptr;
    }
    else{
        tail = nullptr;
    }
    delete oldHead;
}

template<class T>
void LinkedList<T>::removeLast(){
    Node<T>* oldTail = tail;
    tail = tail->prev;
    if(tail!=nullptr){
        tail->next = nullptr;
    }
    else{
        head = nullptr;
    }
    delete oldTail;
}

template<class T>
const T& LinkedList<T>::getHeadValue() const{
    return head->value;
}

template<class T>
const T& LinkedList<T>::getTailValue() const{
    return tail->value;
}

