#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

class DynamicArray {
  protected:
    int* arr;
    int size;
    int capacity;
  
    void resize(); // Zwiększa pojemność tablicy dwukrotnie, O(n)
  
  public:
    DynamicArray(int n = 4); // Konstruktor
    ~DynamicArray();         // Destruktor

    int getSize() const;     // Zwraca aktualny rozmiar tablicy, O(1)
    int getCapacity() const; // Zwraca pojemność tablicy, O(1)
    
    void add_front(int value);         // Dodaje element na początek tablicy, O(n)
    void add_back(int value);          // Dodaje element na koniec tablicy, O(1) amortyzowane (czasami O(n) podczas resize)
    void add_at(int index, int value); // Dodaje element na określony indeks, O(n)
    
    void rm_front();       // Usuwa element z początku tablicy, O(n)
    void rm_back();        // Usuwa element z końca tablicy, O(1) amortyzowane (czasami O(n) podczas resize)
    void rm_at(int index); // Usuwa element z określonego indeksu, O(n)
    
    bool find(int value); // Wyszukuje element w tablicy, O(n)
    void print() const;   // Wypisuje elementy tablicy, O(n)
};

#endif