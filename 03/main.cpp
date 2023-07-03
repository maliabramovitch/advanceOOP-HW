#include "Controller.h"

using namespace std;

deque<string> args;


void split(string input) {
    stringstream ss;
    ss << input;
    std::string arg;
    while (ss >> arg) {
        args.push_back(arg);
    }
    for (int i = 0; i < args.size(); ++i) {
        for (auto it = args[i].begin(); it != args[i].end();) {
            if (*it == ')' || *it == '(' || *it == ',') {
                args[i].replace(it, it + 1, "");
            } else {
                ++it;
            }
        }
    }
}

int main(int argc, char **argv) {
    try {
        shared_ptr<Controller> controller = Controller::getControllerInstance(argv[1], argv[2]);
        controller->run(true);
    }
    catch (exception &e) {
        cout << e.what() << endl;
    }
    string input = "create Pippin Peasant (0.00, 0.00)";
}


