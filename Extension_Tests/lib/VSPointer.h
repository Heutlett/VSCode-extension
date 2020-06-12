#ifndef VSPTR_DYNAMICLIBRARY_VSPOINTER_H
#define VSPTR_DYNAMICLIBRARY_VSPOINTER_H


#include <iostream>
#include "garbageCollector.h"
//#include "client.h"
using namespace std;

// A generic smart pointer class
template <class T>
class VSPTR_DYNAMICLIBRARY_VSPOINTER_H VSPointer {

private:



public:
    T* ptr; // Actual pointer
    string id;
    int remoteId;
    garbageCollector* getGC(){

        return garbageCollector::getInstance();
    }
    /*
    void * operator new(size_t size)
    {
        void * p = ::new VSPointer<int>();
        //void * p = malloc(size); will also work fine

        return p;
    }

    VSPointer(string pId, int remoteId) {
        ptr = (typeof(*ptr)*)malloc(sizeof(*ptr));
        garbageCollector::getInstance()->garbageTotalList->push_back(ptr);
        string type = typeid(*ptr).name();
        id = pId;

        ostringstream get_the_address3;
        string address3;
        get_the_address3 << (void**)this;
        address3 = get_the_address3.str();

        garbageCollector::getInstance()->garbageList->push_back(new garbageElement(ptr, type, id, address3, remoteId));
        garbageCollector::getInstance()->totalPtrCount++;
    }

    VSPointer(int i, int remoteId) {
        ptr = (typeof(*ptr)*)malloc(sizeof(*ptr));
        garbageCollector::getInstance()->garbageTotalList->push_back(ptr);
        string type = typeid(*ptr).name();
        id = "id" + to_string(garbageCollector::getInstance()->totalPtrCount);

        ostringstream get_the_address3;
        string address3;
        get_the_address3 << (void**)this;
        address3 = get_the_address3.str();

        garbageCollector::getInstance()->garbageList->push_back(new garbageElement(ptr, type, id, address3, remoteId));
        garbageCollector::getInstance()->totalPtrCount++;
    }

    */
    VSPointer() {

    }
    // Constructor
    VSPointer(int i) {

        string type = typeid(*ptr).name();

        if(garbageCollector::getInstance()->remoteMemoryIsActive){
            ptr = (typeof(*ptr)*)malloc(sizeof(*ptr));
            remoteId = garbageCollector::getInstance()->SERVER_vsptrConstructor(type);
            id = "";
            //cout << "No se crea nada porque la remote esta activada" << endl;

        }else{

            ptr = (typeof(*ptr)*)malloc(sizeof(*ptr));
            getGC()->garbageTotalList->push_back(ptr);
            //string type = typeid(*ptr).name();
            id = "id" + to_string(getGC()->totalPtrCount);
            getGC()->garbageList->push_back(new garbageElement(ptr, type, id, (void**)this));
            getGC()->totalPtrCount++;
            garbageElement * copia = getGC()->getGarbageElement(id, (void**)this);
            remoteId = copia->remoteId;

        }
    }

    static VSPointer New(){
        return VSPointer(1);
    }

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

    // Destructor
    ~VSPointer() {

        if(garbageCollector::getInstance()->remoteMemoryIsActive){


        }else{

            if(getGC()->deletePtr(id, reinterpret_cast<void**>(this))){
                free(ptr);

            }
            getGC()->generarJSON();

        }
    }

    // Overloading dereferncing operator
    T& operator*() {

        if(garbageCollector::getInstance()->remoteMemoryIsActive){

            return *ptr;

        }else{
            return *ptr;
        }

    }

    T* operator->() {

        if(garbageCollector::getInstance()->remoteMemoryIsActive){


        }else{

            return ptr;

        }

    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void validateType(string type, T newValue){

        string type2 = typeid(ptr).name();

        if(type.compare(type2) == 0){

            if(garbageCollector::getInstance()->remoteMemoryIsActive){

                cout << "el tipo es: " << type << endl;

                string a = to_string(newValue);

                char b = stoi(a);

                cout << "el valor es: " << a << endl;
                cout << "el valor del char es: " << b << endl;

                garbageCollector::getInstance()->SERVER_vsptrOverloadAssign(type, a, remoteId);

            }else{
                    *ptr = newValue;
                }
            }
        else{
            cout << "Operation failed, the types dont match" << endl;
        }
    }

    VSPointer& operator=(VSPointer<T> other){

        string type = typeid(*ptr).name();
        string type2 = typeid(T).name();

        if(type.compare(type2)==0){

            if(garbageCollector::getInstance()->remoteMemoryIsActive){

                garbageCollector::getInstance()->SERVER_vsptrUpdateReference(remoteId, other.remoteId);

            }else{
                    ptr = other.ptr;
                    getGC()->updateReference(id, other.id, reinterpret_cast<void**>(this));
                    id = other.id;
            }

        }else{
            cout << "Operation fail, the types dont match" << endl;
        }


    }


    VSPointer& operator=(int newValue){
        validateType(typeid(&newValue).name(), newValue);
    }

    VSPointer& operator=(bool newValue){
        validateType(typeid(&newValue).name(), newValue);
    }

    VSPointer& operator=(char newValue){
        validateType(typeid(&newValue).name(), newValue);
    }

    VSPointer& operator=(short newValue){
        validateType(typeid(&newValue).name(), newValue);
    }

    VSPointer& operator=(long newValue){
        validateType(typeid(&newValue).name(), newValue);
    }

    VSPointer& operator=(long long newValue){
        validateType(typeid(&newValue).name(), newValue);
    }

    VSPointer& operator=(float newValue){
        validateType(typeid(&newValue).name(), newValue);
    }

    VSPointer& operator=(double newValue){
        validateType(typeid(&newValue).name(), newValue);
    }

    VSPointer& operator=(long double newValue){
        validateType(typeid(&newValue).name(), newValue);
    }

};

#endif //DYNAMIC_LIBRARY_D_H