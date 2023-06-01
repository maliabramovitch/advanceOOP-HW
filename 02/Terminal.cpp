//
// Created by Mali Abramovitch on 27/05/2023.
//

#include "Terminal.h"

using namespace std;

Terminal::Terminal(int argc, char **argv) {
    try {
        deque<std::string> inFiles;
        string outFile = "-o";
        for (int i = 0; i < argc; ++i) {
            if (outFile == argv[i]) {
                run(inFiles, argv[argc - 1]);
                return;
            }
            inFiles.emplace_back(argv[i]);
        }
        run(inFiles);
    }
    catch (exception &e) {
        cerr << e.what() << endl;
    }
}

void Terminal::run(std::deque<std::string> &inFiles, const std::string &outFile) {
    try {
        BoogieLever bl(inFiles, outFile);
        printMenu();
        string op, arg1, arg2, arg3;
        while (true) {
            try {
                getline(cin, op);
                if (op == "exit") {
                    cout << "good bye!" << endl;
                    break;
                } else if (op == "print") {
                    bl.print();
                } else if (op.find("load") != string::npos) {
                    if (oneArgs("load", op, arg1)) {
                        bl.load(arg1);
                    } else {
                        errorMessage();
                    }
                } else if (op.find("inbound") != string::npos) {
                    if (oneArgs("inbound", op, arg1)) {
                        bl.inbound(arg1);
                    } else {
                        errorMessage();
                    }
                } else if (op.find("outbound") != string::npos) {
                    if (oneArgs("outbound", op, arg1)) {
                        bl.outbound(arg1);
                    } else {
                        errorMessage();
                    }
                } else if (op.find("balance") != string::npos) {
                    if (threeArgs(op, arg1, arg2, arg3)) {
                        bl.balance(arg1, arg2, arg3);
                    } else {
                        errorMessage();
                    }
                } else {
                    errorMessage();
                }
            }
            catch (exception &e) {
                errorMessage();
            }
        }
    }
    catch (exception &e) {
        throw;
    }
}

void Terminal::printMenu() {
    cout << "Welcome To Boogie Lever International Shipping service data base!\n";
    cout << "Operation typing Menu:" << endl;
    cout << "\t- load <file name>" << endl;
    cout << "\t- <port> inbound" << endl;
    cout << "\t- <port> outbound" << endl;
    cout << "\t- <port> balance <dd/mm HH:mm>" << endl;
    cout << "\t- print" << endl;
    cout << "\t- exit\n" << endl;
}

bool Terminal::threeArgs(const string &input, string &arg1, string &arg2, string &arg3) {
    int startPose = 0, endPose;
    for (unsigned int i = 0; i < input.size(); ++i) {
        if (input[i] == ',') {
            endPose = i;
            break;
        }
    }
    arg1 = input.substr(startPose, endPose);
    startPose = (++endPose);
    for (unsigned int i = endPose; i < input.size(); ++i) {
        if (input[i] == ',') {
            endPose = i;
            break;
        }
    }
    string tmp = input.substr(startPose, endPose - startPose);
    if (tmp != "balance") {
        return false;
    }
    startPose = (++endPose);
    for (unsigned int i = endPose; i < input.size(); ++i) {
        if (input[i] == ' ') {
            endPose = i;
            break;
        }
    }
    arg2 = input.substr(startPose, endPose - startPose);
    startPose = (++endPose);
    arg3 = input.substr(startPose, string::npos - startPose);
    return true;
}

bool Terminal::oneArgs(const string &keyWord, string &input, string &arg1) {
    stringstream ss;
    ss << input;
    if (keyWord == "load") {
        ss >> arg1;
        if (ss.eof()) {
            return false;
        }
        ss >> arg1;
        return true;
    } else {
        int pose;
        if (keyWord == "inbound") {
            pose = input.find("inbound");
        } else {
            pose = input.find("outbound");
        }
        string cutting = ss.str();
        arg1 = cutting.substr(0, pose);
        if (arg1[arg1.size() - 1] == ' ') {
            arg1.pop_back();
        }
        if (arg1.empty()) {
            return false;
        }
        return true;
    }
}

void Terminal::errorMessage() {
    cerr << "USAGE:\t‘load’ <file> *or*\n"
            "      \t<node>,'inbound' *or*\n"
            "      \t<node>,’outbound’ *or*\n"
            "      \t<node>,’balance’,dd/mm HH:mm *or*\n"
            "      \t‘print’ *or*\n"
            "      \t‘exit’ *to terminate*\n\n";
}
