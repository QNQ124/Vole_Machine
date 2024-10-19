#include "volemachine.h"
#include <bits/stdc++.h>

using namespace std;


//////////////////////////////////////////////////////////////////////
void Register::setRegister(int index, string output) {

    registers[index] = output;

}

void Register::Clear(int index) {

    registers[index] = "00";
}

void Register::print(){
    for (const auto & i : registers) {
        cout << i << endl;
    }
}

//////////////////////////////////////////////////////////////////////
void Memory::ClearAll() {

    fill(Mem.begin(), Mem.end(),"00");
}

void Memory::ClearCell(int index) {

   if(index % 2 == 0){
      Mem[index] = "00";
      Mem[index + 1] = "00";
   }
   else{
       Mem[index] = "00";
       Mem[index - 1] = "00";
   }
}

void Memory::setMemory(int index, string input) {

    Mem[index] = input;
}

void Memory::print(){
    for (const auto & i : Mem) {
        cout << i << endl;
    }
}

vector<string> &Memory::getMemory() {

    return Mem;
}

////////////////////////////////////////////////////////////////////
void Instructions::setInstruction(int index, string input) {

    instruction[index] = input;
}

vector<string> &Instructions::getInstruction(){

    return instruction;
}

//////////////////////////////////////////////////////////////////////
void Machine::DisplayMemory() {

    Storage.print();
}

void Machine::DisplayRegister() {

    Processor.print();
}

void Machine::RunInstruction() {

    vector <string> input = Input.getInstruction();


    int counter = 0;
    for (int i = 0; i < 128; i++) {
        if(input[i] == ""){
            break;
        }
         string data = "", instruction = "";
         instruction += input[i][0];
         instruction += input[i][1];
         Storage.setMemory(counter, instruction);
         counter++;
         data += input[i][2];
         data += input[i][3];
         Storage.setMemory(counter, data);
         counter++;
    }

    Machine::getNextInstruction();

}

string Machine::getNextInstruction() {

    vector <string> data = Storage.getMemory();

    data[0]
}

void Machine::ReadFromFile(ifstream &inputFile) {

    if(!inputFile.is_open()){
        cout << "Error: File doesn't exist" << endl;
    }
    else{
        string line;
        int counter = 0;

        while(getline(inputFile, line)){

            Input.setInstruction(counter, line);
            counter++;

        }

    }


}