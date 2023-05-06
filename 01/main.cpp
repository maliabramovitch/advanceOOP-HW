#include <iostream>
#include "Terminal.h"

using namespace std;

int main() {
    try {
      Terminal t;
      t.run();
    }
    catch (std::exception& e) {
        std::cerr << e.what();
    }
    return 0;
}
