#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>
#include <vector>


template <typename T>
class Node {
public:
    T data;
    Node<T>* next;

    Node() : data(T()), next(nullptr) {}
    Node(T data) : data(data), next(nullptr) {}
};

template <typename T>
class Double_Node {
public:
    T data;
    Double_Node<T>* next;
    Double_Node<T>* prev;

    Double_Node(T data) : data(data), next(nullptr), prev(nullptr) {}
};

template <typename T>
class Single_Linked_List {
private:
    Node<T>* head;
    int size;

public:
    Single_Linked_List() : head(nullptr), size(0) {}

    // Destruktor                                                                                                                                                                                                                                                                         

    ~Single_Linked_List(){
        while (head != nullptr) {
            rm_front();
        }
    }

    // Dodanie elementu na początek listy                                                                                                                                                                                                                                                 

    void add_front(T data){
        Node<T>* next_node = new Node<T>(data);
        next_node->next = head;
        head = next_node;
        size++;
    }

    // Dodanie elementu na koniec listy                                                                                                                                                                                                                                                   

    void add_back(T data){
        if(head == nullptr){
            add_front(data);
            return;
        }
        Node<T>* next_node = new Node<T>(data);
        Node<T>* temp = head;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = next_node;
        size++;
    }

    // Dodanie elementu na pozycji i-tej                                                                                                                                                                                                                                                  

    void add_at(T data, int i){
        if(i < 0 || i > size){
            std::cout<<"ERROR: i is out of bounds!!!";
        }
        if(i == 0){
            add_front(data);
            return;
        }

        Node<T>* next_node = new Node<T>(data);
        Node<T>* temp = head;
        for(int j = 0; j < i - 1; j++){
            temp = temp->next;
        }
        next_node->next = temp->next;
        temp->next = next_node;
        size++;
    }

    // Usuwanie pierwszego elementu listy                                                                                                                                                                                                                                                 

    void rm_front(){
        if (head == nullptr){
            return;
        }
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    // Usuwanie ostatniego elementu listy                                                                                                                                                                                                                                                 

    void rm_back(){
        if(head == nullptr){
            return;
        }
        if(size == 1){
            rm_front();
            return;
        }

        Node<T>* temp = head;
        while(temp->next->next != nullptr){
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
        size--;
    }

    // Usuwanie i-tego elementu listy                                                                                                                                                                                                                                                     

    void rm_at(int i){
        if(i < 0 || i >= size){
            std::cout<<"ERROR: i is out of bounds!!!";
        }
        if(i == 0){
            rm_front();
            return;
        }

        Node<T>* temp = head;
        for(int j = 0; j < (i - 1); j++){
            temp = temp->next;
        }
        Node<T>* to_delete = temp->next;
        temp->next = to_delete->next;
        delete to_delete;
        size--;
    }   

    // Zwracanie pozycji, na której przechowywana jest wartość data                                                                                                                                                                                                                       

    int find_node(T data){
        Node<T>* temp = head;
        int index = 0;
        while (temp != nullptr){
            if(temp->data == data){
                return index;
            }
            temp = temp->next;
            index++;
        }
        return -1; // Nie znaleziono                                                                                                                                                                                                                                                      
    }

    // Zwracanie wartości na i-tej pozycji w liście                                                                                                                                                                                                                                       

    T find_at(int i){
        if(i < 0 || i >= size){
            std::cout<<"ERROR: i is out of bounds!!!";
        }
        Node<T>* temp = head;
        for(int j = 0; j < i; j++){
            temp = temp->next;
        }
        return temp->data;
    }

    // Zwracanie ilości elementów w liście                                                                                                                                                                                                                                                

    int get_size(){
        return size;
    }
};

template <typename T>
class Double_Linked_List {
private:
    Double_Node<T>* head;
    Double_Node<T>* tail;
    int size;

public:
    Double_Linked_List() : head(nullptr), tail(nullptr), size(0) {}

    // Destruktor                                                                                                                                                                                                                                                                         

    ~Double_Linked_List(){
        while(head != nullptr){
            rm_front();
        }
    }

    // Dodawanie elementu na początek listy                                                                                                                                                                                                                                               

    void add_front(T data){
        Double_Node<T>* newNode = new Double_Node<T>(data);
        if(head == nullptr){
            head = newNode;
            tail = newNode;
        }
        else{
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    // Dodawanie elementu na koniec listy                                                                                                                                                                                                                                                 

    void add_back(T data){
        if(head == nullptr){
            add_front(data);
            return;
        }
        Double_Node<T>* newNode = new Double_Node<T>(data);
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
        size++;
    }

    // Dodawanie elementu na i-tej pozycji w liście                                                                                                                                                                                                                                       
   
    void add_at(T data, int i){
        if(i < 0 || i > size){
            std::cout<<"ERROR: i is out of bounds!!!";
        }
        if(i == 0){
            add_front(data);
        }
        else if(i == size){
            add_back(data);
        }
        else{
            Double_Node<T>* newNode = new Double_Node<T>(data);
            Double_Node<T>* temp = head;
            for(int j = 0; j < i; j++){
                temp = temp->next;
            }
            newNode->next = temp;
            newNode->prev = temp->prev;
            temp->prev->next = newNode;
            temp->prev = newNode;
            size++;
        }
    }

    // Usuwanie pierwszego elementu listy                                                                                                                                                                                                                                                 

    void rm_front(){
	      if(head == nullptr){
            return;
        }
        Double_Node<T>* temp = head;
        head = head->next;
	      if(head != nullptr){
            head->prev = nullptr;
        }
        else{
            tail = nullptr;
        }
    	  delete temp;
        size--;
    }

    // Usuwanie Ostatniego elementu z listy                                                                                                                                                                                                                                               

    void rm_back(){
        if(tail == nullptr){
            return;
        }
        if(head == tail){
            rm_front();
            return;
        }
        Double_Node<T>* temp = tail;
        tail = tail->prev;
	      tail->next = nullptr;
        delete temp;
	      size--;
    }

    // Usuwanie elementu na i-tej pozycji w liście                                                                                                                                                                                                                                        

    void rm_at(int i){
        if(i < 0 || i >= size){
            std::cout<<"ERROR: i is out of bounds!!!";
        }
        if(i == 0){
            rm_front();
        }
        else if(i == size - 1){
            rm_back();
        }
        else{
            Double_Node<T>* temp = head;
            for(int j = 0; j < i; j++){
                temp = temp->next;
            }
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
            size--;
        }
    }

    // Zwracanie indektu na którym przechowywana jest wartość data                                                                                                                                                                                                                        

    int find_node(T data) const {
        Double_Node<T>* temp = head;
        int index = 0;
        while(temp != nullptr){
            if (temp->data == data){
                return index;
            }
            temp = temp->next;
            index++;
        }
        return -1;
    }

    // Zwracanie wartości pod indeksem i-tym - wersja optymalizowana                                                                                                                                                                                                                      

    T find_at(int i){
        if(i < 0 || i >= size){
            std::cout<<"ERROR: i is out of bounds!!!";
        }
        Double_Node<T>* temp;
        if(i < (size / 2)){
            temp = head;
            for (int j = 0; j < i; j++){
                temp = temp->next;
            }
        }
        else{
            temp = tail;
            for (int j = size - 1; j > i; j--){
                temp = temp->prev;
            }
        }
        return temp->data;
    }

    // Zwracanie ilości elementów listy                                                                                                                                                                                                                                                   

    int get_size(){
        return size;
    }
};

template <typename L>
void compare_lists(L** lists, int num_lists, int N){

    // funkcja pomocnicza przygotowująca wszystkie listy do puszczania testów                                                                                                                                                                                                             

    auto prepare_lists = [=](L** ls){
        for(int i = 0; i < num_lists; ++i){
            while(ls[i]->get_size() > 0){
               ls[i]->rm_front();
            }
            for(int j = 0; j < N; ++j){
               ls[i]->add_back(j);
            }
        }
    };

    std::cout << "\n\nOperacja dla " << num_lists << " list o rozmiarze N=" << N << "      Czas sumaryczny [ms]\n";
    std::cout << std::string(75, '-') << "\n";

    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();

    // funkce add_*                                                                                                                                                                                                                                                                       

    prepare_lists(lists);
    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < num_lists; ++i){
       lists[i]->add_front(181);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << std::left << std::setw(45) << "1. add_front (1 el.)" << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    prepare_lists(lists);
    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < num_lists; ++i){
       lists[i]->add_back(181);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << std::left << std::setw(45) << "2. add_back (1 el.)" << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    prepare_lists(lists);
    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < num_lists; ++i){
       lists[i]->add_at(181, N / 2);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << std::left << std::setw(45) << "3. add_at (środek, 1 el.)" << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    // funkcja find_at                                                                                                                                                                                                                                                                    

    prepare_lists(lists);
    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < num_lists; ++i){
       lists[i]->find_at(0);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << std::left << std::setw(45) << "4. find_at (początek)" << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < num_lists; ++i){
       lists[i]->find_at(N / 2);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << std::left << std::setw(45) << "5. find_at (środek)" << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < num_lists; ++i){
       lists[i]->find_at(N - 1);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << std::left << std::setw(45) << "6. find_at (koniec)" << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    // funkcja find_node (wartści znane dzięki sposobie wypełniania list w funkcji prepare_lists()                                                                                                                                                                                        

    int val_start = 0;
    int val_mid = N / 2;
    int val_end = N - 1;

    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < num_lists; ++i){
       lists[i]->find_node(val_start);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << std::left << std::setw(45) << "7. find_node (wartość z początku)" << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < num_lists; ++i){
       lists[i]->find_node(val_mid);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << std::left << std::setw(45) << "8. find_node (wartość ze środka)" << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < num_lists; ++i){
       lists[i]->find_node(val_end);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << std::left << std::setw(45) << "9. find_node (wartość z końca)" << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    // funkcje rm_*                                                                                                                                                                                                                                                                       

    prepare_lists(lists);
    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < num_lists; ++i){
       lists[i]->rm_front();
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << std::left << std::setw(45) << "10. rm_front (1 el.)" << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    prepare_lists(lists);
    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < num_lists; ++i){
       lists[i]->rm_back();
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << std::left << std::setw(45) << "11. rm_back (1 el.)" << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    prepare_lists(lists);
    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < num_lists; ++i){
       lists[i]->rm_at(N / 2);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << std::left << std::setw(45) << "12. rm_at (środek, 1 el.)" << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";
}

int main() {
    const int NUM_LISTS = 50;       // Ile list w tablicy                                                                                                                                                                                                                                       
    const int NUM_EL = 10000;       // Ile elementów na każdą listę                                                                                                                                                                                                                       

    Single_Linked_List<long int>** sll_array = new Single_Linked_List<long int>*[NUM_LISTS];
    Double_Linked_List<long int>** dll_array = new Double_Linked_List<long int>*[NUM_LISTS];

    for(int i = 0; i < NUM_LISTS; ++i){
       sll_array[i] = new Single_Linked_List<long int>();
       dll_array[i] = new Double_Linked_List<long int>();
    }

    compare_lists(sll_array, NUM_LISTS, NUM_EL);
    compare_lists(dll_array, NUM_LISTS, NUM_EL);

    for (int i = 0; i < NUM_LISTS; ++i){
        delete sll_array[i];
        delete dll_array[i];
    }

    delete[] sll_array;
    delete[] dll_array;

    return 0;
}
