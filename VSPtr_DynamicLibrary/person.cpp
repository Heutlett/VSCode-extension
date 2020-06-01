//
// Created by heutlett on 31/5/20.
//

#include <iostream>
#include "person.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

using namespace std;

int person::size = 5;

person::person(int id, int otherId)
{
    this->id = id;
    this->otherId = otherId;
    person::size++;
};
person::~person() {
    person::size--;
}
int person::envio() {

    // ftok to generate unique key
    key_t key = ftok("shmfile",65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key,1024,0666|IPC_CREAT);

    // shmat to attach to shared memory
    int* str = (int*) shmat(shmid,(void*)0,0);



    cout<<"Write Data : " << str;
    str = &size;

    printf("Data written in memory: %s\n",str);

    //detach from shared memory
    shmdt(str);

}
