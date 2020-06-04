#ifndef VSPTR_DYNAMICLIBRARY_VSPOINTER_H __attribute__((visibility("default")));
#define VSPTR_DYNAMICLIBRARY_VSPOINTER_H


#include <iostream>
#include "garbageCollector.h"
using namespace std;

// A generic smart pointer class
template <class T>
class VSPTR_DYNAMICLIBRARY_VSPOINTER_H VSPointer {

private:

    T* ptr; // Actual pointer

public:

    string id;
    bool isNew = true;

    garbageCollector* getGC(){

        return garbageCollector::getInstance();
    }

    VSPointer() {

    }
    // Constructor
    VSPointer(int i) {
        ptr = (typeof(*ptr)*)malloc(sizeof(*ptr));

        getGC()->garbageTotalList->push_back(ptr);
        string type = typeid(*ptr).name();
        id = "id" + to_string(getGC()->totalPtrCount);
        //cout << "VSPointer: " << this << ", refTo: " << ptr <<" type: (" << type << "), Value: " << to_string(*ptr) << " has been created" << endl;
        getGC()->garbageList->push_back(new garbageElement(ptr, type, id, (void**)this));
        getGC()->totalPtrCount++;
    }

    static VSPointer New(){
        return VSPointer(1);
    }

    T operator &(){return *ptr;}

    // Destructor
    ~VSPointer() {
        if(getGC()->deletePtr(id, reinterpret_cast<void**>(this))){
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
            getGC()->updateReference(id, other.id, reinterpret_cast<void**>(this));
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




/*
#include <iostream>
#include "garbageCollector.h"
using namespace std;



// A generic smart pointer class
template <class T>
class VSPTR_DYNAMICLIBRARY_VSPOINTER_H VSPointer {

private:

    T* ptr; // Actual pointer

public:

    string id;

    garbageCollector* getGC();



    VSPointer();
    // Constructor
    VSPointer(T*);

    //static VSPointer New(){
    //    return VSPointer(1);
    //}

    T operator &();

    // Destructor
    ~VSPointer();

    // Overloading dereferncing operator
    T& operator*();

    T* operator->();

    void validateType(string type, T newValue);

    VSPointer& operator=(VSPointer<T> other);

    VSPointer& operator=(int newValue);

    VSPointer& operator=(bool newValue);

    VSPointer& operator=(char newValue);

    VSPointer& operator=(short newValue);

    VSPointer& operator=(long newValue);

    VSPointer& operator=(long long newValue);

    VSPointer& operator=(float newValue);

    VSPointer& operator=(double newValue);

    VSPointer& operator=(long double newValue);

};
*/
#endif //DYNAMIC_LIBRARY_D_H