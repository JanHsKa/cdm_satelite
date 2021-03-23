#pragma once
#include <iostream>

using namespace std;

class FileLoader {
private:
    char* fileContent;
    int filesize;

    bool checkFile();

public:
    FileLoader();
    bool loadFile(const char* filePath);
    char* getFileContent();
};