#include <iostream>
#include <stack>
#include <string>
#include <cctype>

using namespace std;


int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int performOperation(char operation, int operand1, int operand2) {
    switch (operation) {
    case '+': return operand1 + operand2;
    case '-': return operand1 - operand2;
    case '*': return operand1 * operand2;
    case '/':
        if (operand2 == 0) {
            cout << "tak niemona" << endl;
            exit(EXIT_FAILURE);
        }
        return operand1 / operand2;
    default: return 0;
    }
}


string infixToPostfix(const string& expression) {
    stack<char> operators;
    string postfix;
    for (char ch : expression) {
        if (isspace(ch)) continue;
        if (isdigit(ch)) {
            postfix += ch;
        }
        else if (ch == '(') {
            operators.push(ch);
        }
        else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop();
        }
        else {
            while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(ch);
        }
    }
    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }
    return postfix;
}


int evaluatePostfix(const string& postfix) {
    stack<int> operands;
    for (char ch : postfix) {
        if (isdigit(ch)) {
            operands.push(ch - '0');
        }
        else {
            int operand2 = operands.top(); operands.pop();
            int operand1 = operands.top(); operands.pop();
            int result = performOperation(ch, operand1, operand2);
            operands.push(result);
        }
    }
    return operands.top();
}

int main() {
    string expression;
    cout << "Pishi shoto: ";
    getline(cin, expression);

    string postfix = infixToPostfix(expression);
    int result = evaluatePostfix(postfix);

    cout << "result: " << result << endl;
    return 0;
}
