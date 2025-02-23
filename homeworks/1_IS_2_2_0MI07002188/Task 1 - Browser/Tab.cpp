#include <stdio.h>
#include "Tab.h"

Tab::Tab(const std::string& url){
    load(url);
}

const std::string Tab::getUrl() const{
    return url;
}

std::time_t Tab::getTimeStamp() const{
    return timeStamp;
}


void Tab::load(const std::string& url){
    this->url = url;
    timeStamp = std::time(nullptr);
}

void Tab::printInfo() const{
    std::cout<<"Url address: " << url<<std::endl;
    std::cout<<"Loaded at Unix timestamp: " << timeStamp << std::endl;
}


