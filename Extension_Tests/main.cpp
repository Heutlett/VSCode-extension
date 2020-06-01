#include <iostream>
#include "lib/library.h"
#include "lib/person.h"
#include "lib/VSPointer.h"
#include "lib/garbageCollector.h"

garbageCollector * gc = garbageCollector::getInstance();

using namespace std;

//target_link_libraries(project ${CMAKE_SOURCE_DIR}/lib/libVSPtr_DynamicLibrary)


int main(){

    int i;

    VSPointer<int> myPtr = VSPointer<int>::New( );
    *myPtr = 5;

    VSPointer<int> myPtr1 = VSPointer<int>::New( );
    myPtr1 = myPtr;

    VSPointer<int> myPtr2 = VSPointer<int>::New( );
    *myPtr2 = 555;

    VSPointer<int> myPtr3 = VSPointer<int>::New( );
    *myPtr3 = 666;


    VSPointer<int> myPtr4 = VSPointer<int>::New( );
    myPtr4 = myPtr;


    VSPointer<int> myPtr5 = VSPointer<int>::New( );
    myPtr5 = myPtr1;

    VSPointer<int> myPtr6 = VSPointer<int>::New( );
    myPtr6 = myPtr2;

    VSPointer<int> myPtr7 = VSPointer<int>::New( );
    myPtr7 = myPtr6;

    VSPointer<char> myPtr8 = VSPointer<char>::New( );
    *myPtr8 = 'a';

    gc->generarJSON();

    gc->printElements();

    //myPtr = myPtr1;

    cin >> i;

    gc->printElements();

    /*
    int a;
     
    std::cout << VSPTR_DYNAMICLIBRARY_LIBRARY_H::CountPeople() << std::endl;
    person *p1 = new person(1,2);
    person *p2 = new person(3,4);
    person *p3 = new person(3,4);
    person *p19 = new person(3,4);
    person *p20 = new person(3,4);
    person *p22 = new person(3,4);
    person *p23 = new person(3,4);

    std::cout << "Cantidad de personas: " << VSPTR_DYNAMICLIBRARY_LIBRARY_H::CountPeople() << std::endl;
    cin >> a;
    
    
    delete(p1);
    delete(p2);
    std::cout << VSPTR_DYNAMICLIBRARY_LIBRARY_H::CountPeople() << std::endl;
    */
    //char arr[5] = { 'a', 'b', 'c', 'd', 'e' };
    //Array<char> a(arr, 5);
    //a.print();
    //return 0;
    //vsp
    return 0;

}