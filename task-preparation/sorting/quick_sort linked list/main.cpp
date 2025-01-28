#include <iostream>

struct node{
    int val;
    node* next;
    
    node(int val) : val(val),next(nullptr){}
};

void destroy(node* head){
    node* curr = head;
    while(curr){
        node* to_delete = curr;
        curr = curr->next;
        delete to_delete;
    }
}

void push_back(node*& head,node*& tail,node* to_add){
    if(!head)
        head = tail = to_add;
    else{
        tail->next = to_add;
        tail = to_add;
    }
}

template<class predicate>
std::pair<node*,node*> partition(node* list,const predicate& pred){
    node* true_begin = nullptr;
    node* true_end = nullptr;
    node* false_begin = nullptr;
    node* false_end = nullptr;
    
    while(list){
        if(pred(list->val))
            push_back(true_begin, true_end, list);
        else
            push_back(false_begin, false_end, list);
        list = list->next;
    }
    if(true_end)
        true_end->next = nullptr;
    if(false_end)
        false_end->next = nullptr;
    
    return std::make_pair(true_begin, false_begin);
}

std::pair<node*,node*> concat(node* left_begin,node* left_end,node* right_begin,node* right_end){
    if(!left_begin) return std::make_pair(right_begin, right_end);
    if(!right_begin) return std::make_pair(left_begin, left_end);
    
    left_end->next = right_begin;
    return std::make_pair(left_begin, right_end);
}

std::pair<node*,node*> quick_sort(node* list){
    if(!list || !list->next)
        return std::make_pair(list, list);
    int pivot = list->val;
    auto partition_result = partition(list, [&pivot](int el){return el < pivot;});
    
    node* pivot_ptr = partition_result.second;
    auto left_to_concat = quick_sort(partition_result.first);
    auto right_to_concat = quick_sort(partition_result.second->next);
    pivot_ptr->next = right_to_concat.first;
    right_to_concat.first = pivot_ptr;
    if(!right_to_concat.second)
        right_to_concat.second = pivot_ptr;
    
    return concat(left_to_concat.first, left_to_concat.second, right_to_concat.first, right_to_concat.second);
}

void print(node* head){
    node* curr = head;
    while(curr){
        std::cout<<curr->val<<" ";
        curr = curr->next;
    }
}


int main(int argc, const char * argv[]) {
    node* head = new node(12);
    head->next = new node(99);
    head->next->next = new node(0);
    head->next->next->next = new node(1);
    head->next->next->next->next = new node(0);
    auto res = quick_sort(head);
    print(res.first);
    destroy(res.first);
    
}
