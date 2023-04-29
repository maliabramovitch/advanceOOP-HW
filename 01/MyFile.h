//
// Created by Mali Abramovitch on 20/04/2023.
//

#ifndef INC_01_MYFILE_H
#define INC_01_MYFILE_H

#include <iostream>
#include <fstream>
#include "RC.h"

class MyFile {

    struct RC {
        std::fstream file;
        int count;

        explicit RC(std::string& name); //required copy C'tor for T.
        ~RC() = default;
        void operator++();
        void operator--();
    };

    int fileSize;
    RC* fileRC;

public:
    class IndexOutOfRange : public std::exception {
        std::string message;
    public:
        explicit IndexOutOfRange(std::string& message);
        std::string& what();
    };
    explicit MyFile(std::string name);
    MyFile(const MyFile &other);
    MyFile(MyFile&&) = delete;
    ~MyFile();
    MyFile& operator=(const MyFile& other);
    MyFile& operator=(MyFile&&)  =delete;
    char operator[](int offset) const;
    char& operator[](int offset);
    void wc() const;
    friend std::ostream& operator<<(std::ostream& os, const MyFile& mf);
};


#endif //INC_01_MYFILE_H
