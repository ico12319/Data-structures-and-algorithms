#include <iostream>
#include <queue>


// Генерирайте всички възможни троични вектори с дължина n
std::vector<std::string> generate_triplets(size_t n){
    std::vector<std::string> result;
    std::queue<std::string> q;
    q.push("");
    while(!q.empty()){
        auto curr = q.front();
        q.pop();
        if(curr.length() == n)
            result.push_back(curr);
        else{
            q.push(curr + "0");
            q.push(curr + "1");
            q.push(curr + "2");
        }
    }
    return result;
}

void print_triplets(size_t n){
    auto triplets = generate_triplets(n);
    for(const auto& triplet : triplets)
        std::cout<<triplet<<" ";
}

//Генерирайте всички възможни булеви вектори с дължина n, които съдържат точно k единици (1) и n - k нули (0).

bool contains_k_times_target(const std::string& str,size_t k,char target){
    int count = 0;
    for(const auto& el : str){
        if(el == target)
            count++;
    }
    return count == k;
}

std::vector<std::string> generate_all_bool_vectors_with_k_ones(size_t size,size_t k){
    std::vector<std::string> result;
    std::queue<std::string> q;
    q.push("");
    while(!q.empty()){
        auto curr = q.front();
        q.pop();
        if(curr.length() == size){
            if(contains_k_times_target(curr, k, '1'))
                result.push_back(curr);
            else
                continue;
        }
        else{
            q.push(curr + "0");
            q.push(curr + "1");
        }
    }
    return result;
}

void print_bool_vectors_with_k_ones(size_t size,size_t k){
    auto vectors = generate_all_bool_vectors_with_k_ones(size, k);
    for(const auto& vector : vectors)
        std::cout<<vector<<" ";
}


int main(){
    print_bool_vectors_with_k_ones(3, 2);
}
