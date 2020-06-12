//
// Created by heutlett on 11/6/20.
//

#ifndef VSPTR_SERVER_POINTERPARSER_H
#define VSPTR_SERVER_POINTERPARSER_H

#include "VSPointer.h"

VSPointer<int>* createVSPTRint(string pId, string pValue, int remoteId){
    VSPointer<int> * ptr = new VSPointer<int>(pId, remoteId);
    *ptr = stoi(pValue);
    return ptr;
}

VSPointer<bool>* createVSPTRbool(string pId, string pValue, int remoteId){
    VSPointer<bool> * ptr = new VSPointer<bool>(pId, remoteId);
    if(pValue.compare("1")){
        *ptr = true;
    }else{
        *ptr = false;
    }
    return ptr;
}

VSPointer<char>* createVSPTRchar(string pId, string pValue, int remoteId){
    VSPointer<char> * ptr = new VSPointer<char>(pId, remoteId);
    char a = pValue.at(0);
    *ptr = a;
    return ptr;
}

VSPointer<short>* createVSPTRshort(string pId, string pValue, int remoteId){
    VSPointer<short> * ptr = new VSPointer<short>(pId, remoteId);
    short a = stoi(pValue);
    *ptr = a;
    return ptr;
}

VSPointer<long>* createVSPTRlong(string pId, string pValue, int remoteId){
    VSPointer<long> * ptr = new VSPointer<long>(pId, remoteId);
    long a = stoi(pValue);
    *ptr = a;
    return ptr;
}

VSPointer<long long>* createVSPTRlonglong(string pId, string pValue, int remoteId){
    VSPointer<long long> * ptr = new VSPointer<long long>(pId, remoteId);
    long long a = stoi(pValue);
    *ptr = a;
    return ptr;
}

VSPointer<float>* createVSPTRfloat(string pId, string pValue, int remoteId){
    VSPointer<float> * ptr = new VSPointer<float>(pId, remoteId);
    *ptr =stof(pValue);
    return ptr;
}

VSPointer<double>* createVSPTRdouble(string pId, string pValue, int remoteId){
    VSPointer<double> * ptr = new VSPointer<double>(pId, remoteId);
    *ptr =stod(pValue);
    return ptr;
}

VSPointer<long double>* createVSPTRlongdouble(string pId, string pValue, int remoteId){
    VSPointer<long double> * ptr = new VSPointer<long double>(pId, remoteId);
    *ptr =stod(pValue);
    return ptr;
}

/*
void createVSPTR(string pId, string type, string pValue){

    if(type.compare("i")==0){

        VSPointer<int> * ptr = new VSPointer<int>(pId);
        *ptr = stoi(pValue);

    }
    if(type.compare("b")==0){
        VSPointer<bool> * ptr = new VSPointer<bool>(pId);

        if(pValue.compare("1")){
            *ptr = true;
        }else{
            *ptr = false;
        }
    }
    if(type.compare("c")==0){
        VSPointer<char> * ptr = new VSPointer<char>(pId);
        char a = pValue.at(0);
        *ptr = a;
    }
    if(type.compare("s")==0){
        VSPointer<short> * ptr = new VSPointer<short>(pId);
        short a = stoi(pValue);
        *ptr = a;
    }
    if(type.compare("l")==0){
        VSPointer<long> * ptr = new VSPointer<long>(pId);
        long a = stoi(pValue);
        *ptr = a;
    }
    if(type.compare("x")==0){
        VSPointer<long long> * ptr = new VSPointer<long long>(pId);
        long long a = stoi(pValue);
        *ptr = a;
    }
    if(type.compare("f")==0){
        VSPointer<float> * ptr = new VSPointer<float>(pId);
        *ptr =stof(pValue);
    }
    if(type.compare("d")==0){
        VSPointer<double> * ptr = new VSPointer<double>(pId);
        *ptr =stod(pValue);
    }
    if(type.compare("e")==0){
        VSPointer<long double> * ptr = new VSPointer<long double>(pId);
        *ptr =stod(pValue);
    }




}*/

void importPointerFromString(string pointers){

    garbageCollector *g = garbageCollector::getInstance();

    g->clearGC();

    json jsonObj;
    stringstream(pointers) >> jsonObj;

    for(int i = 0; i < jsonObj["listaPunteros"].size(); i++){

        cout << "parseando: " << jsonObj["listaPunteros"].at(i)["id"] << " " << jsonObj["listaPunteros"].at(i)["type"] << " " <<  jsonObj["listaPunteros"].at(i)["value"] << endl;

        string type = jsonObj["listaPunteros"].at(i)["type"];
        string id = jsonObj["listaPunteros"].at(i)["id"];
        string value = jsonObj["listaPunteros"].at(i)["value"];
        int remote = jsonObj["listaPunteros"].at(i)["idRemote"];

        if(type.compare("i")==0){

            VSPointer<int> * ptr;
            ptr = createVSPTRint(id, value, remote);

            for(int e = 0; e < jsonObj["listaPunteros"].at(i)["listOfReferences"].size(); e++){

                int remoteId = jsonObj["listaPunteros"].at(i)["listOfReferences"].at(e)["idRemote"];

                VSPointer<int> * nuevo = new VSPointer<int>(1, remoteId);

                ostringstream get_the_address3;
                string address3;
                get_the_address3 << nuevo;
                address3 = get_the_address3.str();

                nuevo->ptr = ptr->ptr;
                garbageCollector::getInstance()->updateReference(nuevo->id, ptr->id, address3);
                nuevo->id = ptr->id;
            }
        }

        if(type.compare("b")==0){

            VSPointer<bool> * ptr;
            ptr = createVSPTRbool(id, value, remote);

            for(int e = 0; e < jsonObj["listaPunteros"].at(i)["listOfReferences"].size(); e++){

                int remoteId = jsonObj["listaPunteros"].at(i)["listOfReferences"].at(e)["idRemote"];

                VSPointer<bool> * nuevo = new VSPointer<bool>(1, remoteId);

                ostringstream get_the_address3;
                string address3;
                get_the_address3 << nuevo;
                address3 = get_the_address3.str();

                nuevo->ptr = ptr->ptr;

                garbageCollector::getInstance()->updateReference(nuevo->id, ptr->id, address3);
                nuevo->id = ptr->id;
            }
        }

        if(type.compare("c")==0){

            VSPointer<char> * ptr;
            ptr = createVSPTRchar(id, value, remote);

            for(int e = 0; e < jsonObj["listaPunteros"].at(i)["listOfReferences"].size(); e++){

                int remoteId = jsonObj["listaPunteros"].at(i)["listOfReferences"].at(e)["idRemote"];

                VSPointer<char> * nuevo = new VSPointer<char>(1, remoteId);

                ostringstream get_the_address3;
                string address3;
                get_the_address3 << nuevo;
                address3 = get_the_address3.str();

                nuevo->ptr = ptr->ptr;

                garbageCollector::getInstance()->updateReference(nuevo->id, ptr->id, address3);
                nuevo->id = ptr->id;
            }
        }

        if(type.compare("s")==0){

            VSPointer<short> * ptr;
            ptr = createVSPTRshort(id, value, remote);

            for(int e = 0; e < jsonObj["listaPunteros"].at(i)["listOfReferences"].size(); e++){

                int remoteId = jsonObj["listaPunteros"].at(i)["listOfReferences"].at(e)["idRemote"];

                VSPointer<short> * nuevo = new VSPointer<short>(1, remoteId);

                ostringstream get_the_address3;
                string address3;
                get_the_address3 << nuevo;
                address3 = get_the_address3.str();

                nuevo->ptr = ptr->ptr;

                garbageCollector::getInstance()->updateReference(nuevo->id, ptr->id, address3);
                nuevo->id = ptr->id;
            }
        }

        if(type.compare("l")==0){

            VSPointer<long> * ptr;
            ptr = createVSPTRlong(id, value, remote);

            for(int e = 0; e < jsonObj["listaPunteros"].at(i)["listOfReferences"].size(); e++){

                int remoteId = jsonObj["listaPunteros"].at(i)["listOfReferences"].at(e)["idRemote"];

                VSPointer<long> * nuevo = new VSPointer<long>(1, remoteId);

                ostringstream get_the_address3;
                string address3;
                get_the_address3 << nuevo;
                address3 = get_the_address3.str();

                nuevo->ptr = ptr->ptr;
                garbageCollector::getInstance()->updateReference(nuevo->id, ptr->id, address3);
                nuevo->id = ptr->id;
                garbageCollector::getInstance()->printElements();
            }
        }

        if(type.compare("x")==0){

            VSPointer<long long> * ptr;
            ptr = createVSPTRlonglong(id, value, remote);

            for(int e = 0; e < jsonObj["listaPunteros"].at(i)["listOfReferences"].size(); e++){

                int remoteId = jsonObj["listaPunteros"].at(i)["listOfReferences"].at(e)["idRemote"];

                VSPointer<long long> * nuevo = new VSPointer<long long>(1, remoteId);

                ostringstream get_the_address3;
                string address3;
                get_the_address3 << nuevo;
                address3 = get_the_address3.str();

                nuevo->ptr = ptr->ptr;
                garbageCollector::getInstance()->updateReference(nuevo->id, ptr->id, address3);
                nuevo->id = ptr->id;
            }
        }

        if(type.compare("f")==0){

            VSPointer<float> * ptr;
            ptr = createVSPTRfloat(id, value, remote);

            for(int e = 0; e < jsonObj["listaPunteros"].at(i)["listOfReferences"].size(); e++){

                int remoteId = jsonObj["listaPunteros"].at(i)["listOfReferences"].at(e)["idRemote"];

                VSPointer<float> * nuevo = new VSPointer<float>(1, remoteId);

                ostringstream get_the_address3;
                string address3;
                get_the_address3 << nuevo;
                address3 = get_the_address3.str();

                nuevo->ptr = ptr->ptr;
                garbageCollector::getInstance()->updateReference(nuevo->id, ptr->id, address3);
                nuevo->id = ptr->id;
            }
        }

        if(type.compare("d")==0){

            VSPointer<double> * ptr;
            ptr = createVSPTRdouble(id, value, remote);

            for(int e = 0; e < jsonObj["listaPunteros"].at(i)["listOfReferences"].size(); e++){

                int remoteId = jsonObj["listaPunteros"].at(i)["listOfReferences"].at(e)["idRemote"];

                VSPointer<double> * nuevo = new VSPointer<double>(1, remoteId);

                ostringstream get_the_address3;
                string address3;
                get_the_address3 << nuevo;
                address3 = get_the_address3.str();

                nuevo->ptr = ptr->ptr;
                garbageCollector::getInstance()->updateReference(nuevo->id, ptr->id, address3);
                nuevo->id = ptr->id;
            }
        }

        if(type.compare("e")==0){

            VSPointer<long double> * ptr;
            ptr = createVSPTRlongdouble(id, value, remote);

            for(int e = 0; e < jsonObj["listaPunteros"].at(i)["listOfReferences"].size(); e++){

                int remoteId = jsonObj["listaPunteros"].at(i)["listOfReferences"].at(e)["idRemote"];

                VSPointer<long double> * nuevo = new VSPointer<long double>(1, remoteId);

                ostringstream get_the_address3;
                string address3;
                get_the_address3 << nuevo;
                address3 = get_the_address3.str();

                nuevo->ptr = ptr->ptr;
                garbageCollector::getInstance()->updateReference(nuevo->id, ptr->id, address3);
                nuevo->id = ptr->id;
            }
        }

    }

}

/*
 VSPointer& operator=(VSPointer<T> *other){


            ostringstream get_the_address3;
            string address3;
            get_the_address3 << (void**)this;
            address3 = get_the_address3.str();

            ptr = other->ptr;
            getGC()->updateReference(id, other->id, address3);
            id = other->id;

    }
 */


#endif //VSPTR_SERVER_POINTERPARSER_H
