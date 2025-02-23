#include <iostream>
#include <stack>
#include <string>

bool isOperator(char ch){
    return ch == '*' || ch == '-' || ch == '+' || ch == '/';
}

bool isDigit(char ch){
    return ch >= '0' && ch <= '9';
}

int applyOperator(char ch,int first,int second){
    if(ch == '*') return first * second;
    if(ch == '/') return first / second;
    if(ch == '+') return first + second;
    if(ch == '-') return first - second;
    
    throw std::invalid_argument("Invalid operation!");
}

int turnIntoNumber(std::string& str,int& index,size_t size){
    int num = 0;
    while(index < size && isDigit(str[index])){
        num = num * 10 + (str[index] - '0');
        index++;
    }
    return num;
}
int evaluateRPN(std::string& str){
    const size_t size = str.length();
    std::stack<int> stack;
    for(int i = 0;i<size;i++){
        if(isOperator(str[i])){
            int second = stack.top();
            stack.pop();
            int first = stack.top();
            stack.pop();
            int result = applyOperator(str[i], first, second);
            stack.push(result);
        }
        else if(isDigit(str[i])){
            int num = turnIntoNumber(str, i, size);
            stack.push(num);
        }
        else
            continue;
    }
    return stack.top();
}

int main(int argc, const char * argv[]) {
    std::string str = "1 2 3 + -";
    std::cout<<evaluateRPN(str)<<std::endl;// 1 − (2 + 3)
}
