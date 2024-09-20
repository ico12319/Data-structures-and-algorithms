#include <iostream>
#include <stack>
#include <string>

bool isClosingBracket(char ch){
    return ch == ')' || ch == '}' || ch == ']';
}

bool isOpeningBracket(char ch){
    return ch == '(' || ch == '{' || ch == '[';
}

bool areMatchingBrackets(char bracket1,char bracket2){
    return (bracket1 == '(' && bracket2 == ')') || (bracket1 == '{' && bracket2 == '}') || (bracket1 == '[' || bracket2 == ']');
}

bool isBalancedExpression(const std::string& str){
    const size_t size = str.length();
    if(size <= 1)
        return false;
    std::stack<char> brackets;
    for(int i = 0;i<size;i++){
        if(isOpeningBracket(str[i])){
            brackets.push(str[i]);
        }
        else if(isClosingBracket(str[i])){
            if(brackets.size() == 0)
                return false;
            
            char curr = brackets.top();
            if(areMatchingBrackets(curr, str[i]) && brackets.size() > 0)
                brackets.pop();
            else
                return false;
        }
    }
    return brackets.size() == 0;
}

int main(int argc, const char * argv[]) {
    std::string expr = "(())]";
    std::string expr2 = "([]{})";
    std::string expr3 = "({}([]))";
    std::cout<<isBalancedExpression(expr)<<std::endl;
    std::cout<<isBalancedExpression(expr2)<<std::endl;
    std::cout<<isBalancedExpression(expr3)<<std::endl;
}
