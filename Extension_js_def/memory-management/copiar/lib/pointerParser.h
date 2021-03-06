//
// Created by heutlett on 12/6/20.
//

#ifndef VSPTR_DYNAMICLIBRARY_POINTERPARSER_H
#define VSPTR_DYNAMICLIBRARY_POINTERPARSER_H


#include "VSPointer.h"

/**
 * @brief crea un VSPointer para el parseo de json a local memory
 */
VSPointer<int>* createVSPTRint(string pId, string pValue, int remoteId){
    VSPointer<int> * ptr = new VSPointer<int>(pId, remoteId);
    *ptr = stoi(pValue);
    return ptr;
}
/**
 * @brief crea un VSPointer para el parseo de json a local memory
 * @param pId
 * @param pValue
 * @param remoteId
 * @return
 */
VSPointer<bool>* createVSPTRbool(string pId, string pValue, int remoteId){
    VSPointer<bool> * ptr = new VSPointer<bool>(pId, remoteId);
    if(pValue.compare("1") == 0){
        *ptr = true;
    }else{
        *ptr = false;
    }
    return ptr;
}
/**
 * @brief crea un VSPointer para el parseo de json a local memory
 * @param pId
 * @param pValue
 * @param remoteId
 * @return
 */
VSPointer<char>* createVSPTRchar(string pId, string pValue, int remoteId){
    VSPointer<char> * ptr = new VSPointer<char>(pId, remoteId);
    char a = pValue.at(0);
    *ptr = a;
    return ptr;
}
/**
 * @brief crea un VSPointer para el parseo de json a local memory
 * @param pId
 * @param pValue
 * @param remoteId
 * @return
 */
VSPointer<short>* createVSPTRshort(string pId, string pValue, int remoteId){
    VSPointer<short> * ptr = new VSPointer<short>(pId, remoteId);
    short a = stoi(pValue);
    *ptr = a;
    return ptr;
}
/**
 * @brief crea un VSPointer para el parseo de json a local memory
 * @param pId
 * @param pValue
 * @param remoteId
 * @return
 */
VSPointer<long>* createVSPTRlong(string pId, string pValue, int remoteId){
    VSPointer<long> * ptr = new VSPointer<long>(pId, remoteId);
    long a = stol(pValue);
    *ptr = a;
    return ptr;
}
/**
 * @brief crea un VSPointer para el parseo de json a local memory
 * @param pId
 * @param pValue
 * @param remoteId
 * @return
 */
VSPointer<long long>* createVSPTRlonglong(string pId, string pValue, int remoteId){
    VSPointer<long long> * ptr = new VSPointer<long long>(pId, remoteId);
    long long a = stoll(pValue);
    *ptr = a;
    return ptr;
}
/**
 * @brief crea un VSPointer para el parseo de json a local memory
 * @param pId
 * @param pValue
 * @param remoteId
 * @return
 */
VSPointer<float>* createVSPTRfloat(string pId, string pValue, int remoteId){
    VSPointer<float> * ptr = new VSPointer<float>(pId, remoteId);
    *ptr =stof(pValue);
    return ptr;
}
/**
 * @brief crea un VSPointer para el parseo de json a local memory
 * @param pId
 * @param pValue
 * @param remoteId
 * @return
 */
VSPointer<double>* createVSPTRdouble(string pId, string pValue, int remoteId){
    VSPointer<double> * ptr = new VSPointer<double>(pId, remoteId);
    *ptr =stod(pValue);
    return ptr;
}
/**
 * @brief crea un VSPointer para el parseo de json a local memory
 * @param pId
 * @param pValue
 * @param remoteId
 * @return
 */
VSPointer<long double>* createVSPTRlongdouble(string pId, string pValue, int remoteId){
    VSPointer<long double> * ptr = new VSPointer<long double>(pId, remoteId);
    *ptr =stold(pValue);
    return ptr;
}
/**
 * @brief importa punteros desde un string al garbage collector de la memoria local
 * @param pointers
 */
void importPointerFromString(string pointers){

    garbageCollector *g = garbageCollector::getInstance();

    g->clearGC();

    json jsonObj;
    stringstream(pointers) >> jsonObj;

    for(int i = 0; i < jsonObj["listaPunteros"].size(); i++){

        cout << "Parsing: " << jsonObj["listaPunteros"].at(i)["id"] << " " << jsonObj["listaPunteros"].at(i)["type"] << " " <<  jsonObj["listaPunteros"].at(i)["value"] << endl;

        string type = jsonObj["listaPunteros"].at(i)["type"];
        string id = jsonObj["listaPunteros"].at(i)["id"];
        string value = jsonObj["listaPunteros"].at(i)["value"];
        int remote = jsonObj["listaPunteros"].at(i)["idRemote"];

        if(type.compare("i")==0){

            VSPointer<int> * ptr;
            ptr = createVSPTRint(id, value, remote);
            garbageElement::countRemoteId++;

            for(int e = 0; e < jsonObj["listaPunteros"].at(i)["listOfReferences"].size(); e++){

                int remoteId = jsonObj["listaPunteros"].at(i)["listOfReferences"].at(e)["idRemote"];

                VSPointer<int> * nuevo = new VSPointer<int>(1, remoteId);
                garbageElement::countRemoteId++;

                ostringstream get_the_address3;
                string address3;
                get_the_address3 << nuevo;
                address3 = get_the_address3.str();

                nuevo->ptr = ptr->ptr;
                garbageCollector::getInstance()->updateReference(nuevo->id, ptr->id, address3);
                nuevo->id = ptr->id;
            }
        }

        if(type.compare("b")==0){

            VSPointer<bool> * ptr;
            ptr = createVSPTRbool(id, value, remote);
            garbageElement::countRemoteId++;

            for(int e = 0; e < jsonObj["listaPunteros"].at(i)["listOfReferences"].size(); e++){

                int remoteId = jsonObj["listaPunteros"].at(i)["listOfReferences"].at(e)["idRemote"];

                VSPointer<bool> * nuevo = new VSPointer<bool>(1, remoteId);
                garbageElement::countRemoteId++;

                ostringstream get_the_address3;
                string address3;
                get_the_address3 << nuevo;
                address3 = get_the_address3.str();

                nuevo->ptr = ptr->ptr;

                garbageCollector::getInstance()->updateReference(nuevo->id, ptr->id, address3);
                nuevo->id = ptr->id;
            }
        }

        if(type.compare("c")==0){

            VSPointer<char> * ptr;
            ptr = createVSPTRchar(id, value, remote);
            garbageElement::countRemoteId++;

            for(int e = 0; e < jsonObj["listaPunteros"].at(i)["listOfReferences"].size(); e++){

                int remoteId = jsonObj["listaPunteros"].at(i)["listOfReferences"].at(e)["idRemote"];

                VSPointer<char> * nuevo = new VSPointer<char>(1, remoteId);
                garbageElement::countRemoteId++;

                ostringstream get_the_address3;
                string address3;
                get_the_address3 << nuevo;
                address3 = get_the_address3.str();

                nuevo->ptr = ptr->ptr;

                garbageCollector::getInstance()->updateReference(nuevo->id, ptr->id, address3);
                nuevo->id = ptr->id;
            }
        }

        if(type.compare("s")==0){

            VSPointer<short> * ptr;
            ptr = createVSPTRshort(id, value, remote);
            garbageElement::countRemoteId++;

            for(int e = 0; e < jsonObj["listaPunteros"].at(i)["listOfReferences"].size(); e++){

                int remoteId = jsonObj["listaPunteros"].at(i)["listOfReferences"].at(e)["idRemote"];

                VSPointer<short> * nuevo = new VSPointer<short>(1, remoteId);
                garbageElement::countRemoteId++;

                ostringstream get_the_address3;
                string address3;
                get_the_address3 << nuevo;
                address3 = get_the_address3.str();

                nuevo->ptr = ptr->ptr;

                garbageCollector::getInstance()->updateReference(nuevo->id, ptr->id, address3);
                nuevo->id = ptr->id;
            }
        }

        if(type.compare("l")==0){

            VSPointer<long> * ptr;
            ptr = createVSPTRlong(id, value, remote);
            garbageElement::countRemoteId++;

            for(int e = 0; e < jsonObj["listaPunteros"].at(i)["listOfReferences"].size(); e++){

                int remoteId = jsonObj["listaPunteros"].at(i)["listOfReferences"].at(e)["idRemote"];

                VSPointer<long> * nuevo = new VSPointer<long>(1, remoteId);
                garbageElement::countRemoteId++;

                ostringstream get_the_address3;
                string address3;
                get_the_address3 << nuevo;
                address3 = get_the_address3.str();

                nuevo->ptr = ptr->ptr;
                garbageCollector::getInstance()->updateReference(nuevo->id, ptr->id, address3);
                nuevo->id = ptr->id;
                garbageCollector::getInstance()->printElements();
            }
        }

        if(type.compare("x")==0){

            VSPointer<long long> * ptr;
            ptr = createVSPTRlonglong(id, value, remote);
            garbageElement::countRemoteId++;

            for(int e = 0; e < jsonObj["listaPunteros"].at(i)["listOfReferences"].size(); e++){

                int remoteId = jsonObj["listaPunteros"].at(i)["listOfReferences"].at(e)["idRemote"];

                VSPointer<long long> * nuevo = new VSPointer<long long>(1, remoteId);
                garbageElement::countRemoteId++;

                ostringstream get_the_address3;
                string address3;
                get_the_address3 << nuevo;
                address3 = get_the_address3.str();

                nuevo->ptr = ptr->ptr;
                garbageCollector::getInstance()->updateReference(nuevo->id, ptr->id, address3);
                nuevo->id = ptr->id;
            }
        }

        if(type.compare("f")==0){

            VSPointer<float> * ptr;
            ptr = createVSPTRfloat(id, value, remote);
            garbageElement::countRemoteId++;

            for(int e = 0; e < jsonObj["listaPunteros"].at(i)["listOfReferences"].size(); e++){

                int remoteId = jsonObj["listaPunteros"].at(i)["listOfReferences"].at(e)["idRemote"];

                VSPointer<float> * nuevo = new VSPointer<float>(1, remoteId);
                garbageElement::countRemoteId++;

                ostringstream get_the_address3;
                string address3;
                get_the_address3 << nuevo;
                address3 = get_the_address3.str();

                nuevo->ptr = ptr->ptr;
                garbageCollector::getInstance()->updateReference(nuevo->id, ptr->id, address3);
                nuevo->id = ptr->id;
            }
        }

        if(type.compare("d")==0){

            VSPointer<double> * ptr;
            ptr = createVSPTRdouble(id, value, remote);
            garbageElement::countRemoteId++;

            for(int e = 0; e < jsonObj["listaPunteros"].at(i)["listOfReferences"].size(); e++){

                int remoteId = jsonObj["listaPunteros"].at(i)["listOfReferences"].at(e)["idRemote"];

                VSPointer<double> * nuevo = new VSPointer<double>(1, remoteId);
                garbageElement::countRemoteId++;

                ostringstream get_the_address3;
                string address3;
                get_the_address3 << nuevo;
                address3 = get_the_address3.str();

                nuevo->ptr = ptr->ptr;
                garbageCollector::getInstance()->updateReference(nuevo->id, ptr->id, address3);
                nuevo->id = ptr->id;
            }
        }

        if(type.compare("e")==0){

            VSPointer<long double> * ptr;
            ptr = createVSPTRlongdouble(id, value, remote);
            garbageElement::countRemoteId++;

            for(int e = 0; e < jsonObj["listaPunteros"].at(i)["listOfReferences"].size(); e++){

                int remoteId = jsonObj["listaPunteros"].at(i)["listOfReferences"].at(e)["idRemote"];

                VSPointer<long double> * nuevo = new VSPointer<long double>(1, remoteId);
                garbageElement::countRemoteId++;

                ostringstream get_the_address3;
                string address3;
                get_the_address3 << nuevo;
                address3 = get_the_address3.str();

                nuevo->ptr = ptr->ptr;
                garbageCollector::getInstance()->updateReference(nuevo->id, ptr->id, address3);
                nuevo->id = ptr->id;
            }
        }

    }

}
#endif //VSPTR_DYNAMICLIBRARY_POINTERPARSER_H
