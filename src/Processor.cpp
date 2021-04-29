#include "Processor.h"

Processor::Processor() {
    vector<Satellite*> new_vector;
    satellites = new_vector;
    generator = new GoldCodeGenerator();
}



vector<Satellite> Processor::decode() {
    vector<Satellite> result;
    createSatellites();
    /* for (auto i = 0; i < SIGNALSIZE; i++) {
        printf("%d, ", signalData[i]);
    } */

    /* for (auto i = 0; i < SATELLITE_COUNT; i++) {
        printSatelliteSignal(i+1);
    } */

    for (auto satellite : satellites) {
        if (checkSatelliteSignal(satellite->id)) {
            result.push_back(*satellite);
        }
    }

    return result;
}

void Processor::createSatellites() {
    for (auto i = 0; i < SATELLITE_COUNT; i++) {
        Satellite* satellite = new Satellite;
        satellite->id = i + 1;
        satellite->t = DURATIONS[i];
        satellite->chipSequence = generator->generate(REGISTER_PAIRS[i][0], REGISTER_PAIRS[i][1]);
        createSatelliteSignal(satellite);
        satellites.push_back(satellite);
    }

    cout<<"end create\n";
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
    cout<<"Checking Satellite: "<<(int)satelliteId<<endl;

    for (auto i = 0; i < SIGNALSIZE; i++) {
        if (checkSignal(i, satelliteId)) {
            satellites[satelliteId - 1]->delta = i;
            return true;
        }
    }

    return false;
}

void Processor::printSatelliteSignal(uint8_t satelliteId) {
    printf("Stalleite: %d\n", satelliteId);
    printf("[");
    for (auto i = 0; i < SIGNALSIZE; i++) {
        printf("%d, ", satellites[satelliteId-1]->signal[i]);
    }
    printf("]\n");
}

bool Processor::checkSignal(uint8_t start, uint8_t satelliteId) {
    int checkSum = 0;
    int index = start;

    for (auto signalNumber : satellites[satelliteId - 1]->signal) {
        /* printf("checkSum: %d\n", checkSum);
        printf("signaldata[%d] : %d\n", index % SIGNALSIZE, signalData[index % SIGNALSIZE]);
        printf("signalNumber: %d\n\n", signalNumber); */

        checkSum += signalData[index % SIGNALSIZE] * signalNumber;
        index++;
    } 

    if (checkSum > 200 || checkSum < -200) {
        printf("Check Sum : %d \n", checkSum);

    }

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