#include "include/hashtable.h"

pair<int, string> findMaxSequence(string& str) {
    HashTable<int> charIndex;
    int maxLength = 0;
    int start = 0; // Начальный индекс текущей подстроки
    string longestSubstr = ""; // Для хранения самой длинной подстроки

    for (int i = 0; i < str.length(); ++i) {
        string token(1, str[i]); // Создание строки из одного символа
        int value = charIndex.get(token);
        bool check = charIndex.find(token);
        
        if (check && value >= start) { // Если символ уже встречался и его индекс больше или равен началу текущей подстроки
            start = value + 1;
        }

        if (!check) {
            charIndex.insert(token, i);
        } else {
            charIndex.replace(token, i);
        }

        int currentLength = i - start + 1;
        if (currentLength > maxLength) {
            maxLength = currentLength;
            longestSubstr = str.substr(start, currentLength); // Обновляем самую длинную подстроку
        }
    }

    return {maxLength, longestSubstr};
}

int main() {
    while (true) {
        string str;
        cout << "Введите строку: ";
        getline(cin, str);
        while (str.size() > 50000) {
            cout << "Строка не может содержать > 50.000 символов!" << endl;
            cout << "Повторите ввод: ";
            getline(cin, str);
        }
        if (str == "exit") break;

        auto result = findMaxSequence(str);
        cout << "Длина самой длинной последовательности неповторяющихся символов: " << result.first << endl;
        cout << "Самая длинная последовательность: " << result.second << endl;
    }

    return 0;
}