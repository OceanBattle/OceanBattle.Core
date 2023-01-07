#include <cstdio>
#include <cstdlib>
#include <read.hpp>
#include <fstream>
#include <sstream>
#include <string.h>


void FileManager::ReadFile(const char *filename) {

    std::stringstream buffer;

    std::ifstream file(filename);
    buffer << file.rdbuf();

    std::string stringTemp = buffer.str();
    const char * temp = stringTemp.c_str();
    int length = stringTemp.length();

    char * inhalt = new char[length + 1]; // without this 1 couses error

    strcpy(inhalt, temp);
    _streams.push_back(inhalt);

}

FileManager::~FileManager() {

    for (char * x : _streams) {
        delete[] x;
    }
}

const char * FileManager::GetFile(int index) {

    return _streams[index];
}