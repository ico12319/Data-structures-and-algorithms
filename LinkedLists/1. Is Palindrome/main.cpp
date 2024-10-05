#include <stdio.h>
#include <iostream>
#include "LinkedList.h"

// Task: You are given a Doubly Linked List. Determine whether it is a palindrome or not.
// Example of palindrome: 1 -> 4 -> 1

bool isPalindrome(LinkedList& list){
    if(list.count == 0 || list.count == 1)
        return true;
    
    Node* left = list.head;
    Node* right = list.tail;
    
    while(left!=right && left->prev != right){
        if(left->val != right->val)
            return false;
        else{
            left = left->next;
            right = right->prev;
        }
    }
    return true;
    
}

int main(){
    LinkedList list;
    list.addFirst(5);
    list.addLast(1);
    list.addLast(4);
    list.addLast(1);
    list.addLast(5);
    std::cout<<isPalindrome(list)<<std::endl;
}
