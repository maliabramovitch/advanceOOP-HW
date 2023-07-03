//
// Created by Mali Abramovitch on 17/06/2023.
//

#ifndef INC_03_MODEL_H
#define INC_03_MODEL_H

#include <memory>
#include <iostream>
#include "SimObject.h"
#include "Agent.h"
#include "Peasant.h"
#include "Knight.h"
#include "Thug.h"
#include "Structure.h"
#include "Farm.h"
#include "Castle.h"
#include "View.h"

class Model { /** Singleton **/
private:
    /**
     * friend classes
     */

    /**
     * fields
     */
    static shared_ptr<Model> instance; //singleton instancePtr
    deque<shared_ptr<SimObject>> simObjects;
    deque<shared_ptr<Agent>> agents;
    deque<shared_ptr<Structure>> structures;
    shared_ptr<View> view;
    unsigned int time;
    deque<string> args;

    /**
     * private methods
     */
    Model();

    void checkCastle(const string &fileName);

    void checkFarm(const string &fileName);

    void initStructureArgs(const string &fileName, int i);

    static void positionHelper(std::string &input, float &d);

    shared_ptr<Agent> &getAgent(const string &name);

    shared_ptr<Structure> &getStructure(const string &name);

    bool isAgentExist(const string& agentName);

    bool isStructureExist(const string& structureName);

public:

    /**
     * class's methods
     */
    static shared_ptr<Model> getModelInstance();

    ~Model();

    Model(const Model &) = delete;

    Model(Model &&) = delete;

    Model &operator=(const Model &) = delete;

    Model &operator=(Model &&) = delete;

    const deque<shared_ptr<SimObject>> &getSimObjects() const;

    const deque<shared_ptr<Agent>> &getAgents() const;

    const deque<shared_ptr<Structure>> &getStructures() const;

    unsigned int getTime() const;

    void initCastles(const char *castlesFileName);

    void initFarms(const char *farmsFileName);

    void status();

    void go();

    void createKnight(const string &name, const string &structureName);

    void createPeasant(const string &name, float x, float y);

    void createThug(const string &name, float x, float y);

    void setCourseAgent(const string &agentName, float course, float speed = 0);

    void setPositionAgent(const string &agentName, float newX, float newY, float speed = 0);

    void setDestinationAgent(const string &agentName, const string &newDest);

    void stopAgent(const string &agentName);

    void attack(const string &thugName, const string &peasantName);

    void start_working(const string &peasantName, const string &castle, const string &farm);

    void attachedView(shared_ptr<View> &view);

    void detachesView();

    /**
     * exception classes
     */
    class AgentAlreadyExistException : public exception {
        std::string mess;
    public:
        explicit AgentAlreadyExistException(std::string mess);

        const char *what() const noexcept override;
    };

    class InputDataException : public exception {
        std::string mess;
    public:
        explicit InputDataException(std::string mess);

        const char *what() const noexcept override;
    };
};


#endif //INC_03_MODEL_H
