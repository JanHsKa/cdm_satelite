#include "GoldCodeGenerator.h"

GoldCodeGenerator::GoldCodeGenerator():g1(new ShiftRegister), g2(new ShiftRegister) {
    g1->registerBits = 0b1111111111;
    g1->shiftBits = {0b0010000000, 0b0000000001};
    g1->resultBits = {0b00000000001};

    g2->registerBits = 0b1111111111;
    g2->shiftBits = {0b0100000000, 0b0010000000, 0b0000010000, 0b0000000100, 0b0000000010, 0b0000000001};
    g2->resultBits = {};
}

void GoldCodeGenerator::generate(vector<uint8_t> &chipsequence, uint16_t first, uint16_t second) {
    reset();
    g2->resultBits.push_back(1 << (10 - first));
    g2->resultBits.push_back(1 << (10 - second));

    for (auto i = 0; i <= SIGNALSIZE; i++) {
        chipsequence[i] = get_next_bit();
    }
}

uint8_t GoldCodeGenerator::get_next_bit() {
    uint8_t shift1 = shift(g1);
    uint8_t shift2 = shift(g2);

    return shift1 ^ shift2;
}

uint8_t GoldCodeGenerator::shift(ShiftRegister *shiftRegister) {
    uint8_t resultBit = (uint8_t)applyBitmasks(shiftRegister->resultBits, shiftRegister->registerBits);
    uint16_t shiftBit = applyBitmasks(shiftRegister->shiftBits, shiftRegister->registerBits);


    shiftRegister->registerBits >>= 1;
    shiftRegister->registerBits |= shiftBit << 9;

    return resultBit;
}

uint16_t GoldCodeGenerator::applyBitmasks(const vector<uint16_t> &bitmasks, uint16_t registerBits) {
    uint16_t resultBit = 0;
    uint16_t helpBit = 0;

    for (auto bitmask : bitmasks) {
         helpBit = registerBits & bitmask;
         while (helpBit >= 2) {
             helpBit >>= 1;
         }
         resultBit ^= helpBit;
    }

    return resultBit;
}

void GoldCodeGenerator::reset() {
    g1->registerBits = 0b1111111111;
    g2->registerBits = 0b1111111111;

    g2->resultBits = {};
}

GoldCodeGenerator::~GoldCodeGenerator() {
    delete g1;
    delete g2;
}