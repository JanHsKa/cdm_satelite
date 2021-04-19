#include "Controller.h"
#include <iostream>
#include "Processor.h"

using namespace std;

Controller::Controller(const char* argument) {
    processor = Processor();
    loadSuccess = processor.loadFile(argument);
}

void Controller::run() {
    if (loadSuccess) {
        vector<Satellite> results = processor.decode();

        for (auto satellite : results) {
            cout<<"Satellite  "<<satellite.id<<" has sent bit "<<satellite.sentBit<<" (delta = "<<satellite.delta<<")"<<endl;
        }
    }
}