#include <iostream>

struct ListNode{
    ListNode* next;
    int val;
    
    ListNode(int val) : val(val) , next(nullptr){}
    ListNode(int val, ListNode* next) : val(val), next(next){}
};

ListNode* merge(ListNode* list1,ListNode* list2){
    ListNode* dummy = new ListNode(0);
    ListNode* curr = dummy;
    while(list1!=nullptr && list2!=nullptr){
        if(list1->val <= list2->val){
            curr->next = list1;
            list1 = list1->next;
        }
        else{
            curr->next = list2;
            list2 = list2->next;
        }
        curr = curr->next;
    }
    if(list1!=nullptr)
        curr->next = list1;
    else
        curr->next = list2;
    
    ListNode* res = dummy->next;
    delete dummy;
    return res;
}

ListNode* getMid(ListNode* head){
    ListNode* slow = head;
    ListNode* fast = head->next;
    while(fast!= nullptr && fast->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

ListNode* mergeSort(ListNode* list){
    if(list == nullptr || list->next == nullptr)
        return list;
    
    ListNode* secondHalf = getMid(list)->next;
    getMid(list)->next = nullptr;
    ListNode* left = mergeSort(list);
    ListNode* right = mergeSort(secondHalf);
    
    return merge(left,right);
    
}

int main(int argc, const char * argv[]) {
    ListNode* list = new ListNode(20, new ListNode(14, new ListNode(7,new ListNode(77,new ListNode(1)))));
    std::cout<<getMid(list)->val<<std::endl;
    ListNode* curr = mergeSort(list);
    while(curr!=nullptr){
        std::cout<<curr->val<<" ";
        curr = curr->next;
    }
    delete list;
}
