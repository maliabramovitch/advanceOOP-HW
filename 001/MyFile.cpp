//
// Created by Mali Abramovitch on 21/04/2023.
//

#include <iterator>
#include <sstream>
#include "MyFile.h"


using namespace std;

MyFile::RC::RC(string &name) : count(1), fileName(name), fileSize(0) { ; }

void MyFile::RC::operator++() {
    ++count;
}

void MyFile::RC::operator--() {
    --count;
}

void MyFile::writeToFile() {
    if (fileRC->data.size() == 0) {
        ::FILE* f = fopen(fileRC->fileName.c_str(), "w");
        ::fclose(f);
    }
    else {
        open();
        while (!fileRC->file) {
            open();
        }
        fileRC->file.seekp(0, ios::beg);
        string::iterator start(fileRC->data.begin()), end(fileRC->data.end());
        ostreambuf_iterator<char> out(fileRC->file);
        copy(start, end, out);
    }

}


MyFile::MyFile() : fileRC(nullptr){}

MyFile::MyFile(std::string name) : fileRC(new RC(name)) {
    open();
    stringstream buffer;
    buffer << fileRC->file.rdbuf();
    fileRC->data = buffer.str();
    fileRC->fileSize = fileRC->data.length();
}

MyFile::MyFile(const MyFile &other) {
    fileRC = other.fileRC;
}

MyFile::~MyFile() {
    writeToFile();
    if (fileRC->count > 1) {
        --(*fileRC);
    } else {
        delete fileRC;
    }

}

MyFile &MyFile::operator=(const MyFile &other) {
    if (this == &other) return *this;
    if (fileRC && fileRC->count == 1) {
        delete fileRC;
    } else if (fileRC && fileRC->count > 1){// if (fileRC.count > 1)
        --(*fileRC);
    }
    fileRC = other.fileRC;
    ++(*fileRC);
    return *this;
}

const char &MyFile::operator[](int offSet) const noexcept(false) {
    if (offSet > fileRC->fileSize || offSet < 0) throw IndexOutOfRange("Index Out Of Range");
    return fileRC->data[offSet];
}

char &MyFile::operator[](int offSet) {
    if (offSet > fileRC->fileSize || offSet < 0) throw IndexOutOfRange("Index Out Of Range");
    if (offSet == fileRC->fileSize) fileRC->data.insert(fileRC->data.end(), ' ');
    return fileRC->data[offSet];
}

void MyFile::wc() const { //the function is const but There may have been a call to writeToFile()
    int chars = 0;
    int words = 0;
    int lines = 0;
    bool flag = false;
    string::iterator start(fileRC->data.begin()), end(fileRC->data.end());
    while (1) {
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
        if (*start == '\n', *start == '\r') {
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

void MyFile::open() const {
    fileRC->file.open(fileRC->fileName, ios::app);
    fileRC->file.close();
    fileRC->file.open(fileRC->fileName);
    if (!fileRC->file) {
        throw OpenFileException("file was not opened\n");
    }
}

int MyFile::getRcCount() const {
    return fileRC->count;
}

size_t MyFile::getDataSize() const {
    return fileRC->fileSize;
}

void MyFile::clear() {
    fileRC->data.clear();
}

MyFile &MyFile::operator>>(MyFile &other) const {
    other.fileRC->data = fileRC->data;
    return other;
}

MyFile &MyFile::copyToMyFile(MyFile &other) const {
    return *this >> other;
}

bool MyFile::operator<(const MyFile &other) const {
    return fileRC->fileName < other.fileRC->fileName;
}

const std::string& MyFile::getFileName() const {
    return fileRC->fileName;
}





