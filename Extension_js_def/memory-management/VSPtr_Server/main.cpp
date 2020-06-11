#include <iostream>
#include "VSPointer.h"
#include "server.h"

using namespace std;

int main() {

    VSPointer<int> ptr = VSPointer<int>::New();
    *ptr = 5;

    garbageCollector::getInstance()->printElements();

    return 0;
}
