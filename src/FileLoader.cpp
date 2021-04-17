#include "FileLoader.h"
#include <fstream>
#include <stdio.h>


FileLoader::FileLoader() {
    filesize = 1023;
    fileContent = (uint8_t*)malloc(sizeof(uint8_t) * 1023);
}

bool FileLoader::loadFile(const char* filePath) {
    FILE* file = fopen(filePath, "r");

    if(file == NULL) {
        printf("Failed to open file \n");
        return false;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    if (fileSize > 1023) {
        printf("File is to large to read \n");
        return false;
    }

    char* fileBuffer = (char*)malloc(sizeof(char) * filesize);

    size_t readSize = fread(fileBuffer, sizeof(char), (size_t)fileSize, file);

    if (readSize != fileSize) {
        printf("Failed to read file \n");
        return false;
    }

    for (int i = 0; i < fileSize; i++) {
        fileContent[i] = (char)fileBuffer[i];
    }

    fclose(file);
    free(fileBuffer);

    return true;
}

uint8_t* FileLoader::getFileContent() {
    uint8_t* copy = (uint8_t*)malloc(sizeof(uint8_t) * 1023);

    for (int i = 0; i < 1023; i++) {
        copy[i] = fileContent[i];
    }

    return fileContent;
    //return copy;
}

FileLoader::~FileLoader(){
    free(fileContent);
}