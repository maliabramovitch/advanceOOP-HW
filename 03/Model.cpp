#include <fstream>
#include <memory>
#include "Model.h"

/**
 * Model private
 */
shared_ptr<Model> Model::instance = getModelInstance();

Model::Model() {
    time = 0;
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
            float d;
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
        default: {
        }
    }
}


void Model::positionHelper(string &input, float &d) {
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
    ss << "Agent " << name << " don't exist" << endl;
    throw InputDataException(ss.str());
}

shared_ptr<Structure> &Model::getStructure(const string &name) {
    for (auto &structure: structures) {
        if (structure->getName() == name) {
            return structure;
        }
    }
    stringstream ss;
    ss << "Structure " << name << " don't exist" << endl;
    throw InputDataException(ss.str());
}


bool Model::isAgentExist(const string &agentName) {
    try {
        getAgent(agentName);
        return true;
    }
    catch (exception &e) {
        return false;
    }
}

bool Model::isStructureExist(const string &structureName) {
    try {
        getAgent(structureName);
        return false;
    }
    catch (exception &e) {
        return true;
    }
}

/**
 * Model public
 */
shared_ptr<Model> Model::getModelInstance() {
    if (!instance) {
        instance = shared_ptr<Model>(new Model());
    }
    return instance;
}

Model::~Model() {
    if (instance.use_count() == 1) {
        instance.reset();
        simObjects.clear();
        view.reset();
    }
}

const deque<shared_ptr<SimObject>> &Model::getSimObjects() const {
    return simObjects;
}

const deque<shared_ptr<Agent>> &Model::getAgents() const {
    return agents;
}

const deque<shared_ptr<Structure>> &Model::getStructures() const {
    return structures;
}

unsigned int Model::getTime() const {
    return time;
}

void Model::initFarms(const char *farmsFileName) {
    try {
        stringstream ss;
        fstream file(farmsFileName);
        if (!file) {
            ss << "file Opening problem in file: " << farmsFileName << endl;
            throw InputDataException(ss.str());
        }
        string line;
        while (!file.eof()) {
            getline(file, line);
            ss.clear();
            ss << line;
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

void Model::initCastles(const char *castlesFileName) {
    try {
        stringstream ss;
        fstream file(castlesFileName);
        if (!file) {
            if (!file) {
                ss << "file Opening problem in file: " << castlesFileName << endl;
                throw InputDataException(ss.str());
            }
        }
        string line;
        while (!file.eof()) {
            getline(file, line);
            ss.clear();
            ss << line;
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

void Model::status() {
    cout << '\n';
    for (const shared_ptr<SimObject> &simObj: simObjects) {
        simObj->broadcastCurrentState();
    }
    cout << endl;
}

void Model::go() {
    ++time;
    for (auto &agent: agents) {
        agent->doMove();
    }
    for (const shared_ptr<SimObject> &simObj: simObjects) {
        simObj->update();
    }
}

void Model::createKnight(const string &agentName, const string &structureName) {
    if (isAgentExist(agentName)) {
        stringstream ss;
        ss << "Agent" << agentName << " already exist" << endl;
        throw AgentAlreadyExistException(ss.str());
    }
    auto structure = getStructure(structureName);
    shared_ptr<Knight> knight = make_shared<Knight>(agentName, structure, structures);
    simObjects.push_back(knight);
    agents.push_back(knight);
}

void Model::createPeasant(const string &agentName, float x, float y) {
    if (isAgentExist(agentName)) {
        stringstream ss;
        ss << "Agent " << agentName << " already exist" << endl;
        throw AgentAlreadyExistException(ss.str());
    }
    shared_ptr<Peasant> peasant = make_shared<Peasant>(agentName, x, y);
    simObjects.push_back(peasant);
    agents.push_back(peasant);
}

void Model::createThug(const string &agentName, float x, float y) {
    if (isAgentExist(agentName)) {
        stringstream ss;
        ss << "Agent" << agentName << " already exist" << endl;
        throw AgentAlreadyExistException(ss.str());
    }
    shared_ptr<Thug> thug = make_shared<Thug>(agentName, x, y);
    simObjects.push_back(thug);
    agents.push_back(thug);
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
                ss << "set course for " << agent->getName() << " dynamic cast" << speed << endl;
                throw InputDataException(ss.str());
            }
            thug->setCourse(course, speed);
        } else if (agent->getRole() == 'K') {
            auto knight = dynamic_pointer_cast<Knight>(agent);
            if (!knight) {
                stringstream ss;
                ss << "set course for " << agent->getName() << " role " << agent->getRole() << endl;
                throw InputDataException(ss.str());
            }
            knight->setCourse(course);
        } else {
            stringstream ss;
            ss << "set course for " << agent->getName() << " from type: " << agent->getRole() << " is illegal"
               << endl;
            throw InputDataException(ss.str());
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
                ss << "set position for " << agent->getName() << ": illegal speed" << speed << endl;
                throw InputDataException(ss.str());
            }
            auto thug = dynamic_pointer_cast<Thug>(agent);
            if (!thug) {
                stringstream ss;
                ss << "set position for " << agent->getName() << "dynamic cast" << speed << endl;
                throw InputDataException(ss.str());
            }
            thug->setNewPosition(newX, newY, speed);
        } else if (agent->getRole() == 'K') {
            auto knight = dynamic_pointer_cast<Knight>(agent);
            if (!knight) {
                stringstream ss;
                ss << "set position for " << agent->getName() << "role" << agent->getRole() << endl;
                throw InputDataException(ss.str());
            }
            knight->setPosition(newX, newY);
        } else {
            stringstream ss;
            ss << "set position for " << agent->getName() << " from type: " << agent->getRole() << " is illegal"
               << endl;
            throw InputDataException(ss.str());
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
                ss << "set destination for " << agent->getName() << "dynamic cast " << agent->getRole()
                   << endl;
                throw InputDataException(ss.str());
            }
            knight->setDestination(structure);
        } else {
            stringstream ss;
            ss << "set destination for " << agent->getName() << " from type: " << agent->getRole() << " is illegal"
               << endl;
            throw InputDataException(ss.str());
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
    try {
        auto peasantAgent = getAgent(peasantName);
        auto thugAgent = getAgent(thugName);
        if (peasantAgent->getRole() != 'P' || thugAgent->getRole() != 'T') {
            stringstream ss;
            ss << thugName << " or " << peasantName << " (or both) is illegal agent(s) for attack" << endl;
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
                    thug->setPeasantToAttack(peasantAgent, true);
                    return;
                }
            }
        }
        thug->setPeasantToAttack(peasantAgent, false);
    } catch (exception &e) {
        throw;
    }
}

void Model::start_working(const string &peasantName, const string &castleName, const string &farmName) {
    try {
        auto agent = getAgent(peasantName);
        if (agent->getRole() != 'P') {
            stringstream ss;
            ss << "start_working for " << agent->getName() << "is illegal" << endl;
            throw InputDataException(ss.str());
        }
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

void Model::attachedView(shared_ptr<View> &newView) {
    this->view = newView;
}

void Model::detachesView() {
    view.reset();
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

