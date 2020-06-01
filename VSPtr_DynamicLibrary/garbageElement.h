//
// Created by heutlett on 14/5/20.
//

#ifndef PRUEBAVS_GARBAGEELEMENT_H
#define PRUEBAVS_GARBAGEELEMENT_H

#include <iostream>
#include <string>
using namespace std;

//template <class T>
class garbageElement{

public:

    void* ptrData;
    void* vsptrAdress;
    vector<garbageElement*> * listOfReferences = new vector<garbageElement*>;
    string id;
    string type;

    /**
     *
     * @param dataPtr
     * @param pType
     * @param pId
     * @param pVsptrAdress
     */
    garbageElement(void * dataPtr, string pType, string pId, void* pVsptrAdress){
        ptrData = dataPtr;

        type = pType;
        id = pId;
        vsptrAdress = pVsptrAdress;

        //cout << "GarbageElement has been created, VSPointerAddress: " << vsptrAdress << ", Value: " << getValue() << ", refTo: " << ptrData << endl <<endl;
    }
    /**
     * Returns the value of the pointer in string
     * @return string
     */
    string getValue(){

        if(type.compare("i")==0){

            if(static_cast<int *>(ptrData) == nullptr){
                return "not initialized";
            }
            return to_string(*static_cast<int *>(ptrData));
        }
        if(type.compare("b")==0){
            if(static_cast<bool *>(ptrData) == nullptr){
                return "not initialized";
            }
            return to_string(*static_cast<bool *>(ptrData));
        }
        if(type.compare("c")==0){
            if(static_cast<char *>(ptrData) == nullptr){
                return "not initialized";
            }
            string s(1, *static_cast<char *>(ptrData));
            return s;
        }
        if(type.compare("s")==0){
            if(static_cast<short *>(ptrData) == nullptr){
                return "not initialized";
            }
            return to_string(*static_cast<short *>(ptrData));
        }
        if(type.compare("l")==0){
            if(static_cast<long *>(ptrData) == nullptr){
                return "not initialized";
            }
            return to_string(*static_cast<long *>(ptrData));
        }
        if(type.compare("x")==0){
            if(static_cast<long long *>(ptrData) == nullptr){
                return "not initialized";
            }
            return to_string(*static_cast<long long *>(ptrData));
        }
        if(type.compare("f")==0){
            if(static_cast<float *>(ptrData) == nullptr){
                return "not initialized";
            }
            return to_string(*static_cast<float *>(ptrData));
        }
        if(type.compare("d")==0){
            if(static_cast<double *>(ptrData) == nullptr){
                return "not initialized";
            }
            return to_string(*static_cast<double *>(ptrData));
        }
        if(type.compare("e")==0){
            if(static_cast<long double *>(ptrData) == nullptr){
                return "not initialized";
            }
            return to_string(*static_cast<long double *>(ptrData));
        }
    }

    void deleteReference(void ** address){

        for(int i = 0; i < listOfReferences->size(); i++){

            if(listOfReferences->at(i)->vsptrAdress == address){

                listOfReferences->erase(listOfReferences->begin() + i);

            }
        }

    }

    garbageElement * getGarbageReference(void** address){

        for(int i = 0; i < listOfReferences->size(); i++){

            if(listOfReferences->at(i)->vsptrAdress == address){

                return listOfReferences->at(i);

            }
        }

    }

    /**
     * Return de memory address of the pointer
     * @return void**
     */
    void ** getAddress(){
        return static_cast<void **>(ptrData);
    }

    void toString(){

        cout << "id: " << id << " | " << "refAddress: " << getAddress() << " | Type: " << type << " | Value: " << getValue()  << " | refQuantity: " << listOfReferences->size()+1 << endl;

        cout << 0 << ": " << vsptrAdress << endl;

        for(int i = 0; i < listOfReferences->size(); i++){

            cout << i+1 << ": " << listOfReferences->at(i)->vsptrAdress << endl;

        }


    }
};

#endif //PRUEBAVS_GARBAGEELEMENT_H
