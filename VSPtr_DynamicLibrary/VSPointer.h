//
// Created by heutlett on 14/5/20.
//

#ifndef PRUEBAVS_VSPOINTER_H
#define PRUEBAVS_VSPOINTER_H


#include <iostream>
#include "garbageCollector.h"
using namespace std;

// A generic smart pointer class
template <class T>
class VSPointer {

private:

    T* ptr; // Actual pointer

public:

    garbageCollector * gc = garbageCollector::getInstance();
    string id;
    bool isNew = true;

    VSPointer() {

    }
    // Constructor
    VSPointer(int i) {
        ptr = (typeof(*ptr)*)malloc(sizeof(*ptr));
        gc->garbageTotalList->push_back(ptr);
        string type = typeid(*ptr).name();
        id = "id" + to_string(gc->totalPtrCount);
        //cout << "VSPointer: " << this << ", refTo: " << ptr <<" type: (" << type << "), Value: " << to_string(*ptr) << " has been created" << endl;
        gc->garbageList->push_back(new garbageElement(ptr, type, id, (void**)this));
        gc->totalPtrCount++;
    }

    static VSPointer New(){
        return VSPointer(1);
    }

    T operator &(){return *ptr;}

    // Destructor
    ~VSPointer() {
        if(gc->deletePtr(id, reinterpret_cast<void**>(this))){
            free(ptr);
        }
    }

    // Overloading dereferncing operator
    T& operator*() {
        isNew = false;
        return *ptr;
    }

    T* operator->() { return ptr; }

    void validateType(string type, T newValue){
        string type2 = typeid(ptr).name();
        if(type.compare(type2) == 0){
            *ptr = newValue;
            isNew = false;
        }else{
            cout << "Operation failed, the types dont match" << endl;
        }
    }

    VSPointer& operator=(VSPointer<T> other){

        //cout << "other data" << endl;
        //cout << "id: " << other.id << " ptr: " << *other.ptr << " is new: " << isNew << endl;

        string type = typeid(*ptr).name();
        string type2 = typeid(T).name();

        //if(other.isNew){
        //    return other;
        //}

        if(type.compare(type2)==0){
            ptr = other.ptr;
            gc->updateReference(id, other.id, reinterpret_cast<void**>(this));
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

#endif //PRUEBAVS_VSPOINTER_H
