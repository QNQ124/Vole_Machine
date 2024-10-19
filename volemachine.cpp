#include "volemachine.h"
#include <bits/stdc++.h>

using namespace std;

void Register::setRegister(int index, string output) {

    registers[index] = output;

}

void Register::Clear(int index) {

    registers[index] = "00";
}

void Memory::ClearAll() {

    fill(Mem.begin(), Mem.end(),"00");
}

void Memory::ClearCell(int index) {}

void Memory::setMemory(int index, string output) {

    Mem[index] = output;
}

void Machine::DisplayMemory() {}

void Machine::DisplayRegister() {}

void Machine::RunInstruction() {}

string Machine::getNextInstruction() {}