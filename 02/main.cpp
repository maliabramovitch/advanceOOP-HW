#include "Terminal.h"

using namespace std;

int main(int argc, char **argv) {
    try {
        Terminal t(argc-1, argv+1);
    }
    catch (exception& e) {
        cerr << e.what();
    }
    return 0;
}
