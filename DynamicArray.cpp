#include "DynamicArray.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

// Konstruktor
DynamicArray::DynamicArray(int n) {
    size = 0;
    capacity = n;
    arr = new int[capacity];
}

// Destruktor
DynamicArray::~DynamicArray() {
    delete[] arr;
}

// Zwiększa pojemność tablicy dwukrotnie, O(n)
void DynamicArray::resize() {
    capacity *= 2;
    int* newArr = new int[capacity];

    for (int i = 0; i < size; i++) {
        newArr[i] = arr[i];
    }

    delete[] arr;
    arr = newArr;
}

// Zwraca aktualny rozmiar tablicy, O(1)
int DynamicArray::getSize() const {
    return size;
}

// Zwraca pojemność tablicy, O(1)
int DynamicArray::getCapacity() const {
    return capacity;
}

// Dodaje element na początek tablicy, O(n)
void DynamicArray::add_front(int value) {
    if (size == capacity) {
        resize();
    }

    for (int i = size; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = value;
    size++;
}

// Dodaje element na koniec tablicy, O(1) amortyzowane (czasami O(n) podczas resize)
void DynamicArray::add_back(int value) {
    if (size == capacity) {
        resize();
    }
    arr[size++] = value;
}

// Dodaje element na określony indeks, O(n)
void DynamicArray::add_at(int index, int value) {
    if (index < 0 || index > size) {
        return;
    }

    if (size == capacity) {
        resize();
    }

    for (int i = size; i > index; i--) {
        arr[i] = arr[i - 1];
    }
    arr[index] = value;
    size++;
}

// Usuwa element z początku tablicy, O(n)
void DynamicArray::rm_front() {
    if (size == 0) {
        return;
    }

    for (int i = 0; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    size--;
}

// Usuwa element z końca tablicy, O(1) amortyzowane (czasami O(n) podczas resize)
void DynamicArray::rm_back() {
    if (size == 0) {
        return;
    }
    size--;
}

// Usuwa element z określonego indeksu, O(n)
void DynamicArray::rm_at(int index) {
    if (index < 0 || index >= size) {
        return;
    }

    for (int i = index; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    size--;
}

// Wyszukuje element w tablicy, O(n)
bool DynamicArray::find(int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}

// Wypisuje elementy tablicy, O(n)
void DynamicArray::print() const { // const, gdyz się nie zmienia
    cout << "Tablica o rozmiarze " << size << " i pojemności " << capacity << ":" << endl;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}