#include <iostream>
#include "lib/VSPointer.h"
#include "lib/garbageCollector.h"

garbageCollector * gc = garbageCollector::getInstance();

using namespace std;

//target_link_libraries(project ${CMAKE_SOURCE_DIR}/lib/libVSPtr_DynamicLibrary)

int main(){
    
    int i;

    cout << "hola";
 
    VSPointer<char> myPtr = VSPointer<char>::New( );
    *myPtr = 'a';

    VSPointer<char> myPtr1 = VSPointer<char>::New( );
    myPtr1 = myPtr;

    VSPointer<char> myPtr2 = VSPointer<char>::New( );
    *myPtr2 = 'b';

    VSPointer<char> myPtr3 = VSPointer<char>::New( );
    *myPtr3 = 'x';

    VSPointer<char> myPtr4 = VSPointer<char>::New( );
    myPtr4 = myPtr;

    //cin >> i;

    VSPointer<char> myPtr5 = VSPointer<char>::New( );
    myPtr5 = myPtr1;

    VSPointer<char> myPtr6 = VSPointer<char>::New( );
    myPtr6 = myPtr2;

    VSPointer<char> myPtr7 = VSPointer<char>::New( );
    myPtr7 = myPtr6;

    cout << garbageCollector::getInstance()->generateStringJSON();

    garbageCollector::getInstance()->sendPointersToServer();

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