#pragma once
#include <iostream>

class Tab{
private:
    std::string url = "about:blank";
    std::time_t timeStamp;
    
public:
    Tab() = default;
    Tab(const std::string& url);
    void load(const std::string& url);
    const std::string getUrl() const;
    std::time_t getTimeStamp() const;
    
    void printInfo() const;
};
