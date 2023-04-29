//
// Created by Mali Abramovitch on 18/04/2023.
//

#include "Directory.h"

using namespace std;

bool Directory::operator<(Directory &other) {
    return name < other.name;
}
