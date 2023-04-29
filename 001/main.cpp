#include <iostream>
#include "MyFile.h"
#include "Directory.h"

using namespace std;

int main() {
    try {
        Directory* home = new Directory("home", 0);
        Directory* mali = new Directory("mali", home);
        MyFile* mf = new MyFile("txt.txt");
        home->getInFiles().insert(*mf);
        MyFile* mf2 = new MyFile();
        *mf2 = *mf;
        mali->getInFiles().insert(*mf2);
        home->mkdir(*mali);
        home->printContent();
        delete home, mali, mf, mf2;
    }
    catch (std::exception e) {
        std::cerr << e.what();
    }
    return 0;
}
