#include <iostream>

//Task:
//Даден е вектор от вектори, които са предварително сортирани. Напишете програма която merge-ва всичките 'подвектори' в един голям вектор, който също е в сортиран вид.

std::vector<int> merge(std::vector<int>& nums1,std::vector<int>& nums2){
    std::vector<int> res;
    int index1 = 0;
    int index2 = 0;
    while(index1 < nums1.size() && index2 < nums2.size()){
        if(nums1[index1] < nums2[index2]){
            res.push_back(nums1[index1]);
            index1++;
        }
        else{
            res.push_back(nums2[index2]);
            index2++;
        }
    }
    
    while(index1 < nums1.size())
        res.push_back(nums1[index1++]);
    while(index2 < nums2.size())
        res.push_back(nums2[index2++]);
    
    return res;
}

std::vector<int> mergeKSortedVectors(std::vector<std::vector<int>>& sortedV){
    std::vector<int> res = sortedV[0];
    for(int i = 1;i<sortedV.size();i++)
        res = merge(res, sortedV[i]);
    return res;
    
}

int main(int argc, const char * argv[]) {
    std::vector<std::vector<int>> v = {{9, 10, 12}, {14, 17, 18}, {10, 11, 12, 22, 90}, {13}, {16, 18}};
    std::vector<int> res = mergeKSortedVectors(v);
    for(const auto& el : res)
        std::cout<<el<<" ";
}
