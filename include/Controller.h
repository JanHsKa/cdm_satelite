#pragma once
#include "FileLoader.h"
#include "Processor.h"

using namespace std;

class Controller {
private:
    Processor processor;
    bool loadSuccess;

public:
    Controller(const char*);
    void run();
};