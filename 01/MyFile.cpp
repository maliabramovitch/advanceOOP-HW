//
// Created by Mali Abramovitch on 20/04/2023.
//

#include "MyFile.h"

using namespace std;

MyFile::RC::RC(string &name) : count(1) {
    file.open(name);
}


void MyFile::RC::operator++() {
    ++count;
}

void MyFile::RC::operator--() {
    --count;
}

MyFile::MyFile(std::string name) : file(new RC(name)), fileSize(0) {}

MyFile::MyFile(const MyFile &other) {
    file = other.file;
    ++(*file);
    fileSize = other.fileSize;
}

MyFile::~MyFile() {
    if (file->count > 1) {
        --(*file);
    }
    else {
        delete file;
    }
}

MyFile &MyFile::operator=(const MyFile &other) {
    if (this == &other) return *this;
    if (file->count == 1) {
        delete file;
    }
    else {// if (file.count > 1)
        --(*file);
    }
    fileSize = other.fileSize;
    file = other.file;
    ++(*file);
    return *this;
}

char MyFile::operator[](int offset) const {
    file->f
    return ;
}

char &MyFile::operator[](int offset) {
    return <#initializer#>;
}

void MyFile::wc() const {

}

std::ostream &operator<<(std::ostream &os, const MyFile &mf) {
    return <#initializer#>;
}


MyFile::IndexOutOfRange::IndexOutOfRange(std::string &message) : message(message) {}

std::string &MyFile::IndexOutOfRange::what() {
    return message;
}