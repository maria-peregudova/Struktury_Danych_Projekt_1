#include <iostream>
#include <iomanip>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include "DynamicArray.cpp"
#include "List.hpp"

using namespace std;
using namespace std::chrono;

// Funkcja do tworzenia kopii tablicy i wypełniania ich losowymi danymi
// Dla Tablicy Dynamicznej
void createCopies(DynamicArray** copiesArr, int numCopies, int size) {
    for (int i = 0; i < numCopies; ++i) {
        copiesArr[i] = new DynamicArray(size + 1); // Tworzenie nowej kopii tablicy dynamicznej o rozmiarze większym o 1, aby umożliwić testowanie
        for (int j = 0; j < size; ++j) copiesArr[i]->add_back(rand() % 10000);
    }
}

// Dla Listy Jednokierunkowej
void createCopies(Single_Linked_List<int>** copiesArr, int numCopies, int size) {
    for (int i = 0; i < numCopies; ++i) {
        copiesArr[i] = new Single_Linked_List<int>(); 
        for (int j = 0; j < size; ++j) copiesArr[i]->add_front(rand() % 10000);
    }
}

// Dla Listy Dwukierunkowej
void createCopies(Double_Linked_List<int>** copiesArr, int numCopies, int size) {
    for (int i = 0; i < numCopies; ++i) {
        copiesArr[i] = new Double_Linked_List<int>(); 
        for (int j = 0; j < size; ++j) copiesArr[i]->add_back(rand() % 10000);
    }
}

// Funkcja do usuwania kopii tablicy
template <typename T>
void deleteCopies(T** copiesArr, int numCopies) {
    for (int i = 0; i < numCopies; ++i) {
        delete copiesArr[i];
    }
}

int main() {
    srand(time(NULL)); 
    int numCopies = 50; // Liczba kopii struktur do testowania dla każdego rozmiaru N

    // Otworzenie pliku CSV do zapisu wyników
    ofstream file("results.csv");

    // Zapisanie nagłówków kolumn do pliku CSV
    file << "Size;TD_AddFront;L1_AddFront;L2_AddFront;"
         << "TD_AddBack;L1_AddBack;L2_AddBack;"
         << "TD_RmFront;L1_RmFront;L2_RmFront;"
         << "TD_RmBack;L1_RmBack;L2_RmBack;"
         << "TD_AddAt;L1_AddAt;L2_AddAt;"
         << "TD_RmAt;L1_RmAt;L2_RmAt;"
         << "TD_Find;L1_Find;L2_Find\n";

    // Wektor zawierający rozmiary struktur (N), dla których będą przeprowadzane testy
    vector<int> tableSize = {1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000};
    
    DynamicArray** td_copies = new DynamicArray*[numCopies]; // Tablica wskaźników na kopie tablicy dynamicznej
    Single_Linked_List<int>** l1_copies = new Single_Linked_List<int>*[numCopies]; // Tablica wskaźników na kopie listy jednokierunkowej
    Double_Linked_List<int>** l2_copies = new Double_Linked_List<int>*[numCopies]; // Tablica wskaźników na kopie listy dwukierunkowej

    int foundCount = 0; // Zmienna do zliczania znalezionych elementów podczas testowania operacji find
    
    // Testowanie operacji dla różnych rozmiarów tablicy
    for (int size : tableSize) {
        int midIndex = size / 2; // Obliczanie indeksu środkowego do testowania operacji na indeksie

        // Zmienne do przechowywania uśrednionych czasów operacji dla poszczególnych struktur (w nanosekundach)
        long long td_af, l1_af, l2_af; 
        long long td_ab, l1_ab, l2_ab;
        long long td_rf, l1_rf, l2_rf;
        long long td_rb, l1_rb, l2_rb;
        long long td_aa, l1_aa, l2_aa;
        long long td_ra, l1_ra, l2_ra;
        long long td_fi, l1_fi, l2_fi;
        
        int randomValue; // Zmienna do przechowywania losowej wartości do dodawania i wyszukiwania
        auto start = high_resolution_clock::now(); // Start zegara
        auto end = high_resolution_clock::now(); // Zatrzymanie zegara

        // Dodawanie na początek
        createCopies(td_copies, numCopies, size);
        randomValue = rand() % 10000;
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            td_copies[i]->add_front(randomValue); // Dodawanie losowej wartości na początek każdej kopii tablicy
        }
        end = high_resolution_clock::now();
        td_af = duration_cast<nanoseconds>(end - start).count() / numCopies; // Obliczanie średniego czasu na jedną operację
        deleteCopies(td_copies, numCopies);

        createCopies(l1_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            l1_copies[i]->add_front(randomValue);
        }
        end = high_resolution_clock::now();
        l1_af = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(l1_copies, numCopies);

        createCopies(l2_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            l2_copies[i]->add_front(randomValue);
        }
        end = high_resolution_clock::now();
        l2_af = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(l2_copies, numCopies);

        // Dodawanie na koniec
        createCopies(td_copies, numCopies, size);
        randomValue = rand() % 10000;
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            td_copies[i]->add_back(randomValue); // Dodawanie losowej wartości na koniec każdej kopii tablicy
        }
        end = high_resolution_clock::now();
        td_ab = duration_cast<nanoseconds>(end - start).count() / numCopies; // Obliczanie średniego czasu na jedną operację
        deleteCopies(td_copies, numCopies);

        createCopies(l1_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            l1_copies[i]->add_back(randomValue);
        }
        end = high_resolution_clock::now();
        l1_ab = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(l1_copies, numCopies);

        createCopies(l2_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            l2_copies[i]->add_back(randomValue);
        }
        end = high_resolution_clock::now();
        l2_ab = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(l2_copies, numCopies);

        // Usuwanie z początku
        createCopies(td_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            td_copies[i]->rm_front(); // Usuwanie pierwszego elementu z każdej kopii tablicy
        }
        end = high_resolution_clock::now();
        td_rf = duration_cast<nanoseconds>(end - start).count() / numCopies; // Obliczanie średniego czasu na jedną operację
        deleteCopies(td_copies, numCopies);

        createCopies(l1_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            l1_copies[i]->rm_front();
        }
        end = high_resolution_clock::now();
        l1_rf = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(l1_copies, numCopies);

        createCopies(l2_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            l2_copies[i]->rm_front();
        }
        end = high_resolution_clock::now();
        l2_rf = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(l2_copies, numCopies);

        // Usuwanie z końca
        createCopies(td_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            td_copies[i]->rm_back(); // Usuwanie ostatniego elementu z każdej kopii tablicy
        }
        end = high_resolution_clock::now();
        td_rb = duration_cast<nanoseconds>(end - start).count() / numCopies; // Obliczanie średniego czasu na jedną operację
        deleteCopies(td_copies, numCopies);

        createCopies(l1_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            l1_copies[i]->rm_back();
        }
        end = high_resolution_clock::now();
        l1_rb = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(l1_copies, numCopies);

        createCopies(l2_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            l2_copies[i]->rm_back();
        }
        end = high_resolution_clock::now();
        l2_rb = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(l2_copies, numCopies);

        // Dodawanie na środek
        createCopies(td_copies, numCopies, size);
        randomValue = rand() % 10000;
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            td_copies[i]->add_at(midIndex, randomValue); // Dodawanie losowej wartości na środek każdej kopii tablicy
        }
        end = high_resolution_clock::now();
        td_aa = duration_cast<nanoseconds>(end - start).count() / numCopies; // Obliczanie średniego czasu na jedną operację
        deleteCopies(td_copies, numCopies);

        createCopies(l1_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            l1_copies[i]->add_at(midIndex, randomValue);
        }
        end = high_resolution_clock::now();
        l1_aa = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(l1_copies, numCopies);

        createCopies(l2_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            l2_copies[i]->add_at(midIndex, randomValue);
        }
        end = high_resolution_clock::now();
        l2_aa = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(l2_copies, numCopies);

        // Usuwanie ze środka
        createCopies(td_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            td_copies[i]->rm_at(midIndex); // Usuwanie elementu ze środka każdej kopii tablicy
        }   
        end = high_resolution_clock::now();
        td_ra = duration_cast<nanoseconds>(end - start).count() / numCopies; // Obliczanie średniego czasu na jedną operację
        deleteCopies(td_copies, numCopies);

        createCopies(l1_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            l1_copies[i]->rm_at(midIndex);
        }
        end = high_resolution_clock::now();
        l1_ra = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(l1_copies, numCopies);

        createCopies(l2_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            l2_copies[i]->rm_at(midIndex);
        }
        end = high_resolution_clock::now();
        l2_ra = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(l2_copies, numCopies);

        // Wyszukiwanie elementu
        createCopies(td_copies, numCopies, size);
        int searchValue = rand() % 10000; // losowanie jakiejś liczby do wyszukania
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            if (td_copies[i]->find(searchValue)) {
                foundCount++;
            }
        }
        end = high_resolution_clock::now();
        td_fi = duration_cast<nanoseconds>(end - start).count() / numCopies; // Obliczanie średniego czasu na jedną operację
        deleteCopies(td_copies, numCopies);

        createCopies(l1_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            if (l1_copies[i]->find(searchValue)) {
                foundCount++;
            }
        }
        end = high_resolution_clock::now();
        l1_fi = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(l1_copies, numCopies);

        createCopies(l2_copies, numCopies, size);
        start = high_resolution_clock::now();
        for (int i = 0; i < numCopies; ++i) {
            if (l2_copies[i]->find(searchValue)) {
                foundCount++;
            }
        }
        end = high_resolution_clock::now();
        l2_fi = duration_cast<nanoseconds>(end - start).count() / numCopies;
        deleteCopies(l2_copies, numCopies);

        // Zapisanie wyników do pliku CSV
        file << size << ";" << td_af << ";" << l1_af << ";" << l2_af << ";"
             << td_ab << ";" << l1_ab << ";" << l2_ab << ";"
             << td_rf << ";" << l1_rf << ";" << l2_rf << ";"
             << td_rb << ";" << l1_rb << ";" << l2_rb << ";"
             << td_aa << ";" << l1_aa << ";" << l2_aa << ";"
             << td_ra << ";" << l1_ra << ";" << l2_ra << ";"
             << td_fi << ";" << l1_fi << ";" << l2_fi << "\n";

        // Wyświetlenie wyników na konsoli w czytelnej formie
        cout << "\nOperacja dla N = " << size << "\n";
        cout << string(60, '-') << "\n";
        cout << left << setw(18) << "Operacja" << setw(14) << "TD [ns]" << setw(14) << "L1 [ns]" << setw(14) << "L2 [ns]" << "\n";
        cout << string(60, '-') << "\n";
        cout << left << setw(18) << "1. add_front"   << setw(14) << td_af << setw(14) << l1_af << setw(14) << l2_af << "\n";
        cout << left << setw(18) << "2. add_back"    << setw(14) << td_ab << setw(14) << l1_ab << setw(14) << l2_ab << "\n";
        cout << left << setw(18) << "3. rm_front"<< setw(14) << td_rf << setw(14) << l1_rf << setw(14) << l2_rf << "\n";
        cout << left << setw(18) << "4. rm_back" << setw(14) << td_rb << setw(14) << l1_rb << setw(14) << l2_rb << "\n";
        cout << left << setw(18) << "5. add_at"      << setw(14) << td_aa << setw(14) << l1_aa << setw(14) << l2_aa << "\n";
        cout << left << setw(18) << "6. rm_at"   << setw(14) << td_ra << setw(14) << l1_ra << setw(14) << l2_ra << "\n";
        cout << left << setw(18) << "7. find"        << setw(14) << td_fi << setw(14) << l1_fi << setw(14) << l2_fi << "\n";
    }

    // Zwalnianie pamięci przez usuwanie kopii tablicy i list
    delete[] td_copies;
    delete[] l1_copies;
    delete[] l2_copies;
    
    file.close(); // Zamknięcie pliku CSV po zakończeniu zapisu wyników

    if (foundCount < 0) {
        cout << "Nie znaleziono żadnego elementu podczas testowania operacji find.\n"; // Wyświetlenie komunikatu, jeśli żaden element nie został znaleziony podczas testowania operacji find, dla zmylenia optymalizacji
    }
    return 0;
}