#include <iostream>

//Даден е двусвързан списък с четен брой елементи. Всеки елемент представлява едносвързан списък от числа в интервала [0,9]. Всеки едносвързан списък сам по себе си интерпретира число, чиито цифри са елементите на списъка в същия ред. ( 3->4->5 е числото 345). Напишете функция, която получава като параметър двусвързан списък от този вид и проверява дали първите n/2 (където n е дължината на списъка) числа образуват растяща редица и вторите n/2 числа - намаляваща.

struct singly_node{
    int val;
    singly_node* next;
    
    singly_node(int val) : val(val),next(nullptr){}
    singly_node(int val,singly_node* next) : val(val),next(next){}
};

struct doubly_node{
    singly_node* val;
    doubly_node* next;
    doubly_node* prev;
    
    doubly_node(singly_node* val) : val(val),next(nullptr),prev(nullptr){}
    doubly_node(singly_node* val,doubly_node* next,doubly_node* prev) : val(val),next(next),prev(prev){}
};


void destroy_singly(singly_node* head){
    singly_node* curr = head;
    while(curr){
        singly_node* toDelete = curr;
        curr = curr->next;
        delete toDelete;
    }
}


void destory_doubly(doubly_node* head){
    doubly_node* curr = head;
    while(curr){
        destroy_singly(curr->val);
        doubly_node* toDelete = curr;
        curr = curr->next;
        delete toDelete;
    }
}

void print_singly(singly_node* head){
    if(!head) return;
    singly_node* curr = head;
    while(curr){
        std::cout<<curr->val<<" ";
        curr = curr->next;
    }
    std::cout<<std::endl;
}


int extract_number(singly_node* head){
    if(!head) return INT_MIN;
    
    singly_node* curr = head;
    int res = 0;
    while(curr){
        (res*=10) += curr->val;
        curr = curr->next;
    }
    return res;
}


doubly_node* find_mid(doubly_node* head){
    if(!head) return head;
    doubly_node* slow = head;
    doubly_node* fast = head->next;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

template<class Comparator>
bool answers_to_pred(doubly_node* head,const Comparator& comp,doubly_node* end){
    doubly_node* curr = head;
    while(curr!=end && curr->next){
        if(comp(extract_number(curr->val), extract_number(curr->next->val)))
            return false;
        curr = curr->next;
    }
    return true;
}

bool task2_solution(doubly_node* head){
    doubly_node* mid = find_mid(head);
    return answers_to_pred(head, std::greater<int>(), mid) && answers_to_pred(mid->next, std::less<int>(), nullptr);
}

int main(int argc, const char * argv[]) {
    singly_node* num1 = new singly_node(1, new singly_node(2, new singly_node(3)));
    singly_node* num2 = new singly_node(2, new singly_node(3, new singly_node(4)));
    singly_node* num3 = new singly_node(1);
        
    singly_node* num4 = new singly_node(4, new singly_node(3, new singly_node(2)));
    singly_node* num5 = new singly_node(3, new singly_node(9, new singly_node(1)));
    singly_node* num6 = new singly_node(1);
    

    doubly_node* dn1 = new doubly_node(num1);
    dn1->next = new doubly_node(num2);
    dn1->prev = nullptr;
    dn1->next->next = new doubly_node(num3);
    dn1->next->prev = dn1;
    dn1->next->next->next = new doubly_node(num4);
    dn1->next->next->prev = dn1->next;
    dn1->next->next->next->next = new doubly_node(num5);
    dn1->next->next->next->prev = dn1->next->next;
    dn1->next->next->next->next->next = new doubly_node(num6);
    dn1->next->next->next->next->prev = dn1->next->next->next;
    dn1->next->next->next->next->next->next = nullptr;
    dn1->next->next->next->next->next->prev = dn1->next->next->next->next;
    
    std::cout<<task2_solution(dn1)<<std::endl;
    destory_doubly(dn1);
}
