#include <iostream>
#include "garbageCollector.h"
#include "VSPointer.h"

using namespace std;


int main() {

    VSPointer<int> ptr = VSPointer<int>::New();
    *ptr = 5;

    VSPointer<int> ptr1 = VSPointer<int>::New();
    *ptr1 = 51;

    VSPointer<int> ptr2 = VSPointer<int>::New();
    ptr2 = ptr;

    garbageCollector::getInstance()->printElements();


    return 0;
}
