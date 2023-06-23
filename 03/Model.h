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
#include "Controller.h"
#include "View.h"

class Model { /** Singleton **/
private:
    /**
     * friend classes
     */
    friend class Controller;

    friend class View;

    friend class ModelDestroyer;

    /**
     * fields
     */
    static shared_ptr<Model> instance; //singleton instance
    deque<shared_ptr<SimObject>> simObjects;
    deque<weak_ptr<Agent>> agents;
    deque<weak_ptr<Structure>> structures;
    shared_ptr<Controller> controller;
    shared_ptr<View> view;
    unsigned int time;
    deque<string> args;

    /**
     * private methods
     */
    Model(const char *castlesFileName, const char *farmsFileName);

    void initCastles(const char *castlesFileName);

    void initFarms(const char *farmsFileName);

    int initKnightArgs(std::string &input);

    void initPeasantThugArgs(std::string &input) noexcept(false);

    void checkCastle(const string &fileName);

    void checkFarm(const string &fileName);

    void initStructureArgs(const string &fileName, int i);

    static void positionHelper(std::string &input, double &d1, double &d2);


public:

    /**
     * class's methods
     */

    Model(const Model &) = delete;

    Model(Model &&) = delete;

    Model &operator=(const Model &) = delete;

    Model &operator=(Model &&) = delete;

    static shared_ptr<Model> &getModelInstance(const char *castlesFileName, const char *farmsFileName);

    ~Model();

    unsigned int getTime() const;

    void status();

    void go();

    void create(std::string input); // only for Agents

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
