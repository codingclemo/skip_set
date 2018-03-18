#include "skip_set.h"

// template <typename V>
// node<V>::node (V* value, int level)
//     :value(value), maxlevel(level) {

//     }

using namespace std;

// Node for Skipset
template <typename V>
skip_set_node<V>::skip_set_node(int lvl, V value)
    :value(value), forward(nullptr) {

    cout << value << endl;
    // skip_set_node<V> *forw[lvl+1];
    // for (int i = 1; i <= lvl; i++) {
    //     forward[i] = nullptr;
    // }
    // forward = forw;
}  

// template <typename V>
// skip_set_node::~skip_set_node(){
//     //nothing 2do
// }


// Set for Skipset Nodes
// skip_set::skip_set()
//     :level(MAXLEVEL) {
//     head = new skip_set_node(level, nullptr);
//     tail = new skip_set_node(level, nullptr);
// };
    
// skip_set::~skip_set(){
//     delete head;
//     delete tail;
// }

// int skip_set::size() const {
//     int counter = 0;
//     skip_set_node *help;
//     help = head->forward[0];
//     while(help != nullptr) {
//         counter++;
//         help = help->forward[0];
//     }

//     return counter;
// }

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