#include <iostream>
#include "priority_queue.h"


int main(int argc, const char * argv[]) {
    priority_queue pq;
    pq.push(1);
    pq.push(12);
    pq.push(44);
    pq.push(0);
    
    while(!pq.is_empty()){
        std::cout<<pq.top()<<" ";
        pq.pop();
    }
}
