#include <iostream>
#include "volemachine.h"
#include <bits/stdc++.h>

using namespace std;

int main(){

    ifstream file("Input.txt", ios::in);

    Machine o;

    o.ReadFromFile(file);
    o.DisplayMemory();
    cout << "\n\n\n\n\n";
    o.RunInstruction();
    cout << "\n\n\n\n\n";
    o.DisplayMemory();

}