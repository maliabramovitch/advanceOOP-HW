
//
// Created by Mali Abramovitch on 16/06/2023.
//


#include <utility>

#include "Geometry.h"
#include "Model.h"
#include "Structure.h"

#ifndef INC_03_MOVINGOBJECT_H
#define INC_03_MOVINGOBJECT_H

#endif //INC_03_MOVINGOBJECT_H

class MovingObject {
private:
    void calculateDistanceToNextStop() {
        Point dest;
        Point currentLocation;
        currentLocation.x = currentPosition->x;
        currentLocation.y = currentPosition->y;
        switch (movement) {
            case DESTINATION:
                dest.x = destination->getX();
                dest.y = destination->getY();
                break;
            case POSITION:
                dest.x = newPosition->x;
                dest.y = newPosition->y;
                break;
        }
        distanceToNextStop = Point::distance(dest, currentLocation);
    }

protected:

    struct Position {
        double x = 0;
        double y = 0;

        Position(double x, double y) : x(x), y(y) {}

        bool operator==(const Point &p) { return (x == p.x) && (y == p.y); }
        bool operator==(const Structure &s) { return (x == s.getX()) && (y == s.getY()); }
        bool operator!=(const Point &p) { !operator==(p); }
        bool operator!=(const Structure &s) { return !operator==(s);}
    };

    int speed;
    shared_ptr<Structure> destination;
    shared_ptr<Position> currentPosition;
    shared_ptr<Position> newPosition;
    double course = 0;
    double distanceToNextStop = 0;
    int movement = 0;
    enum {
        DESTINATION, POSITION, COURSE
    };


public:
    explicit MovingObject(shared_ptr<Structure> &dest, double x = 0, double y = 0,
                          int speed = 5) :
            destination(dest), speed(speed) {
        currentPosition = make_shared<Position>(x, y);
        newPosition = make_shared<Position>(0, 0),
                currentPosition->x = x;
        currentPosition->y = y;
    }

    ~MovingObject() = default;

    const shared_ptr<Structure> &getDestination() const { return destination; }

    virtual void setDestination(shared_ptr<Structure> &newDest) {
        destination = newDest;
        movement = DESTINATION;
        newPosition->x = newDest->getX();
        newPosition->x = newDest->getY();
        calculateDistanceToNextStop();
    }

    double getX() const { return currentPosition->x; }

    void setX(double newX) { currentPosition->x = newX; }

    double getY() const { return currentPosition->y; }

    void setY(double newY) { currentPosition->y = newY; }

    int getSpeed() const { return speed; }

    void setSpeed(int newSpeed) { speed = newSpeed; }

    void setPosition(double newX, double newY, int currentSpeed) {
        newPosition->x = newX;
        newPosition->y = newY;
        speed = currentSpeed;
        movement = POSITION;
        calculateDistanceToNextStop();
    }

    void setCourse(double newCourse, int currentSpeed) {
        course = newCourse;
        speed = currentSpeed;
        movement = COURSE;
    }

    bool startMoving() {
        if (distanceToNextStop > 0) {
            if (movement == DESTINATION || movement == POSITION) {
                Cartesian_vector cv;
                cv.delta_x = destination->getX() - getX();
                cv.delta_x = destination->getY() - getY();
                Polar_vector pv(cv);
                pv.r = pv.r - speed;
                Cartesian_vector cv2(pv);
                currentPosition->x = cv2.delta_x;
                currentPosition->y = cv2.delta_y;
                distanceToNextStop -= speed;
                if (distanceToNextStop <= 0) {
                    distanceToNextStop = 0;
                } else { ///still moving
                    return true;
                }
            } else if (movement == COURSE) {
                calculateDistanceToNextStop();
                Polar_vector pv;
                pv.theta = course;
                pv.r = speed;
                Cartesian_vector cv(pv);
                currentPosition->x = cv.delta_x;
                currentPosition->y = cv.delta_y;
                return true;
            }
        }
        if (distanceToNextStop == 0) {
            currentPosition->x = newPosition->x;
            currentPosition->y = newPosition->y;
        }
        return false;
    }
};
