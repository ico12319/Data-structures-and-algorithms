#include <stdio.h>
#include "LinkedList.h"

LinkedList::~LinkedList(){
    destroy();
}

void LinkedList::destroy(){
    Node* curr = head;
    while(curr!=nullptr){
        Node* nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
    head = nullptr;
    tail = nullptr;
}

LinkedList::LinkedList(){
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;
}

void LinkedList::print() const{
    Node* curr = head;
    while(curr!=nullptr){
        std::cout<<curr->val<<" ";
        curr = curr->next;
    }
}

void LinkedList::addFirst(int value){
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

void LinkedList::addLast(int value){
    Node* newTail = new Node(value);
    if(tail == nullptr)
        head = tail = newTail;
    else{
        newTail->prev = tail;
        tail->next = newTail;
        tail = newTail;
    }
    count++;
}
