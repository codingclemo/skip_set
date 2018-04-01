#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <set>

// #include "skip_set.h"
// #include "skip_set_forward.h"
#include "skip_set_bidirectional.h"

using namespace std;

void speedTestDIY(int NoOfSets, int SetSize) {
    clock_t begin = clock();
    for (int i = 0; i < NoOfSets; i++) {
        skip_set<int> DIY_test;
        for (int j = 0; j < SetSize; j++) {
            DIY_test.insert(j);
        }
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    cout << "****\tDIY-Set\tNumber of Sets:" << NoOfSets << " Size of each Set: " << SetSize << endl;
    cout << elapsed_secs << " sec" << endl;
}

void speedTestSTL(int NoOfSets, int SetSize) {
    clock_t begin = clock();
    for (int i = 0; i < NoOfSets; i++) {
        set<int> STL_test;
        for (int j = 0; j < SetSize; j++) {
            STL_test.insert(j);
        }
    }  
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    cout << "****\tSTL-Set\tNumber of Sets:" << NoOfSets << " Size of each Set: " << SetSize << endl;
    cout << elapsed_secs << " sec" << endl;
}


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
    cout << "setTest1 size is: " << setTest1.size() << endl;

    skip_set<string, 5> setTest2;
    setTest2.insert("a");
    setTest2.insert("b");    
    setTest2.insert("c");
    setTest2.printSet();
    cout << "setTest2 size is: " << setTest2.size() << endl;
    if (setTest2.contains("a")) {cout << "a found" << endl;} else {cout << "a not found" << endl; }


    if (setTest1.contains(20)) {cout << "20 found" << endl;} else {cout << "20 not found" << endl; }
    if (setTest1.contains(25)) {cout << "25 found" << endl;} else {cout << "25 not found" << endl; }
    // for (int i = 0; i < 5; i++) {
    //     cout << setTest1.randomLevel() << endl;
    // }

    // erase test
    // bool erased;
    for (int i = 20; i < 22; i++) {
        if(setTest1.erase(i)) { 
            cout << i << " was erased in the middle" << endl;
        } else {
            cout << i <<" was not erased in the middle" << endl;
        }
    }

    string x = "b";
    if(setTest2.erase(x)) { 
        cout << x << " was erased in the middle" << endl;
    } else {
        cout << x <<" was not erased in the middle" << endl;
    }



    cout << "erase at first and last position:" << endl;
    setTest1.erase(30);
    setTest1.erase(10);
    setTest1.insert(99);
    setTest1.insert(1);

    setTest2.erase("a");
    setTest2.erase("c");
    setTest2.insert("d");
    setTest2.insert("f");
    setTest2.insert("e");
    setTest2.insert("h");
    setTest2.insert("g");

    cout << endl << "setTest1 size is: " << setTest1.size() << endl;
    cout << endl << "setTest1 size is: " << setTest2.size() << endl;

    setTest1.printSet();
    setTest2.printSet();


    cout << endl << "****\tIterator Tests\t****" << endl;

    skip_set_iterator<int> it = setTest1.begin();
    auto iterator = setTest1.begin();
    if ( iterator == it) {
        cout << "== operator works fine." << endl;
    }

    // set 1
    cout << endl << "Forward Iterator using * != ++ operators for this loop:" << endl;
    for (auto it = setTest1.begin(); it != setTest1.end(); it++) {
        cout << *it << endl;
    }
    cout << "Backward Iterator using * != -- operators for this loop:" << endl;
    for (auto it = setTest1.rbegin(); it != setTest1.rend(); --it) {
        cout << *it << endl;
    }
    // set2
    cout << endl << "Forward Iterator using * != ++ operators for this loop:" << endl;
    for (auto it = setTest2.begin(); it != setTest2.end(); it++) {
        cout << *it << endl;
    }
    cout << "Backward Iterator using * != -- operators for this loop:" << endl;
    for (auto it = setTest2.rbegin(); it != setTest2.rend(); --it) {
        cout << *it << endl;
    }


    // speedTestDIY(10, 10000);
    // speedTestDIY(100, 10000);
    // speedTestDIY(1000, 10000);
    // speedTestDIY(2000, 10000);
    // speedTestDIY(3000, 10000);

    // speedTestSTL(10, 10000);
    // speedTestSTL(100, 10000);
    // speedTestSTL(1000, 10000);
    // speedTestSTL(2000, 10000);   
    // speedTestSTL(3000, 10000);

    return 0;
}
