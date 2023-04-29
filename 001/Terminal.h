//
// Created by Mali Abramovitch on 21/04/2023.
//

#ifndef INC_001_TERMINAL_H
#define INC_001_TERMINAL_H


#include <string>
#include <sstream>
#include "VirtualDrive.h"
#include <map>

class Terminal {
    //VirtualDrive vd;
    std::map<std::string, int> commands;

    int getAndCheckInput(std::string &input, int &operation); //Receives input from the user and acts accordingly.
    static bool checkNArgs(int argsNum, std::string& args); //Checks the legality of the arguments passed by the user.
    void fillCommends();


public:
    Terminal();
    ~Terminal() = default;
    Terminal(const Terminal &) = delete;
    Terminal(Terminal &&) = delete;
    Terminal &operator=(const Terminal &) = delete;
    Terminal &operator=(Terminal &&) = delete;

    static void printMenu() ;
    void run(); //Receives input from the user and acts accordingly.

};


#endif //INC_001_TERMINAL_H
