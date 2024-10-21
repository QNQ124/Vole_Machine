#include "volemachine.h"
#include <bits/stdc++.h>

using namespace std;


// Function to convert hexadecimal to decimal
int hexTodec(string num) {
    int strlen = num.length();
    int result = 0;
    for (int i = 0; i < strlen; i++) {
        if (num[i] >= 'A' && num[i] <= 'F') {
            result += (pow(16, (strlen - (1 + i))) * (num[i] - 'A' + 10));
        } else {
            result += (pow(16, (strlen - (1 + i))) * (num[i] - '0'));
        }
    }
    return result;
}

int hexTodec(char hexChar) {
    if (hexChar >= '0' && hexChar <= '9') {
        return hexChar - '0'; // Convert character '0'-'9' to integer 0-9
    } else if (hexChar >= 'A' && hexChar <= 'F') {
        return hexChar - 'A' + 10; // Convert character 'A'-'F' to integer 10-15
    } else if (hexChar >= 'a' && hexChar <= 'f') {
        return hexChar - 'a' + 10; // Convert character 'a'-'f' to integer 10-15
    }
    return 0;
}

// Convert a hexadecimal string to a binary string (8 bits)
string hexToBin(const string& hexa) {
    stringstream ss;
    ss << hex << hexa;
    unsigned n;
    ss >> n;
    bitset<8> b(n);  // 8-bit to limit to 8 bits
    return b.to_string();
}

// Convert a binary string to a hexadecimal string (8 bits)
string binToHex(const string& binary) {
    stringstream ss;
    bitset<8> b(binary);  // 8-bit for limiting to 8 bits
    ss << hex << uppercase << b.to_ulong();
    return ss.str();
}

// Function to add two hexadecimal numbers by converting them to binary (only 8-bit result)
string addBinary(const string& hexa1, const string& hexa2) {
    string bin1 = hexToBin(hexa1);
    string bin2 = hexToBin(hexa2);

    string result = "";  // To store the result of addition
    int carry = 0;       // To store the carry value during addition

    // Add the binary numbers from right to left
    for (int i = bin1.size() - 1; i >= 0; i--) {
        int bit1 = bin1[i] - '0';  // Convert char '0' or '1' to integer 0 or 1
        int bit2 = bin2[i] - '0';

        int sum = bit1 + bit2 + carry;  // Add corresponding bits and carry

        // The new bit to add to the result is sum % 2
        result.insert(result.begin(), (sum % 2) + '0');  // Convert to char and add to result

        // Calculate the new carry: 1 if sum >= 2, otherwise 0
        carry = sum / 2;
    }

    // If there is a carry left at the end, prepend it to the result
    if (carry) {
        result.insert(result.begin(), '1');
    }

    // Only keep the least significant 8 bits (if result is longer, discard the higher bits)
    result = result.substr(result.size() - 8);

    return binToHex(result);  // Convert the result back to hexadecimal
}


//////////////////////////////////////////////////////////////////////
void Register::setRegister(int index, string output) {

    registers[index] = output;

}

string Register::getFromRegister(int index) {

    return registers[index];
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

vector<string> &Memory::getAllMemory() {

    return Mem;
}

string Memory::getMemoryCell(int index) {

    return Mem[index];
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

    vector <string> data = Storage.getAllMemory();

    programCounter = &data;

    Machine::getNextInstruction();

}


void Machine::getNextInstruction() {

    string dataToRegister;

    static int index = 0;
    int counter = 0;

    while(true) {

        char operation = (*programCounter)[index][0];

        if (operation == '1') {
            int indexRegister = hexTodec((*programCounter)[index][1]);
            index++;
            int indexOfMemory = hexTodec((*programCounter)[index]);
            Processor.setRegister(indexRegister, Storage.getMemoryCell(indexOfMemory));
        }
        if (operation == '2') {
            int indexRegister = hexTodec((*programCounter)[index][1]);
            index++;
            dataToRegister = (*programCounter)[index];
            Processor.setRegister(indexRegister, dataToRegister);
        }
        if (operation == '3') {
            int indexRegister = hexTodec((*programCounter)[index][1]);
            string dataFromRegister = Processor.getFromRegister(indexRegister);
            index++;
            int indexOfMemory = hexTodec((*programCounter)[index]);
            Storage.setMemory(indexOfMemory, dataFromRegister);
//
        }
       if(operation == '4'){
           index++;
           int registerCell1 = hexTodec((*programCounter)[index][0]);
           int registerCell2 = hexTodec((*programCounter)[index][1]);
           string dataFromCell1 = Processor.getFromRegister(registerCell1);
           Processor.setRegister(registerCell1, "00");
           Processor.setRegister(registerCell2, dataFromCell1);

       }
       if(operation == '5'){
           int indexRegister = hexTodec((*programCounter)[index][1]);
           index++;
           int registerCell1 = hexTodec((*programCounter)[index][0]);
           int registerCell2 = hexTodec((*programCounter)[index][1]);
           string dataCell1 = Processor.getFromRegister(registerCell1);
           string dataCell2 = Processor.getFromRegister(registerCell2);

           Processor.setRegister(indexRegister, addBinary(dataCell1, dataCell2));
       }
//       if(operation == '6'){
//           int indexRegister = hexTodec((*programCounter)[index][1]);
//           index++;
//           int registerCell1 = hexTodec((*programCounter)[index][0]);
//           int registerCell2 = hexTodec((*programCounter)[index][1]);
//           string dataCell1 = Processor.getFromRegister(registerCell1);
//           string dataCell2 = Processor.getFromRegister(registerCell2);
//
//           Processor.setRegister(indexRegister, addBinary(dataCell1, dataCell2));
//       }

//       13FF
       if(operation == 'B') {

            counter = index + 2;
           int indexRegister = hexTodec((*programCounter)[index][1]);
           string dataCell0 = Processor.getFromRegister(0);
           string dataCellR = Processor.getFromRegister(indexRegister);

           if (dataCell0 == dataCellR) {
               index++;
               int indexOfMemory = hexTodec((*programCounter)[index]);
               if (indexOfMemory % 2 == 0) {
                   index = indexOfMemory;
                   programCounter = &Storage.getAllMemory();
                   continue;
               } else {
                   index = indexOfMemory - 1;
                   programCounter = &Storage.getAllMemory();
                   continue;
               }
           }
           else {
            index += 2;
           }
       }

       if(operation == 'C'){
           break;
      }
       if(index == 255){
           index = counter;
       }
       else {
           index++;
       }
    }
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