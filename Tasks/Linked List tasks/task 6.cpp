#include <iostream>

//Задача 6 (Flatten): Даден е указател към началото на двойно свързан списък с четен брой елементи, които имат и още един указател - child. Този указател сочи към друг отделен двойно свързан списък.В първата половина на списъка, child указателите на елементите са празни. Но във втората се е получила аномалия на списъка, и някои елементи имат child указатели, които не са празни.По този начин втората половина на списъка се е превърнала в списък на няколко нива.Нашата задача е да превърнем списъка в списък на едно ниво.

struct Node{
    int val;
    Node* next;
    Node* prev;
    Node* child;
    
    Node(int val) : val(val),next(nullptr),prev(nullptr),child(nullptr){}
};


void destroy(Node* curr){
    while(curr){
        Node* toDelete = curr;
        curr =  curr->next;
        delete toDelete;
    }
}

Node* find_mid(Node* head){
    if(!head) return head;
    
    Node* slow = head;
    Node* fast = head;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}


Node* flatten(Node* head){
    Node* curr = find_mid(head);
    while(curr){
        if(curr->child){
            Node* currNext = curr->next;
            Node* currChild = curr->child;
            
            curr->next = currChild;
            currChild->prev = curr;
            curr->child = nullptr;
            
            while(currChild->next)
                currChild = currChild->next;
            if(currNext){
                currChild->next = currNext;
                currNext->prev = currChild;
            }
        }
        curr = curr->next;
        
    }
    return head;
}
int main(int argc, const char * argv[]) {
        Node* n1 = new Node(1);
        Node* n2 = new Node(2);
        Node* n3 = new Node(3);
        Node* n4 = new Node(4);
        Node* n7 = new Node(7);
        Node* n8 = new Node(8);
        Node* n9 = new Node(9);
        Node* n10 = new Node(10);
        Node* n11 = new Node(11);
        Node* n12 = new Node(12);

        n1->next = n2;
        n2->prev = n1;
        n2->next = n3;
        n3->prev = n2;
        n3->next = n4;
        n4->prev = n3;

        n3->child = n7;
        n7->next = n8;
        n8->prev = n7;
        n8->next = n9;
        n9->prev = n8;
        n9->next = n10;
        n10->prev = n9;

        n8->child = n11;
        n11->next = n12;
        n12->prev = n11;
    Node* flat = flatten(n1);
    while(flat){
        std::cout<<flat->val<<" ";
        flat = flat->next;
    }
    destroy(n1);
}
