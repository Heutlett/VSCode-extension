//
// Created by heutlett on 29/4/20.
//
#include "VSPointer.h"
#include <iostream>
#include "CustomLinkedList.h"

using namespace std;
/*
void * procesoSeparado(void *data){

    char *texto = (char *)data;
    while(1){

        cout << texto << endl;
        sleep(4);

    }

}

int main()
{
    pthread_t proceso1;
    pthread_t proceso2;
    pthread_create(&proceso1, NULL, &procesoSeparado, (void *) "hola");
    pthread_create(&proceso2, NULL, &procesoSeparado, (void *) "adios");
    pthread_join(proceso1, NULL);
    pthread_join(proceso2, NULL);
    cout << "aaaaa"<< endl;

}
*/

garbageCollector * gc = garbageCollector::getInstance();

void printTests(){

    //Test#1
    cout << "Test #1:" << endl;
    VSPointer<int> myPtr = VSPointer<int>::New();
    gc->printElements();

    //Test#2
    cout << "Test #2:" << endl;
    *myPtr = 5;
    gc->printElements();

    //Test#3
    cout << "Test #3:" << endl;
    int a = &myPtr;
    cout << "The value of a: " << a << endl << endl;

    //Test#4
    cout << "Test #4:" << endl;
    VSPointer<int> myptr2 = VSPointer<int>::New();
    myptr2 = myPtr;
    gc->printElements();

    //Test#5
    cout << "Test #5:" << endl;
    myPtr = 6;
    gc->printElements();


    //Test#6: Prueba del thread en el GC
    cout << "Test #6: Prueba del thread en el GC" << endl;
    int i;
    VSPointer<int> myPtr3 = VSPointer<int>::New( );
    *myPtr3 = 555;

    VSPointer<int> myPtr4 = VSPointer<int>::New( );
    *myPtr4 = 6666;

    gc->printElements();

    myPtr3 = myPtr4;

    cin >> i;

    gc->printElements();

}

int prueba(int a){

    return a;

}

int main()
{
    /*
    CustomLinkedList<int> firstList;

    firstList.push_back(32);
    firstList.push_back(33);
    firstList.push_back(1233);
    firstList.push_back(3523);
    firstList.push_back(3123);

    firstList.printlist();
*/
/*
    int i;

    VSPointer<int> myPtr = VSPointer<int>::New( );
    *myPtr = 5;

    VSPointer<int> myPtr1 = VSPointer<int>::New( );
    *myPtr1 = 6;

    gc->printElements();

    myPtr = myPtr1;

    cin >> i;

    gc->printElements();
*/

    printTests();

    return 0;
}
