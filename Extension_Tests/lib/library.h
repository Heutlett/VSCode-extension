//
// Created by heutlett on 31/5/20.
//
#include "person.h"

#ifndef VSPTR_DYNAMICLIBRARY_LIBRARY_H __attribute__((visibility("default")));
#define VSPTR_DYNAMICLIBRARY_LIBRARY_H


extern "C"
{
//Funciones que se llaman en JS
int CountPeople();
int recibo();
};



#endif //VSPTR_DYNAMICLIBRARY_LIBRARY_H



/*
extern "C"{

    int Subtract(int, int);
    int Add(int, int);
    int cambia(int);
    int get(int);

}
*/