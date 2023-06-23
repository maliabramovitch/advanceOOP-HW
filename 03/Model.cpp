#include <fstream>
#include "Model.h"

/**
 * Model private
 */

Model::Model(const char *castlesFileName, const char *farmsFileName) {
    try {
        //controller = make_shared<Controller>(getControllerInstance());
        view = make_shared<View>();
        time = 0;
        initCastles(castlesFileName);
        initFarms(farmsFileName);
    }
    catch (exception &e) {
        throw;
    }
}

void Model::initStructureArgs(const string &fileName, int i) {
    stringstream ssExcept;
    ssExcept << "oppsi poosi... input illegal in file: " << fileName << endl;
    stringstream ssEdit;
    string arg;
    arg = args[0];
    if (arg.empty()) {
        throw (InputDataException(ssExcept.str()));
    }
    args.pop_front();
    switch (i) {
        case 0: { // castle name check
            if (args[arg.size() - 1] == ",") {
                arg.pop_back();
            }
            for (const char c: arg) {
                if (!isalpha(c)) {
                    throw (InputDataException(ssExcept.str()));
                }
            }
            args.push_back(arg);
            break;
        }
        case 1: { // position check
            double d1, d2;
            try {
                positionHelper(arg, d1, d2);
            } catch (exception &e) {
                throw (InputDataException(ssExcept.str()));
            }
            ssEdit << arg;
            ssEdit >> d1;
            if (!ssEdit) {
                throw (InputDataException(ssExcept.str()));
            }
            ssEdit >> d2;
            if (!ssEdit) {
                throw (InputDataException(ssExcept.str()));
            }
            ssEdit.clear();
            ssEdit << d1;
            args.push_back(ssEdit.str());
            ssEdit.clear();
            ssEdit << d2;
            args.push_back(ssEdit.str());
            break;
        }
        case 2: { // boxes storage/production check
            ssEdit << arg;
            int n;
            ssEdit >> n;
            if (!ssEdit) {
                throw (InputDataException(ssExcept.str()));
            }
            ssEdit.clear();
            ssEdit << n;
            args.push_back(ssEdit.str());
            break;
        }
    }
}

void Model::checkCastle(const string &fileName) {
    stringstream ssExcept;
    ssExcept << "oppsi poosi... input illegal in file: " << fileName << endl;
    std::string arg;
    if (args.size() != 3) {

        throw (InputDataException(ssExcept.str()));
    }
    try {
        for (int i = 0; i < 3; ++i) {
            initStructureArgs(fileName, i);
        }
    }
    catch (exception &e) {
        throw;
    }
}

void Model::checkFarm(const string &fileName) {
    stringstream ssExcept;
    ssExcept << "oppsi poosi... input illegal in file: " << fileName << endl;
    string arg;
    if (args.size() != 4) {

        throw (InputDataException(ssExcept.str()));
    }
    try {
        for (int i = 0; i < 3; ++i) {
            if (i >= 2) {
                initStructureArgs(fileName, 2);
            } else {
                initStructureArgs(fileName, i);
            }
        }

    }
    catch (exception &e) {
        throw;
    }
}


void Model::initCastles(const char *castlesFileName) {
    try {
        fstream file(castlesFileName);
        string line;
        while (!file.eof()) {
            getline(file, line);
            stringstream ss(line);
            args.clear();
            while (!ss.eof()) {
                string arg;
                ss >> arg;
                args.push_back(arg);
            }
            checkCastle(castlesFileName);
            simObjects.emplace_back(make_shared<Castle>(args[0], stod(args[1]), stod(args[2]), stoi(args[3])));
        }
    }
    catch (exception &e) {
        throw;
    }
}

void Model::initFarms(const char *farmsFileName) {
    try {
        fstream file(farmsFileName);
        string line;
        while (!file.eof()) {
            getline(file, line);
            stringstream ss(line);
            args.clear();
            while (!ss.eof()) {
                string arg;
                ss >> arg;
                args.push_back(arg);
            }
            checkFarm(farmsFileName);
            simObjects.emplace_back(
                    make_shared<Farm>(args[0], stod(args[1]), stod(args[2]), stoi(args[3]), stoi(args[4])));
        }
    }
    catch (exception &e) {
        throw;
    }
}

int Model::initKnightArgs(std::string &input) {
    stringstream ssExcept, ssEdit;
    ssExcept << "oppsi poosi... Knight creation error" << std::endl;
    if (input.empty()) {
        throw InputDataException(ssExcept.str());
    }
    args.clear();
    ssEdit << input;
    string arg;
    while (!ssEdit.eof()) {
        ssEdit >> arg;
        args.push_back(arg);
    }
    if (args.empty()) {
        throw InputDataException(ssExcept.str());
    }
    if (args[0] != "create") {
        args.pop_front();
    }
    for (weak_ptr<Agent> &a: agents) {
        if (a.lock()->getRole() == 'K' && a.lock()->getName() == args[0]) {
            ssExcept.clear();
            ssExcept << "oopsi poopsi... Knight " << args[0] << " already exist" << std::endl;
            throw AgentAlreadyExistException(ssExcept.str());
        }
    }
    auto it(args.begin() + 1);
    if (*it == "Knight") {
        args.erase(it);
    }
    auto itStructures(structures.begin());
    for (; itStructures != structures.end(); ++itStructures) {
        if (args[1] == itStructures->lock()->getName()) {
            break;
        }
    }
    if (itStructures == structures.end()) {
        ssExcept.clear();
        ssExcept << "oopsi poopsi... Knight location: " << args[1] << " doesn't exist" << std::endl;
        throw AgentAlreadyExistException(ssExcept.str());
    }
    return (int) std::distance(structures.begin(), itStructures);
}

void Model::initPeasantThugArgs(std::string &input) {
    stringstream ssExcept, ssEdit;
    ssExcept << "oppsi poosi... Peasant/Thug creation error" << std::endl;
    if (input.empty()) {
        throw InputDataException(ssExcept.str());
    }
    args.clear();
    ssEdit << input;
    string arg;
    while (!ssEdit.eof()) {
        ssEdit >> arg;
        args.push_back(arg);
    }
    if (args.empty()) {
        throw InputDataException(ssExcept.str());
    }
    if (args[0] != "create") {
        args.pop_front();
    }
    auto it(args.begin() + 1);
    if (*it == "Peasant" || *it == "Thug") {
        args.erase(it);
    }
    double d1, d2;
    positionHelper(args[1], d1, d2);
    ssEdit.clear();
    ssEdit << d1;
    args.push_back(ssEdit.str());
    ssEdit.clear();
    ssEdit << d2;
    args.push_back(ssEdit.str());
}


void Model::positionHelper(string &input, double &d1, double &d2) {
    stringstream ssEdit;
    for (auto it = input.begin(); it != input.end(); ++it) {
        if (*it == ',' || *it == '(' || *it == ')') {
            input.replace(it, it + 1, " ");
        }
    }
    ssEdit << input;
    ssEdit >> d1;
    if (!ssEdit) {
        throw (InputDataException("double\n"));
    }
    ssEdit >> d2;
    if (!ssEdit) {
        throw (InputDataException("double\n"));
    }
}

/**
 * Model public
 */

shared_ptr<Model> Model::instance = nullptr;

shared_ptr<Model> &Model::getModelInstance(const char *castlesFileName, const char *farmsFileName) {
    if (!instance) {
        Model(castlesFileName, farmsFileName);
    }
    return instance;
}

Model::~Model() {
    instance.reset();
    simObjects.clear();
    controller.reset();
    view.reset();
}

unsigned int Model::getTime() const {
    return time;
}

void Model::status() {
    for (const shared_ptr<SimObject> &simObj: simObjects) {
        simObj->broadcastCurrentState();
    }
}

void Model::go() {
    for (const shared_ptr<SimObject> &simObj: simObjects) {
        simObj->update();
    }
}

void Model::create(std::string input) {
    try {
        if (input.find("Knight") != std::string::npos) {
            int locationIndex = initKnightArgs(input);
            shared_ptr<SimObject> sharedKnight = make_shared<Knight>(args[0], structures[locationIndex], structures);
            simObjects.push_back(sharedKnight);
            agents.push_back(static_pointer_cast<Agent>(sharedKnight));

        } else if (input.find("Peasant") != std::string::npos) {
            initPeasantThugArgs(input);
            shared_ptr<SimObject> sharedPeasant = make_shared<Peasant>(args[0], stof(args[1]), stof(args[2]));
            simObjects.emplace_back(sharedPeasant);
            agents.emplace_back(static_pointer_cast<Agent>(sharedPeasant));
        } else {
            initPeasantThugArgs(input);
            shared_ptr<SimObject> sharedTHug = make_shared<Peasant>(args[0], stof(args[1]), stof(args[2]));
            simObjects.push_back(sharedTHug);
            agents.push_back(static_pointer_cast<Agent>(sharedTHug));
        }
    }
    catch (exception &e) {
        throw;
    }
}


/**
 * AgentAlreadyExistException
 */
Model::AgentAlreadyExistException::AgentAlreadyExistException(string
                                                              mess) : mess(std::move(mess)) {}

const char *Model::AgentAlreadyExistException::what() const noexcept {
    return mess.c_str();
}

/**
 * InputDataException
 */
Model::InputDataException::InputDataException(string
                                              mess) : mess(std::move(mess)) {}

const char *Model::InputDataException::what() const noexcept {
    return mess.c_str();
}

//
// Created by Mali Abramovitch on 17/06/2023.
//

