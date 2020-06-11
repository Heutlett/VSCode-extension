#include <iostream>
#include "VSPointer.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

using namespace std;

int server_fd, new_socket, valread;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);
char buffer[1024] = {0};

void prueba(){

    int a;

    VSPointer<int> ptr = VSPointer<int>::New();
    *ptr = 5;

    VSPointer<int> ptr1 = VSPointer<int>::New();
    *ptr1 = 51;

    VSPointer<int> ptr2 = VSPointer<int>::New();
    ptr2 = ptr;

    garbageCollector::getInstance()->printElements();

    cin >>  a;

}


int main() {

    prueba();

    return 0;
}
