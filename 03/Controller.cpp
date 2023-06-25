//
// Created by Mali Abramovitch on 18/06/2023.
//

#include "Model.h"
#include "Controller.h"


std::shared_ptr<Controller>Controller::instancePtr = nullptr;


shared_ptr<Controller> &Controller::getControllerInstance(char *castlesFileName, char *farmsFileName) {
    if (!instancePtr) {
        instancePtr = shared_ptr<Controller>(new Controller());
        Model::getModelInstance()->initCastles(castlesFileName);
        Model::getModelInstance()->initFarms(farmsFileName);
    }
    return instancePtr;
}

Controller::~Controller() {
    instancePtr.reset();
}

void Controller::run() {
    cout << "Welcome friend to SimMedieval!" << endl;
    cout << "Commands:\n"
            "\t1.  go\n"
            "\t2.  status\n"
            "\t3.exit\n"
            "Agents Commands:\n"
            "\t1.  create <NAME> <Knight/Peasant/Thug> <[Knight=Castle/Farm]/[Peasant/Thug=(dd.dd,dd.dd)]\n"
            "\t2.  <NAME> course <DEGREE> <Thug=SPEED>\n"
            "\t3.  <NAME> position <(FLOAT.00, FLOAT.00)> <Thug=SPEED>\n"
            "\t4.  <NAME> destination <CASTLE/FARM>\n"
            "\t5.  <NAME> stop\n"
            "\t6.  <THUG> attack <PEASANT>\n"
            "\t7.  <PEASANT> start_working <FARM> <CASTLE>\n"
            "View Commands:\n"
            "\t1.  default\n"
            "\t2.  size <SIZE>\n"
            "\t3.  zoom <<FLOAT > 0>\n"
            "\t4.  pan <FLOAT.00> <FLOAT.00>\n"
            "\t5.  show\n";
    while (true) {
        try {
            stringstream ss;
            cout << "Time: " << Model::getModelInstance()->getTime() << " Enter input: ";
            string input;
            getline(std::cin, input);
            ss.seekp(ios::beg);
            ss << input;
            /// Commands
            if (input.find("exit") != string::npos) {
                cout << "Farewell -> Goodbye." << endl;
                return;
            }
            if (input.find("go") != string::npos) {
                goHelper(input);
            } else if (input.find("status") != string::npos) {
                statusHelper(input);
            } else if (input.find("show") != string::npos) {
                showHelper(input);
            } else if (input.find("default") != string::npos) {
                defaultHelper(input);
            } else if (input.find("size") != string::npos) {
                sizeHelper(input);
            } else if (input.find("zoom") != string::npos) {
                zoomHelper(input);
            } else if (input.find("pan") != string::npos) {
                panHelper(input);
            } /// Agent Commands
            else if (input.find("create") != string::npos) {
                createHelper(input);
            } else if (input.find("course") != string::npos) {
                courseHelper(input);
            } else if (input.find("position") != string::npos) {
                positionHelper(input);
            } else if (input.find("destination") != string::npos) {
                destinationHelper(input);
            } else if (input.find("stop") != string::npos) {
                stopHelper(input);
            } else if (input.find("attack") != string::npos) {
                attackHelper(input);
            } else if (input.find("start_working") != string::npos) {
                start_workingHelper(input);
            } else {
                cerr << "illegal command" << input << endl;
            }
        }
        catch (exception &e) {
            cerr << e.what();
        }
    }

}

void Controller::goHelper(string &input) {
    stringstream ss;
    ss << input;
    ss >> input;
    if (input != "go" || !ss.eof()) {
        ss.seekp(ios::beg);
        ss << "illegal go command" << input << endl;
        throw ControllerException(ss.str());
    }
    Model::getModelInstance()->go();
}

void Controller::statusHelper(string &input) {
    stringstream ss;
    ss << input;
    ss >> input;
    if (input != "status" || !ss.eof()) {
        ss.seekp(ios::beg);
        ss << "illegal status command" << input << endl;
        throw ControllerException(ss.str());
    }
    Model::getModelInstance()->status();
}

void Controller::showHelper(string &input) {
    stringstream ss;
    ss << input;
    ss >> input;
    if (input != "show" || !ss.eof()) {
        ss.seekp(ios::beg);
        ss << "illegal show command" << input << endl;
        throw ControllerException(ss.str());
    }
    Model::getModelInstance()->show();
}

void Controller::defaultHelper(string &input) {
    stringstream ss;
    ss << input;
    ss >> input;
    if (input != "default" || !ss.eof()) {
        ss.seekp(ios::beg);
        ss << "illegal default command" << input << endl;
        throw ControllerException(ss.str());
    }
    Model::getModelInstance()->setDefaultView();
}

void Controller::sizeHelper(string &input) {
    try {
        stringstream ss;
        int size;
        string command;
        ss >> command;
        if (command != "size") {
            ss.seekp(ios::beg);
            ss << "illegal size command" << input << endl;
            throw ControllerException(ss.str());
        }
        ss >> size;
        if (!ss || !ss.eof()) {
            ss.seekp(ios::beg);
            ss << "illegal size command" << input << endl;
            throw ControllerException(ss.str());
        }
        Model::getModelInstance()->setSizeView(size);
    }
    catch (exception &e) {
        throw;
    }
}

void Controller::zoomHelper(string &input) {
    try {
        stringstream ss;
        float zoom;
        string command;
        ss >> command;
        if (command != "zoom") {
            ss.seekp(ios::beg);
            ss << "illegal zoom command" << input << endl;
            throw ControllerException(ss.str());
        }
        ss >> zoom;
        if (!ss || !ss.eof()) {
            ss.seekp(ios::beg);
            ss << "oopsi poopsi... illegal zoom command" << input << endl;
            throw ControllerException(ss.str());
        }
        Model::getModelInstance()->setZoomView(zoom);
    }
    catch (exception &e) {
        throw;
    }
}

void Controller::panHelper(string &input) {
    stringstream ss;
    float x, y;
    string command;
    ss >> command;
    ss >> x >> y;
    if (!ss || !ss.eof()) {
        ss.seekp(ios::beg);
        ss << "illegal pan command" << input << endl;
        throw ControllerException(ss.str());
    }
    Model::getModelInstance()->setPanView(x, y);
}

void Controller::createHelper(const string &input) {
    Model::getModelInstance()->create(input);
}

void Controller::courseHelper(string &input) {
    stringstream ss;
    deque<string> args;
    string arg;
    for (int i = 0; i < 3; ++i) {
        ss >> arg;
        args.push_back(arg);
    }
    if (args[1] != "course") {
        ss.seekp(ios::beg);
        ss << "illegal course command" << input << endl;
        throw ControllerException(ss.str());
    }
    shared_ptr<Agent> agent = Model::getModelInstance()->getAgent(args[0]);
    shared_ptr<Agent> thug = dynamic_pointer_cast<Thug>(agent);
    ss.seekp(ios::beg);
    float course;
    ss << args[2];
    ss >> course;
    if (!ss) {
        ss.seekp(ios::beg);
        ss << "illegal course command" << input << endl;
        throw ControllerException(ss.str());
    }
    if (!thug) {
        if (!ss.eof()) {
            ss.seekp(ios::beg);
            ss << "illegal course command" << input << endl;
            throw ControllerException(ss.str());
        }
        Model::getModelInstance()->setCourseAgent(args[0], course);
    } else {
        ss >> arg;
        if (!ss.eof()) {
            ss.seekp(ios::beg);
            ss << "illegal course command" << input << endl;
            throw ControllerException(ss.str());
        }
        ss.seekp(ios::beg);
        float speed;
        ss << arg;
        ss >> speed;
        if (!ss || speed < 0) {
            ss.seekp(ios::beg);
            ss << "illegal course command" << input << endl;
            throw ControllerException(ss.str());
        }
        args.push_back(arg);
        Model::getModelInstance()->setCourseAgent(args[0], course, speed);
    }
}

void Controller::positionHelper(string &input) {
    stringstream ss;
    deque<string> args;
    string arg;
    for (int i = 0; i < 4; ++i) {
        ss >> arg;
        args.push_back(arg);
    }
    if (args[1] != "position") {
        ss.seekp(ios::beg);
        ss << "illegal position command" << input << endl;
        throw ControllerException(ss.str());
    }
    shared_ptr<Agent> agent = Model::getModelInstance()->getAgent(args[0]);
    shared_ptr<Agent> thug = dynamic_pointer_cast<Thug>(agent);
    ss.seekp(ios::beg);
    float x, y;
    ss << args[2] << args[3];
    ss >> x;
    ss >> y;
    if (!ss) {
        ss.seekp(ios::beg);
        ss << "illegal position command" << input << endl;
        throw ControllerException(ss.str());
    }
    if (!thug) {
        if (!ss.eof()) {
            ss.seekp(ios::beg);
            ss << "illegal position command" << input << endl;
            throw ControllerException(ss.str());
        }
        Model::getModelInstance()->setCourseAgent(args[0], x, y);
    } else {
        ss >> arg;
        if (!ss.eof()) {
            ss.seekp(ios::beg);
            ss << "illegal position command" << input << endl;
            throw ControllerException(ss.str());
        }
        ss.seekp(ios::beg);
        float speed;
        ss << arg;
        ss >> speed;
        if (!ss || speed < 0) {
            ss.seekp(ios::beg);
            ss << "illegal position command" << input << endl;
            throw ControllerException(ss.str());
        }
        args.push_back(arg);
        Model::getModelInstance()->setPositionAgent(args[0], x, y, speed);
    }
}

void Controller::destinationHelper(string &input) {
    stringstream ss;
    deque<string> args;
    string arg;
    for (int i = 0; i < 3; ++i) {
        ss >> arg;
        args.push_back(arg);
    }
    if (args[1] != "destination") {
        ss.seekp(ios::beg);
        ss << "illegal destination command" << input << endl;
        throw ControllerException(ss.str());
    }
    shared_ptr<Agent> agent = Model::getModelInstance()->getAgent(args[0]);
    Model::getModelInstance()->setDestinationAgent(args[0], args[2]);
}

void Controller::stopHelper(string &input) {
    stringstream ss;
    deque<string> args;
    string arg;
    while (ss >> arg) {
        args.push_back(arg);
    }
    if (args.size() != 2 || args[1] != "stop") {
        ss.seekp(ios::beg);
        ss << "illegal stop command" << input << endl;
        throw ControllerException(ss.str());
    }
    Model::getModelInstance()->stopAgent(args[0]);
}

void Controller::attackHelper(string &input) {
    stringstream ss;
    deque<string> args;
    string arg;
    while (ss >> arg) {
        args.push_back(arg);
    }
    if (args.size() != 3 || args[1] != "attack") {
        ss.seekp(ios::beg);
        ss << "illegal attack command" << input << endl;
        throw ControllerException(ss.str());
    }
    Model::getModelInstance()->attack(args[0], args[2]);
}

void Controller::start_workingHelper(string &input) {
    stringstream ss;
    deque<string> args;
    string arg;
    while (ss >> arg) {
        args.push_back(arg);
    }
    if (args.size() != 4 || args[1] != "start_working") {
        ss.seekp(ios::beg);
        ss << "illegal start_working command" << input << endl;
        throw ControllerException(ss.str());
    }
    Model::getModelInstance()->start_working(args[0], args[2], args[3]);
}


