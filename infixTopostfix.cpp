#include <iostream>
#include <stack>
#include <string>
#include <map>

// Define the precedence of operators
std::map<char, int> precedence{
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2},
    {'^', 3}
};

// Function to check if a character is an operator
bool isOperator(char c) {
    return precedence.find(c) != precedence.end();
}

// Function to convert infix to postfix
std::string infixToPostfix(const std::string& infix) {
    std::stack<char> operatorStack;
    std::string postfix = "";

    for (char c : infix) {
        if (isalnum(c)) {
            // If it's an operand, add it to the postfix expression
            postfix += c;
        } else if (c == '(') {
            // If it's an open parenthesis, push it onto the operator stack
            operatorStack.push(c);
        } else if (c == ')') {
            // If it's a close parenthesis, pop operators from the stack and add to the postfix
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            if (!operatorStack.empty() && operatorStack.top() == '(') {
                operatorStack.pop();
            }
        } else if (isOperator(c)) {
            // If it's an operator, pop operators from the stack and add to the postfix
            while (!operatorStack.empty() && operatorStack.top() != '(' &&
                   precedence[c] <= precedence[operatorStack.top()]) {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(c);
        }
    }

    // Pop any remaining operators from the stack and add to the postfix
    while (!operatorStack.empty()) {
        postfix += operatorStack.top();
        operatorStack.pop();
    }

    return postfix;
}

int main() {
    std::string infixExpression;
    std::cout << "Enter an infix expression: ";
    std::cin >> infixExpression;

    std::string postfixExpression = infixToPostfix(infixExpression);

    std::cout << "Postfix expression: " << postfixExpression << std::endl;

    return 0;
}
