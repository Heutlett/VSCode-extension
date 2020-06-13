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
    /**
     * @brief constructor
     */
    garbageCollector();
    /**
     * @brief thread que revisa los punteros en busca de memory leaks
     */
    void memoryLeakThread();

public:

    bool remoteMemoryIsActive;
    vector<garbageElement*> * garbageList;
    vector<void*> * garbageTotalList;
    static int totalPtrCount;
    /**
     * @brief devuelve la instancia del garbage collector (singleton)
     * @return
     */
    static garbageCollector* getInstance();
    /**
     * @brief imprime todos los elementos del garbage collector
     */
    void printElements();
    /**
     * @brief devuelve un elemento del garbage collector
     * @param id
     * @return
     */
    garbageElement* getGarbageElement(string id);
    /**
     * @brief devuelve un elemento del garbage collector
     * @param id
     * @param address
     * @return
     */
    garbageElement* getGarbageElement(string id, string address);
    /**
     * @brief elimina un elemento del garbage collector
     * @param id
     * @param address
     */
    void deleteGarbageElement(string id, string address);
    /**
     * @brief actualiza un elemento del garbage collector
     * @param id
     * @param newId
     * @param address
     */
    void updateReference(string id, string newId, string address);
    /**
     * @brief transfiere un elemento del garbage collector
     * @param gOldElement
     * @param newId
     * @param gNewElement
     */
    void transferReferences(garbageElement * gOldElement, string newId, garbageElement * gNewElement);
    /**
     * @brief elimina un puntero del garbage collector
     * @param id
     * @param address
     * @return
     */
    bool deletePtr(string id, string address);
    /**
     * @brief checkea si hay memory leaks
     */
    void checkMemoryLeaks();
    /**
     * @brief genera un json con todos los punteros que contiene el garbage collector
     */
    void generarJSON();
    /**
     * @brief verifica las configuraciones a ver si se activo la remote memory desde la extension
     */
    void checkRemoteMemoryConf();
    /**
     * @brief procedimiento del thread
     */
    void checkRemoteThread();
    /**
     * @brief genera un json en formato string
     * @return
     */
    string generateStringJSON();
    /**
     * @brief genera un json con todos los punteros del garbage collector
     * @return
     */
    json JsonGenerator();
    /**
     * @brief envia todos los punteros al servidor mediante un json
     */
    void sendPointersToServer();
    /**
     * @brief limpia las listas del garbage collector
     */
    void clearGC();
    /**
     * @brief verifica si el garbage collector esta vacio
     * @return
     */
    bool gcIsClear();
    /**
     * @brief sobrecarga del constructor cuando se usa la remote memory
     * @param type
     * @return
     */
    int SERVER_vsptrConstructor(string type);
    /**
     * @brief obtiene el valor de un vspointer cuando se esta usando la memoria remota
     * @param remoteID
     * @return
     */
    string SERVER_vsptrGetValue(int remoteID);
    /**
     * @brief actualiza un puntero si se encuentra en el extranjero
     * @param thisRemoteId
     * @param otherRemoteId
     */
    void SERVER_vsptrUpdateReference(int thisRemoteId, int otherRemoteId);
    /**
     * @brief sobrecarga del operador (=) cuando se utiliza la remote memory
     * @param newValueType
     * @param newValue
     * @param thisIdRemote
     */
    void SERVER_vsptrOverloadAssign(string newValueType, string newValue, int thisIdRemote);
    /**
     * @brief importa los punteros del servidor a la memoria local
     */
    void getPointersFromServer();
};


#endif //PRUEBAVS_GARBAGECOLLECTOR_H
