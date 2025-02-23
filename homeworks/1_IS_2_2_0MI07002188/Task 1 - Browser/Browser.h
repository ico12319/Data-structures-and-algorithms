#pragma once
#include "Tab.h"
#include "DoublyLinkedList.hpp"

class Browser{
private:
    DoublyLinkedList<Tab> tabs;
    DoublyLinkedList<Tab>::iterator currTab;
    
public:
    Browser();
    void move_back();
    void move_forward();
    void open_new_tab(const std::string& new_tab_url);
    void close_tab();
    void print();
    void go_to(const std::string& tab_url);
    
    template<class Pred>
    void sortBy(const Pred& pred){
        tabs.mergeSort(pred);
        currTab = tabs.begin();
    }
};
