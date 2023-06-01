//
// Created by Mali Abramovitch on 27/05/2023.
//

#ifndef INC_02_TERMINAL_H
#define INC_02_TERMINAL_H

#include "BoogieLever.h"

/**
 * class for communicating with the user.
 */
class Terminal {
    static void printMenu();

    static void errorMessage();

    /**
     * for checking Input legality
     * @param input
     * @param arg1
     * @param arg2
     * @param arg3
     * @return
     */
    static bool threeArgs(const std::string &input, std::string &arg1, std::string &arg2, std::string &arg3);

    /**
     * for checking Input legality
     * @param keyWord
     * @param input
     * @param arg1
     * @return
     */
    static bool oneArgs(const std::string &keyWord, std::string &input, std::string &arg1);

    /**
    * run the communication unit with the user.
    * @param inFiles
    * @param outFile
    */
    static void run(std::deque<std::string> &inFiles, const std::string &outFile = "output.dat");

public:
    Terminal(int argc, char **argv);
    ~Terminal() = default; ///no data members...
    Terminal(const Time&) = delete;
    Terminal(Time&&) = delete;
    Terminal& operator=(const Time&) = delete;
    Terminal& operator=(Time&&) = delete;
};


#endif //INC_02_TERMINAL_H
