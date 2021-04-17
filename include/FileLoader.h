#pragma once
#include <iostream>

using namespace std;

class FileLoader {
private:
    uint8_t* fileContent;
    int filesize;

    bool checkFile();

public:
    FileLoader();
    bool loadFile(const char* filePath);
    uint8_t* getFileContent();
    ~FileLoader();
};