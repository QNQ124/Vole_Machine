#include "vmachine.h"
#include <QBitArray>
#include <QFile>
#include <QTextStream>
#include <QtMath>
#include <QDebug>
#include <QtGlobal>
#include <cmath>     // For std::log2 if needed
#include <bits/stdc++.h>
#include <QRegularExpression>
#include <QString>

using namespace std;
int Machine::index = 0;
int Machine::Counter = 0;
int Machine::Count = 0;
bool StartOrEnd = false;
bool halt = false;


// Convert a hexadecimal string to a binary string (8 bits)
QString ALU::hexToBin(const QString &hexa) {
    bool ok;
    int n = hexa.toInt(&ok, 16); // Convert hex to int
    return QString::number(n, 2).rightJustified(8, '0'); // Convert int to binary and pad to 8 bits
}

QString ALU::decToHex(int num) {
    if (num == 0) {
        return "0";
    }

    QString result = "";
    QString hex_chars = "0123456789ABCDEF";

    while (num > 0) {
        result.prepend(hex_chars[num % 16]); // Prepend to build the hex string
        num /= 16;
    }

    return result; // Return the hexadecimal QString
}


int ALU::binToDec(const QString& num) {
    int result = 0;
    int strlen = num.length();

    for (int i = 0; i < strlen; i++) {
        // Convert each character to an integer (0 or 1) and calculate its decimal value
        result += (num[i].digitValue() * qPow(2, (strlen - 1 - i)));
    }

    return result;
}

QString ALU::fract(float fract) {
    int sign = 1;
    int expo = 0;
    int mntsa = 0;

    if (fract < 0) {
        sign = -1;
    }

    // Handle specific fractional cases
    if (qFabs(fract) == 0.5) {
        expo = 2;
        mntsa = 0;
    } else if (qFabs(fract) == 0.25) {
        expo = 1;
        mntsa = 0;
    } else if (qFabs(fract) >= 0.5) {
        expo = 2;
        QString result = "";
        for (int i = 0; i < 4; ++i) {
            fract *= 2;
            int floor = static_cast<int>(fract); // Using static_cast for clarity
            if (floor == 1) {
                result += '1';
            } else {
                result += '0';
            }
            fract -= floor; // Reduce the fractional part
        }
        mntsa = ALU::binToDec(result);
    } else if (qFabs(fract) > 0.25) {
        expo = 1;
        QString result = "";
        for (int i = 0; i < 4; ++i) {
            fract *= 2;
            int floor = static_cast<int>(fract);
            if (floor == 1) {
                result += '1';
            } else {
                result += '0';
            }
            fract -= floor; // Reduce the fractional part
        }
        mntsa = ALU::binToDec(result);
    }

    if (sign != 1) {
        expo += 8;
    }

    return ALU::decToHex(expo) + ALU::decToHex(mntsa);
}

QString ALU::dec_to_bin(int num)
{
    QString result;

    while (num >= 1) {
        result.prepend(QString::number(num % 2));  // Use prepend to build the binary string from the least significant bit
        num /= 2;
    }

    if (result.isEmpty()) {
        return "0";
    }

    return result;
}

QString ALU::decFractToHex(int intgr, float fract)
{
    QString bin_fract = ALU::decFract_to_bin(fract);  // Assuming this returns a QString
    QString bin_intgr = ALU::dec_to_bin(intgr);       // Assuming this returns a QString
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
        QString result = ALU::dec_to_bin(expo) + bin_fract.mid(expo_count, 2) + "00";

        return ALU::binToHex(result);  // Assuming binToHex also returns a QString
    }
    else
    {
        expo_count = bin_intgr.size() - 1;
        int expo = 4 + expo_count + (sign * 8);
        QString result = ALU::dec_to_bin(expo) + bin_intgr.mid(1) + bin_fract;

        return ALU::binToHex(result);
    }
}

QString ALU::decFract_to_bin(float fract)
{
    fract = std::abs(fract);  // Using std::abs for clarity
    QString result;

    for (int i = 0; i < 4; ++i) {
        fract *= 2;
        int floor = static_cast<int>(fract);  // Casting to int to get the floor value

        if (floor == 1) {
            fract -= floor;
            result += '1';
        } else {
            result += '0';
        }
    }

    return result;
}


float ALU::binFractToDec(const QString& fract) {
    int strlen = fract.length();
    float result = 0;

    for (int i = 0; i < strlen; i++) {
        // Convert the character at index i to a digit (0 or 1)
        result += (qPow(2, -(1 + i)) * (fract[i].digitValue()));
    }

    return result;
}


float ALU::floatToDecimal(const QString& hexa1)
{
    QString bin = ALU::hexToBin(hexa1);  // Assuming hexToBin returns a QString
    QChar sign_c = bin[0];
    int sign = (sign_c == '1') ? -1 : 1;

    QString expo = bin.mid(1, 3);
    QString fraction = bin.mid(4, 4);

    int exp = ALU::binToDec(expo);          // Assuming bin_to_dec accepts a QString and returns an int
    float fract = ALU::binFractToDec(fraction); // Assuming binFract_to_dec accepts a QString and returns a float
    fract += 1;

    return sign * std::pow(2, exp - 4) * fract;
}



QString ALU::addTwoFloat(const QString& hexa1, const QString& hexa2)
{
    double sum = ALU::floatToDecimal(hexa1) + ALU::floatToDecimal(hexa2);
    int intgr = static_cast<int>(sum);
    double fraction = sum - intgr;

    QString result = ALU::decFractToHex(intgr, fraction);  // Assuming decFract_to_hex returns a QString

    // Ensure the result has at least two characters for proper padding
    if (result.length() == 1) {
        result.prepend("0");
    } else if (result == "0") {
        return "00";
    }

    return result;
}

// Convert hexadecimal string to decimal
int ALU::hexToDec(const QString& num) {
    int result = 0;
    for (int i = 0; i < num.length(); i++) {
        QChar hexChar = num[i];
        if (hexChar >= 'A' && hexChar <= 'F') {
            result += (std::pow(16, (num.length() - (1 + i))) * (hexChar.toLatin1() - 'A' + 10));
        } else if (hexChar >= '0' && hexChar <= '9') {
            result += (std::pow(16, (num.length() - (1 + i))) * (hexChar.toLatin1() - '0'));
        } else if (hexChar >= 'a' && hexChar <= 'f') {
            result += (std::pow(16, (num.length() - (1 + i))) * (hexChar.toLatin1() - 'a' + 10));
        }
    }
    return result;
}

// Convert a single hexadecimal character to decimal
int ALU::hexToDec(QChar hexChar) {
    if (hexChar >= '0' && hexChar <= '9') {
        return hexChar.toLatin1() - '0'; // Convert character '0'-'9' to integer 0-9
    } else if (hexChar >= 'A' && hexChar <= 'F') {
        return hexChar.toLatin1() - 'A' + 10; // Convert character 'A'-'F' to integer 10-15
    } else if (hexChar >= 'a' && hexChar <= 'f') {
        return hexChar.toLatin1() - 'a' + 10; // Convert character 'a'-'f' to integer 10-15
    }
    return 0; // Return 0 for invalid characters
}

// Convert a binary string to a hexadecimal string (8 bits)
QString ALU::binToHex(const QString& binary) {
    if (binary == "00000000") {
        return "00";
    }
    std::bitset<8> b(binary.toStdString());  // Convert QString to std::string
    std::stringstream ss;
    ss << std::hex << std::uppercase << b.to_ulong(); // Convert to hex
    QString hexValue = QString::fromStdString(ss.str());
    return hexValue.rightJustified(2, '0'); // Ensure two characters for the hex value
}

// Bitwise OR operation
QString ALU::bitwise_OR(const QString& hexa1, const QString& hexa2) {
    int hex1 = ALU::hexToDec(hexa1);
    int hex2 = ALU::hexToDec(hexa2);
    QString result = ALU::decToHex((hex1 | hex2));

    // Ensure the result has at least two characters for proper padding
    if (result.length() == 1) {
        result.prepend('0');
    } else if (result == "0") {
        return "00";
    }
    return result;
}

// Bitwise AND operation
QString ALU::bitwise_AND(const QString& hexa1, const QString& hexa2) {
    int hex1 = ALU::hexToDec(hexa1);
    int hex2 = ALU::hexToDec(hexa2);
    QString result = ALU::decToHex((hex1 & hex2));

    // Ensure the result has at least two characters for proper padding
    if (result.length() == 1) {
        result.prepend('0');
    } else if (result == "0") {
        return "00";
    }
    return result;
}

// Bitwise XOR operation
QString ALU::bitwise_XOR(const QString& hexa1, const QString& hexa2) {
    int hex1 = ALU::hexToDec(hexa1);
    int hex2 = ALU::hexToDec(hexa2);
    QString result = ALU::decToHex((hex1 ^ hex2));

    // Ensure the result has at least two characters for proper padding
    if (result.length() == 1) {
        result.prepend('0');
    } else if (result == "0") {
        return "00";
    }
    return result;
}

// Bitwise rotate operation
QString ALU::bitwise_Rotate(const QString& hexa, int steps) {
    int hex = ALU::hexToDec(hexa);
    int result = (hex >> steps) | (hex << (8 - steps));  // Rotate right

    QString nResult = ALU::decToHex(result);

    // Ensure the result has at least two characters for proper padding
    if (nResult.length() == 1) {
        nResult.prepend('0');
    } else if (nResult == "0") {
        return "00";
    }
    return nResult;
}

// Function to add two hexadecimal numbers by converting them to binary (only 8-bit result)
QString ALU::addBinary(const QString& hexa1, const QString& hexa2) {
    QString bin1 = ALU::hexToBin(hexa1);
    QString bin2 = ALU::hexToBin(hexa2);

    QString result = "";  // To store the result of addition
    int carry = 0;       // To store the carry value during addition

    // Add the binary numbers from right to left
    for (int i = bin1.size() - 1; i >= 0; i--) {
        int bit1 = bin1[i].digitValue();  // Convert QChar to integer
        int bit2 = bin2[i].digitValue();

        int sum = bit1 + bit2 + carry;  // Add corresponding bits and carry

        // The new bit to add to the result is sum % 2
        result.prepend(QChar((sum % 2) + '0'));  // Convert to QChar and prepend to result

        // Calculate the new carry: 1 if sum >= 2, otherwise 0
        carry = sum / 2;
    }

    // If there is a carry left at the end, prepend it to the result
    if (carry) {
        result.prepend('1');
    }

    // Only keep the least significant 8 bits (if result is longer, discard the higher bits)
    result = result.right(8);  // Keep the last 8 bits

    return binToHex(result);  // Convert the result back to hexadecimal
}

bool ALU::isValidInput(QString &i) {


    for (auto &c : i) {
        if(isalpha(c.unicode())){
            c = c.toUpper(); // Convert to uppercase
        }

    }
    // Define the regex pattern for the input
    QRegularExpression regex(R"(^([1-9]|[A-D])[0-9A-F]{3}$)");

    // Check if the input matches the regex
    return regex.match(i).hasMatch();
}



//////////////////////////////////////////////////////////////////////

void Register::setRegister(int index, QString data) {

    registers[index] = data;


}

QString Register::getFromRegister(int index) {
    return registers[index];
}


//////////////////////////////////////////////////////////////////////


void Memory::setMemory(int indx, QString i) {

    mem[indx] = i;

}

QVector<QString>& Memory::getAllMemory() {
    return mem;
}

QString Memory::getMemoryCell(int indx) {
    return mem[indx];
}

//////////////////////////////////////////////////////////////////////

void Instructions::setInstruction(int count, const QString &input) {
    instruction[count] = input;
}

QVector<QString>& Instructions::getInstruction() {
    return instruction;
}

QString Instructions::getCurrentInstruction(int index) {
    if(index == 0){
        return instruction[index];
    }
    return instruction[(index / 2) - 1];
}

void Instructions::ClearInstructions(){

    for (int k = 0; k < 128; ++k) {
        instruction[k] = "0000";
    }
}

//////////////////////////////////////////////////////////////////////

QString Machine::getIR() {
    return input.getCurrentInstruction(index);
}

QString Machine::getPC() {
    return "0X" + Operation.decToHex(index);
}

bool Machine::getNextInstruction() {

    QString dataToRegister;
    int counter = 0;
    bool stop = false;
    programCounter = &storage.getAllMemory(); // Use storage's memory
    char operation;

    QChar cont1 = (*programCounter)[index][0];
    QChar cont2 = (*programCounter)[index][1];
    char cont3 = cont1.toLatin1() - '0';
    char cont4 = cont2.toLatin1() - '0';

    if(cont3 == 0 && cont4 == 0){
        stop = true;
        halt = true;
        return false;
    }


    while (!stop) {
        QChar Qoperation = (*programCounter)[index][0]; // Get the operation character

        if(Qoperation == '1' || Qoperation == '2' ||Qoperation == '3' ||Qoperation == '4' ||Qoperation == '5' ||Qoperation == '6' ||Qoperation == '7' ||Qoperation == '8' ||Qoperation == '9'){
            operation = Qoperation.toLatin1() - '0'; // Direct conversion
        }

        if (operation == 1) {
            int indexRegister = Operation.hexToDec((*programCounter)[index][1]); // Adjusted method call
            index++;
            int indexOfMemory = Operation.hexToDec((*programCounter)[index]);
            processor.setRegister(indexRegister, storage.getMemoryCell(indexOfMemory));
        }
        else if (operation == 2) {
            int indexRegister = Operation.hexToDec((*programCounter)[index][1]); // Adjusted method call
            index++;
            dataToRegister = (*programCounter)[index];
            processor.setRegister(indexRegister, dataToRegister);
        }
        else if (operation == 3) {
            int indexRegister = Operation.hexToDec((*programCounter)[index][1]); // Adjusted method call
            QString dataFromRegister = processor.getFromRegister(indexRegister);
            index++;
            int indexOfMemory = Operation.hexToDec((*programCounter)[index]);
            storage.setMemory(indexOfMemory, dataFromRegister); // Store in memory
        }
        else if (operation == 4) {
            index++;
            int registerCell1 = Operation.hexToDec((*programCounter)[index][0]); // Adjusted method call
            int registerCell2 = Operation.hexToDec((*programCounter)[index][1]); // Adjusted method call
            QString dataFromCell1 = processor.getFromRegister(registerCell1);
            processor.setRegister(registerCell1, "00");
            processor.setRegister(registerCell2, dataFromCell1);
        }
        else if (operation == 5) {
            int indexRegister = Operation.hexToDec((*programCounter)[index][1]); // Adjusted method call
            index++;
            int registerCell1 = Operation.hexToDec((*programCounter)[index][0]); // Adjusted method call
            int registerCell2 = Operation.hexToDec((*programCounter)[index][1]); // Adjusted method call
            QString dataCell1 = processor.getFromRegister(registerCell1);
            QString dataCell2 = processor.getFromRegister(registerCell2);
            processor.setRegister(indexRegister, Operation.addBinary(dataCell1, dataCell2));
        }
        else if (operation == 6) {
            int indexRegister = Operation.hexToDec((*programCounter)[index][1]); // Adjusted method call
            index++;
            int registerCell1 = Operation.hexToDec((*programCounter)[index][0]); // Adjusted method call
            int registerCell2 = Operation.hexToDec((*programCounter)[index][1]); // Adjusted method call
            QString dataCell1 = processor.getFromRegister(registerCell1);
            QString dataCell2 = processor.getFromRegister(registerCell2);
            processor.setRegister(indexRegister, Operation.addTwoFloat(dataCell1, dataCell2));
        }
        else if (operation == 7) {
            int indexRegister = Operation.hexToDec((*programCounter)[index][1]); // Adjusted method call
            index++;
            int registerCell1 = Operation.hexToDec((*programCounter)[index][0]); // Adjusted method call
            int registerCell2 = Operation.hexToDec((*programCounter)[index][1]); // Adjusted method call
            QString dataCell1 = processor.getFromRegister(registerCell1);
            QString dataCell2 = processor.getFromRegister(registerCell2);
            processor.setRegister(indexRegister, Operation.bitwise_OR(dataCell1, dataCell2));
        }
        else if (operation == 8) {
            int indexRegister = Operation.hexToDec((*programCounter)[index][1]); // Adjusted method call
            index++;
            int registerCell1 = Operation.hexToDec((*programCounter)[index][0]); // Adjusted method call
            int registerCell2 = Operation.hexToDec((*programCounter)[index][1]); // Adjusted method call
            QString dataCell1 = processor.getFromRegister(registerCell1);
            QString dataCell2 = processor.getFromRegister(registerCell2);
            processor.setRegister(indexRegister, Operation.bitwise_AND(dataCell1, dataCell2));
        }
        else if (operation == 9) {
            int indexRegister = Operation.hexToDec((*programCounter)[index][1]); // Adjusted method call
            index++;
            int registerCell1 = Operation.hexToDec((*programCounter)[index][0]); // Adjusted method call
            int registerCell2 = Operation.hexToDec((*programCounter)[index][1]); // Adjusted method call
            QString dataCell1 = processor.getFromRegister(registerCell1);
            QString dataCell2 = processor.getFromRegister(registerCell2);
            processor.setRegister(indexRegister, Operation.bitwise_XOR(dataCell1, dataCell2));
        }
        else if (operation == 'A') {
            int indexRegister = Operation.hexToDec((*programCounter)[index][1]); // Adjusted method call
            QString dataCell = processor.getFromRegister(indexRegister);
            index++;
            int steps = Operation.hexToDec((*programCounter)[index][1]); // Adjusted method call
            processor.setRegister(indexRegister, Operation.bitwise_Rotate(dataCell, steps));
        }
        else if (operation == 'B') {
            counter = index + 2;
            int indexRegister = Operation.hexToDec((*programCounter)[index][1]); // Adjusted method call
            QString dataCell0 = processor.getFromRegister(0);
            QString dataCellR = processor.getFromRegister(indexRegister);

            if (dataCell0 == dataCellR) {
                index++;
                int indexOfMemory = Operation.hexToDec((*programCounter)[index]);
                index = (indexOfMemory % 2 == 0) ? indexOfMemory : indexOfMemory - 1;
                programCounter = &storage.getAllMemory(); // Update the program counter
                continue; // Restart the loop with new index
            }
            else {
                index += 2; // Move to the next instruction
            }
        }
        else if (operation == 'D') {
            counter = index + 2;
            int indexRegister = Operation.hexToDec((*programCounter)[index][1]); // Adjusted method call
            QString dataCell0 = processor.getFromRegister(0);
            QString dataCellR = processor.getFromRegister(indexRegister);

            if (dataCell0 < dataCellR) {
                index++;
                int indexOfMemory = Operation.hexToDec((*programCounter)[index]);
                index = (indexOfMemory % 2 == 0) ? indexOfMemory : indexOfMemory - 1;
                programCounter = &storage.getAllMemory(); // Update the program counter
                continue; // Restart the loop with new index
            } else {
                index += 2; // Move to the next instruction
            }
        }
        else if (operation == 'C') {
            return true; // Exit condition
        }
        else{
            index++;
        }

        if (index == 255) {
            index = counter; // Reset index if at the end
        } else {
            index++; // Increment index
        }
        stop = true;
    }
    return true;
}



void Machine::setMemory(const QString &Input) {

    QString instruction, data;
    instruction += Input[0];
    instruction += Input[1];
    data += Input[2];
    data += Input[3];
    storage.setMemory(Count, instruction);
    Count++;
    storage.setMemory(Count, data);
    Count++;

}

QString Machine::getMemoryCell(int i){

    return storage.getMemoryCell(i);

}

QString Machine::getRegisterCell(int i){

    return processor.getFromRegister(i);

}

int Machine::setInstructions(QString i){


    if(i == "0000"){
        return 0;
    }
    if(Counter >= 128){
        return 1;
    }

    if(!Operation.isValidInput(i)){
        return 2;
    }

    if(i[0] == 'C'){
        StartOrEnd = true;
    }

    input.setInstruction(Counter, i);
    Counter++;
    setMemory(i);

    return 0;
}

void Machine::clearInstruct(){

    input.ClearInstructions();
}

int Machine::run(){

    if(getNextInstruction()){
        return 0;
    }

    if(halt == true){
        halt = false;
        return 1;
    }

    return 1;
}

QString Machine::displayIR(){
    return getIR();
}

QString Machine::displayPC(){
    return getPC();
}

void Machine::clearMemory(){

    for (int j = 0; j  < 256; ++j ) {
        storage.setMemory(j, "00");
    }

    Counter = 0;
    index = 0;
    Count = 0;
    clearInstruct();
}

void Machine::clearRegister(){

    for (int j = 0; j  < 16; ++j ) {
        processor.setRegister(j, "00");
    }

    index = 0;
}
