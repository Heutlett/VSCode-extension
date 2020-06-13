#ifndef VSPTR_DYNAMICLIBRARY_VSPOINTER_H
#define VSPTR_DYNAMICLIBRARY_VSPOINTER_H

#include <iostream>
#include "garbageCollector.h"
using namespace std;

template <class T>
class VSPTR_DYNAMICLIBRARY_VSPOINTER_H VSPointer {

private:

public:
    T* ptr; // Actual pointer
    string id;
    int remoteId;

    /**
     * @brief sobrecarga del operador new
     * @param size
     * @return
     */
    void * operator new(size_t size)
    {
        void * p = ::new VSPointer<int>();

        return p;
    }
    /**
     * @brief constructor
     * @param pId
     * @param remoteId
     */
    VSPointer(string pId, int remoteId) {
        ptr = (typeof(*ptr)*)malloc(sizeof(*ptr));
        garbageCollector::getInstance()->garbageTotalList->push_back(ptr);
        string type = typeid(*ptr).name();
        id = pId;

        ostringstream get_the_address3;
        string address3;
        get_the_address3 << this;
        address3 = get_the_address3.str();

        garbageCollector::getInstance()->garbageList->push_back(new garbageElement(ptr, type, id, address3, remoteId));
        garbageCollector::getInstance()->totalPtrCount++;
    }
    /**
     * @brief constructor
     * @param i
     * @param remoteId
     */
    VSPointer(int i, int remoteId) {
        ptr = (typeof(*ptr)*)malloc(sizeof(*ptr));
        garbageCollector::getInstance()->garbageTotalList->push_back(ptr);
        string type = typeid(*ptr).name();
        id = "id" + to_string(garbageCollector::getInstance()->totalPtrCount);

        ostringstream get_the_address3;
        string address3;
        get_the_address3 << this;
        address3 = get_the_address3.str();

        garbageCollector::getInstance()->garbageList->push_back(new garbageElement(ptr, type, id, address3, remoteId));
        garbageCollector::getInstance()->totalPtrCount++;
    }

    /**
     * @brief constructor
     */
    VSPointer() {

    }
    /**
     * @brief constructor
     * @param i
     */
    VSPointer(int i) {

        string type = typeid(*ptr).name();

        if(garbageCollector::getInstance()->remoteMemoryIsActive){
            ptr = (typeof(*ptr)*)malloc(sizeof(*ptr));
            remoteId = garbageCollector::getInstance()->SERVER_vsptrConstructor(type);
            id = "";

        }else{

            ptr = (typeof(*ptr)*)malloc(sizeof(*ptr));
            garbageCollector::getInstance()->garbageTotalList->push_back(ptr);
            id = "id" + to_string(garbageCollector::getInstance()->totalPtrCount);

            ostringstream get_the_address3;
            string address3;
            get_the_address3 << this;
            address3 = get_the_address3.str();

            garbageCollector::getInstance()->garbageList->push_back(new garbageElement(ptr, type, id, address3));
            garbageCollector::getInstance()->totalPtrCount++;

            garbageElement * copia = garbageCollector::getInstance()->getGarbageElement(id, address3);
            remoteId = copia->remoteId;

        }
    }
    /**
     * @brief sobrecarga de new
     * @return
     */
    static VSPointer New(){
        return VSPointer(1);
    }
    /**
     * @brief sobrecarga del operador &
     * @return
     */
    T operator &(){

        if(garbageCollector::getInstance()->remoteMemoryIsActive){

            string type = typeid(*ptr).name();
            string valor =garbageCollector::getInstance()->SERVER_vsptrGetValue(remoteId);

            if(type.compare("i")==0){
                *ptr = stoi(valor);
            }
            if(type.compare("b")==0){
                if(valor.compare("1")==0){
                    *ptr = true;
                }else{
                    *ptr = false;
                }
            }
            if(type.compare("c")==0){
                char a = valor.at(0);
                *ptr = a;
            }
            if(type.compare("s")==0){
                *ptr = stoi(valor);
            }
            if(type.compare("l")==0){
                *ptr = stol(valor);
            }
            if(type.compare("x")==0){
                *ptr = stoll(valor);
            }
            if(type.compare("f")==0){
                *ptr = stof(valor);
            }
            if(type.compare("d")==0){
                *ptr = stod(valor);
            }
            if(type.compare("e")==0){
                *ptr = stold(valor);
            }

            return *ptr;

        }else{

            return *ptr;

        }
    }
    /**
     * @brief destructor
     */
    ~VSPointer() {

        if(garbageCollector::getInstance()->remoteMemoryIsActive){


        }else{

            ostringstream get_the_address3;
            string address3;
            get_the_address3 << this;
            address3 = get_the_address3.str();

            if(garbageCollector::getInstance()->deletePtr(id, address3)){
                free(ptr);

            }
            garbageCollector::getInstance()->generarJSON();

        }
    }
    /**
     * @brief sobrecarga del operador *
     * @return
     */
    T& operator*() {

        if(garbageCollector::getInstance()->remoteMemoryIsActive){

            return *ptr;

        }else{
            return *ptr;
        }

    }
    /**
     * @brief sobrecarga del operador ->
     * @return
     */
    T* operator->() {

        if(garbageCollector::getInstance()->remoteMemoryIsActive){

        }else{
            return ptr;
        }
    }
    /**
     * @brief funcion auxiliar para la sobrecarga del operador = con valores
     * @param type
     * @param newValue
     */
    void validateType(string type, T newValue){

        string type2 = typeid(ptr).name();

        if(type.compare(type2) == 0){

            if(garbageCollector::getInstance()->remoteMemoryIsActive){

                string a = to_string(newValue);

                garbageCollector::getInstance()->SERVER_vsptrOverloadAssign(type, a, remoteId);

            }else{
                    *ptr = newValue;
                }
            }
        else{
            cout << "Operation failed, the types dont match" << endl;
        }
    }
    /**
     * @brief sobrecarga del operador = con un VSPointer como right value
     * @param other
     * @return
     */
    VSPointer& operator=(VSPointer<T> other){

        string type = typeid(*ptr).name();
        string type2 = typeid(T).name();

        if(type.compare(type2)==0){

            if(garbageCollector::getInstance()->remoteMemoryIsActive){

                garbageCollector::getInstance()->SERVER_vsptrUpdateReference(remoteId, other.remoteId);

            }else{
                    ptr = other.ptr;

                    ostringstream get_the_address3;
                    string address3;
                    get_the_address3 << this;
                    address3 = get_the_address3.str();

                    garbageCollector::getInstance()->updateReference(id, other.id, address3);
                    id = other.id;
            }

        }else{
            cout << "Operation fail, the types dont match" << endl;
        }
    }

    /**
     * @brief sobrecarga del operador = con valores int
     * @param newValue
     * @return
     */
    VSPointer& operator=(int newValue){
        validateType(typeid(&newValue).name(), newValue);
    }
    /**
     * @brief sobrecarga del operador = con valores bool
     * @param newValue
     * @return
     */
    VSPointer& operator=(bool newValue){
        validateType(typeid(&newValue).name(), newValue);
    }
    /**
     * @brief sobrecarga del operador = con valores char
     * @param newValue
     * @return
     */
    VSPointer& operator=(char newValue){
        validateType(typeid(&newValue).name(), newValue);
    }
    /**
     * @brief sobrecarga del operador = con valores short
     * @param newValue
     * @return
     */
    VSPointer& operator=(short newValue){
        validateType(typeid(&newValue).name(), newValue);
    }
    /**
     * @brief sobrecarga del operador = con valores long
     * @param newValue
     * @return
     */
    VSPointer& operator=(long newValue){
        validateType(typeid(&newValue).name(), newValue);
    }
    /**
     * @brief sobrecarga del operador = con valores long long
     * @param newValue
     * @return
     */
    VSPointer& operator=(long long newValue){
        validateType(typeid(&newValue).name(), newValue);
    }
    /**
     * @brief sobrecarga del operador = con valores float
     * @param newValue
     * @return
     */
    VSPointer& operator=(float newValue){
        validateType(typeid(&newValue).name(), newValue);
    }
    /**
     *
     * @param newValue
     * @return
     */
    VSPointer& operator=(double newValue){
        validateType(typeid(&newValue).name(), newValue);
    }
    /**
     * @brief sobrecarga del operador = con valores long double
     * @param newValue
     * @return
     */
    VSPointer& operator=(long double newValue){
        validateType(typeid(&newValue).name(), newValue);
    }

};

#endif //DYNAMIC_LIBRARY_D_H