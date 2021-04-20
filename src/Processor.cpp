#include "Processor.h"

Processor::Processor() {
    vector<Satellite> new_vector;
    satellites = new_vector;
}



vector<Satellite> Processor::decode() {
    cout<<"!start decode"<<endl;
    vector<Satellite> result;
    createSatellites();
    cout<<"!finish decode"<<endl;

    return result;
}

void Processor::createSatellites() {
    for (auto i = 0; i < SATELLITE_COUNT; i++) {
        cout<<"index  "<<i<<endl;
        Satellite satellite;
        satellite.id = i + 1;
        satellite.chipSequence = generator.generate(REGISTER_PAIRS[i][0], REGISTER_PAIRS[i][1]);
        cout<<"push_back"<<endl;
        satellites.push_back(satellite);
    }

    cout<<"end create";
}

bool Processor::loadFile(const char* filePath) {
    cout<<"start loading"<<endl;
    FILE* file = fopen(filePath, "r");

    if(file == NULL) {
        printf("Failed to open file \n");
        return false;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    /* if (fileSize > 1023) {
        printf("File is to large to read \n");
        printf(" %d Filesize", fileSize);
        return false;
    } */

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
                cout<<"to big   "<<i<<endl;
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