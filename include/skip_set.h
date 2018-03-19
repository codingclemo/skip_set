#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <string>


// Node
template<typename T>
class skip_set_node {
public:
    T value;
    skip_set_node **forward;
    int lvl;
    explicit skip_set_node(int lvl, T value);   
    virtual ~skip_set_node();
};

template <typename T>
skip_set_node<T>::skip_set_node(int lvl, T value)
    :value(value), forward(nullptr), lvl(lvl) {
    std::cout << "value is " << value << std::endl;
    forward = new skip_set_node<T>*[lvl];
    for (int i = 0; i < lvl; i++) {
        forward[i] = nullptr;
        // std::cout << i << std::endl;
    }
}  

template <typename T>
skip_set_node<T>::~skip_set_node(){
    for (int i = 0; i < lvl; i++)
        delete forward[i];
    delete[] forward;
}



// Set
template<typename T, const int MAXLEVEL=4>
class skip_set {
public:
    // explicit skip_set();
    explicit skip_set(){
        level = MAXLEVEL;
        head = new skip_set_node<T>*[level];
        tail = new skip_set_node<T>*[level];
        for (int i = 0; i < level; i++) {
            tail[i] = nullptr;
            head[i] = tail[i];
        }
    }

    ~skip_set(){
        // for (int i = 0; i < lvl; i++)
        //     delete head[i];
        // delete[] head; 
    }
    
    int size() const{
        int counter = 0;
        // not really working
        // skip_set_node<T> *help;
        // help = head[0];
        // while(help != nullptr) {
        //     counter++;
        //     help = help->forward[0];
        // }

        return counter;
    }   

    bool find(T value){
        return false;
    }

    void insert(T value){
        if(find(value)) return;
        //create new node
        skip_set_node<T> *n;
        n = new skip_set_node<T>(level, value);

        //insert
        

        // std::cout << value << std::cout;

        // create node and insert
        // skip_set_node* n;
        // d = new skip_set_node<T>(MAXLEVEL, value);

    }

    bool erase(T value);

private:
    // skip_set_node<T>* head;
    // skip_set_node<T>* tail;
    skip_set_node<T> **head;
    skip_set_node<T> **tail;
    int level;

};


// bool skip_set::find(T value){
//     skip_set_node *help;
//     help = head;
//     for (int i = level - 1; i >=0; i--) {
//         while(help->forward[i]->key < value) {
//             help = help->forward[i];
//         } 
//     }
//     help = forward[0];
//     if(help->value = value) {
//         return value;
//     } else {
//         return nullptr;
//         cout << "not found" << endl;
//     }
// }

// void skip_set::insert(T value){}
// bool skip_set::erase(T value){}