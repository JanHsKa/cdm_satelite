#pragma once
#include <iostream>
#include <vector>

using namespace std;

struct Satellite {
    uint8_t sentBit;
    uint8_t id;
    uint16_t delta;
};

class Processor {
private:
    uint8_t signalData[1023];

public:
    Processor();
    vector<Satellite> decode(uint8_t* data);
};