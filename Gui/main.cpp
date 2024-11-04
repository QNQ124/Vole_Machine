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


#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include "vmachine.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Machine machine;

    app.setWindowIcon(QIcon("D:/Software/letter-v.png")); // Use the path to your icon
    engine.rootContext()->setContextProperty("machine", &machine);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Gui", "Main");

    return app.exec();
}
