//
// Created by heutlett on 14/5/20.
//

#ifndef VSPTR_SERVER_GARBAGECOLLECTOR_H
#define VSPTR_SERVER_GARBAGECOLLECTOR_H

#include <vector>
#include "garbageElement.h"
#include <thread>
#include <unistd.h>
#include <fstream>
#include <iomanip>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

class  garbageCollector {

private:

    static garbageCollector* instance;
    garbageCollector();
    void memoryLeakThread();
    bool remoteMemoryIsActive;

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
    void generarJSON();
    void checkRemoteMemoryConf();
    void checkRemoteThread();

    static int prueba(int a){
        return a;
    }

};


void garbageCollector::checkRemoteMemoryConf(){

    char cadena[128];{}

    ifstream fe("remote_memory_conf.txt");
    fe >> cadena;
    fe.close();

}

void garbageCollector::generarJSON(){

    json j;

    j["listaPunteros"] = {};

    for(int i = 0; i < garbageList->size(); i++){

        json j2;

        string a;

        j2["id"] = garbageList->at(i)->id;

        ostringstream get_the_address;
        get_the_address << garbageList->at(i)->getAddress();
        string address = get_the_address.str();
        j2["refAddress"] = address;

        ostringstream get_the_address2;
        get_the_address2 << garbageList->at(i)->vsptrAdress;
        address = get_the_address2.str();
        j2["vsptrAdress"] = address;


        j2["type"] = garbageList->at(i)->type;
        j2["value"] = garbageList->at(i)->getValue();
        j2["refQuantity"] = garbageList->at(i)->listOfReferences->size()+1;

        j2["listOfReferences"] = {};

        for(int e = 0; e < garbageList->at(i)->listOfReferences->size(); e++){

            ostringstream get_the_address3;
            string address3;
            get_the_address3 << garbageList->at(i)->listOfReferences->at(e)->vsptrAdress;
            address3 = get_the_address3.str();

            j2["listOfReferences"][e] = address3;

        }



        j["listaPunteros"][i] = j2;

    }

    std::ofstream o("pretty.json");
    o << std::setw(4) << j << std::endl;

}

garbageCollector::garbageCollector() {
    garbageList = new vector<garbageElement*>();
    garbageTotalList = new vector<void*>() ;
    thread(&garbageCollector::memoryLeakThread, this).detach();
    thread(&garbageCollector::checkRemoteThread, this).detach();
}


void garbageCollector::checkRemoteThread(){

    while(1) {
        sleep(1);
        generarJSON();
        checkRemoteMemoryConf();
    }

}

void garbageCollector::memoryLeakThread(){
    while(1) {
        sleep(5);
        checkMemoryLeaks();
    }
}


int garbageCollector::totalPtrCount = 0;
garbageCollector* garbageCollector::instance = 0;

garbageCollector* garbageCollector::getInstance(){
    if (instance == 0)
    {
        instance = new garbageCollector();
    }

    return instance;
}
void garbageCollector::printElements(){

    cout << "LIST OF VSPOINTERS" << endl;

    for(int i = 0; i < garbageList->size(); i++){
        garbageList->at(i)->toString();
    }

    cout << endl;
}

garbageElement* garbageCollector::getGarbageElement(string id){
    for(int i = 0; i < garbageList->size(); i++){

        if(garbageList->at(i)->id.compare(id) == 0){
            return garbageList->at(i);
        }
    }
    return nullptr;
}

garbageElement* garbageCollector::getGarbageElement(string id, void** address){
    for(int i = 0; i < garbageList->size(); i++){

        if(garbageList->at(i)->id.compare(id) == 0 && garbageList->at(i)->vsptrAdress == address){
            return garbageList->at(i);
        }
    }
    return nullptr;
}

void garbageCollector::deleteGarbageElement(string id, void** address){
    for(int i = 0; i < garbageList->size(); i++){

        if(garbageList->at(i)->id.compare(id) == 0 && garbageList->at(i)->vsptrAdress == address){

            garbageList->erase(garbageList->begin() + i);
            totalPtrCount--;

        }
    }
}

void garbageCollector::updateReference(string id, string newId, void** address){
    garbageElement * gNewReference = getGarbageElement(id, address);

    if(gNewReference == nullptr){

        garbageElement * gOriginal = getGarbageElement(id);
        garbageElement * gReference = gOriginal->getGarbageReference(address);
        garbageElement * gNewOriginal = getGarbageElement(newId);
        gOriginal->deleteReference(address);
        gReference->id = newId;
        gNewOriginal->listOfReferences->push_back(gReference);

    }else{

        deleteGarbageElement(id, address);
        garbageElement * gOriginalReference = getGarbageElement(newId);
        gNewReference->id = newId;
        gOriginalReference->listOfReferences->push_back(gNewReference);
        transferReferences(gNewReference, newId, gOriginalReference);

    }
    generarJSON();
}

void garbageCollector::transferReferences(garbageElement * gOldElement, string newId, garbageElement * gNewElement){

    while(gOldElement->listOfReferences->size() != 0){

        garbageElement * gTemp = gOldElement->listOfReferences->at(0);
        gTemp->id = newId;
        gTemp->ptrData = gNewElement->ptrData;
        gOldElement->listOfReferences->erase(gOldElement->listOfReferences->begin() + 0);
        gNewElement->listOfReferences->push_back(gTemp);

    }

}

//Si es el ptr original devuelve true, sino false
bool garbageCollector::deletePtr(string id, void ** address){
    garbageElement * original = getGarbageElement(id, address);
    if(original != nullptr){
        deleteGarbageElement(id, address);
        generarJSON();
        return true;

    }else{
        garbageElement * reference = getGarbageElement(id);
        if(reference != nullptr){
            reference->deleteReference(address);
        }
        generarJSON();
        return false;
    }

}

/**
 * Busca los memory leaks y los libera
 */
void garbageCollector::checkMemoryLeaks(){

    bool isMemoryLeaked = true;
    int count = 0;

    cout << "Thread: the memory leaks search started" << endl;

    for(int i = 0; i < garbageTotalList->size(); i++){

        for(int e = 0; e < garbageList->size(); e++){

            if(garbageTotalList->at(i) == garbageList->at(e)->ptrData){
                isMemoryLeaked = false;
            }
        }

        if(isMemoryLeaked) {
            void * deletePtr = garbageTotalList->at(i);
            cout << "The pointer: " << deletePtr << " was successfully free" << endl;
            garbageTotalList->erase(garbageTotalList->begin() + i);
            free(deletePtr);
            count++;
        }
        isMemoryLeaked = true;

    }
    cout << "Thread: the memory leaks has finished with " << count << " pointers free" << endl << endl;
}


#endif //PRUEBAVS_GARBAGECOLLECTOR_H