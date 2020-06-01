//
// Created by heutlett on 29/4/20.
//
#include "VSPointer.h"
#include <iostream>

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
    cout << "The value of a: " << a << endl;

    //Test#4
    cout << "Test #4:" << endl;
    VSPointer<int> myptr2 = VSPointer<int>::New();
    myptr2 = myPtr;
    gc->printElements();

    //Test#5
    cout << "Test #5:" << endl;
    myPtr = 6;
    gc->printElements();

}

int prueba(int a){

    return a;

}

int main()
{

    int i;

    VSPointer<int> myPtr = VSPointer<int>::New( );
    *myPtr = 'A';

    VSPointer<int> myPtr1 = VSPointer<int>::New( );
    *myPtr1 = 'b';

    gc->printElements();

    myPtr = myPtr1;

    cin >> i;

    gc->printElements();

    return 0;
}
