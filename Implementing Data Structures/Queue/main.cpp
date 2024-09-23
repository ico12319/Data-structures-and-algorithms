#include "Queue.hpp"


int main(int argc, const char * argv[]) {
    Queue<int>q;
    q.enqueue(2);
    q.enqueue(45);
    q.enqueue(65);
    q.dequeue();
    std::cout<<q.top()<<std::endl;
    q.print();
}
