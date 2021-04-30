#include "Processor.h"

Processor::Processor() {
    vector<Satellite*> new_vector(SATELLITE_COUNT);
    satellites = new_vector;
    generator = new GoldCodeGenerator();
    createSatellites();
    loopCount = 0;
}



void Processor::decode() {
    for (auto satellite : satellites) {
        if (checkSatelliteSignal(satellite->id)) {
           printSatellite(satellite);
        }
    }
}

void Processor::printSatellite(Satellite* satellite) {
    printf("Satellite %*d has sent bit %d (delta = %d)\n", 2, satellite->id, 
            satellite->sentBit, satellite->delta);
}


void Processor::createSatellites() {
    for (auto i = 0; i < SATELLITE_COUNT; i++) {
        Satellite* satellite = new Satellite;
        satellite->id = i + 1;
        satellite->t = DURATIONS[i];
        satellite->chipSequence = vector<uint8_t>(SIGNALSIZE);
        generator->generate(satellite->chipSequence, REGISTER_PAIRS[i][0], REGISTER_PAIRS[i][1]);
        createSatelliteSignal(satellite);
        satellites[i] = satellite;
    }
}

void Processor::createSatelliteSignal(Satellite* satellite) {
    for (auto bit : satellite->chipSequence) {
        if (bit == 1) {
            satellite->signal.push_back(1);
        } else {
            satellite->signal.push_back(-1);
        }
    }
}

bool Processor::checkSatelliteSignal(uint8_t satelliteId) {
    for (auto i = 0; i < SIGNALSIZE; i++) {
        if (checkSignal(i, satelliteId)) {
            satellites[satelliteId - 1]->delta = i;
            return true;
        }
    }

    return false;
}

bool Processor::checkSignal(uint16_t start, uint8_t satelliteId) {
    int checkSum = 0;
    int index = start;
    for (auto signalNumber : satellites[satelliteId - 1]->signal) {
        checkSum += signalData[index % SIGNALSIZE] * signalNumber;
        index++;
    } 

    checkSum /= SIGNALSIZE;

    switch (checkSum) {
        case 1:
            satellites[satelliteId - 1]->sentBit = 1;
            return true;

        case -1:
            satellites[satelliteId - 1]->sentBit = 0;
            return true;

        default:
            return false;
    }

    return false;
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