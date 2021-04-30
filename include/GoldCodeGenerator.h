#pragma once
#include <iostream>
#include <vector>

const uint16_t SIGNALSIZE = 1023;

using namespace std;

struct ShiftRegister {
    uint16_t registerBits;
    vector<uint16_t> shiftBits;
    vector<uint16_t> resultBits;
};


class GoldCodeGenerator {
private:
    ShiftRegister *g1;
    ShiftRegister *g2;

    uint8_t get_next_bit();
    uint8_t shift(ShiftRegister *shiftRegister);
    uint16_t applyBitmasks(const vector<uint16_t> &bitmasks, uint16_t registerBits);

public:
    GoldCodeGenerator();
    void generate(vector<uint8_t> &chipsequence, uint16_t first, uint16_t second);
    void reset();
    ~GoldCodeGenerator();
};