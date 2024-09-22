#include <stdio.h>
#include "DoublyLinkedList.h"

DoublyLinkedList::DoublyLinkedList(){
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;
}

void DoublyLinkedList::destroy(){
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    tail = nullptr;
}

DoublyLinkedList::~DoublyLinkedList(){
    destroy();
}

void DoublyLinkedList::addFirst(int value){
    Node* newHead = new Node(value);
    if(head == nullptr){
        head = tail = newHead;
    }
    else{
        newHead->next = head;
        head->prev = newHead;
        head = newHead;
    }
    count++;
}

void DoublyLinkedList::print() const{
    Node* curr = head;
    while(curr!=nullptr){
        curr->print();
        curr = curr->next;
    }
}

void DoublyLinkedList::addLast(int value){
    Node* newTail = new Node(value);
    if(tail == nullptr){
        head = tail = newTail;
    }
    else{
        newTail->prev = tail;
        tail->next = newTail;
        tail = newTail;
    }
    count++;
}

int DoublyLinkedList::size() const{
    return count;
}

void DoublyLinkedList::removeFirst(){
    if(head == nullptr)
        throw "The list is empty!";
    Node* oldHead = head;
    head = head->next;
    if(head!= nullptr)
        head->prev = nullptr;
    else
        tail = nullptr;
    delete oldHead;
    count--;
}

void DoublyLinkedList::removeLast(){
    if(tail == nullptr)
        throw "The list is empty!";
    Node* oldTail = tail;
    tail = tail->prev;
    if(tail!=nullptr)
        tail->next = nullptr;
    else
        head = nullptr;
    delete oldTail;
    count--;
}
