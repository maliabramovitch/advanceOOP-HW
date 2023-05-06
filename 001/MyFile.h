//
// Created by Mali Abramovitch on 21/04/2023.
//

#ifndef INC_001_MYFILE_H
#define INC_001_MYFILE_H


#include <iostream>
#include <fstream>
#include <utility>
#include <string>

class MyFile {

    struct RC {
        //data members
        std::fstream file;
        int count;
        std::string fileName;
        std::string data;
        int fileSize;

        // methods
        explicit RC(const std::string &name); //required copy C'tor for T.
        void operator++();
        void operator--();
    };
    std::string name;
    RC *fileRC;
    void writeToFile();

public:
    class IndexOutOfRange : public std::exception{
        std::string message;
    public:
        explicit IndexOutOfRange(std::string message) : message(std::move(message)) {};

        const char *what() const noexcept override {
            return message.c_str();
        };
    };

    class OpenFileException : public std::exception{
        std::string message;
    public:
        explicit OpenFileException(std::string message) : message(std::move(message)) {};
        const char * what() const noexcept override {
            return message.c_str();
        }
    };

    explicit MyFile();

    explicit MyFile(const std::string& name);

    MyFile(const MyFile &other);

    MyFile(MyFile &&) noexcept ;

    ~MyFile();

    MyFile &operator=(const MyFile &other);

    MyFile& operator=(MyFile &&other) noexcept(false) ;

    char &operator[](int offSet) noexcept(false);

    const char &operator[](int offSet) const noexcept(false);

    void wc() const noexcept(false);

    void cat() const noexcept(false);

    void operator++();

    void operator--();

    int getRcCount() const;

    MyFile &operator>>(MyFile &other) const;

    friend std::ostream &operator<<(std::ostream &os, const MyFile &mf) noexcept(false);

    bool operator<(const MyFile &other) const;

    const std::string &getRCFileName() const;

    const std::string &getMyFileName() const;

    void touch();
    bool operator ==(const MyFile& other) const;
    bool operator ==(const std::string &fileName) const;
};

#endif //INC_001_MYFILE_H
