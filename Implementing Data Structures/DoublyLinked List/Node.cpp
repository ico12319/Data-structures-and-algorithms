#include <stdio.h>
#include "Node.h"

Node::Node(int value){
    this->value = value;
    this->next = this->prev = nullptr;
}

void Node::print() const{
    std::cout<<"<-"<<value<<"->";
}

