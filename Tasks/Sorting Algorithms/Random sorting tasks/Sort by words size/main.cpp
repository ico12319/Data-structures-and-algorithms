#include <iostream>

//Task: Sort the words by their length

bool maxPredicate(int num1,int num2){
    return num1 < num2;
}

bool minPredicate(int num1,int num2){
    return num1 > num2;
}

int findElement(const std::vector<std::string>& words ,bool(*pred)(int,int)){
    const size_t size = words.size();
    int predValue = words[0].length();
    for(int i = 1;i<size;i++){
        if(pred(predValue,words[i].length())){
            predValue = words[i].length();
        }
    }
    return predValue;
}


void sortByWordsSize(std::vector<std::string>& words){
    int minValue = findElement(words, minPredicate);
    int maxValue = findElement(words, maxPredicate);
    const size_t size = words.size();
    std::vector<int> count(maxValue - minValue + 1,0);
    for(size_t i = 0;i<size;i++){
        count[words[i].length() - minValue]++;
    }
    
    for(int i = 1;i<maxValue - minValue + 1;i++){
        count[i] += count[i-1];
    }
    
    std::vector<std::string> res(words.size());
    for(int i = words.size() - 1;i>=0;i--){
        std::string word = words[i];
        size_t index = --count[words[i].length() - minValue];
        res[index] = word;
    }
    
    for(int i = 0;i<words.size();i++)
        words[i] = res[i];
}

int main(int argc, const char * argv[]) {
   
    std::vector<std::string> words = {"apple", "a", "banana", "dog", "cat", "ant", "elephant", "fox","b","ev"};
    sortByWordsSize(words);
    for(const auto& el : words)
        std::cout<<el<<" ";
    
}
