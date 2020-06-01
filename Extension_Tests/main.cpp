#include <iostream>
#include "lib/library.h"
#include "lib/person.h"

using namespace std;

//target_link_libraries(project ${CMAKE_SOURCE_DIR}/lib/libVSPtr_DynamicLibrary)


int main(){

    int a;
     
    std::cout << VSPTR_DYNAMICLIBRARY_LIBRARY_H::recibo() << std::endl;
    person *p1 = new person(1,2);
    person *p2 = new person(3,4);
    person *p3 = new person(3,4);
    person *p19 = new person(3,4);
    person *p20 = new person(3,4);
    person *p22 = new person(3,4);
    person *p23 = new person(3,4);

    std::cout << "Cantidad de personas: " << VSPTR_DYNAMICLIBRARY_LIBRARY_H::recibo() << std::endl;
    cin >> a;
    
    
    delete(p1);
    delete(p2);
    std::cout << VSPTR_DYNAMICLIBRARY_LIBRARY_H::recibo() << std::endl;
    //char arr[5] = { 'a', 'b', 'c', 'd', 'e' };
    //Array<char> a(arr, 5);
    //a.print();
    //return 0;
    //vsp
    return 0;

}