//
// Created by heutlett on 14/5/20.
//

#ifndef VSPTR_DYNAMICLIBRARY_GARBAGEELEMENT_H
#define VSPTR_DYNAMICLIBRARY_GARBAGEELEMENT_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class VSPTR_DYNAMICLIBRARY_GARBAGEELEMENT_H garbageElement{

public:

    void* ptrData;
    string vsptrAdress;
    vector<garbageElement*> * listOfReferences;
    string id;
    int remoteId;
    static int countRemoteId;
    string type;

    /**
     * @brief construcor para garbageElement
     * @param dataPtr
     * @param pType
     * @param pId
     * @param pVsptrAdress
     */
    garbageElement(void * dataPtr, string pType, string pId, string pVsptrAdress);
    /**
     * @brief construcor para garbageElement
     * Returns the value of the pointer in string
     * @return string
     */
    garbageElement(void * dataPtr, string pType, string pId, string pVsptrAdress, int remoteId);
    /**
     * @brief devuelve el valor del garbage element
     * @return
     */
    string getValue();
    /**
     * @brief devuelve el valor del garbageElement
     * @param address
     */
    void deleteReference(string address);
    /**
     * @brief elimina una referencia del garbage element
     * @param address
     * @return
     */
    garbageElement * getGarbageReference(string address);

    /**
     * @brief obtiene una referencia del garbage element
     * Return de memory address of the pointer
     * @return void**
     */
    void ** getAddress();
    /**
     * convierte a string...
     */
    void toString();
};

#endif //PRUEBAVS_GARBAGEELEMENT_H
