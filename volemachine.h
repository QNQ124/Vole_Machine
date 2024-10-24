#ifndef VOLE_MACHINE_VOLEMACHINE_H
#define VOLE_MACHINE_VOLEMACHINE_H

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

////////////////////////////////////////////////////////////////////
class Register{

private:
    vector <string> registers;

public:

    Register() : registers(16, "00"){}
    void setRegister(int , string);
    string getFromRegister(int);
    void Clear (int);
    void print();

};


/////////////////////////////////////////////////////////////////////
class Memory{

private:
    vector <string> Mem;

public:
    Memory() : Mem(256, "00"){}
    void setMemory(int, string);
    vector<string> &getAllMemory();
    string getMemoryCell(int);
    void ClearAll ();
    void ClearCell(int);
    void print();

};


//////////////////////////////////////////////////////////////////////////
class Instructions{

private:
    vector <string> instruction;

public:
    Instructions() : instruction(128){}
    void setInstruction(int, string);
    vector<string> &getInstruction();
    string getCurrentInstruction(int index);

};


//////////////////////////////////////////////////////////////
class Machine{

private:
    Register Processor;
    Memory Storage;
    Instructions Input;
    vector <string> *programCounter;
    static int index;
public:
    vector<string> *PC;
    bool getNextInstruction(); // increment 2
    void ReadFromFile(ifstream &inputFile); // DONE
    void RunInstruction(); // current and next
    string getIR();
    void getPC();
    void DisplayMemory(); // DONE
    void DisplayScreen();
    void DisplayRegister(); // DONE
};


#endif //VOLE_MACHINE_VOLEMACHINE_H
