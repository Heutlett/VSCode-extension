#ifndef DYNAMIC_LIBRARY_GARBAGECOLLECTOR_H
#define DYNAMIC_LIBRARY_GARBAGECOLLECTOR_H

#include <vector>
#include "garbageElement.h"
#include <thread>
#include <unistd.h>

using namespace std;

class garbageCollector {

    private:
        /* Here will be the instance stored. */
        static garbageCollector* instance;

        /* Private constructor to prevent instancing. */
        garbageCollector(){

            garbageList = new vector<garbageElement*>();
            garbageTotalList = new vector<void*>() ;
            thread(&garbageCollector::memoryLeakThread, this).detach();

        }

        void memoryLeakThread(){
            while(1) {

                sleep(5);
                checkMemoryLeaks();

            }
        }

    public:

          vector<garbageElement*> * garbageList;
          vector<void*> * garbageTotalList;


        /* Static access method. */
        int totalPtrCount = 0;

        static garbageCollector* getInstance();

        void printElements(){

            cout << "LIST OF VSPOINTERS" << endl;

            for(int i = 0; i < garbageList->size(); i++){
                 garbageList->at(i)->toString();
            }

            cout << endl;
        }
        garbageElement* getGarbageElement(string id){
            for(int i = 0; i < garbageList->size(); i++){

                if(garbageList->at(i)->id.compare(id) == 0){
                    return garbageList->at(i);
                }
            }
            return nullptr;
        }

        garbageElement* getGarbageElement(string id, void** address){
            for(int i = 0; i < garbageList->size(); i++){

                if(garbageList->at(i)->id.compare(id) == 0 && garbageList->at(i)->vsptrAdress == address){
                    return garbageList->at(i);
                }
            }
            return nullptr;
        }

        void deleteGarbageElement(string id, void** address){
            for(int i = 0; i < garbageList->size(); i++){

                if(garbageList->at(i)->id.compare(id) == 0 && garbageList->at(i)->vsptrAdress == address){

                    garbageList->erase(garbageList->begin() + i);
                    totalPtrCount--;

                }
            }
        }

        void updateReference(string id, string newId, void** address){
            garbageElement * gNewReference = getGarbageElement(id, address);

            if(gNewReference == nullptr){

                cout << "si gNewReference == null" << endl;

                garbageElement * gOriginal = getGarbageElement(id);
                garbageElement * gReference = gOriginal->getGarbageReference(address);
                garbageElement * gNewOriginal = getGarbageElement(newId);
                gOriginal->deleteReference(address);
                gReference->id = newId;
                gNewOriginal->listOfReferences->push_back(gReference);

                //cout << "gOriginal:";
                //gOriginal->toString();
                //cout << "gReference:";
                //gReference->toString();
                //cout << "gNewOriginal:";
                //gNewOriginal->toString();


            }else{

                //cout << "si gNewReference != null" << endl;

                deleteGarbageElement(id, address);
                garbageElement * gOriginalReference = getGarbageElement(newId);
                gNewReference->id = newId;
                gOriginalReference->listOfReferences->push_back(gNewReference);
                transferReferences(gNewReference, newId, gOriginalReference);

            }
        }

        void transferReferences(garbageElement * gOldElement, string newId, garbageElement * gNewElement){

                while(gOldElement->listOfReferences->size() != 0){

                    garbageElement * gTemp = gOldElement->listOfReferences->at(0);
                    gTemp->id = newId;
                    gTemp->ptrData = gNewElement->ptrData;
                    gOldElement->listOfReferences->erase(gOldElement->listOfReferences->begin() + 0);
                    gNewElement->listOfReferences->push_back(gTemp);

                }

            }

            //Si es el ptr original devuelve true, sino false
            bool deletePtr(string id, void ** address){
                garbageElement * original = getGarbageElement(id, address);
                if(original != nullptr){
                    deleteGarbageElement(id, address);
                    return true;

                }else{
                    garbageElement * reference = getGarbageElement(id);
                    if(reference != nullptr){
                        reference->deleteReference(address);
                    }
                    return false;
                }
            }

            /**
             * Busca los memory leaks y los libera
             */
              void checkMemoryLeaks(){

                bool isMemoryLeaked = true;
                int count = 0;

                cout << "Thread: the memory leaks search started" << endl;

                for(int i = 0; i < garbageTotalList->size(); i++){

                    for(int e = 0; e < garbageList->size(); e++){

                        if(garbageTotalList->at(i) == garbageList->at(e)->ptrData){
                            isMemoryLeaked = false;
                        }
                    }

                    if(isMemoryLeaked) {
                        void * deletePtr = garbageTotalList->at(i);
                        cout << "The pointer: " << deletePtr << " was successfully free" << endl;
                        garbageTotalList->erase(garbageTotalList->begin() + i);
                        free(deletePtr);
                        count++;
                    }
                    isMemoryLeaked = true;

                }
                cout << "Thread: the memory leaks has finished with " << count << " pointers free" << endl << endl;
            }

};
garbageCollector* garbageCollector::instance = 0;
garbageCollector* garbageCollector::getInstance()
{
    if (instance == 0)
    {
        instance = new garbageCollector();
    }

    return instance;
}

#endif