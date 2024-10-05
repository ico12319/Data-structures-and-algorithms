#pragma once
#include "Node.h"

class LinkedList{
public:
    Node* head;
    Node* tail;
    int count;
    
    void destroy();
    ~LinkedList();
    LinkedList();
    void addFirst(int value);
    void addLast(int value);
    void print() const;
};
