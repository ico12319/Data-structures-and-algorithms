#include "k-ary heap.hpp"


int main(int argc, const char * argv[]) {
   
    std::vector<int> v = {1,99,101,5,200,0,1,500,6,2};
    k_ary_heap<int> heap(4,v);
    while(!heap.empty()){
        std::cout<<heap.top()<<" ";
        heap.pop();
    }
    
    k_ary_heap<int,std::greater<int>> heap2(2);
    for(int i = 0;i<1000;i++)
        heap2.push(i);
    std::cout<<std::endl;
    
    while(!heap2.empty()){
        std::cout<<heap2.top()<<" ";
        heap2.pop();
    }
}
