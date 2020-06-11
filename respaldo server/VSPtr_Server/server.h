//
// Created by heutlett on 9/6/20.
//

#ifndef VSPTR_SERVER_SERVER_H
#define VSPTR_SERVER_SERVER_H

#include "VSPointer.h"

void initServer(){

    int a;

    VSPointer<int> ptr = VSPointer<int>::New();
    *ptr = 5;

    VSPointer<int> ptr1 = VSPointer<int>::New();
    *ptr1 = 51;

    VSPointer<int> ptr2 = VSPointer<int>::New();
    ptr2 = ptr;

    garbageCollector::getInstance()->printElements();

    cin >>  a;

}

#endif //VSPTR_SERVER_SERVER_H
