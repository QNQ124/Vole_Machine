// ==================================================================================== //
// FCAI – Object-Oriented Programming – 2024 - Assignment                               //
//                                                                                      //
// File:    A1-Task4Task5-S1-20230003_20230016_20230233.cpp                             //
//                                                                                      //
// Purpose: This provides a detailed explanation of the VOLE Machine s code,            //
//          which is structured into multiple classes, each responsible for             //
//          different functionalities of the machine. These classes include             //
//          Register, ALU (Arithmetic Logic Unit), Memory, Instructions, and            //
//          Machine. Each class encapsulates specific operations and data,              //
//          creating a modular and organized virtual machine for executing              //
//          instructions.                                                               //
//                                                                                      //
// Author:  Ibrahim Mohamed Saad Mohamed_S1_20230003 => Main, Register                  //
//          Ahmed Hussein Mohamed Ahmed_S1_20230016  => Memory, Instruction             //
//          Ezz eldin Omar Abd El-latif_S1_20230233  => Main, ALU                       //
//                                                                                      //
// Emails:  hes93314@gmail.com                                                          //
//          hzrdu3500@gmail.com                                                         //
//          ezzeldinomar7@gmail.com                                                     //
//                                                                                      //
// TA name: Bassant Samer                                                               //
// Date:    11/2/2024                                                                   //
// Version: 2.0                                                                         //
// ==================================================================================== //

// ==================================================================================== //
//              Gui Repository Link: https://github.com/QNQ124/Vole_Machine             //
// ==================================================================================== //

#include <iostream>
#include "volemachine.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
    cout << "|-------------- Ahlan ya User ya Habibi --------------|\n"
         << "|    In this Application we have a Vole machine       |\n"
         << "|    simulator. You must input a file to read data    |\n"
         << "|    and instructions from, and the program will      |\n"
         << "|    display the memory and registers to you.         |\n"
         << "|-----------------------------------------------------|\n\n";

    string filename;
    bool isValid = false;
    Machine vole_machine;

    cout << "Please enter a file name: ";

    while (!isValid) {

        cin >> filename;
        cin.ignore(); // Clear the input buffer

        // Open the file in a fresh ifstream instance
        ifstream file(filename);

        // Check if file opened successfully
        if (file.is_open()) {
            // Attempt to read from the file
            isValid = vole_machine.ReadFromFile(file);
            file.close();

            if (!isValid) {
                cout << "\nError: Invalid input. Please enter a valid file: ";
            }
        } else {
            cout << "\nError: Invalid file name. Please enter again: ";
        }
    }

    // Run the instructions loaded into the machine
    vole_machine.RunInstruction();

    // Infinite loop to display the menu and let the user interact with the machine
    while (true) {
        string choice;
        bool flag = false;

        // Display the options menu
        cout << "\n|------- What do you want to do? -------|\n";
        cout << "1) Load new file                        |\n";
        cout << "2) Display Memory                       |\n";
        cout << "3) Run the next Instruction             |\n";
        cout << "4) Display Register                     |\n";
        cout << "5) Display Instruction Register(IR)     |\n";
        cout << "6) Display Program Counter(PC)          |\n";
        cout << "7) Clear Memory                         |\n";
        cout << "8) Clear Register                       |\n";
        cout << "9) Exit                                 |\n";
        cout << "|---------------------------------------|\n";

        cout << "Please enter your choice from the menu: ";
        getline(cin, choice); // Get the user's choice

        // Validate the user's choice
        while (choice < "1" || choice > "9") {
            cout << "Please enter your choice from the menu: ";
            getline(cin, choice);
        }

        // Handle user choices based on the input
        if (choice == "1") { // Option to load a new file
            vole_machine.ClearMemory(); // Clear memory for new file
            isValid = false;
            cout << "\nPlease enter the new file name: ";

            while (!isValid) {

                cin >> filename;
                cin.ignore(); // Clear the input buffer

                ifstream newFile(filename); // Open the new file

                if (newFile.is_open()) {
                    isValid = vole_machine.ReadFromFile(newFile);
                    newFile.close();

                    if (!isValid) {
                        cout << "\nError: Invalid input in file. Please enter a different file: ";
                    }
                } else {
                    cout << "\nError: Invalid file name. Please enter again: ";
                }
            }
            vole_machine.RunInstruction();
        }
        else if (choice == "2") { // Display Memory
            vole_machine.DisplayMemory();
        }
        else if (choice == "3") { // Run next Instruction
            flag = vole_machine.getNextInstruction();
            if (flag) {
                cout << "\n----------------------------------\n";
                cout << "| The instructions are finished. |\n";
                cout << "----------------------------------\n";
            }
        }
        else if (choice == "4") { // Display Register
            vole_machine.DisplayRegister();
        }
        else if (choice == "5") { // Display Instruction Register (IR)
            cout << "\n----\n";
            cout << vole_machine.getIR() << endl;
            cout << "----\n";
        }
        else if (choice == "6") { // Display Program Counter (PC)
            cout << "\n----\n";
            vole_machine.getPC();
            cout << "----\n";
        }
        else if (choice == "7") { // Clear Memory
            vole_machine.ClearMemory();
        }
        else if (choice == "8") { // Clear Register
            vole_machine.ClearRegister();
        }
        else { // Exit
            break;
        }

        cin.clear(); // Clear any input errors
    }
}
