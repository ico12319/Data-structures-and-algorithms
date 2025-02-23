#include <iostream>
#include <forward_list>
#include <unordered_set>

struct node{
    int val;
    node* next;
    
    node(int val) : val(val),next(nullptr){}
};

void destroy(node* head){
    while(head){
        node* to_delete = head;
        head = head->next;
        delete to_delete;
    }
}

node* remove_node(node* head,node* to_delete){
    node** curr = &head;
    while(*curr){
        if(*curr == to_delete){
            node* removed = *curr;
            *curr = (*curr)->next;
            delete removed;
            break;
        }
        curr = &(*curr)->next;
    }
    return head;
}

void print_list(node* head){
    node* curr = head;
    while(curr){
        std::cout<<curr->val<<" ";
        curr = curr->next;
    }
}

node* remove_duplicates(node* head){
    std::unordered_set<int> values;
    node** curr = &head;
    while(*curr){
        if(values.contains((*curr)->val)){
            node* to_delete = *curr;
            *curr = (*curr)->next;
            delete to_delete;
        }
        else{
            values.insert((*curr)->val);
            curr = &(*curr)->next;
        }
    }
    return head;
}


node* remove_consecutive(node* head){
    node** curr = &head;
    while(*curr){
        if((*curr)->next && (*curr)->val == (*curr)->next->val){
            while((*curr)->next && (*curr)->val == (*curr)->next->val){
                node* to_delete = *curr;
                *curr = (*curr)->next;
                delete to_delete;
            }
            node* to_delete = *curr;
            *curr = (*curr)->next;
            delete to_delete;
        }
        else
            curr = &(*curr)->next;
    }
    return head;
}

int main(int argc, const char * argv[]) {
    
    
    node* head = new node(1);
    head->next = new node(1);
    head->next->next = new node(1);
    head->next->next->next = new node(1);
    head->next->next->next->next = new node(3);
    head->next->next->next->next->next = new node(3);
    head->next->next->next->next->next->next = new node(1);
    head->next->next->next->next->next->next->next = new node(2);
    head->next->next->next->next->next->next->next->next = new node(5);
    head = remove_consecutive(head);
    print_list(head);
    
    destroy(head);
}

