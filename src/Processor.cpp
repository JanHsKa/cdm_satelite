#include "Processor.h"

Processor::Processor() {
    vector<Satellite> new_vector;
    satellites = new_vector;
    generator = new GoldCodeGenerator();
}



vector<Satellite> Processor::decode() {
    vector<Satellite> result;
    createSatellites();

    return result;
}

void Processor::createSatellites() {
    for (auto i = 0; i < SATELLITE_COUNT; i++) {
        Satellite satellite;
        satellite.id = i + 1;
        satellite.chipSequence = generator->generate(REGISTER_PAIRS[i][0], REGISTER_PAIRS[i][1]);
        satellites.push_back(satellite);
    }

    cout<<"end create";
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

    char* fileBuffer = (char*)malloc(sizeof(char) * fileSize);

    size_t readSize = fread(fileBuffer, sizeof(char), (size_t)fileSize, file);

    if (readSize != fileSize) {
        printf("Failed to read file \n");
        return false;
    }

    int index = 0;
    bool nextNegative = false;
    char entry = ' ';

    for (int i = 0; i < fileSize; i++) {
        entry = (char)fileBuffer[i];

        if (entry == '-') {
            nextNegative = true;
        } else if (entry == 32) {
            nextNegative = false;
        } else {
            if (index >= SIGNALSIZE) {
                 printf("File is to large to read \n");
                return false;
            }
            signalData[index] = entry - '0';
            if (nextNegative) {
                signalData[index] *= -1;
            }

            nextNegative = false;
            index++;
        }
    }

    fclose(file);
    free(fileBuffer);

    return true;
}