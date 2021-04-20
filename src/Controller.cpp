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
        cout<<"loaded"<<endl;
        vector<Satellite> results = processor.decode();
        cout<<"decoded"<<endl;

        for (auto satellite : results) {
            cout<<"Satellite  "<<satellite.id<<" has sent bit "<<satellite.sentBit<<" (delta = "<<satellite.delta<<")"<<endl;
        }
    }
}