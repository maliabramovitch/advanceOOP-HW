//
// Created by Mali Abramovitch on 18/06/2023.
//

#ifndef INC_03_VIEW_H
#define INC_03_VIEW_H
#include "Model.h"

class View {
    float x = 0, y = 0; // axis origin
    float zoom = 2.0;
    int size = 25;

public:
    class ViewException : public exception{
        std::string mess;
    public:
        explicit ViewException(string&& mess) : mess(std::move(mess)) {}
        const char * what() const noexcept override { return mess.c_str();}
    };
    void default_view();
    void adjustSize(int newSize);
    void adjustZoom(float newZoom);
    void adjustPan(float newX, float newY);
    void show() const;

};


#endif //INC_03_VIEW_H
