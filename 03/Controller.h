//
// Created by Mali Abramovitch on 18/06/2023.
//

#ifndef INC_03_CONTROLLER_H
#define INC_03_CONTROLLER_H

#include <utility>

#include "Model.h"

class Controller {
    deque<string> args;
    shared_ptr<View> view;
    static shared_ptr<Model> model;

    Controller();

    static shared_ptr<Controller> instancePtr; //singleton instancePtr

    static void goHelper(string &input);

    static void statusHelper(string &input);

    void showHelper(string &input);

    void defaultHelper(string &input);

    void sizeHelper(string &input); // 6 < s <= 30

    void zoomHelper(string &input);

    void panHelper(string &input);

    void createHelper(const string &input);

    void courseHelper(string &input);

    void positionHelper(string &input);

    void destinationHelper(string &input);

    void stopHelper(string &input);

    void attackHelper(string &input);

    void start_workingHelper(string &input);

    void split(const string& input);

public:

    static shared_ptr<Controller> &getControllerInstance(char *castlesFileName, char *farmsFileName);

    Controller(const Controller &) = delete;

    Controller(Controller &&) = delete;

    Controller &operator=(const Controller &) = delete;

    Controller &operator=(Controller &&) = delete;

    ~Controller();

    void run(bool checkMode);

    class ControllerException : public exception {
        string mess;
    public:
        explicit ControllerException(string mess) : mess(std::move(mess)) {}

        const char *what() const noexcept override { return mess.c_str(); }
    };
};


#endif //INC_03_CONTROLLER_H
