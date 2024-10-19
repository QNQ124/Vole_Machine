#include <iostream>
#include "volemachine.h"

using namespace std;

int main(){

    Memory o;
    o.setMemory(0, "FF");
    o.setMemory(1, "AA");
    o.print();
    cout << "\n\n\n\n\n\n";
    o.ClearAll();
    o.print();

}