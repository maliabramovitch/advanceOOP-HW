//
// Created by Mali Abramovitch on 18/04/2023.
//

#ifndef INC_01_DIRECTORY_H
#define INC_01_DIRECTORY_H


#include <string>
#include <set>
#include <iostream>
#include <vector>
#include "RCfstream.h"

class Directory {
    std::string name;
    std::vector<std::string> path;
    std::set<Directory> inDirectories;
    std::set<RCfstream> files;

    bool operator<(Directory &other);


public:
    class IllegalDirectoryNameException : public std::exception {
        std::string message;
    public:
        IllegalDirectoryNameException(std::string mes) : message(mes) {};

        void printMessage() const {
            std::cout << message << std::endl;
        }

        friend std::ostream &operator<<(std::ostream &os, IllegalDirectoryNameException &e) {
            std::cout << e.message << std::endl;
            return os;
        }
    };

    // big 5
    Directory(std::string name);

    Directory(std::string name, std::vector<std::string> path);


    Directory(const Directory &other);

    Directory(Directory &&other);

    ~Directory();

    Directory &operator=(const Directory &other);

    Directory &operator=(Directory &&other);

    /**
     * creates new sub Directory
     */
    void mkdir(std::string name) throw(IllegalDirectoryNameException);

    /**
     * changes the current working Directory.
     */
    void chdir(std::string name) throw(IllegalDirectoryNameException);

    /**
     * Deletes all the contents of the folder, its sub folders, and the folder itself.
     */
    void rmdir();

    /**Prints the contents of the folder*/
    void ls();

    /**This function will print all the names of the files and folders in the virtual drive,
     * in a hierarchy. the correct one, when the value of the counter (reference counter)
     * of each file must appear next to the name of the file (printing format as you wish).
     */

    /**
     * void pwd(); //Function to print current working location on the virtual drive.
     */
    void lproot();


};


#endif //INC_01_DIRECTORY_H
