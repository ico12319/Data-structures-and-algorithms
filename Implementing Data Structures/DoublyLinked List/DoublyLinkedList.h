#include "Node.h"

class DoublyLinkedList{
    
private:
    Node* head;
    Node* tail;
    int count;
    
    void destroy();
    
public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void addFirst(int value);
    void addLast(int value);
    int size() const;
    void removeFirst();
    void removeLast();
    void print() const;
    
};
