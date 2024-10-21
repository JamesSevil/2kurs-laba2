#include "../include/set.h"

template<typename T>
NodeS<T>::NodeS(T value) : data(value), next(nullptr) {}


template<typename T>
Set<T>::Set() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table[i] = nullptr;
    }
}

template<typename T>
Set<T>::~Set() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        NodeS<T>* current = table[i];
        while (current) {
            NodeS<T>* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
}

template<typename T>
int Set<T>::hashFunction(const T& value) {
    hash<T> hashFn;
    return hashFn(value) % TABLE_SIZE;
}

template<typename T>
void Set<T>::insert(const T& value) {
    int index = hashFunction(value);
    
    if (!contains(value)) {
        NodeS<T>* newNode = new NodeS<T>(value);
        
        // Вставляем элемент в упорядоченный список
        if (!table[index] || table[index]->data > value) {
            // Вставляем на начало списка
            newNode->next = table[index];
            table[index] = newNode;
            sizeset++;
        } else {
            // Ищем правильное место для вставки
            NodeS<T>* current = table[index];
            while (current->next && current->next->data < value) {
                current = current->next;
            }
            newNode->next = current->next; // Присоединяем новый узел
            current->next = newNode; // Вставляем новый узел
            sizeset++;
        }
    }
}

template<typename T>
void Set<T>::remove(const T& value) {
    int index = hashFunction(value);
    NodeS<T>* current = table[index];
    NodeS<T>* previous = nullptr;

    while (current) {
        if (current->data == value) {
            if (previous) {
                previous->next = current->next; // Удаляем узел из цепочки
            } else {
                table[index] = current->next; // Удаляем первый узел
            }
            delete current;
            sizeset--;
            return;
        }
        previous = current;
        current = current->next;
    }
}

template<typename T>
bool Set<T>::contains(const T& value) {
    int index = hashFunction(value);
    NodeS<T>* current = table[index];

    while (current) {
        if (current->data == value) {
            return true; // Элемент найден
        }
        current = current->next;
    }
    return false; // Элемент не найден
}

template<typename T>
T Set<T>::get(int index) {
        if (index < 0 || index >= size()) {
            throw out_of_range("Index out of range");
        }

        int count = 0;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            NodeS<T>* current = table[i];
            while (current) {
                if (count == index) {
                    return current->data; // Возвращаем элемент по индексу
                }
                current = current->next;
                count++;
            }
        }

        throw out_of_range("Index out of range"); // На случай, если индекс не найден
    }

template<typename T>
int Set<T>::size() {
    return sizeset;
}

template<typename T>
void Set<T>::print() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        NodeS<T>* current = table[i];
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
    }
    cout << endl;
}