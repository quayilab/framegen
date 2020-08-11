#include <iostream>
#include "model.h"
using namespace std;

int main() {
    cout << "Library version : " << getVersion() << endl;
    stripSvg("paths.svg", "strippedSvg.svg", "0.0.1");
    return 0;
} 