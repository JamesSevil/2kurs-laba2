#pragma once

#include "includes.h"

const int TABLE_SIZE = 100; // Размер хеш-таблицы

template<typename T>
struct NodeS {
    T data;
    NodeS* next;
    NodeS(T value);
};

template<typename T>
struct Set {
    NodeS<T>* table[TABLE_SIZE];
    int sizeset = 0;

    Set();
    Set(const Set<T>& other); // конструктор копирования(для вложения множества в структуру)
    ~Set();
    Set<T>& operator=(const Set<T>& other); // оператор присваивания(для вложения множества в структуру))

    int hashFunction(const T& value);
    void insert(const T& value);
    void remove(const T& value);
    bool contains(const T& value);
    T get(int index);
    int size();
    void print();
};

#include "../src/set.cpp"