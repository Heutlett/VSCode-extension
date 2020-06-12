#ifndef VSPTR_SERVER_VSPOINTER_H
#define VSPTR_SERVER_VSPOINTER_H


#include <iostream>
#include "garbageCollector.h"
using namespace std;

// A generic smart pointer class
template <class T>
class VSPointer {

private:



public:

    T* ptr; // Actual pointer
    string id;
    int remoteId;

    VSPointer() {

    }

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


    // Constructor
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

    // Constructor
    VSPointer(int i) {
        ptr = (typeof(*ptr)*)malloc(sizeof(*ptr));
        *ptr = NULL;
        garbageCollector::getInstance()->garbageTotalList->push_back(ptr);
        string type = typeid(*ptr).name();
        id = "id" + to_string(garbageCollector::getInstance()->totalPtrCount);

        ostringstream get_the_address3;
        string address3;
        get_the_address3 << (void**)this;
        address3 = get_the_address3.str();

        remoteId = garbageElement::countRemoteId;

        garbageCollector::getInstance()->garbageList->push_back(new garbageElement(ptr, type, id, address3, remoteId));
        garbageCollector::getInstance()->totalPtrCount++;

        garbageElement::countRemoteId++;
    }


    static VSPointer New(){
        return VSPointer(1,0);
    }

    T operator &(){return *ptr;}

    // Destructor
    ~VSPointer() {

        ostringstream get_the_address3;
        string address3;
        get_the_address3 << (void**)this;
        address3 = get_the_address3.str();

        if(garbageCollector::getInstance()->deletePtr(id, address3)){
            free(ptr);

        }
    }

    // Overloading dereferncing operator
    T& operator*() {
        return *ptr;
    }

    T* operator->() { return ptr; }

    void validateType(string type, T newValue){
        string type2 = typeid(ptr).name();

        //cout << "el tipo mio es: " << type << " el tipo parametro es: " << type2 << endl;

        if(type.compare(type2) == 0){
            *ptr = newValue;
        }else{
            cout << "Operation failed, the types dont match" << endl;
        }
    }

    VSPointer& operator=(VSPointer<T> other){

        string type = typeid(*ptr).name();
        string type2 = typeid(T).name();

        if(type.compare(type2)==0){

            ostringstream get_the_address3;
            string address3;
            get_the_address3 << (void**)this;
            address3 = get_the_address3.str();

            ptr = other.ptr;
            garbageCollector::getInstance()->updateReference(id, other.id, address3);
            id = other.id;
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