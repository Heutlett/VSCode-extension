//
// Created by heutlett on 14/5/20.
//

#ifndef PRUEBAVS_GARBAGECOLLECTOR_H
#define PRUEBAVS_GARBAGECOLLECTOR_H

#include <vector>
#include "garbageElement.h"
#include <thread>
#include <unistd.h>

using namespace std;

class garbageCollector {

private:

    static garbageCollector* instance;
    garbageCollector();
    void memoryLeakThread();

public:

    vector<garbageElement*> * garbageList;
    vector<void*> * garbageTotalList;
    static int totalPtrCount;
    static garbageCollector* getInstance();
    void printElements();
    garbageElement* getGarbageElement(string id);
    garbageElement* getGarbageElement(string id, void** address);
    void deleteGarbageElement(string id, void** address);
    void updateReference(string id, string newId, void** address);
    void transferReferences(garbageElement * gOldElement, string newId, garbageElement * gNewElement);
    bool deletePtr(string id, void ** address);
    void checkMemoryLeaks();

    static int prueba(int a){
        return a;
    }

};


#endif //PRUEBAVS_GARBAGECOLLECTOR_H
