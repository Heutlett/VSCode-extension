//
// Created by heutlett on 28/5/20.
//

#include "garbageCollector.h"
#include "json.hpp"
#include <sstream>
#include "client.h"

using json = nlohmann::json;


void garbageCollector::SERVER_vsptrOverloadAssign(string newValueType, string newValue, int thisIdRemote){

    updateAssign(newValueType, newValue, thisIdRemote);

}

void garbageCollector::SERVER_vsptrUpdateReference(int thisRemoteId, int otherRemoteId){

    updateReferenceServer(thisRemoteId, otherRemoteId);

}

string garbageCollector::SERVER_vsptrGetValue(int remoteID){

    return getValue(remoteID);

}

int garbageCollector::SERVER_vsptrConstructor(string type){

    return createVSPTR(type);

}

void garbageCollector::clearGC(){

    garbageList->clear();
    garbageTotalList->clear();
    totalPtrCount = 0;
    garbageElement::countRemoteId = 0;

}

bool garbageCollector::gcIsClear(){

    if(garbageList->empty() && garbageTotalList->empty()){
        return true;
    }
    return false;
}

void garbageCollector::sendPointersToServer(){

    sendPointers(generateStringJSON());
    clearGC();

}

void garbageCollector::checkRemoteMemoryConf(){

    char cadena[128];{}

    ifstream fe("remote_memory_conf.txt");
    fe >> cadena;
    if(cadena[0]=='1'){
        //cout << "cadena es 1" << endl;
        this->remoteMemoryIsActive = true;
        if(!gcIsClear()){
            this->sendPointersToServer();
        }

    }else{
        this->remoteMemoryIsActive = false;
        if(gcIsClear()){
            this->getPointersFromServer();
        }
    }
    cout << "la memoria remota es: " << cadena << endl;
    fe.close();

}

json garbageCollector::JsonGenerator(){

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
        j2["idRemote"] = garbageList->at(i)->remoteId;

        j2["listOfReferences"] = {};

        for(int e = 0; e < garbageList->at(i)->listOfReferences->size(); e++){

            json j3;

            ostringstream get_the_address3;
            string address3;
            get_the_address3 << garbageList->at(i)->listOfReferences->at(e)->vsptrAdress;
            address3 = get_the_address3.str();

            j3["address"] = address3;
            j3["idRemote"] = garbageList->at(i)->listOfReferences->at(e)->remoteId;

            j2["listOfReferences"][e] = j3;

        }

        j["listaPunteros"][i] = j2;

    }
    return j;
}

string garbageCollector::generateStringJSON(){

    ifstream file("pretty.json");
    ostringstream tmp;
    tmp<<file.rdbuf();
    string s = tmp.str();

    return s;

}

void garbageCollector::generarJSON(){

    json j = JsonGenerator();

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
        sleep(3);
        generarJSON();
        checkRemoteMemoryConf();
    }

}

void garbageCollector::memoryLeakThread(){
    while(1) {
        sleep(5);

        if(!gcIsClear()){
            checkMemoryLeaks();
        }
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

    if(!gcIsClear()){
        cout << "LIST OF VSPOINTERS" << endl;

        for(int i = 0; i < garbageList->size(); i++){
            garbageList->at(i)->toString();
        }

        cout << endl;
    }
}

garbageElement* garbageCollector::getGarbageElement(string id){
    for(int i = 0; i < garbageList->size(); i++){

        if(garbageList->at(i)->id.compare(id) == 0){
            return garbageList->at(i);
        }
    }
    return nullptr;
}

garbageElement* garbageCollector::getGarbageElement(string id, string address){
    for(int i = 0; i < garbageList->size(); i++){

        if(garbageList->at(i)->id.compare(id) == 0 && garbageList->at(i)->vsptrAdress.compare(address) == 0){
            return garbageList->at(i);
        }
    }
    return nullptr;
}

void garbageCollector::deleteGarbageElement(string id, string address){
    for(int i = 0; i < garbageList->size(); i++){

        if(garbageList->at(i)->id.compare(id) == 0 && garbageList->at(i)->vsptrAdress.compare(address) == 0){

            garbageList->erase(garbageList->begin() + i);
            totalPtrCount--;

        }
    }
}

void garbageCollector::updateReference(string id, string newId, string address){
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

bool garbageCollector::deletePtr(string id, string address){
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

void garbageCollector::getPointersFromServer() {

    getPointers();

}

