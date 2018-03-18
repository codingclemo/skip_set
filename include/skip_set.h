#pragma once
#include <iostream>
#include <sstream>
#include <vector>


// Node for Skipset
template<typename V>
class skip_set_node {
public:
    V value;
    skip_set_node** forward;
    // skip_set_node<V, maxlvl> *forward[maxlvl+1]; //pointer to array of skip_set_node with size MAXLEVEL

    explicit skip_set_node(int lvl, V value);   
    // virtual ~skip_set_node();
};

// template<typename V>
// struct node {
//     V* value;
//     // int maxlevel;
//     std::vector<node*> forward;
//     node (V* value, int level);
// };


// template<typename T, const int MAXLEVEL=4>
// class skip_set {
// public:
//     explicit skip_set();
//     ~skip_set();
    
//     int size() const;
//     bool find(T value);
//     void insert(T value);
//     bool erase(T value);

// private:
//     skip_set_node* head;
//     skip_set_node* tail;
//     int level;

// };