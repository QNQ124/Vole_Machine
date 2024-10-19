#ifndef VOLE_MACHINE_VOLEMACHINE_H
#define VOLE_MACHINE_VOLEMACHINE_H

#include <iostream>
#include <vector>

using namespace std;

class Register{

private:
    vector <string> registers;

public:

    Register() : registers(16, "00"){}
    void setRegister(int , string);
    void Clear (int);

};

class Memory{

private:
    vector <string> Mem;

public:
    Memory() : Mem(256, "00"){}
    void setMemory(int, string);
    void ClearAll ();
    void ClearCell(int);
    void print(){

        for (const auto & i : Mem) {
            cout << i << endl;
        }
    }


};

class Instructions{

private:
    vector <string> Instruction;

public:
//    ReadFromFile();
//    Decode();

};

class Machine{
    Machine();
    string getNextInstruction();
    void RunInstruction();
    void DisplayMemory();
    void DisplayRegister();

};

#endif //VOLE_MACHINE_VOLEMACHINE_H
