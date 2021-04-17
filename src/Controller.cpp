#include "Controller.h"
#include <iostream>
#include "Processor.h"

using namespace std;

Controller::Controller(const char* argument) {
    fileLoader = FileLoader();
    loadSuccess = fileLoader.loadFile(argument);    
    processor = Processor();

}

void Controller::run() {
    if (loadSuccess) {
        vector<Satellite> results = processor.decode(fileLoader.getFileContent());

        for (auto satellite : results) {
            cout<<"Satellite  "<<satellite.id<<" has sent bit "<<satellite.sentBit<<" (delta = "<<satellite.delta<<")"<<endl;
        }
    }
}