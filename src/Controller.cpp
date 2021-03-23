#include "Controller.h"
#include <iostream>

using namespace std;

Controller::Controller(const char* argument) {
    FileLoader loader = FileLoader();
    loadSuccess = loader.loadFile(argument);    
}

void Controller::run() {

}