#include <iostream>

constexpr size_t ALPHABET_SIZE = 26;
void countSortForWords(std::vector<std::string>& words){
    std::vector<int> count(ALPHABET_SIZE,0);
    for(int i = 0;i<words.size();i++){
        count[words[i][0] - 'a']++;
    }
    for(int i = 1;i<ALPHABET_SIZE;i++)
        count[i]+=count[i-1];
    
    int index = 0;
    while(index < words.size()){
        int correctIndex = count[words[index][0] - 'a'] - 1;

        if (index == correctIndex || count[words[index][0] - 'a'] <= index)
                index++;
        else {
            std::swap(words[index], words[correctIndex]);
            count[words[correctIndex][0] - 'a']--;
        }
    }
}

int main(int argc, const char * argv[]) {
    std::vector<std::string> words = {"banana","apple","alpaca","cat","biscuit","elephant","string","house","progress","trousers","mouse"};
    countSortForWords(words);
    for(const auto& el : words)
        std::cout<<el<<" ";
    
}
