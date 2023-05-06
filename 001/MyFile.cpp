//
// Created by Mali Abramovitch on 21/04/2023.
//

#include <iterator>
#include <sstream>
#include "MyFile.h"


using namespace std;

MyFile::RC::RC(const string &name) : count(1), fileName(name), fileSize(0) {
    file.open(fileName, ios_base::app);
    file.close();
    file.open(fileName);
    if (!file) {
        throw (OpenFileException("File was not opened"));
    }
    file.seekg(0, ios::beg);
    stringstream buffer;
    buffer << file.rdbuf();
    data = buffer.str();
    fileSize = data.length();
    file.close();
}


void MyFile::RC::operator++() {
    ++count;
}

void MyFile::RC::operator--() {
    --count;
}

void MyFile::writeToFile() {
    fileRC->file.open(fileRC->fileName);
    if (!fileRC->file) {
        throw (OpenFileException("File was not opened"));
    }
    fileRC->file.seekp(0, ios::beg);
    string::iterator start(fileRC->data.begin()), end(fileRC->data.end());
    ostreambuf_iterator<char> out(fileRC->file);
    copy(start, end, out);
    fileRC->file.close();
}


MyFile::MyFile() : fileRC(nullptr) {}

MyFile::MyFile(const std::string &name) : name(name), fileRC(new RC(name)) {}

MyFile::MyFile(const MyFile &other) {
    fileRC = other.fileRC;
    name = other.name;
    ++(*fileRC);
}

MyFile::~MyFile() {
    if (fileRC->count > 1) {
        --(*fileRC);
    } else {
        writeToFile();
        delete fileRC;
    }

}


MyFile::MyFile(MyFile &&other) noexcept {
    fileRC = other.fileRC;
    other.fileRC = nullptr;
    name = std::move(other.name);
    other.fileRC = nullptr;
    other.name = "";
}

MyFile &MyFile::operator=(const MyFile &other) {
    if (this == &other) return *this;
    if (fileRC && fileRC->count == 1) {
        delete fileRC;
    } else if (fileRC && fileRC->count > 1) {// if (fileRC.count > 1)
        --(*fileRC);
    }
    fileRC = other.fileRC;
    ++(*fileRC);
    return *this;
}


MyFile &MyFile::operator=(MyFile &&other) noexcept(false) {
    if (this != &other) {
        fileRC = other.fileRC;
        other.fileRC = nullptr;
        name = other.name;
        other.fileRC = nullptr;
        other.name = "";
    }
    return *this;
}

const char &MyFile::operator[](int offSet) const noexcept(false) {
    fileRC->fileSize = fileRC->data.size();
    if (offSet > fileRC->fileSize || offSet < 0) {
        stringstream ss;
        ss << "Index " << offSet << " is out of range!";
        throw IndexOutOfRange(ss.str());
    }
    return fileRC->data[offSet];
}

char &MyFile::operator[](int offSet) {
    fileRC->fileSize = fileRC->data.size();
    if (offSet > fileRC->fileSize || offSet < 0) {
        stringstream ss;
        ss << "Index " << offSet << " is out of range!";
        throw IndexOutOfRange(ss.str());
    }
    if (offSet == fileRC->fileSize) fileRC->data.insert(fileRC->data.end(), ' ');
    return fileRC->data[offSet];
}

void MyFile::wc() const { //the function is const but There may have been a call to writeToFile()
    int chars = 0;
    int words = 0;
    int lines = 0;
    bool flag = false;
    string::iterator start(fileRC->data.begin()), end(fileRC->data.end());
    while (true) {
        if ((::isalnum(*start) || ispunct(*start)) && (start != end)) {
            flag = true;
            ++chars;
        }
        if (start == end) {
            if (flag) {
                ++words;
                ++lines;
            }
            break;
        }

        if (*start == ' ') {
            ++words;
            flag = true;
        }
        if (*start == '\n' || *start == '\r') {
            if (flag) {
                ++lines;
                ++words;
            }
            flag = false;
        }
        ++start;
    }
    cout << "\nCharacters: " << chars << "\t||\t" << "Words: " << words << "\t||\t" << "Lines: " << lines << endl;
}


void MyFile::cat() const {
    cout << *this;
}

void MyFile::operator++() {
    ++fileRC->fileSize;
}

void MyFile::operator--() {
    --fileRC->fileSize;
}

std::ostream &operator<<(std::ostream &os, const MyFile &mf) {
    for (char c: mf.fileRC->data) {
        os << c;
    }
    os << endl;
    return os;
}

int MyFile::getRcCount() const {
    return fileRC->count;
}

MyFile &MyFile::operator>>(MyFile &other) const {
    other.fileRC->data = fileRC->data;
    return other;
}

bool MyFile::operator<(const MyFile &other) const {
    return name < other.name;
}

const std::string &MyFile::getRCFileName() const {
    return fileRC->fileName;
}

const std::string &MyFile::getMyFileName() const {
    return name;
}


void MyFile::touch() {
    fileRC->file.open(fileRC->fileName);
    if (!fileRC->file) {
        throw (OpenFileException("File was not opened"));
    }
    fileRC->file.flush();
    fileRC->file.close();
}

bool MyFile::operator==(const MyFile &other) const {
    return name == other.name;
}

bool MyFile::operator==(const string &fileName) const {
    return name == fileName;
}






