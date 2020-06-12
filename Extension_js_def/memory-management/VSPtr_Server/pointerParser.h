//
// Created by heutlett on 11/6/20.
//

#ifndef VSPTR_SERVER_POINTERPARSER_H
#define VSPTR_SERVER_POINTERPARSER_H

#include "VSPointer.h"


VSPointer<int>* createVSPTR(string pId, string pValue){

    VSPointer<int> * ptr = new VSPointer<int>(pId);
    *ptr = stoi(pValue);

    //cout << "el valor de ptr es " << **ptr << endl;

    //garbageCollector::getInstance()->printElements();

    //cout << "mi address es " << ptr << endl;

    return ptr;

}

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

        cout << "parseando: " << jsonObj["listaPunteros"].at(i)["id"] << " " << jsonObj["listaPunteros"].at(i)["type"] << " " <<  jsonObj["listaPunteros"].at(i)["value"] << endl;

        string type = jsonObj["listaPunteros"].at(i)["type"];
        string id = jsonObj["listaPunteros"].at(i)["id"];
        string value = jsonObj["listaPunteros"].at(i)["value"];
        VSPointer<int> * ptr;

        if(type.compare("i")==0){

            ptr = createVSPTR(id, value);

        }

        garbageCollector::getInstance()->printElements();

        cout << "helo" << endl;

        //createVSPTR(jsonObj["listaPunteros"].at(i)["id"], jsonObj["listaPunteros"].at(i)["type"], jsonObj["listaPunteros"].at(i)["value"]);

        for(int e = 0; e < jsonObj["listaPunteros"].at(i)["listOfReferences"].size(); e++){

            VSPointer<int> * nuevo = new VSPointer<int>(1);

            garbageCollector::getInstance()->printElements();

            ostringstream get_the_address3;
            string address3;
            get_the_address3 << nuevo;
            address3 = get_the_address3.str();

            cout << "address de nuevo es " << address3 << endl;

            nuevo->ptr = ptr->ptr;

            cout << "nuevo->ptr = " << nuevo->ptr << endl;
            cout << "ptr->ptr = " << ptr->ptr << endl;

            garbageCollector::getInstance()->updateReference(nuevo->id, ptr->id, address3);
            nuevo->id = ptr->id;

            garbageCollector::getInstance()->printElements();

        }

    }

}

/*
 VSPointer& operator=(VSPointer<T> *other){


            ostringstream get_the_address3;
            string address3;
            get_the_address3 << (void**)this;
            address3 = get_the_address3.str();

            ptr = other->ptr;
            getGC()->updateReference(id, other->id, address3);
            id = other->id;

    }
 */


#endif //VSPTR_SERVER_POINTERPARSER_H
