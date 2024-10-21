#include "include/hashtable.h"

int findMaxSequence(string& str) {
    HashTable<int> charIndex;
    int maxLenght = 0;
    int start = 0; // Начальный индекс текущей подстроки

    for (int i = 0; i < str.length(); ++i) {
        string token;
        token += str[i];
        int value = charIndex.get(token);
        bool check = charIndex.find(token);
        if (check && value >= start) { // Если символ уже встречался и его индекс больше или равен началу текущей подстроки
            start = value + 1;
        }

        if (!check) charIndex.insert(token, i);
        else charIndex.replace(token, i);

        maxLenght = max(maxLenght, i - start + 1);
    }

    return maxLenght;
}

int main() {

    while (true) {
        string str;
        cout << "Введите строку: ";
        getline(cin, str);
        while (str.size() > 50.000) {
            cout << "Строка не может содержать > 50.000 символов!" << endl;
            cout << "Повторите ввод: ";
            getline(cin, str);
        }
        if (str == "exit") break;
        cout << "Дина самой длинной последовательности неповторяющихся символов: " << findMaxSequence(str) << endl;
    }

    return 0;
}