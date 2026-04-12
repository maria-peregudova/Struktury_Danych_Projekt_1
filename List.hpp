#ifndef LIST_HPP
#define LIST_HPP

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

    void add_at(int i, T data){
        if(i < 0 || i > size){
            std::cout<<"ERROR: i is out of bounds!!!";
            return;
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
            return;
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

    // Zwracanie informacji czy wartość data znajduje się w liście                                                                                                                                                                                                                      

    bool find(T data){
        Node<T>* temp = head;
        while (temp != nullptr){
            if(temp->data == data){
                return true;
            }
            temp = temp->next;
        }
        return false; 
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
   
    void add_at(int i, T data){
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

    // Zwracanie informacji czy wartość data znajduje się w liście

    bool find(T data) {
        Double_Node<T>* temp = head;
        while(temp != nullptr){
            if (temp->data == data){
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    // Zwracanie ilości elementów listy                                                                                                                                                                                                                                                   

    int get_size() {
        return size;
    }
};

#endif