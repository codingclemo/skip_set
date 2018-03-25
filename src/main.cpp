#include <iostream>
#include <string>
// #include "skip_set.h"
#include "skip_set_forward.h"

using namespace std;

int main() {

    // int x1 = 24;
    // int x2 = 42;
    // double x1 = 2.4;
    // double x2 = 4.2;
    string x1 ("vierundzwanzig");
    string x2 ("zweiundvierzig");
    // int* y = &x;
    // x = 32;
    // cout << *y << endl;
    // skip_set_node<int> testnode1(4, x1);
    // skip_set_node<int> testnode2(4, x2);
    // skip_set_node<string> testnode1(4, x1);
    // skip_set_node<string> testnode2(4, x2);

    skip_set<int, 5> setTest1;
    setTest1.insert(10);
    setTest1.insert(20);    
    setTest1.insert(30);
    setTest1.insert(13);
    setTest1.insert(10);
    setTest1.printSet();
    int y = setTest1.size();
    cout << "size: " << y << endl;

    if (setTest1.find(20)) {cout << "20 found" << endl;} else {cout << "20 not found" << endl; }
    if (setTest1.find(25)) {cout << "25 found" << endl;} else {cout << "25 not found" << endl; }
    // for (int i = 0; i < 5; i++) {
    //     cout << setTest1.randomLevel() << endl;
    // }

    // erase test
    // bool erased;
    for (int i = 20; i < 22; i++) {
        if(setTest1.erase(i)) { 
            cout << i << " was erased" << endl;
        } else {
            cout << i <<" was not erased" << endl;
        }
    }


    setTest1.printSet();
    cout << "fin" << endl;
    return 0;
}
