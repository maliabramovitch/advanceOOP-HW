//
// Created by Mali Abramovitch on 18/06/2023.
//

#include "Model.h"

void View::default_view() {
    x = 0;
    y = 0;
    zoom = 2.0;
    size = 25;
}

void View::adjustSize(int newSize) {
    if (newSize <= 6 || newSize > 30) {
        stringstream ss;
        ss << "oppsi poosi... Size: " << newSize << "illegal, (6 < size <= 30)" << endl;
        throw ViewException(ss.str());
    }
    size = newSize;
}

void View::adjustZoom(float newZoom) {
    if (newZoom < 0) {
        stringstream ss;
        ss << "oppsi poosi... Zoom: " << newZoom << "illegal, (Zoom > 0)" << endl;
        throw ViewException(ss.str());
    }
    zoom = newZoom;
}

void View::adjustPan(float newX, float newY) {
    x = newX;
    y = newY;
}

int getLen(int row, int col, int x, int y) {
    int len = 3;
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

void View::show() {
    cout << setprecision(2) << std::fixed << "Display size: " << size << ", scale: "
         << zoom << ", origin: (" << x << ", " << y << ")" << endl;
    int row = (int) (y + zoom * ((float) size - 1));
    int col = (int) (x + zoom * ((float) size - 1));
    int len = getLen(row, col, x, y);
    int counter = size - 1;
    std::ios_base::fmtflags f(cout.flags());
    for (int i = row; i >= (int) y; i -= (int) zoom) {
        if (counter % 3 == 0) {
            cout << setw(len) << setfill(' ') << right << i << ' ';
            cout.flags(f);
        } else {
            cout << setw(4) << setfill(' ') << ' ';
        }
        --counter;
        for (int j = x; j <= col; j += (int) zoom) {
            string square = ".";
            for (auto &agent: Model::getModelInstance()->agents) {
                if (agent->getCurrentY() >= (float) i && agent->getCurrentY() < (float) i + zoom &&
                    agent->getCurrentX() >= (float) j && agent->getCurrentX() < (float) j + zoom) {
                    square = agent->getName().substr(0, 2);
                }
            }
            stringstream ss;
            for (auto &structure: Model::getModelInstance()->structures) {
                if (structure->getY() >= (float) i && structure->getY() < (float) i + zoom &&
                    structure->getX() >= (float) j && structure->getX() < (float) j + zoom) {
                    square = structure->getName().substr(0, 2);
                    square = structure->getName().substr(0, 2);
                    ss << '\n' << square << ",  " << i << ", " << j << ",  " << structure->getY() << ", "
                       << structure->getX() << endl;
                }
            }
            cout << setw(2) << setfill(' ') << left << square;
        }
        cout << endl;
    }
    cout.flags(f);
    counter = size - 1;
    stringstream ss;
    for (int i = x; i <= col; i += (int) zoom) {
        if (counter % 3 == 0) {
            if (i == x) {
                cout << setw(len + 2) << setfill(' ') << right << i;
            } else {
                ss << i << ' ';
                cout << setw(6) << setfill(' ') << right << i;
                ss.seekp(ios::beg);
            }
        }
        --counter;
    }
}