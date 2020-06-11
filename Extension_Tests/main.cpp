#include <iostream>
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

    //cin >> i;

    VSPointer<int> myPtr5 = VSPointer<int>::New( );
    myPtr5 = myPtr1;

    VSPointer<int> myPtr6 = VSPointer<int>::New( );
    myPtr6 = myPtr2;

    VSPointer<int> myPtr7 = VSPointer<int>::New( );
    myPtr7 = myPtr6;

    garbageCollector::getInstance()->generateStringJSON();

    cin >> i;

    //gc->generarJSON();

    //gc->printElements();

    //myPtr = myPtr1;

    

    //VSPointer<int> myPtr20 = VSPointer<int>::New( );
    //*myPtr20 = 112;

    //VSPointer<int> myPtr30 = VSPointer<int>::New( );
    //*myPtr30 = 132;


    //gc->generarJSON();

    //cin >> i;

    //myPtr2 = myPtr1;
    //myPtr3 = myPtr;

   // gc->generarJSON();

    //cin >> i;

    //gc->printElements();
    

    /*
    int i;

    VSPointer<int> myPtr = VSPointer<int>::New( );
    *myPtr = 15;

    VSPointer<int> myPtr1 = VSPointer<int>::New( );
    *myPtr1 = 22;

    gc->printElements();

    cin >> i;

    myPtr = myPtr1;

    cin >> i;

    gc->printElements();
    return 0;
    */

}