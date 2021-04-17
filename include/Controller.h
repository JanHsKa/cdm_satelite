#pragma once
#include "FileLoader.h"
#include "Processor.h"

using namespace std;

class Controller {
private:
    FileLoader fileLoader;
    Processor processor;
    bool loadSuccess;

public:
    Controller(const char*);
    void run();

};