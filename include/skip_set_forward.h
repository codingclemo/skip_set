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

    friend std::ostream & operator<<(std::ostream &os, const skip_set_node<T> & node){
        os << node.value;
        return os; 
    }   
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
    typedef skip_set_iterator<T> iterator;
    iterator find(T value) {
        
    }

    iterator begin() const {
        return iterator(head->forward[0]);
    }
    iterator end() {
        skip_set_node<T>* n;
        n = head;
        while (n->forward[0] != nullptr) {
            n = n->forward[0];
        }
        return iterator(n);
    }


    explicit skip_set(){
        level = MAXLEVEL;
        head = new skip_set_node<T>(level);
        for (int i = 0; i < level; i++) {
            head->forward[i] = nullptr;
        }

        // head = new skip_set_node<T>*[level];
        // tail = new skip_set_node<T>*[level];
        // for (int i = 0; i < level; i++) {
        //     tail[i] = nullptr;
        //     head[i] = tail[i];
        // }
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
        // not really working
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
        // return false;
    }

    void insert(T value){
        // if(this->find(value)) {return;}

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
            // std::cout << "weird" << std::endl;
            
            for (int i = 0; i < randLvl; i++) {
                newNode->forward[i] = update->forward[i]->forward[i];
                update->forward[i]->forward[i] = newNode;
            }
        } //endelse
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
            // std::cerr << "Node does not exist, no node is deleted" << std::endl;
            return false;
        } //endelse
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
    // skip_set_node<T> *tail;
    int level;

};


// Iterator inside skip_set
template<typename T>
class skip_set_iterator {
private:
    skip_set_node<T>* n;
public:
    skip_set_iterator() = delete; //dunno why
    skip_set_iterator(skip_set_node<T>* it) 
        : n(it) {
            std::cout << "skip_set_iterator  constructor " << std::endl;
    }

    skip_set_iterator(const skip_set_iterator &it)
        : n(it.n) {  
    }   

    ~skip_set_iterator() {
        std::cout << "destructor skip_set_iterator "  << std::endl;
    };

    // operator for forward iterator
    bool operator == (const skip_set_iterator &it){
        return n == it.n;
    }

    bool operator != (const skip_set_iterator &it) {
        return n != it.n;
    }

    // pre increment
    skip_set_iterator & operator++ () {
        n = n->forward[0];
        return *this;
    } 

    // post increment
    skip_set_iterator operator++(int){
        skip_set_iterator it(*this); 
        operator++(); 
        return it; 
    }

    T & operator*(){
        return n->value;
    }

    friend std::ostream & operator << (std::ostream &os, const skip_set_iterator &it) {
        os << *(it.n);
        return os; 
    }
};

