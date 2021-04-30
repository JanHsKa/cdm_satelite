#include <iostream>
#include "Processor.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc > 1) {
        Processor processor = Processor();

        if (processor.loadFile(argv[1])) {
            processor.decode();
        }
    } else {
        cout<<"No file was parsed"<<endl;
    }
    
    return 0;
}