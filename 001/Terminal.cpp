//
// Created by Mali Abramovitch on 21/04/2023.
//

#include <iostream>
#include <map>
#include "Terminal.h"

using namespace std;
/*
 * PUBLIC
 */
Terminal::Terminal() {
    //TODO VirtualDrive
    fillCommends();
}

void Terminal::run() {
    printMenu();
    string input, action, arg1, arg2, arg3;
    int operation = 0;
    bool on = true;
    while (on) {
        while (getAndCheckInput(input, operation) == -1) {
            cout << "oppsi poopsi illegal input: " << input << endl;
        }
        stringstream ss(input);
        ss >> action;
        switch (operation) {
            case 1: //read
                ss >> arg1;
                ss >> arg2;
                cout << "read op" << endl;
                //TODO call func
                break;
            case 2: //write
                ss >> arg1;
                ss >> arg2;
                ss >> arg3;
                cout << "write op" << endl;
                //TODO call func
                break;
            case 3: //touch
                ss >> arg1;
                cout << "touch op" << endl;
                //TODO call func
                break;
            case 4: //copy
                ss >> arg1;
                ss >> arg2;
                cout << "copy op" << endl;
                //TODO call func
                break;
            case 5: //remove
                ss >> arg1;
                cout << "remove op" << endl;
                //TODO call func
                break;
            case 6: //move
                ss >> arg1;
                ss >> arg2;
                cout << "move op" << endl;
                //TODO call func
                break;
            case 7: //cat
                ss >> arg1;
                cout << "cat op" << endl;
                //TODO call func
                break;
            case 8: //wc
                ss >> arg1;
                cout << "wc op" << endl;
                //TODO call func
                break;
            case 9: //ln
                ss >> arg1;
                ss >> arg2;
                cout << "ln op" << endl;
                //TODO call func
                break;
            case 10: //mkdir
                ss >> arg1;
                cout << "mkdirop" << endl;
                //TODO call func
                break;
            case 11: //chdir
                ss >> arg1;
                cout << "chdir op" << endl;
                //TODO call func
                break;
            case 12: //clearDirectory
                ss >> arg1;
                cout << "clearDirectory op" << endl;
                //TODO call func
                break;
            case 13: //ls
                ss >> arg1;
                cout << "ls op" << endl;
                //TODO call func
                break;
            case 14: //lproot
                cout << "lproot op" << endl;
                //TODO call lproot
                break;
            case 15: //pwd
                cout << "pwd op" << endl;
                //TODO call func
                break;
            case 16: // exit
                cout << "exit op" << endl;
                on = false;
                break;
            default:
                break;
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
    if (operation == 1 || operation == 4 || operation == 6 || operation == 9) {// 2 argument
        if (checkNArgs(2, args)) return operation;
        else return -1;
    }
    else if (operation == 2) {// 3 arguments
        if (checkNArgs(3, args)) return operation;
        else return -1;
    }
    else if (operation == 3 || operation == 5 || operation == 7 || operation == 8 || operation == 10 || operation == 11 ||
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
    commands["clearDirectory"] = 12;
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
    string menu = "[1] read FILENAME POSITION\n"
                  "[2] write FILENAME POSITION CHARACTER\n"
                  "[3] touch FILENAME\n"
                  "[4] copy SOURCE_FILENAME TARGET_FILENAME\n"
                  "[5] remove FILENAME\n"
                  "[6] move SOURCE_FILENAME TARGET_FILENAME\n"
                  "[7] cat FILENAME\n"
                  "[8] wc FILENAME\n"
                  "[9] ln TARGET_FILENAME LINK_NAME\n"
                  "[10] mkdir FOLDERNAME\n"
                  "[11] chdir FOLDERNAME\n"
                  "[12] clearDirectory FOLDERNAME\n"
                  "[13] ls FOLDERNAME\n"
                  "[14] lproot\n"
                  "[15] pwd\n"
                  "[16] exit\n\n";
    cout << menu;
}
