#ifndef VOLE_MACHINE_VOLEMACHINE_H
#define VOLE_MACHINE_VOLEMACHINE_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>

////////////////////////////////////////////////////////////////////

class Register : public QObject {
    Q_OBJECT

private:
    QVector<QString> registers;

public:
    explicit Register(QObject *parent = nullptr) : QObject(parent), registers(16, "00") {}
    void setRegister(int index, QString data);
    QString getFromRegister(int index);

};

/////////////////////////////////////////////////////////////////////

class ALU : public QObject {
    Q_OBJECT

public:
    explicit ALU(QObject *parent = nullptr) : QObject(parent) {}

    // Convert a hexadecimal string to a binary string (8 bits)
    QString hexToBin(const QString &hexa);
    QString decToHex(int num);
    QString dec_to_bin(int num);
    int binToDec(const QString &num);
    QString decFractToHex(int intgr, float fract);
    float binFractToDec(const QString &fract);
    float floatToDecimal(const QString &hexa1);
    QString decFract_to_bin(float fract);
    QString addTwoFloat(const QString &hexa1, const QString &hexa2);
    QString fract(float fract);
    QString bitwise_Rotate(const QString& hexa, int steps);
    QString bitwise_XOR(const QString& hexa1, const QString& hexa2);
    QString bitwise_AND(const QString& hexa1, const QString& hexa2);
    QString bitwise_OR(const QString& hexa1, const QString& hexa2);
    // Function to convert hexadecimal to decimal
    int hexToDec(const QString &num);
    int hexToDec(QChar hexChar);
    bool isValidInput(QString &i);

    // Convert a binary string to a hexadecimal string (8 bits)
    QString binToHex(const QString &binary);

    // Function to add two hexadecimal numbers by converting them to binary (only 8-bit result)
    QString addBinary(const QString &hexa1, const QString &hexa2);
};

/////////////////////////////////////////////////////////////////////

class Memory : public QObject {
    Q_OBJECT

private:
    QVector<QString> mem;

public:
    explicit Memory(QObject *parent = nullptr) : QObject(parent), mem(256, "00") {}
    void setMemory(int indx, QString i);
    QVector<QString>& getAllMemory();
    QString getMemoryCell(int index);
};

//////////////////////////////////////////////////////////////////////////

class Instructions : public QObject {
    Q_OBJECT

private:
    QVector<QString> instruction;

public:
    explicit Instructions(QObject *parent = nullptr) : QObject(parent), instruction(128) {}
    void setInstruction(int index, const QString &value);
    QVector<QString>& getInstruction();
    QString getCurrentInstruction(int index);
    void ClearInstructions();
};

//////////////////////////////////////////////////////////////

class Machine : public QObject {
    Q_OBJECT

private:
    Register processor;
    Memory storage;
    Instructions input;
    ALU Operation;
    QVector<QString> *programCounter;
    static int index;
    static int Counter;
    static int Count;

public:
    explicit Machine(QObject *parent = nullptr) : QObject(parent), processor(this), storage(this), input(this), Operation(this), programCounter(nullptr) {}
    QVector<QString> *PC;
    bool getNextInstruction(); // increment 2
    void setMemory(const QString &Input);
    void runInstruction(); // current and next
    QString getIR();
    Q_SIGNAL void memoryUpdated();
    void setRegister();
    QString getPC();
    void displayMemory(); // DONE
    void displayRegister(); // DONE

signals:

public slots:

    QString getMemoryCell(int i);
    QString getRegisterCell(int i);
    int setInstructions(QString i);
    int run();
    QString displayIR();
    QString displayPC();
    void clearMemory();
    void clearRegister();
    void clearInstruct();
};

#endif // VOLE_MACHINE_VOLEMACHINE_H
