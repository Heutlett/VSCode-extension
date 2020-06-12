#include <iostream>
#include "lib/VSPointer.h"
#include "lib/garbageCollector.h"

garbageCollector * gc = garbageCollector::getInstance();

using namespace std;

int main(){
    
    int i;
 
    VSPointer<int> myPtr = VSPointer<int>::New( );
    myPtr = 666;

    VSPointer<int> myPtr1 = VSPointer<int>::New( );
    myPtr1 = myPtr;

    VSPointer<int> myPtr2 = VSPointer<int>::New( );
    *myPtr2 = 777;

    VSPointer<int> myPtr3 = VSPointer<int>::New( );
    *myPtr3 = 888;

    cout << "el valor de myptr3 es " << &myPtr3 << endl;

    VSPointer<int> myPtr4 = VSPointer<int>::New( );
    myPtr4 = myPtr;

    //cin >> i;

    VSPointer<int> myPtr5 = VSPointer<int>::New( );
    myPtr5 = myPtr1;

    VSPointer<int> myPtr6 = VSPointer<int>::New( );
    myPtr6 = myPtr2;

    VSPointer<char> myPtr7 = VSPointer<char>::New( );
    *myPtr7 = 'a';

    garbageCollector::getInstance()->printElements();

    cin >> i;

    VSPointer<int> myPtr8 = VSPointer<int>::New( );
    myPtr8 = myPtr6;

    garbageCollector::getInstance()->printElements();
    cout << "el valor de myPtr7 es " << &myPtr7 << endl;

    VSPointer<char> myPtr9 = VSPointer<char>::New( );

    cin >> i;

    myPtr9 = 'b';

    cin >> i;


}