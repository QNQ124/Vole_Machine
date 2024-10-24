#include "volemachine.h"
#include <bits/stdc++.h>

using namespace std;


int Machine::index = 0;

// Convert a hexadecimal string to a binary string (8 bits)
string hexToBin(const string& hexa) {
    stringstream ss;
    ss << hex << hexa;
    unsigned n;
    ss >> n;
    bitset<8> b(n);  // 8-bit to limit to 8 bits
    return b.to_string();
}

string dec_to_hex(int num) {
    string result = "";
    string hex_chars = "0123456789ABCDEF";
    while (num >= 1) {
        result = hex_chars[num % 16] + result;
        num /= 16;
    }
    return result;
}

int bin_to_dec(string num) {
    int strlen = num.length();
    int result = 0;
    for (int i = 0; i < strlen; i++) {
        result += (pow(2, (strlen - (1 + i))) * (num[i] - '0'));
    }
    return result;
}

string decFract_to_hex(float fract)
{
    string result = "";
    for (int i = 0; i < 4; ++i) {
        int floor = 0;
        fract *=2;
        floor = fract;
        if(floor == 1)
        {
            result += '1';
        }else { result += '0'; }
    }
    int decTohex = bin_to_dec(result);

    return dec_to_hex(decTohex);
}


float binFract_to_dec(string fract)
{
    int strlen = fract.length();
    float result = 0;
    for (int i = 0; i < strlen; i++) {
        result += (pow(2, (-(1 + i))) * (fract[i] - '0'));
    }
    return result;
}

float floatTodecimal(string hexa1)
{
    string bin = hexToBin(hexa1);
    char sign_c = bin[0];
    int sign = 1;
    if(sign_c == '1')
    { sign = -1; }

    string expo = bin.substr(1,3);
    string fraction = bin.substr(4,4);

    int exp = bin_to_dec(expo);
    float fract = binFract_to_dec(fraction);

    if(exp == 0)
    {
        return (sign * (pow(2,1-3)) * fract);

    }else
    {
        fract+=1;
        return (sign * (pow(2,exp-3)) * fract);

    }
}


string addTwoFloat(string hexa1, string hexa2){ //

    float sum;
    sum = floatTodecimal(hexa1) + floatTodecimal(hexa2);
    int expo = sum;
    float fraction = (sum - expo)/expo;
    expo = log2(expo) + 3;
    if(sum < 0)
    {expo + 8; }
    string result = dec_to_hex(expo) + decFract_to_hex(fraction);
    return result;

}

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

string Instructions::getCurrentInstruction(int Index) {

    return instruction[(Index / 2) - 1];
}

//////////////////////////////////////////////////////////////////////
void Machine::DisplayMemory() {

    Storage.print();
}

void Machine::DisplayRegister() {

    Processor.print();
}

string Machine::getIR() {

    return Input.getCurrentInstruction(index);
}

void Machine::getPC() {

    cout << "0X" << dec_to_hex(index) << endl;
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

}

void Machine::DisplayScreen(){

    cout << "The output screen from (3R00): " << Storage.getMemoryCell(0) << endl;
}
bool Machine::getNextInstruction() {

    string dataToRegister;

    int counter = 0;

    bool stop = false;

    programCounter = &Storage.getAllMemory();


    while(!stop) {

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
            if(indexOfMemory == 0) {
                Storage.setMemory(indexOfMemory, dataFromRegister);
                cout << "\n-----------------------\n";
                DisplayScreen();
                cout << "-------------------------\n";
            }
            Storage.setMemory(indexOfMemory, dataFromRegister);

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
       if(operation == '6'){
           int indexRegister = hexTodec((*programCounter)[index][1]);
           index++;
           int registerCell1 = hexTodec((*programCounter)[index][0]);
           int registerCell2 = hexTodec((*programCounter)[index][1]);
           string dataCell1 = Processor.getFromRegister(registerCell1);
           string dataCell2 = Processor.getFromRegister(registerCell2);

           Processor.setRegister(indexRegister, addTwoFloat(dataCell1, dataCell2));
       }

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
           return true;
           break;
      }
       if(index == 255){
           index = counter;
       }
       else {
           index++;
       }
    stop = true;
    }

    return false;
}

void Machine::ReadFromFile(ifstream &inputFile) {

    if(!inputFile.is_open()){
        cout << "Error: File doesn't exist" << endl;
    }
    else{
        string line;
        int instructionIndex = 0, xCount = 0;

        while(getline(inputFile, line)){

            string singleInstruction = "";
            xCount = 0;

            for (int i = 0; i < line.size(); i++) {

                if(line[i] == 'X'){
                    xCount++;

                    if(xCount == 3){
                        singleInstruction += toupper(line[i + 1]);
                        singleInstruction += toupper(line[i + 2]);
                    }
                    else{
                        singleInstruction += toupper(line[i + 1]);
                    }
                }
            }
            Input.setInstruction(instructionIndex, singleInstruction);

            instructionIndex++;

        }

    }

}