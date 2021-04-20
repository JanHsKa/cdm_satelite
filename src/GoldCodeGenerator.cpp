#include "GoldCodeGenerator.h"

GoldCodeGenerator::GoldCodeGenerator():g1(new ShiftRegister), g2(new ShiftRegister) {
    g1->registerBits = 0b1111111111;
    g1->shiftBits = {0b0010000000, 0b0010000000};
    g1->resultBits = {0b1111111111};

    g2->registerBits = 0b1111111111;
    g2->shiftBits = {0b0100000000, 0b0010000000, 0b0000010000, 0b0000000100, 0b0000000010, 0b0000000001};
    g2->resultBits = {};
}


vector<uint8_t> GoldCodeGenerator::generate(uint16_t first, uint16_t second) {
    vector<uint8_t> code;
    cout<<"generate"<<endl;
    reset();
    cout<<"1"<<endl;
    g2->resultBits.push_back(first);
    cout<<"1,2"<<endl;

    g2->resultBits.push_back(second);
    cout<<"2"<<endl;
    uint8_t safe;

    for (auto i = 0; i <= SIGNALSIZE; i++) {
        safe = get_next_bit();
        code.push_back(safe);
    }
    return code;
}


uint8_t GoldCodeGenerator::get_next_bit() {
    uint8_t shift1 = shift(g1);
    uint8_t shift2 = shift(g2);

    return shift1 ^ shift2;
}


uint8_t GoldCodeGenerator::shift(ShiftRegister *shiftRegister) {
    uint8_t resultBit = 0;
    uint16_t helpBit = 0;
    uint16_t shiftBit = 0;


    for (auto bitmask : shiftRegister->resultBits) {
         helpBit = shiftRegister->registerBits & bitmask;
         while (helpBit > 2) {
             helpBit >>= 1;
         }
         resultBit ^= helpBit;
    }

    helpBit = 0;

    for (auto bitmask : shiftRegister->shiftBits) {
        helpBit ^= shiftRegister->registerBits & bitmask;
        while (helpBit > 2) {
             helpBit >>= 1;
         }

         shiftBit ^= helpBit;
    }

    shiftRegister->registerBits |= shiftBit << 9;

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