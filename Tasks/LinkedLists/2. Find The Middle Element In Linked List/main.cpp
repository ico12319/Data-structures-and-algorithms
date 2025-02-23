#include <stdio.h>
#include <iostream>

// Task: Find the middle element of a singly linked list

struct Node{
    int val;
    Node* next;
    
    Node(int val){
        this->val = val;
        this->next = nullptr;
    }
    Node(int val,Node* next){
        this->val = val;
        this->next = next;
    }
};

int findMiddleElement(Node* head){
    Node* slowPtr = head;
    Node* fastPtr = head;
    
    while(fastPtr!=nullptr && fastPtr->next!=nullptr){
        slowPtr = slowPtr->next;
        fastPtr = fastPtr->next->next;
    }
    return slowPtr->val;
}

int main(){
    Node* l = new Node(1,new Node(4,new Node(2,new Node(1))));
    std::cout<<findMiddleElement(l)<<std::endl;
    
    
}
