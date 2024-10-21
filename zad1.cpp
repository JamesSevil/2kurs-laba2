#include "include/stack.h"

int priority(char simv) {
    if (simv == '*' || simv == '/') return 2;
    else if (simv == '+' || simv == '-') return 1;
    else return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

string toPostfix(string& conditions) {
    string postfix;
    Stack<char> operators(30);
    for (char simv : conditions) {
        if (isalnum(simv)) {
            postfix += simv;
        } else if (simv == '(') {
            operators.push(simv);
        } else if (simv == ')') {
            while (!operators.isEmpty() && operators.peek() != '(') {
                postfix += operators.peek();
                operators.pop();
            }
            operators.pop();
        }
        else if (isOperator(simv)) {
            while (!operators.isEmpty() && priority(operators.peek()) >= priority(simv)) {
                postfix += operators.peek();
                operators.pop();
            }
            operators.push(simv);
        }
    }

    while (!operators.isEmpty()) {
        postfix += operators.peek();
        operators.pop();
    }

    return postfix;
}

int main() {

    while (true) {
        string conditions;
        cout << "Введите выражение: ";
        getline(cin, conditions);
        if (conditions == "exit") break;
        while (conditions.find_first_of(' ') != -1) {
            conditions.erase(conditions.find_first_of(' '), 1);
        }
        cout << toPostfix(conditions) << endl << endl;
    }
    
    return 0;
}

// вариант 3