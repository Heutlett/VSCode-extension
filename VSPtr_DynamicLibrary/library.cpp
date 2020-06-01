#include "library.h"
#include "person.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
using namespace std;

int CountPeople()
{
    return person::size;

};


/*
#include "library.h"

#include "person.h"

int Subtract(int num1, int num2)
{
    return num1 - num2;
}

int Add(int num1, int num2)
{
    return num1 + num2;
}

int cambia(int a){

    person::cambiar(a);

}
int get(int a){

    return person::getA();

}

*/
/*
int getInfo(int num)
{
    return garbageCollector::prueba(num);
}

void get_md5_string(string s)
{
    s = "hoasdasdasdasd";
}
 */
