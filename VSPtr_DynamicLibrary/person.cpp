//
// Created by heutlett on 31/5/20.
//

#include <iostream>
#include "person.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>

#define OBJECT_NAME "OBJETO1"

using namespace std;

int person::size = 5;

person::person(int id, int otherId)
{
    this->id = id;
    this->otherId = otherId;
    person::size++;
};
person::~person() {
    person::size--;
}

