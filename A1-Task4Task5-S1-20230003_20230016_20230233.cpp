#include "A1-Task4Task5-S1-20230003_20230016_20230233.h"
#include <bits/stdc++.h>

using namespace std;


int Machine::index = 0;

// Convert a hexadecimal string to a binary string (8 bits)
string ALU::hexToBin(const string& hexa) {
    stringstream ss;
    ss << hex << hexa;
    unsigned n;
    ss >> n;
    bitset<8> b(n);  // 8-bit to limit to 8 bits
    return b.to_string();
}


string ALU::dec_to_hex(int num) {
    if (num == 0)
    {
        return "0";
    }
    string result = "";
    string hex_chars = "0123456789ABCDEF";
    while (num >= 1) {
        result = hex_chars[num % 16] + result;
        num /= 16;
    }
    return result;
}


int ALU::bin_to_dec(string num) {
    int strlen = num.length();
    int result = 0;
    for (int i = 0; i < strlen; i++) {
        result += (pow(2, (strlen - (1 + i))) * (num[i] - '0'));
    }
    return result;
}


string ALU::decFract_to_bin(float fract)
{
    fract = abs(fract);
    string result = "";
    for (int i = 0; i < 4; ++i) {
        int floor = 0;
        fract *=2;
        floor = fract;
        if(floor == 1)
        {
            fract --;
            result += '1';
        }else { result += '0'; }
    }
    return result;
}

string ALU::dec_to_bin(int num) {
    string result = "";
    while (num >= 1) {
        result = to_string(num % 2) + result;
        num /= 2;
    }
    if(result == "")
    {
        return "0";
    }
    return result;
}


string ALU::decFract_to_hex(int intgr,float fract)
{
    string bin_fract = ALU::decFract_to_bin(fract);
    string bin_intgr = ALU::dec_to_bin(intgr);
    int sign = (fract < 0) ? 1 : 0;
    int expo_count = 0;
    if(intgr == 0)
    {
        for (int i = 0; i < bin_fract.size(); ++i) {
            if(bin_fract[i] == '0')
            {
                expo_count++;
            } else if (bin_fract[i] == '1')
            {
                expo_count++;
                break;
            }
        }
        int expo = 4 - expo_count + (sign * 8);
        string result = ALU::dec_to_bin(expo) + bin_fract.substr(expo_count,2) + "00";

        return ALU::binToHex(result);
    }
    else
    {
        expo_count = bin_intgr.size() - 1;
        int expo = 4 + expo_count + (sign * 8);
        string result = ALU::dec_to_bin(expo) + bin_intgr.substr(1) +bin_fract;

        return ALU::binToHex(result);
    }

}


float ALU::binFract_to_dec(string fract)
{
    int strlen = fract.length();
    float result = 0;
    for (int i = 0; i < strlen; i++) {
        result += (pow(2, (-(1 + i))) * (fract[i] - '0'));
    }
    return result;
}


float ALU::floatTodecimal(string hexa1)
{
    string bin = ALU::hexToBin(hexa1);
    char sign_c = bin[0];
    int sign = 1;
    if(sign_c == '1')
    { sign = -1; }

    string expo = bin.substr(1,3);
    string fraction = bin.substr(4,4);

    int exp = ALU::bin_to_dec(expo);
    float fract = ALU::binFract_to_dec(fraction);
    fract+=1;

    return (sign * (pow(2,exp-4)) * fract);


}


string ALU::addTwoFloat(string hexa1, string hexa2){

    double sum;
    sum = ALU::floatTodecimal(hexa1) + ALU::floatTodecimal(hexa2);
    int intgr = sum;
    double fraction;
    fraction = sum - intgr;

    string result = ALU::decFract_to_hex(intgr,fraction);

    // Ensure the result has at least two characters for proper padding
    if (result.length() == 1) {
        result = "0" + result;
    } else if (result == "0") {
        return "00";
    }

    return result;
}

// Function to convert hexadecimal to decimal
int ALU::hexTodec(string num) {
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

int ALU::hexTodec(char hexChar) {
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
string ALU::binToHex(const string& binary) {
    if (binary == "00000000") {
        return "00";
    }
    stringstream ss;
    bitset<8> b(binary);  // 8-bit for limiting to 8 bits
    ss << hex << uppercase << b.to_ulong();
    return ss.str();
}

string ALU::bitwise_OR(string hexa1, string hexa2){

    int hex1 = ALU::hexTodec(hexa1);
    int hex2 = ALU::hexTodec(hexa2);

    string result = ALU::dec_to_hex((hex1 | hex2));

    // Ensure the result has at least two characters for proper padding
    if (result.length() == 1) {
        result = "0" + result;
    } else if (result == "0") {
        return "00";
    }
    return result;
}

string ALU::bitwise_AND(string hexa1, string hexa2){

    int hex1 = ALU::hexTodec(hexa1);
    int hex2 = ALU::hexTodec(hexa2);

    string result = ALU::dec_to_hex((hex1 & hex2));

    // Ensure the result has at least two characters for proper padding
    if (result.length() == 1) {
        result = "0" + result;
    } else if (result == "0") {
        return "00";
    }

    return result;
}

string ALU::bitwise_XOR(string hexa1, string hexa2){

    int hex1 = ALU::hexTodec(hexa1);
    int hex2 = ALU::hexTodec(hexa2);

    string result = ALU::dec_to_hex((hex1 ^ hex2));

    // Ensure the result has at least two characters for proper padding
    if (result.length() == 1) {
        result = "0" + result;
    } else if (result == "0") {
        return "00";
    }

    return result;
}

string ALU::bitwise_Rotate( string hexa, int steps) {


    int hex = ALU::hexTodec(hexa);

    int result = hex >> steps;

    string nResult = ALU::dec_to_hex(result);

    // Ensure the result has at least two characters for proper padding
    if (nResult.length() == 1) {
        nResult = "0" + nResult;
    } else if (nResult == "0") {
        return "00";
    }

    return nResult;
}

// Function to add two hexadecimal numbers by converting them to binary (only 8-bit result)
string ALU::addBinary(const string& hexa1, const string& hexa2) {
    string bin1 = ALU::hexToBin(hexa1);
    string bin2 = ALU::hexToBin(hexa2);

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

bool ALU::isValidInput(string &i) {
    // Convert any alphabetic characters to uppercase
    for (auto &c : i) {
        if (isalpha(c)) {
            c = toupper(c); // Convert to uppercase
        }
    }

    // Define the regex pattern for the input
    regex regex1(R"(^([1-9]|[A-D])[0-9A-F]{3}$)");

    // Check if the input matches the regex
    return regex_match(i, regex1);
}


//////////////////////////////////////////////////////////////////////
void Register::setRegister(int index, string output) {

    if(output.size() == 1){
        registers[index] = "";
        registers[index] += "0";
        registers[index] += output;
    }
    else {
        registers[index] = output;
    }
}

string Register::getFromRegister(int index) {

    return registers[index];
}

void Register::Clear() {

    for (int i = 0; i < 16; ++i) {
        registers[i] = "00";
    }
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

void Memory::setMemory(int index, string input) {

    if(input.size() == 1){
        Mem[index] = "";
        Mem[index] += "0";
        Mem[index] = input;
    }
    else {
        Mem[index] = input;
    }
}

void Memory::print(){
    for (int i = 0; i < 256; i++){

        if(i % 16 == 0){
            cout << endl;
        }
        cout << Mem[i] << " ";
    }
    cout << endl;
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

void Instructions::ClearInstruction(){

    for (int i = 0; i < 128; ++i) {
        instruction[i] = "0000";
    }
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

void Machine::ClearMemory(){

    Storage.ClearAll();
    index = 0;

}
void Machine::ClearRegister(){

    Processor.Clear();
    index = 0;

}
void Machine::getPC() {

    cout << "0X" << Operation.dec_to_hex(index) << endl;
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
    char skip1, skip2;

    int counter = 0;

    bool stop = false;

    programCounter = &Storage.getAllMemory();

    skip1 = (*programCounter)[index][0];
    skip2 = (*programCounter)[index][1];

    if(skip1 == '0' && skip2 == '0' && index != 0){

        stop = true;
        cout << "\n-------------------------\n";
        cout << "Opcode not found. Halting";
        cout << "\n-------------------------\n";
    }

    while(!stop) {

        char operation = (*programCounter)[index][0];

        if (operation == '1') {
            int indexRegister = Operation.hexTodec((*programCounter)[index][1]);
            index++;
            int indexOfMemory = Operation.hexTodec((*programCounter)[index]);
            Processor.setRegister(indexRegister, Storage.getMemoryCell(indexOfMemory));
        }
        else if (operation == '2') {
            int indexRegister = Operation.hexTodec((*programCounter)[index][1]);
            index++;
            dataToRegister = (*programCounter)[index];
            Processor.setRegister(indexRegister, dataToRegister);
        }
        else if (operation == '3') {
            int indexRegister = Operation.hexTodec((*programCounter)[index][1]);
            string dataFromRegister = Processor.getFromRegister(indexRegister);
            string newData = "0";
            index++;
            int indexOfMemory = Operation.hexTodec((*programCounter)[index]);

            if(indexOfMemory == 0) {
                Storage.setMemory(indexOfMemory, dataFromRegister);
                cout << "\n---------------------------------\n";
                DisplayScreen();
                cout << "---------------------------------\n";
            }

            Storage.setMemory(indexOfMemory, dataFromRegister);

        }
       else if(operation == '4'){
           index++;
           int registerCell1 = Operation.hexTodec((*programCounter)[index][0]);
           int registerCell2 = Operation.hexTodec((*programCounter)[index][1]);
           string dataFromCell1 = Processor.getFromRegister(registerCell1);
           Processor.setRegister(registerCell1, "00");
           Processor.setRegister(registerCell2, dataFromCell1);

       }
       else if(operation == '5'){
           int indexRegister = Operation.hexTodec((*programCounter)[index][1]);
           index++;
           int registerCell1 = Operation.hexTodec((*programCounter)[index][0]);
           int registerCell2 = Operation.hexTodec((*programCounter)[index][1]);
           string dataCell1 = Processor.getFromRegister(registerCell1);
           string dataCell2 = Processor.getFromRegister(registerCell2);

           Processor.setRegister(indexRegister, Operation.addBinary(dataCell1, dataCell2));
       }
       else if(operation == '6'){
           int indexRegister = Operation.hexTodec((*programCounter)[index][1]);
           index++;
           int registerCell1 = Operation.hexTodec((*programCounter)[index][0]);
           int registerCell2 = Operation.hexTodec((*programCounter)[index][1]);
           string dataCell1 = Processor.getFromRegister(registerCell1);
           string dataCell2 = Processor.getFromRegister(registerCell2);

           Processor.setRegister(indexRegister, Operation.addTwoFloat(dataCell1, dataCell2));
       }
       else if(operation == '7'){
           int indexRegister = Operation.hexTodec((*programCounter)[index][1]);
           index++;
           int registerCell1 = Operation.hexTodec((*programCounter)[index][0]);
           int registerCell2 = Operation.hexTodec((*programCounter)[index][1]);
           string dataCell1 = Processor.getFromRegister(registerCell1);
           string dataCell2 = Processor.getFromRegister(registerCell2);

           Processor.setRegister(indexRegister, Operation.bitwise_OR(dataCell1, dataCell2));

       }
        else if(operation == '8'){
            int indexRegister = Operation.hexTodec((*programCounter)[index][1]);
            index++;
            int registerCell1 = Operation.hexTodec((*programCounter)[index][0]);
            int registerCell2 = Operation.hexTodec((*programCounter)[index][1]);
            string dataCell1 = Processor.getFromRegister(registerCell1);
            string dataCell2 = Processor.getFromRegister(registerCell2);

            Processor.setRegister(indexRegister, Operation.bitwise_AND(dataCell1, dataCell2));

        }
        else if(operation == '9'){
            int indexRegister = Operation.hexTodec((*programCounter)[index][1]);
            index++;
            int registerCell1 = Operation.hexTodec((*programCounter)[index][0]);
            int registerCell2 = Operation.hexTodec((*programCounter)[index][1]);
            string dataCell1 = Processor.getFromRegister(registerCell1);
            string dataCell2 = Processor.getFromRegister(registerCell2);

            Processor.setRegister(indexRegister, Operation.bitwise_XOR(dataCell1, dataCell2));

        }
        else if(operation == 'A'){
            int indexRegister = Operation.hexTodec((*programCounter)[index][1]);
            string dataCell = Processor.getFromRegister(indexRegister);
            index++;
            int steps = Operation.hexTodec((*programCounter)[index][1]);
            Processor.setRegister(indexRegister, Operation.bitwise_Rotate(dataCell, steps));
        }
       else if(operation == 'B') {

           counter = index + 2;
           int indexRegister = Operation.hexTodec((*programCounter)[index][1]);
           string dataCell0 = Processor.getFromRegister(0);
           string dataCellR = Processor.getFromRegister(indexRegister);

           if (dataCell0 == dataCellR) {
               index++;
               int indexOfMemory = Operation.hexTodec((*programCounter)[index]);
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
        else if(operation == 'D'){
            counter = index + 2;
            int indexRegister = Operation.hexTodec((*programCounter)[index][1]);
            string dataCell0 = Processor.getFromRegister(0);
            string dataCellR = Processor.getFromRegister(indexRegister);

            if (dataCell0 < dataCellR) {
                index++;
                int indexOfMemory = Operation.hexTodec((*programCounter)[index]);
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

       else if(operation == 'C'){
           return true;
           break;
      }
      else{
           index++;
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

bool Machine::ReadFromFile(ifstream &inputFile) {


    string line;
    int xCount = 0;
    ClearInstruct();
    while(getline(inputFile, line)){

        if(!Operation.isValidInput(line)){

            ClearInstruct();
            index = 0;
            return false;
        }

        transform(line.begin(), line.end(), line.begin(), ::toupper);
        Input.setInstruction(xCount, line);

        xCount++;

    }
    return true;

}

void Machine::ClearInstruct() {

    Input.ClearInstruction();
}