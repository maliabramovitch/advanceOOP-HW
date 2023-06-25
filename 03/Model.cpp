#include <fstream>
#include <memory>
#include "Model.h"

/**
 * Model private
 */
shared_ptr<Model> Model::instance = getModelInstance();

Model::Model() {
    view = std::make_shared<View>();
    time = 0;
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
            if (arg[arg.size() - 1] == ',') {
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
        case 1:
        case 2: { // x/y position check
            double d;
            try {
                positionHelper(arg, d);
            } catch (exception &e) {
                throw (InputDataException(ssExcept.str()));
            }
            ssEdit << arg;
            if (!ssEdit) {
                throw (InputDataException(ssExcept.str()));
            }
            args.push_back(arg);
            break;
        }
        case 3:
        case 4: { // boxes storage/production check
            if (arg[arg.size() - 1] == ',') arg.pop_back();
            ssEdit << arg;
            int n;
            ssEdit >> n;
            if (!ssEdit) {
                throw (InputDataException(ssExcept.str()));
            }
            ssEdit.clear();
            args.push_back(arg);
            break;
        }
    }
}

void Model::checkCastle(const string &fileName) {
    stringstream ssExcept;
    ssExcept << "oppsi poosi... input illegal in file: " << fileName << endl;
    std::string arg;
    if (args.size() != 4) {

        throw (InputDataException(ssExcept.str()));
    }
    try {
        for (int i = 0; i < 4; ++i) {
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
    if (args.size() != 5) {

        throw (InputDataException(ssExcept.str()));
    }
    try {
        for (int i = 0; i < 5; ++i) {
            initStructureArgs(fileName, i);
        }

    }
    catch (exception &e) {
        throw;
    }
}


void Model::initCastles(const char *castlesFileName) {
    try {
        fstream file(castlesFileName);
        if (!file) {
            stringstream ssExcept;
            ssExcept << "oppsi poosi... file: " << castlesFileName << " was not opened" << endl;
        }
        string line;
        while (!file.eof()) {
            getline(file, line);
            stringstream ss(line);
            args.clear();
            string arg;
            while (ss >> arg) {
                args.push_back(arg);
            }
            checkCastle(castlesFileName);
            simObjects.emplace_back(make_shared<Castle>(args[0], stod(args[1]), stod(args[2]), stoi(args[3])));
            structures.push_back(static_pointer_cast<Structure>(simObjects[simObjects.size() - 1]));
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
            string arg;
            while (ss >> arg) {
                args.push_back(arg);
            }
            checkFarm(farmsFileName);
            simObjects.emplace_back(
                    make_shared<Farm>(args[0], stod(args[1]), stod(args[2]), stoi(args[3]), stoi(args[4])));
            structures.push_back(static_pointer_cast<Structure>(simObjects[simObjects.size() - 1]));
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
    for (shared_ptr<Agent> &a: agents) {
        if (a->getRole() == 'K' && a->getName() == args[0]) {
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
        if (args[1] == (*itStructures)->getName()) {
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
    while (ssEdit >> arg) {
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
    double d;
    positionHelper(args[1], d);
    ssEdit.clear();
    ssEdit << d;
    args.push_back(ssEdit.str());
    positionHelper(args[2], d);
    ssEdit.clear();
    ssEdit << d;
    args.push_back(ssEdit.str());
}


void Model::positionHelper(string &input, double &d) {
    stringstream ssEdit;
    for (auto it = input.begin(); *it != '\0';) {
        if (*it == ',' || *it == '(' || *it == ')') {
            input.replace(it, it + 1, " ");
        } else {
            ++it;
        }
    }
    ssEdit << input;
    ssEdit >> d;
    if (!ssEdit) {
        throw (InputDataException("double\n"));
    }
}

/**
 * Model public
 */


shared_ptr<Model> &Model::getModelInstance() {
    if (!instance) {
        instance = shared_ptr<Model>(new Model());
    }
    return instance;
}

Model::~Model() {
    instance.reset();
    simObjects.clear();
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
    ++time;
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

void Model::show() {
    view->show();
}

shared_ptr<Agent> &Model::getAgent(const string &name) {
    for (auto &agent: agents) {
        if (agent->getName() == name) {
            if (!agent->getIsAlive()) {
                stringstream ss;
                ss << agent->getName() << " is dead" << endl;
                throw InputDataException(ss.str());
            }
            return agent;
        }
    }
    stringstream ss;
    ss << "Agent" << name << "don't exist" << endl;
    throw InputDataException(ss.str());
}

shared_ptr<Structure> &Model::getStructure(const string &name) {
    for (auto &structure: structures) {
        if (structure->getName() == name) {
            return structure;
        }
    }
    stringstream ss;
    ss << "Structure" << name << "don't exist" << endl;
    throw InputDataException(ss.str());
}

void Model::setDefaultView() {
    view->default_view();
}

void Model::setSizeView(int newSize) {
    try {
        view->adjustSize(newSize);
    }
    catch (exception &e) {
        throw;
    }
}

void Model::setZoomView(float newZoom) {
    try {
        view->adjustZoom(newZoom);
    }
    catch (exception &e) {
        throw;
    }
}

void Model::setPanView(float newX, float newY) {
    view->adjustPan(newX, newY);
}

void Model::setCourseAgent(const string &agentName, float course, float speed) {
    try {
        auto agent = getAgent(agentName);
        if (agent->getRole() == 'T') {
            if (speed <= 0) {
                stringstream ss;
                ss << "set course for " << agent->getName() << ": illegal speed" << speed << endl;
                throw InputDataException(ss.str());
            }
            auto thug = dynamic_pointer_cast<Thug>(agent);
            if (!thug) {
                stringstream ss;
                ss << "set course for " << agent->getName() << "dynamic cast" << speed << endl;
                throw InputDataException(ss.str());
            }
            thug->setCourse(course, speed);
        } else {
            auto knight = dynamic_pointer_cast<Knight>(agent);
            if (!knight) {
                stringstream ss;
                ss << "set course for " << agent->getName() << "role" << agent->getRole() << endl;
                throw InputDataException(ss.str());
            }
            knight->setCourse(course);
        }
    }
    catch (exception &e) {
        throw;
    }
}

void Model::setPositionAgent(const string &agentName, float newX, float newY, float speed) {
    try {
        auto agent = getAgent(agentName);
        if (agent->getRole() == 'T') {
            if (speed <= 0) {
                stringstream ss;
                ss << "set course for " << agent->getName() << ": illegal speed" << speed << endl;
                throw InputDataException(ss.str());
            }
            auto thug = dynamic_pointer_cast<Thug>(agent);
            if (!thug) {
                stringstream ss;
                ss << "set course for " << agent->getName() << "dynamic cast" << speed << endl;
                throw InputDataException(ss.str());
            }
            thug->setNewPosition(newX, newY, speed);
        } else {
            auto knight = dynamic_pointer_cast<Knight>(agent);
            if (!knight) {
                stringstream ss;
                ss << "set course for " << agent->getName() << "role" << agent->getRole() << endl;
                throw InputDataException(ss.str());
            }
            knight->setPosition(newX, newY);
        }
    }
    catch (exception &e) {
        throw;
    }
}

void Model::setDestinationAgent(const string &agentName, const string &newDest) {
    try {
        auto agent = getAgent(agentName);
        auto structure = getStructure(newDest);
        if (agent->getRole() == 'K') {
            auto knight = dynamic_pointer_cast<Knight>(agent);
            if (!knight) {
                stringstream ss;
                ss << "set course for " << agent->getName() << "dynamic cast " << agent->getRole()
                   << endl;
                throw InputDataException(ss.str());
            }
            knight->setDestination(structure);
        } else {

        }
    }
    catch (exception &e) {
        throw;
    }
}

void Model::stopAgent(const string &agentName) {
    try {
        auto agent = getAgent(agentName);
        agent->setStopped(true);
    }
    catch (exception &e) {
        throw;
    }
}

void Model::attack(const string &thugName, const string &peasantName) {
    auto peasantAgent = getAgent(peasantName);
    auto thugAgent = getAgent(thugName);
    if (!peasantAgent || !thugAgent) {
        stringstream ss;
        ss << thugName << " or " << peasantName << "doe's not exist" << endl;
        throw InputDataException(ss.str());
    }
    auto thug = dynamic_pointer_cast<Thug>(thugAgent);
    if (!thug) {
        throw InputDataException("dynamic cast problem in Model::attack\n");
    }
    for (auto &agent: agents) {
        if (agent->getRole() == 'K') {
            if (MovingObject::calculateDistance(agent->getCurrentX(), agent->getCurrentY(),
                                                peasantAgent->getCurrentX(), peasantAgent->getCurrentY()) <= 2.5) {
                return;
            }
        }
    }
    thug->srtPeasantToAttack(peasantAgent);
}

void Model::start_working(const string &peasantName, const string &castleName, const string &farmName) {
    try {
        auto agent = getAgent(peasantName);
        auto castle = getStructure(castleName);
        auto farm = getStructure(farmName);
        auto peasant = dynamic_pointer_cast<Peasant>(agent);
        if (!peasant) {
            stringstream ss;
            ss << "start_working for " << agent->getName() << "dynamic cast" << endl;
            throw InputDataException(ss.str());
        }
        peasant->addTask(farm, castle);

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

