//
// Created by heutlett on 14/5/20.
//

#ifndef VSPTR_DYNAMICLIBRARY_GARBAGECOLLECTOR_H
#define VSPTR_DYNAMICLIBRARY_GARBAGECOLLECTOR_H

#include <vector>
#include "garbageElement.h"
#include <thread>
#include <unistd.h>
#include <fstream>
#include <iomanip>
#include "json.hpp"


using json = nlohmann::json;
using namespace std;

class VSPTR_DYNAMICLIBRARY_GARBAGECOLLECTOR_H garbageCollector {

private:

    static garbageCollector* instance;
    garbageCollector();
    void memoryLeakThread();

public:
    bool remoteMemoryIsActive;
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
    void generarJSON();
    void checkRemoteMemoryConf();
    void checkRemoteThread();
    string generateStringJSON();
    json JsonGenerator();
    void sendPointersToServer();
    void clearGC();
    bool gcIsClear();

    int SERVER_vsptrConstructor(string type);
    string SERVER_vsptrGetValue(int remoteID);
    void SERVER_vsptrUpdateReference(int thisRemoteId, int otherRemoteId);
    void SERVER_vsptrOverloadAssign(string newValueType, string newValue, int thisIdRemote);

    void getPointersFromServer();
};


#endif //PRUEBAVS_GARBAGECOLLECTOR_H
