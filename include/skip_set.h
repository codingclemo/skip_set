#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <random>


// Node
template<typename T>
class skip_set_node {
public:
    T value;
    skip_set_node **forward;
    int lvl;
    explicit skip_set_node(int lvl);  
    explicit skip_set_node(int lvl, T value);   
    virtual ~skip_set_node();

    virtual void printForward();
};

template <typename T>
skip_set_node<T>::skip_set_node(int lvl)
    :forward(nullptr), lvl(lvl) {
    forward = new skip_set_node<T>*[lvl];
    for (int i = 0; i < lvl; i++) {
        forward[i] = nullptr;
    }
}  

template <typename T>
skip_set_node<T>::skip_set_node(int lvl, T value)
    :value(value), forward(nullptr), lvl(lvl) {
    std::cout << "****\tcreate new node\t\t**** " << std::endl;
    std::cout << "\tValue: " << value << std::endl;    
    std::cout << "\tLevel: " << lvl << std::endl;
    forward = new skip_set_node<T>*[lvl];
    for (int i = 0; i < lvl; i++) {
        forward[i] = nullptr;
    }
}  

template <typename T>
skip_set_node<T>::~skip_set_node(){
    delete[] forward;
}

template <typename T>
void skip_set_node<T>::printForward(){
    std::cout << "Forwards of node " << value << std::endl;
    for (int i = lvl-1; i >=0; i--){
        if (forward[i] == nullptr) {
            std::cout << "\t[" << i << "]: " << "nullptr" << std::endl;
        } else {
            std::cout << "\t[" << i << "]: " << forward[i]->value << std::endl;
        }
    }
}


// Set
template<typename T, const int MAXLEVEL=10>
class skip_set {
public:
    explicit skip_set(){
        level = MAXLEVEL;
        head = new skip_set_node<T>(level);
        for (int i = 0; i < level; i++) {
            head->forward[i] = nullptr;
        }
    }

    ~skip_set(){
        skip_set_node<T> *n, *help;
        n = head;
        while (n != nullptr) {
            help = n->forward[0];
            delete n;
            n = help;
        }
        std::cout << "set deleted" << std::endl;
    }
    
    int size() const{
        int counter = 0;
        skip_set_node<T> *help;
        help = head->forward[0];
        while(help != nullptr) {
            counter++;
            help = help->forward[0];
        }

        return counter;
    }   

    bool find(T value){
         skip_set_node<T> *n;
         n = head;
         
        for (int i = level - 1; i >=0; i--) {
            while(n->forward[i] != nullptr && n->forward[i]->value < value) {
                n = n->forward[i];
            } 
        }
        n = n->forward[0];

        return (n->value == value);
    }

    void insert(T value){
        //create update
        skip_set_node<T> *update;
        update = new skip_set_node<T>(level);

        //create iterator
        skip_set_node<T> *n;
        n = head;

        //collect pointers to predecessors
        for (int i = level-1; i >= 0; i--) {
            while (n->forward[i] != nullptr && n->forward[i]->value < value) {
                n = n->forward[i];
            }
            update->forward[i] = n;
        }
        n = n->forward[0];

        if (n != nullptr && n->value == value) { // node already exists
            std::cerr << "Node already exists, no new node is generated" << std::endl;
            return;
        } else { // node does not yet exist
            //generate new random level for the node
            int randLvl = randomLevel();
            if (randLvl > this->level) {
                for (int i = level + 1; i < randLvl; i++) {
                    update->forward[i] = head;
                }
                this->level = randLvl;
            }
            //create new node   
            skip_set_node<T> *newNode;
            newNode = new skip_set_node<T>(randLvl, value);
            
            for (int i = 0; i < randLvl; i++) {
                newNode->forward[i] = update->forward[i]->forward[i];
                update->forward[i]->forward[i] = newNode;
            }
        }
    }

    bool erase(T value) {
        //create update
        skip_set_node<T> *update;
        update = new skip_set_node<T>(level);

        //create iterator
        skip_set_node<T> *n;
        n = head;
        
        //collect pointers to predecessors
        for (int i = level-1; i >= 0; i--) {
            while (n->forward[i] != nullptr && n->forward[i]->value < value) {
                n = n->forward[i];
            }
            update->forward[i] = n;
        }
        n = n->forward[0]; // set pointer to the supposed to-delete node

        if (n != nullptr && n->value == value) { // node exists and must be erased
            for (int i = 0; i < level; i++) { // checks not only up to the level of the node, but to the max level
                if (update->forward[i]->forward[i] != n) {
                    break;
                } else {
                    update->forward[i]->forward[i] = n->forward[i]; //redirect pointers to successors of to-delete-node
                }
            }
            
            delete n;
            delete update;

            //check if the set-level needs to be reduced
            n = head;
            while (level > 1 && n->forward[level] == nullptr) {  
                level--;
            }
            return true;
        } else { // node does not exist
            return false;
        }
    }

    int randomLevel(){
        int level = 1;
        double probability = 0.5;
        double randomP = ((double) rand() / (RAND_MAX));
        while ( randomP < probability && level < MAXLEVEL) {
            level += 1;
            randomP = ((double) rand() / (RAND_MAX));
        }
        return level;
    }

    void printSet(){
        skip_set_node<T>* n;
        n = head;
        while (n != nullptr) {
            n->printForward();
            n = n->forward[0];
        }
    }

private:
    skip_set_node<T> *head;
    int level;
};