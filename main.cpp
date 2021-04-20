#include <iostream>
#include "include/Controller.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc > 1) {
        Controller controller = Controller(argv[1]);

        controller.run();
        cout<<"running3"<<endl;

    } else {
        cout<<"No file was parsed"<<endl;
    }
    
    cout<<"test"<<endl;
    return 0;
}