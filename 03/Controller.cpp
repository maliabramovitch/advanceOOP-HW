//
// Created by Mali Abramovitch on 18/06/2023.
//

#include <fstream>
#include "Model.h"
#include "Controller.h"


std::shared_ptr<Controller>Controller::instancePtr = nullptr;
std::shared_ptr<Model>Controller::model = nullptr;

Controller::Controller() {
    view = make_shared<View>();
    model = Model::getModelInstance();
    model->attachedView(view);
}


shared_ptr<Controller> &Controller::getControllerInstance(char *castlesFileName, char *farmsFileName) {
    if (!instancePtr) {
        instancePtr = shared_ptr<Controller>(new Controller());
        model->initCastles(castlesFileName);
        model->getModelInstance()->initFarms(farmsFileName);
    }
    return instancePtr;
}

Controller::~Controller() {
    instancePtr.reset();
    Model::getModelInstance()->detachesView();
    view.reset();
}

void Controller::run(bool checkMode) {
    if (checkMode) { ///TODO
        // all output goes to file output.dat
        fstream infile("input.dat");
        if (!infile) {
            cout << "infile" << endl;
            return;
        }
        fstream outfile("output.txt", ios::out);
        if (!outfile) {
            cout << "outfile" << endl;
            return;
        }
        std::streambuf *oldCoutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(outfile.rdbuf());
        cout << "Welcome friend to SimMedieval!" << endl;
        cout << "Commands:\n"
                "\t1.  go\n"
                "\t2.  status\n"
                "\t3.  exit\n"
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
                "\t3.  zoom <FLOAT.00>\n"
                "\t4.  pan <FLOAT.00> <FLOAT.00>\n"
                "\t5.  show\n";
        while (true) {
            try {
                stringstream ss;
                cout << "Time: " << Model::getModelInstance()->getTime() << " Enter command: ";
                string input;
                getline(infile, input);
                cout << input;
                input.pop_back();
                /// Commands
                if (input.find("exit") != string::npos) {
                    cout << "\nFarewell -> Goodbye." << endl;
                    break;
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
                    cout << "illegal command " << input << endl;
                }
            }
            catch (exception &e) {
                cout << e.what();
            }
            cin.clear();
            cout << endl;
        }
        std::cout.rdbuf(oldCoutBuffer);
        outfile.close();
    } else {
        cout << "Welcome friend to SimMedieval!" << endl;
        cout << "Commands:\n"
                "\t1.  go\n"
                "\t2.  status\n"
                "\t3.  exit\n"
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
                cout << "Time: " << Model::getModelInstance()->getTime() << " Enter command: ";
                string input;
                getline(std::cin, input);
                ss.clear();
                ss << input;
                if (input == "exit") {
                    cout << "\nFarewell -> Goodbye." << endl;
                    break;
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
                    cerr << "illegal command " << input << endl;
                }
            }
            catch (exception &e) {
                cerr << e.what();
            }
            cin.clear();
            cout << endl;
        }
    }
}

void Controller::goHelper(string &input) {
    stringstream ss;
    ss << input;
    ss >> input;
    if (input != "go" || !ss.eof()) {
        ss.clear();
        ss << "oppsi poosi... illegal go command: " << input << endl;
        throw ControllerException(ss.str());
    }
    model->go();
}

void Controller::statusHelper(string &input) {
    stringstream ss;
    ss << input;
    ss >> input;
    if (input != "status" || !ss.eof()) {
        ss.clear();
        ss << "oppsi poosi... illegal status command: " << input << endl;
        throw ControllerException(ss.str());
    }
    model->status();
}

void Controller::showHelper(string &input) {
    stringstream ss;
    ss << input;
    ss >> input;
    if (input != "show" || !ss.eof()) {
        ss.clear();
        ss << "oppsi poosi... illegal show command: " << input << endl;
        throw ControllerException(ss.str());
    }
    cout << endl;
    view->show();
}

void Controller::defaultHelper(string &input) {
    stringstream ss;
    ss << input;
    ss >> input;
    if (input != "default" || !ss.eof()) {
        ss.clear();
        ss << "oppsi poosi... illegal default command: " << input << endl;
        throw ControllerException(ss.str());
    }
    view->default_view();
}

void Controller::sizeHelper(string &input) {
    try {
        stringstream ss;
        int sizeInt = 0;
        split(input);
        if (args.size() != 2 || args[0] != "size") {
            ss.clear();
            ss << "oppsi poosi... illegal size command: " << input << endl;
            throw ControllerException(ss.str());
        }
        ss << args[1];
        ss >> sizeInt;
        if (!ss || !ss.eof()) {
            ss.clear();
            ss << "oppsi poosi... illegal size command: " << input << endl;
            throw ControllerException(ss.str());
        }
        view->adjustSize(sizeInt);
    }
    catch (exception &e) {
        throw;
    }
}

void Controller::zoomHelper(string &input) {
    try {
        stringstream ss;
        split(input);
        if (args.size() != 2 || args[0] != "zoom") {
            ss.clear();
            ss << "oppsi poosi... illegal zoom command: " << input << endl;
            throw ControllerException(ss.str());
        }
        float zoom;
        ss << args[1];
        ss >> zoom;
        if (!ss) {
            ss.clear();
            ss << "oppsi poosi... illegal zoom command: " << input << endl;
            throw ControllerException(ss.str());
        }
        view->adjustZoom(zoom);
    }
    catch (exception &e) {
        throw;
    }
}

void Controller::panHelper(string &input) {
    stringstream ss;
    float x, y;
    split(input);
    if (args[0] != "pan" || args.size() != 3) {
        ss.clear();
        ss << "oppsi poosi... illegal pan command: " << input << endl;
        throw ControllerException(ss.str());
    }
    ss << args[1] << " " << args[2];
    ss >> x >> y;
    if (!ss || !ss.eof()) {
        ss.clear();
        ss << "oppsi poosi... illegal pan command: " << input << endl;
        throw ControllerException(ss.str());
    }
    view->adjustPan(x, y);
}

void Controller::createHelper(const string &input) {
    try {
        stringstream ss;
        split(input);
        if (args[0] != "create") {
            ss.clear();
            ss << "oppsi poosi... illegal create command: " << input << endl;
            throw ControllerException(ss.str());
        }
        if (args[2] == "Knight" && args.size() == 4) {
            model->createKnight(args[1], args[3]);
        } else {
            if (args.size() != 5) {
                ss.clear();
                ss << "oppsi poosi... illegal create command: " << input << endl;
                throw ControllerException(ss.str());
            }
            ss.clear();
            float x, y;
            ss << args[3] << " " << args[4];
            ss >> x >> y;
            if (!ss) {
                ss << "oppsi poosi... illegal create command: " << input << endl;
                throw ControllerException(ss.str());
            }
            if (args[2] == "Peasant") {
                model->createPeasant(args[1], x, y);
            } else if (args[2] == "Thug") {
                model->createThug(args[1], x, y);
            } else {
                ss << "oppsi poosi... illegal create command: " << input << endl;
                throw ControllerException(ss.str());
            }
        }
    }
    catch (exception &e) {
        throw;
    }
}

void Controller::courseHelper(string &input) {
    try {
        stringstream ss;
        split(input);
        if (args[1] != "course") {
            ss.clear();
            ss << "oppsi poosi... illegal course command: " << input << endl;
            throw ControllerException(ss.str());
        }
        ss.clear();
        float course;
        ss << args[2];
        ss >> course;
        if (!ss) {
            ss.clear();
            ss << "oppsi poosi... illegal course command: " << input << endl;
            throw ControllerException(ss.str());
        }
        if (args.size() == 3) {
            if (!ss.eof()) {
                ss.clear();
                ss << "oppsi poosi... illegal course command: " << input << endl;
                throw ControllerException(ss.str());
            }
            model->setCourseAgent(args[0], course);
        } else {
            ss.clear();
            float speed;
            ss << args[3];
            ss >> speed;
            if (!ss || args.size() != 4) {
                ss.clear();
                ss << "oppsi poosi... illegal course command: " << input << endl;
                throw ControllerException(ss.str());
            }
            model->setCourseAgent(args[0], course, speed);
        }
    } catch (exception &e) {
        throw;
    }
}

void Controller::positionHelper(string &input) {
    try {
        stringstream ss;
        split(input);
        if (args[1] != "position") {
            ss.clear();
            ss << "oppsi poosi... illegal position command: " << input << endl;
            throw ControllerException(ss.str());
        }
        float x, y;
        ss << args[2] << " " << args[3];
        if (!ss) {
            ss.clear();
            ss << "oppsi poosi... illegal position command: " << input << endl;
            throw ControllerException(ss.str());
        }
        ss >> x >> y;
        if (args.size() == 4) {
            model->setPositionAgent(args[0], x, y);
        } else {
            ss.clear();
            float speed;
            ss << args[4];
            ss >> speed;
            if (!ss || speed < 0 || args.size() != 5) {
                ss.clear();
                ss << "oppsi poosi... illegal position command: " << input << endl;
                throw ControllerException(ss.str());
            }
            model->setPositionAgent(args[0], x, y, speed);
        }
    } catch (exception &e) {
        throw;
    }

}

void Controller::destinationHelper(string &input) {
    try {
        stringstream ss;
        split(input);
        if (args[1] != "destination" || args.size() != 3) {
            ss.clear();
            ss << "oppsi poosi... illegal destination command: " << input << endl;
            throw ControllerException(ss.str());
        }
        model->setDestinationAgent(args[0], args[2]);
    }
    catch (exception &e) {
        throw;
    }
}

void Controller::stopHelper(string &input) {
    try {
        stringstream ss;
        split(input);
        if (args.size() != 2 || args[1] != "stop") {
            ss.clear();
            ss << "oppsi poosi... illegal stop command " << input << endl;
            throw ControllerException(ss.str());
        }
        model->stopAgent(args[0]);
    }
    catch (exception &e) {
        throw;
    }
}

void Controller::attackHelper(string &input) {
    try {
        stringstream ss;
        split(input);
        if (args.size() != 3 || args[1] != "attack") {
            ss.clear();
            ss << "oppsi poosi... illegal attack command: " << input << endl;
            throw ControllerException(ss.str());
        }
        model->attack(args[0], args[2]);
    }
    catch (exception &e) {
        throw;
    }
}

void Controller::start_workingHelper(string &input) {
    try {
        stringstream ss;
        split(input);
        if (args.size() != 4 || args[1] != "start_working") {
            ss.clear();
            ss << "oppsi poosi... illegal start_working command: " << input << endl;
            throw ControllerException(ss.str());
        }
        model->start_working(args[0], args[3], args[2]);
    }
    catch (exception &e) {
        throw;
    }
}

void Controller::split(const string &input) {
    args.clear();
    stringstream ss;
    ss << input;
    std::string arg;
    while (ss >> arg) {
        args.push_back(arg);
    }
    for (auto &str: args) {
        for (auto it = str.begin(); it != str.end();) {
            if (*it == ')' || *it == '(' || *it == ',') {
                str.replace(it, it + 1, "");
            } else {
                ++it;
            }
        }
    }
}
