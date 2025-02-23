#include <iostream>


struct node{
    int val;
    node* next;
    
    node(int val) : val(val),next(nullptr){}
    node(int val,node* next) : val(val),next(next){}
};

void print(node* head){
    node* curr = head;
    while(curr){
        std::cout<<curr->val<<" ";
        curr = curr->next;
    }
    std::cout<<std::endl;
}

void destroy(node* head){
    if(!head)
        return;
    while(head){
        node* curr = head;
        head = head->next;
        delete curr;
    }
}

node* generate_random_list(size_t length){
    if(length == 0 || length < 0)
        return nullptr;
    return new node(std::rand() % 100,generate_random_list(length - 1));
}


void push_back(node*& head,node*& tail,node* to_add){
    if(!head)
        head = tail = to_add;
    else{
        tail->next = to_add;
        tail = to_add;
    }
}
// 1 1 1 1 1 2 2 3
node* remove_consecutive_duplicates(node* head){
    node* new_list_head = nullptr;
    node* new_list_end = nullptr;
    node* curr = head;
    
    while(curr){
        if(curr->next && curr->val == curr->next->val){
            while(curr->next && curr->val == curr->next->val){
                node* to_delete = curr;
                curr = curr->next;
                delete to_delete;
            }
            node* to_delete = curr;
            curr = curr->next;
            delete to_delete;
        }
        else{
            push_back(new_list_head, new_list_end, curr);
            curr = curr->next;
        }
    }
    if(new_list_end)
        new_list_end->next = nullptr;
    
    return new_list_head;
}


node* merge(node* list1,node* list2){
    node* merged_list_begin = nullptr;
    node* merged_list_end = nullptr;
    
    while(list1 && list2){
        if(list1->val < list2->val){
            push_back(merged_list_begin, merged_list_end, list1);
            list1 = list1->next;
        }
        else{
            push_back(merged_list_begin, merged_list_end, list2);
            list2 = list2->next;
        }
    }
    if(list1 && merged_list_end)
        merged_list_end->next = list1;
    
    if(list2 && merged_list_end)
        merged_list_end->next = list2;
    
    return merged_list_begin;
}

int main() {
    node* head = new node(1);
    head->next = new node(2);
    head->next->next = new node(4);
    
    node* head2 = new node(0);
    head2->next = new node(0);
    head2->next->next = new node(1);
    head2->next->next->next = new node(19);
    head2->next->next->next->next = new node(20);
    
    head = merge(head, head2);
    print(head);
    
}
