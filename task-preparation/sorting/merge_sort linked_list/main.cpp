#include <iostream>

struct node{
    int val;
    node* next;
    
    node(int val) : val(val),next(nullptr){}
};

void push_back(node*& head,node*& tail,node* to_add){
    if(!head)
        head = tail = to_add;
    else{
        tail->next = to_add;
        tail = to_add;
    }
}

node* merge(node* list1,node* list2){
    node* merged_begin = nullptr;
    node* merged_end = nullptr;
    
    while(list1 && list2){
        if(list1->val < list2->val){
            push_back(merged_begin, merged_end, list1);
            list1 = list1->next;
        }
        else{
            push_back(merged_begin, merged_end, list2);
            list2 = list2->next;
        }
    }
    
    if(list1 && merged_end)
        merged_end->next = list1;
    if(list2 && merged_end)
        merged_end->next = list2;
    
    return merged_begin;
}


node* find_mid(node* head){
    node* fast = head->next;
    node* slow = head;
    while(fast && fast->next){
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}


node* merge_sort(node* list){
    if(!list || !list->next)
        return list;
    node* mid = find_mid(list);
    node* left = list;
    node* right = mid->next;
    mid->next = nullptr;
    
    left = merge_sort(left);
    right = merge_sort(right);
    
    return merge(left,right);
}

void print(node* head){
    node* curr = head;
    while(curr){
        std::cout<<curr->val<<" ";
        curr = curr->next;
    }
}

void destroy(node* head){
    if(!head)
        return;
    while(head){
        node* to_delete = head;
        head = head->next;
        delete to_delete;
    }
}

int main(int argc, const char * argv[]) {
    node* head = new node(2);
    head->next = new node(0);
    head->next->next = new node(1);
    head->next->next->next = new node(3);
    head->next->next->next->next = new node(90);
    
    head = merge_sort(head);
    print(head);
    destroy(head);
}
