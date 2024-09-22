#include <iostream>

class Node{
public:
    Node* prev;
    Node* next;
    int value;
    
    
public:
    Node() = delete;
    Node(int value);
    void print() const;
};
