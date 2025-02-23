#include <iostream>
#include <queue>
#include <stack>


int precedence(char s1){
    if(s1 == '*' || s1 == '/') return 2;
    if(s1 == '+' || s1 == '-') return 1;
    return 0;
}

bool is_digit(char s){
    return s >= '0' && s <= '9';
}

bool is_opening_bracket(char s){
    return s == '(';
}

bool is_closing_bracket(char s){
    return s == ')';
}

bool is_operator(char s){
    return s == '+' || s == '-' || s == '*' || s == '/';
}

std::vector<char> shunting_yard(const std::string& str){
    std::vector<char>output;
    std::stack<char> operations;
    for(int i = 0;i<str.length();i++){
        if(is_digit(str[i]))
            output.push_back(str[i]);
        else if(is_operator(str[i])){
            while(!operations.empty() && operations.top() != '(' && precedence(operations.top()) >= precedence(str[i])){
                output.push_back(operations.top());
                operations.pop();
            }
            operations.push(str[i]);
        }
        else if(is_opening_bracket(str[i]))
            operations.push(str[i]);
        else if(is_closing_bracket(str[i])){
            while(!operations.empty() && operations.top() != '('){
                output.push_back(operations.top());
                operations.pop();
            }
            operations.pop();
        }
    }
    while(!operations.empty()){
        output.push_back(operations.top());
        operations.pop();
    }
    return output;
}

int apply_operation(char operation,int num1,int num2){
    if(operation == '*') return num1 * num2;
    if(operation == '/') return num1 / num2;
    if(operation == '+') return num1 + num2;
    if(operation == '-') return num1 - num2;
    
    return 0;
}

int eval(std::vector<char>& expr){
    std::stack<int> numbers;
    
    for(int i = 0;i<expr.size();i++){
        if(is_digit(expr[i]))
            numbers.push(expr[i] - '0');
        else{
            char operation = expr[i];
            int num2 = numbers.top();
            numbers.pop();
            int num1 = numbers.top();
            numbers.pop();
            int new_num = apply_operation(operation, num1, num2);
            numbers.push(new_num);
        }
    }
    return numbers.top();
}


int calculator(const std::string& str){
    std::vector<char> expr = shunting_yard(str);
    return eval(expr);
}

int main(int argc, const char * argv[]) {
    std::string str = "((2+1)*3)";
    std::cout<<calculator(str)<<std::endl;
}
