#include <iostream>
#include "volemachine.h"
#include <bits/stdc++.h>

using namespace std;

int main(){

    // Display the welcome message to the user
    cout << "|-------------- Ahlan ya User ya Habibi --------------|\n"
         << "|    In this Application we have a Vole machine       |\n"
         << "|    simulator. You must input a file to read a data  |\n"
         << "|    and Instructions from it and the program will    |\n"
         << "|    Display the Memory and register to you.          |\n"
         << "|-----------------------------------------------------|\n\n";


    string filename;
    ifstream file;
    bool isValid = false;
    cout << "Please enter a file name: ";
    // Create a Machine object
    Machine vole_machine;
// Read the new file and load the instructions into the machine

    while(!isValid) {

        // Keep asking for the correct file name until a valid one is provided
        while (true) {
            // Ask the user for a filename to load the data
            cin >> filename;
            cin.ignore(); // Clear the input buffer

            // Open the file for reading
            file.open(filename, ios::in);

            if (file.is_open()) { // If the file is successfully opened, break the loop
                break;
            } else { // If the file is not opened, ask for another filename
                cout << "Error: Invalid file name. Please enter again: ";
            }
        }

        isValid = vole_machine.ReadFromFile(file);
    }

    // Read data and instructions from the file
    vole_machine.ReadFromFile(file);
    // Run the instructions loaded into the machine
    vole_machine.RunInstruction();

    // Infinite loop to display the menu and let the user interact with the machine
    while(true) {

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
        cout << "7) Exit                                 |\n";
        cout << "|---------------------------------------|\n";

        // Ask the user for a choice
        cout << "Please enter your choice from the menu: ";
        getline(cin, choice); // Get the user's choice

        // Validate the user's choice (make sure it's a number between 1 and 7)
        while (true) {
            if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" ||
                choice == "6" || choice == "7")
                break; // Exit the loop if the choice is valid
            else {
                cout << "Please enter your choice from the menu: ";
                getline(cin, choice); // Ask for input again until a valid choice is provided
            }
        }

        // Handle user choices based on the input
        if (choice == "1"){ // Option to load a new file

            file.close(); // Close the previous file
            cout << "Please enter the new file name: ";

            // Keep asking for the correct file name until a valid one is provided
            while (true) {

                cin >> filename;
                cin.ignore(); // Clear the input buffer

                // Open the file for reading
                file.open(filename, ios::in);

                if (file.is_open()) { // If the file is successfully opened, break the loop
                    break;
                } else { // If the file is not opened, ask for another filename
                    cout << "Error: Invalid file name. Please enter again: ";
                }
            }

            ifstream newFile(filename, ios::in); // Open the new file

            // Read the new file and load the instructions into the machine
            isValid = vole_machine.ReadFromFile(newFile);
            while(!isValid){
                file.close(); // Close the previous file
                cout << "\nPlease enter the new file name: ";

                // Keep asking for the correct file name until a valid one is provided
                while (true) {

                    cin >> filename;
                    cin.ignore(); // Clear the input buffer

                    // Open the file for reading
                    file.open(filename, ios::in);

                    if (file.is_open()) { // If the file is successfully opened, break the loop
                        break;
                    } else { // If the file is not opened, ask for another filename
                        cout << "Error: Invalid file name. Please enter again: ";
                    }
                }
                isValid = vole_machine.ReadFromFile(newFile);
            }

            vole_machine.RunInstruction(); // Execute the instructions
        }
        else if (choice == "2"){ // Option to display the memory
            cout << "\n---------------\n";
            vole_machine.DisplayMemory(); // Show the memory content
        }
        else if (choice == "3"){ // Option to run the next instruction
            flag = vole_machine.getNextInstruction(); // Get the next instruction

            if(flag){ // If no more instructions, notify the user
                cout << "\n-----------------------------\n";
                cout << "The instructions are finished\n";
                cout << "-----------------------------\n";
                continue;
            }
        }
        else if (choice == "4"){ // Option to display the register
            cout << "\n---------------\n";
            vole_machine.DisplayRegister(); // Show the register content
        }

        else if (choice == "5"){ // Option to display the Instruction Register (IR)
            cout << "\n---------------\n";
            cout << vole_machine.getIR() << endl; // Print the IR content
        }

        else if (choice == "6"){ // Option to display the Program Counter (PC)
            cout << "\n---------------\n";
            vole_machine.getPC(); // Print the PC value
        }

        else{ // Exit the loop if the user chooses to exit
            break;
        }

        cin.clear(); // Clear any input errors
    }
}