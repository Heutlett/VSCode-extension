//
// Created by heutlett on 11/6/20.
//

#ifndef VSPTR_SERVER_POINTERPARSER_H
#define VSPTR_SERVER_POINTERPARSER_H

#include "VSPointer.h"


void createVSPTR(string pId, string type, string pValue){


    if(type.compare("i")==0){

        VSPointer<int> * ptr = new VSPointer<int>(pId);
        *ptr = stoi(pValue);

    }
    if(type.compare("b")==0){
        VSPointer<bool> * ptr = new VSPointer<bool>(pId);

        if(pValue.compare("1")){
            *ptr = true;
        }else{
            *ptr = false;
        }
    }
    if(type.compare("c")==0){
        VSPointer<char> * ptr = new VSPointer<char>(pId);
        char a = pValue.at(0);
        *ptr = a;
    }
    if(type.compare("s")==0){
        VSPointer<short> * ptr = new VSPointer<short>(pId);
        short a = stoi(pValue);
        *ptr = a;
    }
    if(type.compare("l")==0){
        VSPointer<long> * ptr = new VSPointer<long>(pId);
        long a = stoi(pValue);
        *ptr = a;
    }
    if(type.compare("x")==0){
        VSPointer<long long> * ptr = new VSPointer<long long>(pId);
        long long a = stoi(pValue);
        *ptr = a;
    }
    if(type.compare("f")==0){
        VSPointer<float> * ptr = new VSPointer<float>(pId);
        *ptr =stof(pValue);
    }
    if(type.compare("d")==0){
        VSPointer<double> * ptr = new VSPointer<double>(pId);
        *ptr =stod(pValue);
    }
    if(type.compare("e")==0){
        VSPointer<long double> * ptr = new VSPointer<long double>(pId);
        *ptr =stod(pValue);
    }




}

void importPointerFromString(string pointers){

    garbageCollector *g = garbageCollector::getInstance();

    g->clearGC();

    json jsonObj;
    stringstream(pointers) >> jsonObj;

    //cout << jsonObj["listaPunteros"].at(0) << endl;

    for(int i = 0; i < jsonObj["listaPunteros"].size(); i++){
        /*
        ptr = (typeof(*ptr)*)malloc(sizeof(*ptr));
        getGC()->garbageTotalList->push_back(ptr);
        string type = typeid(*ptr).name();
        id = "id" + to_string(getGC()->totalPtrCount);
        getGC()->garbageList->push_back(new garbageElement(ptr, type, id, (void**)this));
        getGC()->totalPtrCount++;
        */
        cout << "parseando: " << jsonObj["listaPunteros"].at(i)["id"] << " " << jsonObj["listaPunteros"].at(i)["type"] << " " <<  jsonObj["listaPunteros"].at(i)["value"] << endl;

        createVSPTR(jsonObj["listaPunteros"].at(i)["id"], jsonObj["listaPunteros"].at(i)["type"], jsonObj["listaPunteros"].at(i)["value"]);
    }

}


#endif //VSPTR_SERVER_POINTERPARSER_H
