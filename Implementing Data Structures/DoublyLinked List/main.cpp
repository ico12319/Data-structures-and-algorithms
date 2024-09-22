#include <iostream>
#include <queue>
#include "DoublyLinkedList.h"

int main(int argc, const char * argv[]) {
    DoublyLinkedList list;
    list.addFirst(3);
    list.addLast(43);
    list.removeFirst();
    list.print();
    std::cout<<std::endl;
    std::cout<<list.size()<<std::endl;
}
