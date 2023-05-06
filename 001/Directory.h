//
// Created by Mali Abramovitch on 22/04/2023.
//

#ifndef INC_001_DIRECTORY_H
#define INC_001_DIRECTORY_H


#include <string>
#include <deque>
#include <set>
#include "MyFile.h"

class Directory {
    std::string fullName;
    std::string name;
    Directory* parent;
    std::set<Directory> inDirectories;
    std::set<MyFile> inFiles;


public:
    class DirectoryAlreadyExistException : public std::exception{
        std::string message;
    public:
        explicit DirectoryAlreadyExistException(std::string  message);
        const char * what() const noexcept override;
    };
    explicit Directory(const std::string& dirName, Directory* parent=nullptr);
    Directory(const Directory&);
    Directory& operator=(const Directory&) const = delete;
    Directory& operator=(Directory&&) = delete;

    void mkdir(const std::string& dirName) noexcept(false);
    std::string getName() const;
    std::string getFullName() const;
    std::set<Directory>& getInDirectories();
    std::set<MyFile>& getInFiles();
    const Directory* getPatent() const;
    void printContent() const;
    void printInDirectories() const;
    void printInFiles() const;
    bool operator<(const Directory& other) const;
    friend std::ostream& operator<<(std::ostream& os, Directory& dir);
    bool operator==(const std::string& dirName) const;
    bool operator==(const Directory& d) const;
    bool operator!=(const std::string& dirName) const;
    bool operator!=(const Directory& d) const;

};


#endif //INC_001_DIRECTORY_H
