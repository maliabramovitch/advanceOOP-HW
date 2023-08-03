#include "Controller.h"

using namespace std;

deque<string> args;

int main(int argc, char **argv) {
    try {
        shared_ptr<Controller> controller = Controller::getControllerInstance(argv[1], argv[2]);
        controller->run(true);
    }
    catch (exception &e) {
        cout << e.what() << endl;
    }
}


