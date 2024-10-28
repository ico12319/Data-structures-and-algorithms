#include <iostream>

//task: partition the elements in the linked list so that even numbers are before odd ones.


struct ListNode{
    int val;
    ListNode* next;
    
    ListNode(int val) : val(val),next(nullptr){}
    ListNode(int val,ListNode* next) : val(val),next(next){}
};


bool isEven(int num){
    return !(num & 1);
}

ListNode* partition(ListNode* head){
    if(!head)
        return nullptr;
    
    ListNode* evens = new ListNode(0);
    ListNode* odds = new ListNode(0);
    ListNode* currEvens = evens;
    ListNode* currOdds = odds;
    ListNode* curr = head;
    while(curr!=nullptr){
        if(isEven(curr->val)){
            currEvens->next = new ListNode(curr->val);
            currEvens = currEvens->next;
        }
        else{
            currOdds->next = new ListNode(curr->val);
            currOdds = currOdds->next;
        }
        curr = curr->next;
    }
    currOdds->next = nullptr;
    currEvens->next = odds->next;
    ListNode* res = evens->next;
    delete evens;
    delete odds;
    return res;
}
int main(int argc, const char * argv[]) {
   
    ListNode* list = new ListNode(2);
    ListNode* parted = partition(list);
    ListNode* curr = parted;
    while(curr){
        std::cout<<curr->val<<" ";
        curr = curr->next;
    }
}
