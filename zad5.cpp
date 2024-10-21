#include "include/tree.h"

int main() {

    BinaryTree tree;
    string conditions;
    cout << "Введите через пробел числа для дерева: ";
    getline(cin, conditions);
    stringstream stream(conditions);
    string token;
    while(getline(stream, token, ' ')) {
        tree.insert(stoi(token));
    }

    tree.print();
    tree.printZmeyka();

    return 0;
}

// вариант 2