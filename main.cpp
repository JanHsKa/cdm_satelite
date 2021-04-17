#include <iostream>
#include "FileLoader.h"
#include "include/Controller.h"

using namespace std;

int main(int argc, char** argv) {
    Controller controller = Controller(argv[1]);
    controller.run();
    return 0;
}