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
    uint16_t t;
    uint16_t delta;
    vector<uint8_t> chipSequence;
    vector<int8_t> signal;
};

class Processor {
private:
    int8_t signalData[SIGNALSIZE];
    vector<Satellite*> satellites;
    GoldCodeGenerator* generator;

    void createSatellites();
    void createSatelliteSignal(Satellite* satellite);
    bool checkSatelliteSignal(uint8_t satelliteId);
    bool checkSignal(uint8_t start, uint8_t satelliteId);

    void printSatelliteSignal(uint8_t satelliteId);
    void printSatellite(Satellite* satellite);
    
public:
    Processor();
    void decode();
    bool loadFile(const char* filePath);
};