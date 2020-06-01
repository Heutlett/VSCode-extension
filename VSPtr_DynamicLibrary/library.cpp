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

int recibo(){

    person::envio();

    // ftok to generate unique key
    key_t key = ftok("shmfile",65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key,1024,0666|IPC_CREAT);

    // shmat to attach to shared memory
    int * str = (int*) shmat(shmid,(void*)0,0);

    printf("Data read from memory: %s\n",str);

    return *str;

    //detach from shared memory
    shmdt(str);

    // destroy the shared memory
    shmctl(shmid,IPC_RMID,NULL);

}





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
