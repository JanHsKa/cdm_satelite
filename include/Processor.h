#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "GoldCodeGenerator.h"

using namespace std;

struct Satellite {
    uint8_t sentBit;
    uint8_t id;
    uint16_t delta;
    uint8_t signalCode[SIGNALSIZE];
};

class Processor {
private:
    uint8_t signalData[SIGNALSIZE];
    Satellite satellites[24];

    void createSatellites();
    
public:
    Processor();
    vector<Satellite> decode();
    bool loadFile(const char* filePath);
};