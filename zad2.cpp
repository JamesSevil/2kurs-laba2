#include "include/set.h"

// Вспомогательные ф-ии
string Fulltext (string& filename, string& nameStruct) { // ф-ия сохранения фулл текста файла без нужной структуры
    string str, textfull;
    ifstream fileinput;
    fileinput.open(filename);
    while(getline(fileinput, str)) { // сохранение фулл текста в переменную
        stringstream ss(str);
        string token;
        getline(ss, token, ' ');
        if (token != nameStruct) {
            textfull += str + "\n";
        }
    }
    fileinput.close();
    return textfull;
}
void writefile (string& filename, string& textfull) { // ф-ия записи данных в файл
    ofstream fileoutput;
    fileoutput.open(filename);
    fileoutput << textfull;
    fileoutput.close();
}

// ф-ии множества
Set<int> Sreadfile (string& filename, string& name) { // ф-ия чтения множества из файла
    Set<int> nums;
    string str;
    ifstream fileinput;
    fileinput.open(filename);
    while (getline(fileinput, str)) { // добавления значения в множество
        stringstream ss(str);
        string token;
        getline(ss, token, ' ');
        if (token == name) {
            while (getline(ss, token, ' ')) {
                nums.insert(stoi(token));
            }
        }
    }
    fileinput.close();
    return nums;
}
void SETADD(string& name, int& value, string& filename) {
    string textfull = Fulltext(filename, name);
    Set<int> nums = Sreadfile(filename, name);

    string str;
    if (nums.size() != 0) {
        nums.insert(value);
        str = name + ' ';
        for (int i = 0; i < nums.size(); ++i) {
            str += to_string(nums.get(i)) + ' ';
        }
        textfull += str;
        writefile(filename, textfull);
    } else {
        str = name + ' ' + to_string(value);
        textfull += str;
        writefile(filename, textfull);
    }
}
void SETDEL(string& name, int& value, string& filename) {
    string textfull = Fulltext(filename, name);
    Set<int> nums = Sreadfile(filename, name);

    string str;
    if (nums.size() != 0) {
        nums.remove(value);
        str = name + ' ';
        for (int i = 0; i < nums.size(); ++i) {
            str += to_string(nums.get(i)) + ' ';
        }
        textfull += str;
        writefile(filename, textfull);
    } else {
        cout << "Ошибка, нет такого множества или оно пустое!" << endl;
        exit(1);
    }
}
void SET_AT(string& name, int& value, string& filename) {
    Set<int> nums = Sreadfile(filename, name);

    string str;
    if (nums.size() != 0) {
        if (nums.contains(value)) cout << "true" << endl;
        else cout << "false" << endl;
    } else {
        cout << "Ошибка, нет такого множества или оно пусто!" << endl;
        exit(1);
    }
}
void SETPRINT(string& name, string& filename) {
    Set<int> nums = Sreadfile(filename, name);

    if (nums.size() != 0) {
        nums.print();
    } else {
        cout << "Ошибка, нет такого множества или оно пусто!" << endl;
    }
}


int main(int argc, char* argv[]) {
    if (argc != 5) {
        cerr << "Использование: " << argv[0] << " --file <filename> --query '<command>'" << endl;
        return 1;
    }

    // Разбор аргументов командной строки
    string filename;
    string query;
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "--file") {
            filename = argv[++i];
        } else if (string(argv[i]) == "--query") {
            query = argv[++i];
        }
    }

    // Обработка команды
    string name;
    int value;
    if (query.substr(0, 7) == "SETADD ") {
        stringstream stream(query.substr(7));
        stream >> name >> value;
        SETADD(name, value, filename);
    } else if (query.substr(0, 7) == "SETDEL ") {
        stringstream stream(query.substr(7));
        stream >> name >> value;
        SETDEL(name, value, filename);
    } else if (query.substr(0, 7) == "SET_AT ") {
        stringstream stream(query.substr(7));
        stream >> name >> value;
        SET_AT(name, value, filename);
    } else if (query.substr(0, 9) == "SETPRINT ") {
        stringstream stream(query.substr(9));
        stream >> name;
        SETPRINT(name, filename);
    } else {
        cout << "Ошибка, нет такой команды!" << endl;
        exit(1);
    }

    return 0;
}