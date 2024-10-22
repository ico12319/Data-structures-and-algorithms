#include <iostream>


bool isEven(int num){
    return !(num & 1);
}

std::vector<int> merge(std::vector<int>& v1,std::vector<int>& v2){
    std::vector<int> res;
    int index1 = 0;
    int index2 = 0;
    
    while(index1 < v1.size() && index2 < v2.size()){
        if(v1[index1] <= v2[index2]){
            if(isEven(v1[index1])) res.push_back(v1[index1]);
            index1++;
        }
        else if(v1[index1] > v2[index2]){
            if(isEven(v2[index2])) res.push_back(v2[index2]);
            index2++;
        }
    }
    index1 = index2 = 0;
    while(index1 < v1.size() && index2 < v2.size()){
        if(v1[index1] <= v2[index2]){
            if(!isEven(v1[index1])) res.push_back(v1[index1]);
            index1++;
        }
        else if(v1[index1] > v2[index2]){
            if(!isEven(v2[index2])) res.push_back(v2[index2]);
            index2++;
        }
    }
    
    while(index1 < v1.size()){
        if(!isEven(v1[index1]))
            res.push_back(v1[index1]);
        index1++;
    }
    while(index2 < v2.size()){
        if(!isEven(v2[index2]))
            res.push_back(v2[index2]);
        index2++;
    }
    return res;
}

int main(int argc, const char * argv[]) {
    std::vector<int> v1 = {1, 1, 2, 3, 4, 5, 6};
    std::vector<int> v2 = {1, 1, 1, 2, 2, 2, 3, 9};
    std::vector<int> v3 = merge(v1, v2);
    for(const auto& el : v3)
        std::cout<<el<<" ";
}
