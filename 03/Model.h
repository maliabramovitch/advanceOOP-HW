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
    friend class Controller;

    friend class View;

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

    void initCastles(const char *castlesFileName);

    void initFarms(const char *farmsFileName);

    int initKnightArgs(std::string &input);

    void initPeasantThugArgs(std::string &input) noexcept(false);

    void checkCastle(const string &fileName);

    void checkFarm(const string &fileName);

    void initStructureArgs(const string &fileName, int i);

    static void positionHelper(std::string &input, double &d);


public:

    /**
     * class's methods
     */

    Model(const Model &) = delete;

    Model(Model &&) = delete;

    Model &operator=(const Model &) = delete;

    Model &operator=(Model &&) = delete;

    static shared_ptr<Model> &getModelInstance();

    ~Model();

    unsigned int getTime() const;

    void status();

    void go();

    void show();

    void setDefaultView();

    void setSizeView(int newSize);

    void setZoomView(float newZoom);

    void setPanView(float newX, float newY);

    void create(std::string input); // only for Agents

    void setCourseAgent(const string &agentName, float course, float speed = 0);

    void setPositionAgent(const string &agentName, float newX, float newY, float speed = 0);

    void setDestinationAgent(const string &agentName, const string &newDest);

    void stopAgent(const string &agentName);

    void attack(const string &thugName, const string &peasantName);

    void start_working(const string &peasantName, const string &castle, const string &farm);


    shared_ptr<Agent> &getAgent(const string &name);

    shared_ptr<Structure> &getStructure(const string &name);

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
