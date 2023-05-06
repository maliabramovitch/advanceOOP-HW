//
// Created by Mali Abramovitch on 21/04/2023.
//

#ifndef INC_001_VIRTUALDRIVE_H
#define INC_001_VIRTUALDRIVE_H

#include <sstream>
#include <utility>
#include "Directory.h"

class VirtualDrive {
    Directory *homeDir;
    Directory *pwdDir;
    std::deque<std::string> dirs; //for path split
    std::string fileToFindName; //for correct fileToFindName searching
    std::string dirToFindName; //for correct directory searching
    std::deque<MyFile> systemFiles;
    bool systemFile = false;

    void splitArgs(const std::string &arg1, bool fileCond, bool newDirCon);
    void rest(); // rest dirs,fileToFindName & dirToFindName

    MyFile &getTheFile() noexcept(false);

    Directory &getTheDirectory() noexcept(false);

public:
    class FileNotFoundException : public std::exception {
        std::string message;
    public:
        explicit FileNotFoundException(std::string mes) : message(std::move(mes)) {};

        const char *what() const noexcept override { return message.c_str(); }
    };

    class DirectoryNotFoundException : public std::exception {
        std::string message;
    public:
        explicit DirectoryNotFoundException(std::string mes) : message(std::move(mes)) {};

        const char *what() const noexcept override { return message.c_str(); }
    };

    VirtualDrive();

    VirtualDrive(const VirtualDrive &) = delete;

    VirtualDrive(VirtualDrive &&) = delete;

    ~VirtualDrive();

    VirtualDrive &operator=(const VirtualDrive &) = delete;

    VirtualDrive &operator=(VirtualDrive &&) = delete;

    void read(const std::string &fileName, int offset) noexcept(false); ///read from a char given fileToFindName.
    void write(const std::string &fileName, int offset, char c) noexcept(false); ///write to a given fileToFindName.
    void touch(const std::string &fileName) noexcept(false); ///open or create a fileToFindName.
    void copy(const std::string &source, const std::string &dest) noexcept(false); ///copy the content of source to dest.
    void remove(const std::string &fileName) noexcept(false); ///remove the fileToFindName by it's full name.
    void move(const std::string &source, const std::string &dest) noexcept(false); ///move fileToFindName from source to dest.
    void cat(const std::string &fileName) noexcept(false); ///prints the content of a given fileToFindName.
    void ln(const std::string &source, const std::string &dest) noexcept(false); ///create a hard link to given fileToFindName.
    void mkdir(const std::string &dirName) noexcept(false); ///create new directory in the given path.
    void rmdir(const std::string &dirName) noexcept(false); ///remove a directory in the given path.
    void ls(const std::string &dirName = "") noexcept(false); ///prints the content of the current location or dirName
    void lproot() const; ///prints all the content in the VirtualDrive.
    void pwd() const; ///prints the current location
    void wc(const std::string &fileName) noexcept(false); ///statistic on the requested file
    void chdir(const std::string &newDir); ///canges the current location.
};


#endif //INC_001_VIRTUALDRIVE_H
