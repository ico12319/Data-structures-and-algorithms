#include <iostream>

//Task:
//Дадени са два сортирани вектора от числа. Напишете програма, която обединява двата вектора в един, като в новия вектор всички числа, кратни на 3, трябва да предхождат всички останали числа, като и двете групи трябва да са в сортиран вид.

bool isDivisibleBy3(int num){
    return num % 3 == 0;
}

std::vector<int> merge(std::vector<int>& v1,std::vector<int>& v2){
    int index1 = 0;
    int index2 = 0;
    std::vector<int> res;
    while(index1 < v1.size() && index2 < v2.size()){
        if(v1[index1] <= v2[index2]){
            if(isDivisibleBy3(v1[index1])) res.push_back(v1[index1]);
            index1++;
        }
        else if(v1[index1] > v2[index2]){
            if(isDivisibleBy3(v2[index2])) res.push_back(v2[index2]);
            index2++;
        }
    }
    while(index1 < v1.size()){
        if(isDivisibleBy3(v1[index1])) res.push_back(v1[index1]);
        index1++;
    }
    while(index2 < v2.size()){
        if(isDivisibleBy3(v2[index2])) res.push_back(v2[index2]);
        index2++;
    }
    index1 = index2 = 0;
    while(index1 < v1.size() && index2 < v2.size()){
        if(v1[index1] <= v2[index2]){
            if(!isDivisibleBy3(v1[index1])) res.push_back(v1[index1]);
            index1++;
        }
        else if(v1[index1] > v2[index2]){
            if(!isDivisibleBy3(v2[index2])) res.push_back(v2[index2]);
            index2++;
        }
    }
    while(index1 < v1.size()){
        if(!isDivisibleBy3(v1[index1])) res.push_back(v1[index1]);
        index1++;
    }
    while(index2 < v2.size()){
        if(!isDivisibleBy3(v2[index2])) res.push_back(v2[index2]);
        index2++;
    }
    return res;
}


int main(int argc, const char * argv[]) {
    std::vector<int> v1 = {1, 3, 6, 8, 10, 15};
    std::vector<int> v2 = {2, 3, 9, 12, 14, 18, 21};
    std::vector<int> res = merge(v1, v2);
    for(const auto& el : res)
        std::cout<<el<<" ";
}
