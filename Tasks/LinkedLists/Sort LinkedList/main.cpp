#include "Execute.h"

struct ListNode{
    int val;
    ListNode* next;
    
    ListNode(int val,ListNode* next) : val(val),next(next){}
    ListNode(int val) : val(val),next(nullptr){}
};

ListNode* get_mid(ListNode* head){
    ListNode* fast = head->next;
    ListNode* slow = head;
    
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

ListNode* merge(ListNode* list1,ListNode* list2){
    if (!list1) return list2;
    if (!list2) return list1;
    ListNode* resultHead = nullptr;
    ListNode* resultIter = nullptr;
    ListNode* firstIter = list1;
    ListNode* secondIter = list2;
    
    if(firstIter->val <= secondIter->val){
        resultHead = firstIter;
        resultIter = firstIter;
        firstIter = firstIter->next;
    }
    else if(firstIter->val > secondIter->val){
        resultHead = secondIter;
        resultIter = secondIter;
        secondIter = secondIter->next;
    }
    
    while(firstIter && secondIter){
        if(firstIter->val <= secondIter->val){
            resultIter->next = firstIter;
            firstIter = firstIter->next;
        }
        else{
            resultIter->next = secondIter;
            secondIter = secondIter->next;
        }
        resultIter = resultIter->next;
    }
    if(firstIter)
        resultIter->next = firstIter;
    if(secondIter)
        resultIter->next = secondIter;
    
    return resultHead;
}

ListNode* mergeSort(ListNode* list){
    if(!list || !list->next)
        return list;
    
    ListNode* mid = get_mid(list);
    ListNode* left = list;
    ListNode* right = mid->next;
    mid->next = nullptr;
    
    left = mergeSort(left);
    right = mergeSort(right);
    
    return merge(left, right);
}

int main(int argc, const char * argv[]) {
    
    ListNode* list1 = new ListNode(22,new ListNode(1,new ListNode(0,new ListNode(101,new ListNode(3)))));
   
    ListNode* merged = mergeSort(list1);
    ListNode* curr = merged;
    while(curr){
        std::cout<<curr->val<<" ";
        curr = curr->next;
    }

}
