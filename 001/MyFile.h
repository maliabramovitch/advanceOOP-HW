//
// Created by Mali Abramovitch on 21/04/2023.
//

#ifndef INC_001_MYFILE_H
#define INC_001_MYFILE_H


#include <iostream>
#include <fstream>

class MyFile {

    struct RC {
        //data members
        std::fstream file;
        int count;
        std::string fileName;
        std::string data;
        size_t fileSize;

        // methods
        explicit RC(std::string &name); //required copy C'tor for T.
        void operator++();

        void operator--();
    };

    RC *fileRC;

    void open() const;

    void writeToFile();

public:
    //Exception classes
    class IndexOutOfRange : public std::exception {
        std::string message;
    public:
        explicit IndexOutOfRange(const std::string &message) : message(message) {};

        const char *what() const noexcept override {
            return message.c_str();
        };
    };

    class OpenFileException : public std::exception {
        std::string message;
    public:
        explicit OpenFileException(const std::string &message) : message(message) {};

        const char *what() const noexcept override {
            return message.c_str();
        }
    };

    explicit MyFile();

    explicit MyFile(std::string name);

    MyFile(const MyFile &other);

    MyFile(MyFile &&) = delete;

    ~MyFile();

    MyFile &operator=(const MyFile &other);

    char operator=(MyFile &&) = delete;

    char &operator[](int offSet) noexcept(false);

    const char &operator[](int offSet) const noexcept(false);

    void wc() const noexcept(false); //the function is const but There may have been a call to writeToFile()

    void cat() const noexcept(false); //the function is const but There may have been a call to writeToFile()

    void operator++();

    void operator--();

    int getRcCount() const; //RC count
    size_t getDataSize() const; //text size
    void clear(); //clears the file
    MyFile &copyToMyFile(MyFile &other) const;

    MyFile &operator>>(MyFile &other) const;

    friend std::ostream &operator<<(std::ostream &os, const MyFile &mf) noexcept(false);

    bool operator<(const MyFile &other) const;

    const std::string &getFileName() const;
};

#endif //INC_001_MYFILE_H
