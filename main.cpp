#include <iostream>
#include "FileLoader.h"
#include "include/Controller.h"

using namespace std;

int main(int argc, char** argv) {
    FileLoader* file = new FileLoader();
    Controller* controller = new Controller(argv[1]);
    return 0;
}