#include <stdio.h>
#include "Runner.h"

std::vector<std::string> Runner::tokenize(const std::string& input){
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string word;
    
    while (iss >> word)
        tokens.push_back(word);
    
    return tokens;
}

bool Runner::url_criteria(const Tab& tab1,const Tab& tab2){
    if(tab1.getUrl() == tab2.getUrl())
        return tab1.getTimeStamp() < tab2.getTimeStamp();
    
    return tab1.getUrl() < tab2.getUrl();
}

bool Runner::time_criteria(const Tab& tab1, const Tab& tab2){
    if(tab1.getTimeStamp() == tab2.getTimeStamp())
        return tab1.getUrl() < tab2.getUrl();
    
    return tab1.getTimeStamp() < tab2.getTimeStamp();
}

std::string Runner::readCommand() const{
    std::string cmd;
    std::cin>>cmd;
    return cmd;
}

bool Runner::checkCommand(const std::string& cmd1, const std::string& cmd2){
    return cmd1 == cmd2;
}

void Runner::execute(){
    while(true){
        std::string cmd;
        std::getline(std::cin, cmd);
        std::vector<std::string> tokens = tokenize(cmd);
        std::string mainCommand = tokens[0];
        
        if(checkCommand(mainCommand, "END"))
            break;
        
        if(checkCommand(mainCommand,"GO")){
            std::string url = tokens[1];
            browser.go_to(url);
        }
        else if(checkCommand(mainCommand, "INSERT")){
            std::string url = tokens[1];
            browser.open_new_tab(url);
        }
        else if(checkCommand(mainCommand, "BACK"))
            browser.move_back();
        else if(checkCommand(mainCommand, "REMOVE"))
            browser.close_tab();
        else if(checkCommand(mainCommand, "PRINT"))
            browser.print();
        else if(checkCommand(mainCommand, "SORT")){
            std::string criteria = tokens[1];
            if(checkCommand(criteria, "URL"))
                browser.sortBy(url_criteria);
            else if(checkCommand(criteria, "TIME"))
                browser.sortBy(time_criteria);
        }
        else if(checkCommand(mainCommand, "FORWARD"))
            browser.move_forward();
    }
}
