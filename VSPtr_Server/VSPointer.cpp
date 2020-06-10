//
// Created by heutlett on 28/5/20.
//

#include "VSPointer.h"
/*
template <class T>
garbageCollector* VSPointer<T>::getGC(){

    return garbageCollector::getInstance();
}

template <class T>
VSPointer<T>::VSPointer(){

}
template <class T>
VSPointer<T>::VSPointer(T* value) {
    ptr = (typeof(*ptr)*)malloc(sizeof(*ptr));

    getGC()->garbageTotalList->push_back(ptr);
    string type = typeid(*ptr).name();
    id = "id" + to_string(getGC()->totalPtrCount);
    //cout << "VSPointer: " << this << ", refTo: " << ptr <<" type: (" << type << "), Value: " << to_string(*ptr) << " has been created" << endl;
    getGC()->garbageList->push_back(new garbageElement(ptr, type, id, (void**)this));
    getGC()->totalPtrCount++;
}



template <class T>
T VSPointer<T>::operator &(){
    return *ptr;
}

template <class T>
VSPointer<T>::~VSPointer() {
    if(getGC()->deletePtr(id, reinterpret_cast<void**>(this))){
        free(ptr);
    }
}

template <class T>
T& VSPointer<T>::operator*() {
    return *ptr;
}

template <class T>
T* VSPointer<T>::operator->() { return ptr; }

template <class T>
void VSPointer<T>::validateType(string type, T newValue){
    string type2 = typeid(ptr).name();
    if(type.compare(type2) == 0){
        *ptr = newValue;
    }else{
        cout << "Operation failed, the types dont match" << endl;
    }
}

template <class T>
VSPointer<T>& VSPointer<T>::operator=(VSPointer<T> other){

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
template <class T>
VSPointer<T>& VSPointer<T>::operator=(int newValue){
    validateType(typeid(&newValue).name(), newValue);
}
template <class T>
VSPointer<T>& VSPointer<T>::operator=(bool newValue){
    validateType(typeid(&newValue).name(), newValue);
}
template <class T>
VSPointer<T>& VSPointer<T>::operator=(char newValue){
    validateType(typeid(&newValue).name(), newValue);
}
template <class T>
VSPointer<T>& VSPointer<T>::operator=(short newValue){
    validateType(typeid(&newValue).name(), newValue);
}
template <class T>
VSPointer<T>& VSPointer<T>::operator=(long newValue){
    validateType(typeid(&newValue).name(), newValue);
}
template <class T>
VSPointer<T>& VSPointer<T>::operator=(long long newValue){
    validateType(typeid(&newValue).name(), newValue);
}
template <class T>
VSPointer<T>& VSPointer<T>::operator=(float newValue){
    validateType(typeid(&newValue).name(), newValue);
}
template <class T>
VSPointer<T>& VSPointer<T>::operator=(double newValue){
    validateType(typeid(&newValue).name(), newValue);
}
template <class T>
VSPointer<T>& VSPointer<T>::operator=(long double newValue){
    validateType(typeid(&newValue).name(), newValue);
}
 */