//
// Created by Mali Abramovitch on 22/04/2023.
//

#include "Directory.h"

using namespace std;

Directory::DirectoryAlreadyExistException::DirectoryAlreadyExistException(const std::string& message) : message(message){}

const char *Directory::DirectoryAlreadyExistException::what() const noexcept {
    return message.c_str();
}

Directory::Directory(const std::string& dirName, Directory *parent) : parent(parent), name(dirName){
    if (parent) {
        fullName = parent->name + "/" + dirName;
    } else {
        fullName = dirName;
    }
}


Directory::Directory(const Directory &other){
    fullName = other.fullName;
    name = other.name;
    parent = other.parent;
    inDirectories = other.inDirectories;
    inFiles = other.inFiles;
}

void Directory::mkdir(const std::string& dirName) throw(DirectoryAlreadyExistException) {
    for (const Directory& dir : inDirectories) {
        if (dir.name == dirName) throw DirectoryAlreadyExistException((string &) "Directory already exist");
    }
    inDirectories.insert(Directory(dirName, this));
}


void Directory::mkdir(Directory &newDir) throw(DirectoryAlreadyExistException) {
    if (&newDir == this) throw DirectoryAlreadyExistException("Illegal mkdir operation");
    for (const Directory& dir : inDirectories) {
        if (dir.name == newDir.name) throw DirectoryAlreadyExistException((string &) "Directory already exist");
    }
    inDirectories.insert(newDir);
}


void Directory::clearDirectory() {
    inDirectories.clear();
    inFiles.clear();
}

std::string Directory::getName() const {
    return name;
}

std::string Directory::getFullName() const {
    return fullName;
}

std::set<Directory> &Directory::getInDirectories() {
    return inDirectories;
}

std::set<MyFile> &Directory::getInFiles() {
    return inFiles;
}

const Directory *Directory::getPatent() const {
    return parent;
}

void Directory::printContent() const {
    cout << name << ":" << endl;
    for (const MyFile& mf : inFiles) {
        cout << '\t' << mf.getFileName() << '\t' << mf.getRcCount() << endl;
    }
    for (const Directory& dir : inDirectories) {
        cout << '\t' << dir.name << endl;
    }
    if (inDirectories.empty()) return;
    for (const Directory& dir : inDirectories) {
        dir.printContent();
    }

}


void Directory::printInDirectories() const {
    for (const Directory& dir : inDirectories) {
        dir.printContent();
    }
}



void Directory::printInFiles() const {
    for (const MyFile& mf: inFiles) {
        cout << mf.getFileName() << '\t' << mf.getRcCount() << endl;
    }
}


bool Directory::operator<(const Directory &other) const{
    return fullName < other.fullName;
}

std::ostream &operator<<(ostream &os, Directory &dir) {
    return os << dir.fullName << endl;
}
