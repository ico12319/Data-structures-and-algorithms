#include <iostream>
#include <queue>

//generate all bool vectors with queue

std::vector<std::string> generate_bool_vectors(int size){
    std::queue<std::string> q;
    std::vector<std::string> result;
    q.push("");
    while(!q.empty()){
        auto curr = q.front();
        q.pop();
        if(curr.length() == size)
            result.push_back(curr);
        else{
            q.push(curr + '0');
            q.push(curr + '1');
        }
    }
    return result;
}


void print_vectors(size_t size){
    auto vectors = generate_bool_vectors(size);
    for(const auto& vector : vectors)
        std::cout<<vector<<std::endl;
}


int main(){
    
    print_vectors(3);
}
