#pragma once
#include "Browser.h"
#include <sstream>

class Runner{
private:
    Browser browser;
    
    
    static bool url_criteria(const Tab& tab1,const Tab& tab2);
    static bool time_criteria(const Tab& tab1,const Tab& tab2);
    std::string readCommand() const;
    static bool checkCommand(const std::string& cmd1,const std::string& cmd2);
    static std::vector<std::string> tokenize(const std::string& input);
    
public:
    void execute();
    
};
