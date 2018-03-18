#include <iostream>
#include <string>
#include "skip_set.h"


using namespace std;

int main() {
    cout << "world hi" << endl;

  
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
    skip_set_node<string> testnode1(4, x1);
    skip_set_node<string> testnode2(4, x2);

    skip_set<string, 3> setTest1;
    int y = setTest1.size();
    cout << y << endl;

    return 0;
}
