#include "Processor.h"


Processor::Processor() {

}



vector<Satellite> Processor::decode() {
    vector<Satellite> result;
    return result;
}


bool Processor::loadFile(const char* filePath) {
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

    char* fileBuffer = (char*)malloc(sizeof(char) * fileSize);

    size_t readSize = fread(fileBuffer, sizeof(char), (size_t)fileSize, file);

    if (readSize != fileSize) {
        printf("Failed to read file \n");
        return false;
    }

    for (int i = 0; i < fileSize; i++) {
        signalData[i] = (char)fileBuffer[i];
    }

    fclose(file);
    free(fileBuffer);

    return true;
}