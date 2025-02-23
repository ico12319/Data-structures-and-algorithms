#include <iostream>
#include <forward_list>

//Задача 3: Даден е едносвъран списък, чийто елементи са числа. Напишете функция rearange, която преподрежда елементите, така че първо да бъдат четните числа, после нечетните. Относителната наредба между числата трябва да се запази. Решението ви трябва да работи за O(n) по време.

struct Node{
    int val;
    Node* next;
    
    Node(int val) : val(val),next(nullptr){}
    Node(int val,Node* next) : val(val),next(next){}
};

void destroy(Node* head){
    Node* curr = head;
    while(curr){
        Node* toDelete = curr;
        curr = curr->next;
        delete toDelete;
    }
}

void push_back(Node*& head,Node*& tail,Node* toAdd){
    if(head == nullptr)
        head = tail = toAdd;
    else{
        tail->next = toAdd;
        tail = toAdd;
    }
}

template<class Predicate>
Node* rearrange(Node* head,const Predicate& pred){
    if(!head) return nullptr;
    Node* true_list_begin = nullptr;
    Node* true_list_end = nullptr;
    Node* false_list_begin = nullptr;
    Node* false_list_end = nullptr;
    
    Node* curr = head;
    while(curr){
        if(pred(curr->val))
            push_back(true_list_begin, true_list_end, curr);
        else
            push_back(false_list_begin, false_list_end, curr);
        curr = curr->next;
    }
    if(!true_list_begin && !false_list_begin)
        return nullptr;
    if(!true_list_begin){
        false_list_end->next = nullptr;
        return false_list_begin;
    }
    if(!false_list_begin){
        true_list_end->next = nullptr;
        return true_list_begin;
    }
    false_list_end->next = nullptr;
    true_list_end->next = false_list_begin;
    return true_list_begin;
}


void rearrange(std::forward_list<int>& list){ // with stl partition for exercise
    std::partition(list.begin(),list.end(),[](int x){return !(x & 1);});
}


int main(int argc, const char * argv[]) {
    auto pred = [](int x) {return !(x & 1);};
    Node* list = new Node(1,new Node(3,new Node(2,new Node(7,new Node(6)))));
    
    Node* parted = rearrange(list, pred);
    while(parted){
        std::cout<<parted->val<<" ";
        parted = parted->next;
    }
    
    destroy(list);
    std::cout<<std::endl;
    
    std::forward_list<int> l;
    l.push_front(6);
    l.push_front(7);
    l.push_front(2);
    l.push_front(3);
    l.push_front(1);
    rearrange(l);
    
    for(auto it = l.begin();it!=l.end();it++)
        std::cout<<*it<<" ";
}
