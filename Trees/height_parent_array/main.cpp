#include <iostream>


std::vector<int> getNextLevel(const std::vector<int>& currLevel, const std::vector<int>& parentArray){
    std::vector<int> next_level;
    for(int i = 0;i<parentArray.size();i++){
        auto it = std::find(currLevel.begin(), currLevel.end(), parentArray[i]);
        if(it != currLevel.end())
            next_level.push_back(i);
    }
    return next_level;
    
}

int height(const std::vector<int>& parrent_array){
    std::vector<int> curr_level = {0};
    int level = 0;
    while(!curr_level.empty()){
        curr_level = getNextLevel(curr_level, parrent_array);
        level++;
    }
    return level;
}

int main(int argc, const char * argv[]) {
    std::vector<int> curr_level = {0};
    std::vector<int> parrent = {-1,0,0,1,1,2};
    std::vector<int> next_level = getNextLevel(curr_level,parrent);
    
    std::cout<<height(parrent)<<std::endl;
}
