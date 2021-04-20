#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "GoldCodeGenerator.h"
#include "SatelliteConfig.h"

using namespace std;

struct Satellite {
    uint8_t sentBit;
    int id;
    uint16_t delta;
    vector<uint8_t> chipSequence;
};

class Processor {
private:
    int8_t signalData[SIGNALSIZE];
    vector<Satellite> satellites;
    GoldCodeGenerator generator;

    void createSatellites();
    
public:
    Processor();
    vector<Satellite> decode();
    bool loadFile(const char* filePath);
};