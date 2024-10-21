#include <iostream>
#include "volemachine.h"
#include <bits/stdc++.h>

using namespace std;

int main(){

    // Display the welcome message
    cout << "|-------------- Ahlan ya User ya Habibi --------------|\n"
         << "|    In this Application we have a Vole machine       |\n"
         << "|    simulator. You must input a file to read a data  |\n"
         << "|    and Instructions from it and the program will    |\n"
         << "|    Display the Memory and register to you.          |\n"
         << "|-----------------------------------------------------|\n\n";


    string filename;
    cout << "Please enter a file name: ";
    cin >> filename;

    ifstream file(filename, ios::in);

    while(true){
        if(file.is_open()){
            break;
        }
        else{
            cout << "Error: Invalid file name please enter again: ";
            cin >> filename;
            continue;
        }
    }


    Machine o;

    o.ReadFromFile(file);
    o.DisplayMemory();
    cout << "\n\n\n\n\n";
    o.RunInstruction();
    cout << "\n\n\n\n\n";
    o.DisplayMemory();
    cout << "\n\n\n\n\n";
    o.DisplayRegister();

}