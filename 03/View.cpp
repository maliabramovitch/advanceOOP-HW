//
// Created by Mali Abramovitch on 18/06/2023.
//

#include "Model.h"
#include <cmath>

void View::default_view() {
    x = 0;
    y = 0;
    zoom = 2.0;
    size = 25;
}

void View::adjustSize(int newSize) {
    if (newSize <= 6 || newSize > 30) {
        stringstream ss;
        ss << "oppsi poosi... Size: " << newSize << " illegal, (6 < size <= 30)" << endl;
        throw ViewException(ss.str());
    }
    size = newSize;
}

void View::adjustZoom(float newZoom) {
    if (newZoom < 0) {
        stringstream ss;
        ss << "oppsi poosi... Zoom: " << newZoom << " illegal, (Zoom > 0)" << endl;
        throw ViewException(ss.str());
    }
    zoom = newZoom;
}

void View::adjustPan(float newX, float newY) {
    x = newX;
    y = newY;
}

unsigned int getLen(int row, int col, int x, int y) {
    unsigned int len = 3;
    stringstream ss;
    ss << row;
    if (ss.str().size() > len) len = ss.str().size();
    ss.seekp(ios::beg);
    ss << col;
    if (ss.str().size() > len) len = ss.str().size();
    ss.seekp(ios::beg);
    ss << x;
    if (ss.str().size() > len) len = ss.str().size();
    ss.seekp(ios::beg);
    ss << y;
    if (ss.str().size() > len) len = ss.str().size();
    ss.seekp(ios::beg);
    return len;
}

void View::show() const {
    cout << setprecision(2) << std::fixed << "Display size: " << size << ", scale: "
         << zoom << ", origin: (" << x << ", " << y << ")" << endl;
    int row = (int) (y + zoom * ((float) size - 1));
    int col = (int) (x + zoom * ((float) size - 1));
    unsigned int len = getLen(row, col, (int) x, (int) y);
    int counter = size - 1;
    std::ios_base::fmtflags f(cout.flags());
    for (int i = row; i >= y; i -= zoom) {
        if (counter % 3 == 0) {
            cout << setw(len) << setfill(' ') << right << (int) i << ' ';
            cout.flags(f);
        } else {
            cout << setw(4) << setfill(' ') << ' ';
        }
        --counter;
        for (int j = x; j <= col; j += zoom) {
            string square = ".";
            float agentX, agentY;
            for (const auto &agent: Model::getModelInstance()->getAgents()) {
                agentX = (agent->getCurrentX());
                agentY = (agent->getCurrentY());
                if (((agentX == j) || (agentX >= (j) && agentX < (j + zoom))) &&
                    (((agentY == i) || (agentY >= (i) && agentY < (i + zoom))))) {
                    square = agent->getName().substr(0, 2);
                }
            }
            stringstream ss;
            for (const auto &structure: Model::getModelInstance()->getStructures()) {
                if (structure->getY() >= i && structure->getY() < i + zoom &&
                    structure->getX() >= j && structure->getX() < j + zoom) {
                    square = structure->getName().substr(0, 2);
                }
            }
            cout << setw(2) << setfill(' ') << left << square;
        }
        cout << endl;
    }
    cout.flags(f);
    counter = 0;
    stringstream ss;
    for (int i = x; i <= col; i = i + (int) zoom) {
        if (counter % 3 == 0) {
            if (i == x) {
                cout << setw(len + 2) << setfill(' ') << right << i;
            } else {
                ss << i << ' ';
                cout << setw(6) << setfill(' ') << right << i;
                ss.seekp(ios::beg);
            }
        }
        ++counter;
    }
    cout << endl;
}