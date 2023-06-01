#include "Terminal.h"

using namespace std;

int main(int argc, char **argv) {
    Terminal t(argc-1, argv+1);
    return 0;
}
