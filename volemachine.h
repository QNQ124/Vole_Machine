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

class ALU{

public:

// Convert a hexadecimal string to a binary string (8 bits)
    string hexToBin(const string& hexa);
    string dec_to_hex(int num);
    int bin_to_dec(string num);
    string decFract_to_hex(float fract);
    float binFract_to_dec(string fract);
    float floatTodecimal(string hexa1);
    string addTwoFloat(string hexa1, string hexa2);

// Function to convert hexadecimal to decimal
    int hexTodec(string num);

    int hexTodec(char hexChar);

// Convert a binary string to a hexadecimal string (8 bits)
    string binToHex(const string& binary);
    string fract(float fract);
    string bitwise_Rotate( string hexa, int steps);
    string bitwise_XOR(string hexa1, string hexa2);
    string bitwise_AND(string hexa1, string hexa2);
    string bitwise_OR(string hexa1, string hexa2);
// Function to add two hexadecimal numbers by converting them to binary (only 8-bit result)
    string addBinary(const string& hexa1, const string& hexa2);


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
    ALU Operation;
    vector <string> *programCounter;
    static int index;
public:
    vector<string> *PC;
    bool getNextInstruction(); // increment 2
    bool ReadFromFile(ifstream &inputFile); // DONE
    void RunInstruction(); // current and next
    string getIR();
    void getPC();
    void DisplayMemory(); // DONE
    void DisplayScreen();
    void DisplayRegister(); // DONE
};


#endif //VOLE_MACHINE_VOLEMACHINE_H
