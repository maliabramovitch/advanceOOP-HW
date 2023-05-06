//
// Created by Mali Abramovitch on 21/04/2023.
//

#include <iostream>
#include <map>
#include "Terminal.h"

using namespace std;

Terminal::Terminal() {
    fillCommends();
}

void Terminal::run() {
    printMenu();
    string input, action, arg1, arg2, arg3;
    int operation = 0;
    bool on = true;
    while (on) {
        try {
            while (getAndCheckInput(input, operation) == -1) {
                cout << "oppsi poopsi illegal input: " << input << endl;
            }
            stringstream ss(input);
            ss >> action;
            switch (operation) {
                case 1: //read
                    ss >> arg1;
                    ss >> arg2;
                    vd.read(arg1, stoi(arg2));
                    break;
                case 2: //write
                    ss >> arg1;
                    ss >> arg2;
                    ss >> arg3;
                    vd.write(arg1, stoi(arg2), *arg3.c_str());
                    break;
                case 3: //touch
                    ss >> arg1;
                    vd.touch(arg1);
                    break;
                case 4: //copy
                    ss >> arg1;
                    ss >> arg2;
                    vd.copy(arg1, arg2);
                    break;
                case 5: //remove
                    ss >> arg1;
                    vd.remove(arg1);
                    break;
                case 6: //move
                    ss >> arg1;
                    ss >> arg2;
                    vd.move(arg1, arg2);
                    break;
                case 7: //cat
                    ss >> arg1;
                    vd.cat(arg1);
                    break;
                case 8: //wc
                    ss >> arg1;
                    vd.wc(arg1);
                    break;
                case 9: //ln
                    ss >> arg1;
                    ss >> arg2;
                    vd.ln(arg1, arg2);
                    break;
                case 10: //mkdir
                    ss >> arg1;
                    vd.mkdir(arg1);
                    break;
                case 11: //chdir
                    ss >> arg1;
                    vd.chdir(arg1);
                    break;
                case 12: //rmdir
                    ss >> arg1;
                    vd.rmdir(arg1);
                    break;
                case 13: //ls
                    ss >> arg1;
                    vd.ls(arg1);
                    break;
                case 14: //lproot
                    vd.lproot();
                    break;
                case 15: //pwd
                    vd.pwd();
                    break;
                case 16: // exit
                    on = false;
                    break;
                default:
                    break;
            }


        }
        catch (exception &e) {
            cerr << "oopsi poopsi" << endl;
            cerr << e.what() << endl;
        }
    }
    cout << "Adiós amigo" << endl;
}


/*
 * PRIVATE
 */
int Terminal::getAndCheckInput(string &input, int &operation) {
    getline(cin, input);
    string args;
    stringstream ss(input);
    ss >> args;
    auto mapIter(commands.find(args));
    if (mapIter == commands.end()) return -1; //command not in commands
    operation = mapIter->second;
    args = "";
    args = ss.str();
    if (operation == 13 && args == "ls") {
        return operation;
    }
    else if (operation == 1 || operation == 4 || operation == 6 || operation == 9) {// 2 argument
        if (checkNArgs(2, args)) return operation;
        else return -1;
    } else if (operation == 2) {// 3 arguments
        if (checkNArgs(3, args)) return operation;
        else return -1;
    } else if (operation == 3 || operation == 5 || operation == 7 || operation == 8 || operation == 10 ||
               operation == 11 ||
               operation == 12 || operation == 13) {// 1 argument
        if (checkNArgs(1, args)) return operation;
        else return -1;
    } else {
        if (ss.eof()) return operation;
        else return -1;
    }
}

void Terminal::fillCommends() {
    commands["read"] = 1;
    commands["write"] = 2;
    commands["touch"] = 3;
    commands["copy"] = 4;
    commands["remove"] = 5;
    commands["move"] = 6;
    commands["cat"] = 7;
    commands["wc"] = 8;
    commands["ln"] = 9;
    commands["mkdir"] = 10;
    commands["chdir"] = 11;
    commands["rmdir"] = 12;
    commands["ls"] = 13;
    commands["lproot"] = 14;
    commands["pwd"] = 15;
    commands["exit"] = 16;
}

bool Terminal::checkNArgs(int argsNum, string &args) {
    string arg;
    stringstream ss(args);
    ss >> args;
    for (int i = 0; i < argsNum; ++i) {
        if (!(ss >> arg)) {
            return false;
        }
    }
    if (!ss.eof()) {
        return false;
    }
    return true;
}

void Terminal::printMenu() {
    string menu = "- read FILENAME POSITION\n"
                  "- write FILENAME POSITION CHARACTER\n"
                  "- touch FILENAME\n"
                  "- copy SOURCE_FILENAME TARGET_FILENAME\n"
                  "- remove FILENAME\n"
                  "- move SOURCE_FILENAME TARGET_FILENAME\n"
                  "- cat FILENAME\n"
                  "- wc FILENAME\n"
                  "- ln TARGET_FILENAME LINK_NAME\n"
                  "- mkdir FOLDERNAME\n"
                  "- chdir FOLDERNAME\n"
                  "- clearDirectory FOLDERNAME\n"
                  "- ls FOLDERNAME (optional)\n"
                  "- lproot\n"
                  "- pwd\n"
                  "- exit\n\n";
    cout << menu;
}