//
// Created by Mali Abramovitch on 21/04/2023.
//

#include <iterator>
#include <vector>
#include "VirtualDrive.h"

using namespace std;

VirtualDrive::VirtualDrive() {
    homeDir = new Directory("V", nullptr);
    pwdDir = homeDir;
}

VirtualDrive::~VirtualDrive() {
    delete homeDir;
}

void VirtualDrive::read(const std::string &fileName, int offset) noexcept(false) {
    try {
        splitArgs(fileName, true, false);
        MyFile &mf = getTheFile();
        cout << mf[offset] << endl;
    }
    catch (FileNotFoundException &e) {
        throw;
    }
    catch (DirectoryNotFoundException &e) {
        throw;
    }
}

void VirtualDrive::write(const std::string &fileName, int offset, char c) noexcept(false) {
    try {
        splitArgs(fileName, true, false);
        MyFile &mf = getTheFile();
        mf[offset] = c;
    }
    catch (FileNotFoundException &e) {
        throw;
    }
    catch (DirectoryNotFoundException &e) {
        throw;
    }
}

void VirtualDrive::touch(const std::string &fileName) {
    try {
        splitArgs(fileName, true, false);
        MyFile &mf = getTheFile();
        mf.touch();
    }
    catch (FileNotFoundException &e) {
        splitArgs(fileName, true, false);
        Directory &dir = getTheDirectory();
        MyFile mf(fileToFindName);
        dir.getInFiles().insert(mf);
    }
    catch (DirectoryNotFoundException &e) {
        throw;
    }
}

void VirtualDrive::copy(const std::string &source, const std::string &dest) noexcept(false) {
    bool srcFound = false;
    try {
        splitArgs(source, true, false);
        MyFile &s = getTheFile();
        srcFound = true;
        splitArgs(dest, true, false);
        MyFile &d = getTheFile();
        s >> d;
    }
    catch (FileNotFoundException &e) {
        if (srcFound) {
            splitArgs(source, true, false);
            MyFile &s = getTheFile();
            splitArgs(dest, true, false);
            Directory &dir = getTheDirectory();
            MyFile d(fileToFindName);
            s >> d;
            dir.getInFiles().insert(d);
        } else {
            throw;
        }
    }
    catch (DirectoryNotFoundException &e) {
        throw;
    }
}

void VirtualDrive::remove(const std::string &fileName) noexcept(false) {
    try {
        splitArgs(fileName, true, false);
        Directory &dir = getTheDirectory();
        MyFile &mf = getTheFile();
        dir.getInFiles().erase(mf);
    }
    catch (FileNotFoundException &e) {
        throw;
    }
    catch (DirectoryNotFoundException &e) {
        throw;
    }
}

void VirtualDrive::move(const std::string &source, const std::string &dest) noexcept(false) {
    bool src = false;
    try {
        splitArgs(source, true, false);
        MyFile &deadFile = getTheFile();
        src = true;
        Directory &sourceDir = getTheDirectory();
        splitArgs(dest, true, false);
        Directory &destDir = getTheDirectory();
        MyFile &newFile = getTheFile();
        deadFile >> newFile;
        sourceDir.getInFiles().erase(deadFile);
        destDir.getInFiles().insert(newFile);
    }
    catch (FileNotFoundException &e) {
        if (src) {
            splitArgs(source, true, false);
            MyFile &deadFile = getTheFile();
            Directory &sourceDir = getTheDirectory();
            splitArgs(dest, true, false);
            Directory &destDir = getTheDirectory();
            MyFile newFile(dirs[dirs.size() - 1]);
            sourceDir.getInFiles().erase(deadFile);
            destDir.getInFiles().insert(newFile);
        } else {
            throw;
        }
    }
    catch (DirectoryNotFoundException &e) {
        throw;
    }
}

void VirtualDrive::cat(const std::string &fileName) noexcept(false) {
    try {
        splitArgs(fileName, true, false);
        MyFile &mf = getTheFile();
        mf.cat();
    }
    catch (FileNotFoundException &e) {
        throw;
    }
    catch (DirectoryNotFoundException &e) {
        throw;
    }
}

void VirtualDrive::ln(const std::string &source, const std::string &dest) noexcept(false) {
    try {
        splitArgs(source, true, false);
        MyFile &sourceFile = getTheFile();
        splitArgs(dest, true, false);
        Directory &destDir = getTheDirectory();
        MyFile mfLn = MyFile(fileToFindName);
        mfLn = sourceFile;
        destDir.getInFiles().insert(mfLn);
    }
    catch (FileNotFoundException &e) {
        throw;
    }
    catch (DirectoryNotFoundException &e) {
        throw;
    }
}

void VirtualDrive::mkdir(const std::string &dirName) noexcept(false) {
    try {
        splitArgs(dirName, false, true);
        Directory &d = getTheDirectory();
        d.mkdir(dirToFindName);
    }
    catch (Directory::DirectoryAlreadyExistException &e) {
        throw;
    }
    catch (DirectoryNotFoundException &e) {
        throw;
    }
}

void VirtualDrive::rmdir(const std::string &dirName) noexcept(false) {
    stringstream ss;
    try {
        splitArgs(dirName, false, true);
        if (dirToFindName == "V") throw (FileNotFoundException("YOU CAN'T REMOVE HOME DIRECTORY!"));
        Directory &parentDir = getTheDirectory();
        for (const Directory &d: parentDir.getInDirectories()) {
            if (d == dirToFindName) {
                if (d == *pwdDir) pwdDir = homeDir;
                parentDir.getInDirectories().erase(d);
                return;
            }
        }
        ss << "The directory *" << dirToFindName << "* do not exist in the current location: "
           << pwdDir->getFullName();
        throw (DirectoryNotFoundException(ss.str()));
    }
    catch (DirectoryNotFoundException &e) {
        throw;
    }
}

void VirtualDrive::ls(const std::string &dirName) noexcept(false) {
    Directory *dir;
    try {
        if (dirName.empty()) {
            dir = pwdDir;
        } else {
            splitArgs(dirName, false, false);
            dir = &getTheDirectory();
        }
        cout << dir->getFullName() << ":\n";
        cout << "files:" << endl;
        dir->printInFiles();
        cout << "directories:" << endl;
        pwdDir->printInDirectories();
    }
    catch (FileNotFoundException &e) {
        throw;
    }
}

void VirtualDrive::lproot() const {
    homeDir->printContent();
}

void VirtualDrive::pwd() const {
    cout << pwdDir->getFullName() << '/' << endl;
}

void VirtualDrive::wc(const string &fileName) noexcept(false) {
    try {
        splitArgs(fileName, true, false);
        MyFile &mf = getTheFile();
        mf.wc();
    }
    catch (FileNotFoundException &e) {
        throw;
    }
}

void VirtualDrive::chdir(const string &newDir) {
    try {
        pwdDir = homeDir;
        splitArgs(newDir, false, false);
        dirs.pop_front();
        pwdDir = &getTheDirectory();
    }
    catch (DirectoryNotFoundException &e) {
        throw;
    }
}

void VirtualDrive::splitArgs(const string &arg, bool fileCon, bool newDirCon) {
    if (fileCon && arg[arg.size() - 1] == '/') {
        stringstream ss;
        ss << "File's name can't end with /: ";
        ss << arg;
        throw FileNotFoundException(ss.str());
    }
    rest();
    string input;
    stringstream ss(arg);
    while ((getline(ss, input, '/'))) {
        dirs.push_back(input);
    }
    if (fileCon) {
        fileToFindName = dirs[dirs.size() - 1];
        dirs.pop_back();
        if (dirs.empty() && (dirs[0] != homeDir->getName() || dirs[0] != pwdDir->getName())) {
            systemFile = true;
        }

    } else if (newDirCon) {
        dirToFindName = dirs[dirs.size() - 1];
        dirs.pop_back();
    }
}

MyFile &VirtualDrive::getTheFile() noexcept(false) {
    if (systemFile) {
        systemFiles.emplace_front(fileToFindName);
        systemFile = false;
        return systemFiles[0];
    }
    Directory &dir = getTheDirectory();
    if (!dir.getInFiles().empty()) {
        for (const MyFile &mf: dir.getInFiles()) {
            if (mf.getMyFileName() == fileToFindName) {
                return const_cast<MyFile &>(mf);
            }
        }
    }
    stringstream ss;
    ss << "The file: *";
    ss << fileToFindName;
    ss << "* was not found in ";
    ss << dir.getFullName();
    throw FileNotFoundException(ss.str());
}


Directory &VirtualDrive::getTheDirectory() noexcept(false) {
    Directory *dir = homeDir;
    if (dirs[0] == "V") {
        dirs.pop_front();
    }
    bool foundDir;
    for (unsigned int i = 0; i < dirs.size(); ++i) {
        foundDir = false;
        if (!dir->getInDirectories().empty()) {
            for (const Directory &d: dir->getInDirectories()) {
                if (dirs[i] == d.getName()) {
                    dir = &const_cast<Directory &>(d);
                    foundDir = true;
                    break;
                }
            }
        }
        if (!foundDir) {
            stringstream ss;
            ss << "The directory: *";
            ss << dirs[i];
            ss << "* was not found in ";
            ss << dir->getFullName();
            throw DirectoryNotFoundException(ss.str());
        }
    }
    return *dir;
}

void VirtualDrive::rest() {
    dirs.clear();
    fileToFindName.clear();
    dirToFindName.clear();
}
