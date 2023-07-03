
//
// Created by Mali Abramovitch on 16/06/2023.
//


#include <utility>

#include "Geometry.h"
#include <cmath>
#include "Model.h"
#include "Structure.h"

#ifndef INC_03_MOVINGOBJECT_H
#define INC_03_MOVINGOBJECT_H

#endif //INC_03_MOVINGOBJECT_H

class MovingObject {
private:
    float distanceFromPosition = 0;

protected:
    bool stopped = true;
    //bool position = false;
    float speed = 0;
    float currentX = 0, currentY = 0;
    float newX = 0, newY = 0;
    float course = 0;
    enum {
        STOPPED = -1, POSITION = 0, COURSE = 1, DESTINATION = 2
    };
    int movement = STOPPED;


    void calculateDistanceFromPosition() {
        distanceFromPosition = calculateDistance(currentX, currentY, newX, newY);
    }

public:
    explicit MovingObject(float speed, float x, float y)
            : stopped(true), distanceFromPosition(0), speed(speed), currentX(x), currentY(y), newX(x), newY(y) {}


    MovingObject(const MovingObject &rhs) { *this = rhs; }

    MovingObject(MovingObject &&lhs) noexcept { *this = lhs; }

    MovingObject &operator=(const MovingObject &rhs) {
        if (this != &rhs) {
            distanceFromPosition = rhs.distanceFromPosition;
            stopped = rhs.stopped;
            //position = rhs.position;
            speed = rhs.speed;
            currentX = rhs.currentX;
            currentX = rhs.currentX;
            newY = rhs.newY;
            newY = rhs.newY;
            movement = rhs.movement;
        }
        return *this;
    }

    MovingObject &operator=(MovingObject &&lhs) noexcept {
        if (this != &lhs) {
            distanceFromPosition = lhs.distanceFromPosition;
            stopped = lhs.stopped;
            //position = lhs.position;
            speed = lhs.speed;
            currentX = lhs.currentX;
            currentX = lhs.currentX;
            newY = lhs.newY;
            newY = lhs.newY;
            movement = lhs.movement;
            lhs.distanceFromPosition = 0;
            lhs.stopped = false;
            //lhs.position = false;
            lhs.speed = 0;
            lhs.currentX = 0;
            lhs.currentX = 0;
            lhs.newY = 0;
            lhs.newY = 0;
            lhs.movement = 0;
        }
        return *this;
    }

    ~MovingObject() = default;

    float getDistanceFromDestination() const { return distanceFromPosition; }

    void setDistanceFromDestination(float d) { distanceFromPosition = d; }

    float getSpeed() const { return speed; }

    void setSpeed(float s) { speed = s; }

    float getCurrentX() const { return currentX; }

    void setCurrentX(float x) { currentX = x; }

    float getCurrentY() const { return currentY; }

    void setCurrentY(float y) { currentY = y; }

    float getNewX() const { return newX; }

    void setNewX(float x) { newX = x; }

    float getNewY() const { return newY; }

    void setNewPosition(float x, float y, float s) {
        newX = x;
        newY = y;
        speed = s;
        stopped = false;
        movement = POSITION;
    }

    bool getStopped() const { return stopped; }

    void setStopped(bool newStopped) { stopped = newStopped; }

    //bool isPosition() const { return position; }

    int getMovement() const { return movement; }

    float getCourse() const { return course; }

    void setCourse(float newCourse, float newSpeed) {
        course = newCourse;
        speed = newSpeed;
        stopped = false;
        movement = COURSE;
    }

    static float finedDeg(float x1, float y1, float x2, float y2) {
        float prod = x1 * x2 + y1 * y2;
        float mag = sqrt((float) (pow((x1), 2) + pow(y1, 2))) * sqrt((float) (pow((x2), 2) + pow(y2, 2)));
        return atan2(y1 - y2, x1 - x2);
    }

    virtual void doMove() {
        if (!stopped) {
            Cartesian_vector cv;
            if (movement == POSITION || movement == DESTINATION) {
                if (distanceFromPosition == 0) {
                    calculateDistanceFromPosition();
                }
                if (distanceFromPosition > 0) {
                    cv.delta_y = (newY - currentY);
                    cv.delta_x = (newX - currentX);
                    Polar_vector pv;
                    course = (float) to_degrees(finedDeg(newX, newY, currentX, currentY));
                    pv.theta = to_radians(course);
                    pv.r = speed;
                    cv = Cartesian_vector(pv);
                    distanceFromPosition -= (speed / 10);
                    if (distanceFromPosition <= 0) {
                        distanceFromPosition = 0;
                        currentX = newX;
                        currentY = newY;
                        return;
                    } else {
                    }
                }
                currentX += (float) (cv.delta_x) / 10;
                currentY += (float) (cv.delta_y) / 10;
            } else {
                Polar_vector pv;
                pv.r = speed;
                pv.theta = to_radians(course);
                cv = Cartesian_vector(pv);

                currentX += (float) (cv.delta_y) / 10;
                currentY += (float) (cv.delta_x) / 10;
            }
        }
    }

    static float calculateDistance(float x1, float y1, float x2, float y2) {
        return (float) std::sqrt((std::pow((x1 - x2), 2) + std::pow((y1 - y2), 2)));
    }
};
