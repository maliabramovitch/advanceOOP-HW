//
// Created by Mali Abramovitch on 22/04/2023.
//

#include "Directory.h"

#include <utility>

using namespace std;

Directory::DirectoryAlreadyExistException::DirectoryAlreadyExistException(std::string  message) : message(std::move(message)){}

const char *Directory::DirectoryAlreadyExistException::what() const noexcept {
    return message.c_str();
}

Directory::Directory(const std::string& dirName, Directory *parent) :name(dirName),  parent(parent){
    if (parent) {
        fullName = parent->fullName + "/" + dirName;
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

void Directory::mkdir(const std::string& dirName) noexcept(false) {
    for (const Directory& dir : inDirectories) {
        if (dir.name == dirName) throw DirectoryAlreadyExistException("Directory already exist");
    }
    inDirectories.insert(Directory(dirName, this));
}

std::string Directory::getName() const {
    return name;
}

std::string Directory::getFullName() const {
    return fullName;
}

std::set<Directory> &Directory::getInDirectories(){
    return inDirectories;
}

std::set<MyFile> &Directory::getInFiles(){
    return inFiles;
}

const Directory *Directory::getPatent() const {
    return parent;
}

void Directory::printContent() const {
    cout << fullName << "/:" << endl;
    for (const MyFile& mf : inFiles) {
        cout << '\t' << mf.getMyFileName() << '\t' << mf.getRcCount() << endl;
    }
    if (inDirectories.empty()) return;
    for (const Directory& dir : inDirectories) {
        dir.printContent();
    }

}


void Directory::printInDirectories() const {
    for (const Directory& dir : inDirectories) {
        cout << '\t' << dir.getName() << endl;
    }
}



void Directory::printInFiles() const {
    for (const MyFile& mf: inFiles) {
        cout << '\t' << mf.getMyFileName() << '\t' << mf.getRcCount() << endl;
    }
}


bool Directory::operator<(const Directory &other) const{
    return fullName < other.fullName;
}

std::ostream &operator<<(ostream &os, Directory &dir) {
    return os << dir.fullName << endl;
}

bool Directory::operator==(const std::string& dirName) const {
    return dirName == name;
}

bool Directory::operator==(const Directory &d) const {
    return d.name == name;
}

bool Directory::operator!=(const string &dirName) const {
    return dirName != name;
}

bool Directory::operator!=(const Directory &d) const {
    return d.name != name;
}
