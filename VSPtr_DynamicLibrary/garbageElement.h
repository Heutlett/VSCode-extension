//
// Created by heutlett on 14/5/20.
//

#ifndef VSPTR_DYNAMICLIBRARY_GARBAGEELEMENT_H
#define VSPTR_DYNAMICLIBRARY_GARBAGEELEMENT_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//template <class T>
class VSPTR_DYNAMICLIBRARY_GARBAGEELEMENT_H garbageElement{

public:

    void* ptrData;
    void* vsptrAdress;
    vector<garbageElement*> * listOfReferences;
    string id;
    int remoteId;
    static int countRemoteId;
    string type;

    /**
     *
     * @param dataPtr
     * @param pType
     * @param pId
     * @param pVsptrAdress
     */
    garbageElement(void * dataPtr, string pType, string pId, void* pVsptrAdress);
    /**
     * Returns the value of the pointer in string
     * @return string
     */
    string getValue();

    void deleteReference(void ** address);

    garbageElement * getGarbageReference(void** address);

    /**
     * Return de memory address of the pointer
     * @return void**
     */
    void ** getAddress();

    void toString();
};

#endif //PRUEBAVS_GARBAGEELEMENT_H
