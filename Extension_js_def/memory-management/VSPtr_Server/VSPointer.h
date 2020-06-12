#ifndef VSPTR_SERVER_VSPOINTER_H
#define VSPTR_SERVER_VSPOINTER_H


#include <iostream>
#include "garbageCollector.h"
using namespace std;

// A generic smart pointer class
template <class T>
class VSPointer {

private:

    T* ptr; // Actual pointer

public:

    string id;

    garbageCollector* getGC(){

        return garbageCollector::getInstance();
    }

    VSPointer() {

    }

    void * operator new(size_t size)
    {
        cout<< "Overloading new operator with size: " << size << endl;
        void * p = ::new VSPointer<int>();
        //void * p = malloc(size); will also work fine

        return p;
    }

    VSPointer(string pId) {
        ptr = (typeof(*ptr)*)malloc(sizeof(*ptr));
        getGC()->garbageTotalList->push_back(ptr);
        string type = typeid(*ptr).name();
        id = pId;

        ostringstream get_the_address3;
        string address3;
        get_the_address3 << (void**)this;
        address3 = get_the_address3.str();

        getGC()->garbageList->push_back(new garbageElement(ptr, type, id, address3));
        getGC()->totalPtrCount++;
    }

    /*
    // Constructor
    VSPointer(int i) {
        ptr = (typeof(*ptr)*)malloc(sizeof(*ptr));
        getGC()->garbageTotalList->push_back(ptr);
        string type = typeid(*ptr).name();
        id = "id" + to_string(getGC()->totalPtrCount);
        getGC()->garbageList->push_back(new garbageElement(ptr, type, id, (void**)this));
        getGC()->totalPtrCount++;
    }
     */

    static VSPointer New(string id){
        return VSPointer(id);
    }

    T operator &(){return *ptr;}

    // Destructor
    ~VSPointer() {

        ostringstream get_the_address3;
        string address3;
        get_the_address3 << (void**)this;
        address3 = get_the_address3.str();

        if(getGC()->deletePtr(id, address3)){
            free(ptr);

        }
        getGC()->generarJSON();
    }

    // Overloading dereferncing operator
    T& operator*() {
        return *ptr;
    }

    T* operator->() { return ptr; }

    void validateType(string type, T newValue){
        string type2 = typeid(ptr).name();
        if(type.compare(type2) == 0){
            *ptr = newValue;
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

            ostringstream get_the_address3;
            string address3;
            get_the_address3 << (void**)this;
            address3 = get_the_address3.str();

            ptr = other.ptr;
            getGC()->updateReference(id, other.id, address3);
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