#include <stdio.h>
#include "Browser.h"

Browser::Browser(){
    Tab t;
    tabs.push_back(t);
    currTab = tabs.begin();
}


void Browser::open_new_tab(const std::string& new_tab_url){
    Tab newTab(new_tab_url);
    currTab = tabs.insert_after(currTab, newTab);
}

void Browser::close_tab(){
    if(tabs.getSize() <= 1)
        currTab->load("about:blank");
    else{
        DoublyLinkedList<Tab>::iterator toRemove = currTab;
        DoublyLinkedList<Tab>::iterator next = currTab;
        next++;
        if(next != tabs.end())
            currTab = next;
        else
            currTab--;
        
        tabs.remove(toRemove);
    }
}

void Browser::move_back(){
    if(currTab != tabs.begin() && tabs.getSize() > 1)
        currTab--;
    else
        return;
}

void Browser::move_forward(){
    if(currTab == --tabs.end())
        return;
    if(tabs.getSize() > 1)
        currTab++;
}

void Browser::print(){
    DoublyLinkedList<Tab>::iterator it = tabs.begin();
    for(;it!=tabs.end();it++){
        if(it == currTab)
            std::cout<<">";
        (*it).printInfo();
    }
}


void Browser::go_to(const std::string& tab_url){
    currTab->load(tab_url);
}


