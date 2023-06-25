//
// Created by Mali Abramovitch on 18/06/2023.
//

#ifndef INC_03_CONTROLLER_H
#define INC_03_CONTROLLER_H

#include <utility>

#include "Model.h"

class Controller {

    Controller() = default;

    static shared_ptr<Controller> instancePtr; //singleton instancePtr

    static void goHelper(string& input);

    static void statusHelper(string& input);

    static void showHelper(string& input);

    static void defaultHelper(string& input);

    static void sizeHelper(string &input); // 6 < s <= 30

    static void zoomHelper(string &input);

    static void panHelper(string &input);

    static void createHelper(const string &input);

    static void courseHelper(string &input);

    static void positionHelper(string &input);

    static void destinationHelper(string &input);

    static void stopHelper(string &input);

    static void attackHelper(string &input);

    static void start_workingHelper(string &input);



public:

    static shared_ptr<Controller> &getControllerInstance(char *castlesFileName, char *farmsFileName);

    Controller(const Controller &) = delete;

    Controller(Controller &&) = delete;

    Controller &operator=(const Controller &) = delete;

    Controller &operator=(Controller &&) = delete;

    ~Controller();

    static void run();

    class ControllerException : public exception {
        string mess;
    public:
        explicit ControllerException(string mess) : mess(std::move(mess)) {}

        const char *what() const noexcept override { return mess.c_str(); }
    };
};


#endif //INC_03_CONTROLLER_H
