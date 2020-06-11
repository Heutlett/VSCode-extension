#include <iostream>
#include "VSPointer.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "garbageCollector.h"
#define PORT 8080

using namespace std;

int server_fd, new_socket, valread;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);
char buffer[999999] = {0};

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


void limpiarBuffer(){

    for(int i = 0; i < 999999; i++){

        buffer[i] = NULL;

    }

}

void crearSocket(){

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

}

void attributes(){

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

}

void attachSocket(){

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

}

void listen(){
    \
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

}

void socketName(){

    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

}

void accept(){

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

}

void recibir(){

    valread = read( new_socket , buffer, 1024);
    printf("Recibi: %s\n",buffer );

}

void enviar(string e){

    send(new_socket , e.data() , e.size() , 0 );
    printf("Mensaje enviado: %s\n",e.c_str());

}

int main(int argc, char const *argv[])
{

    //int puerto;
    //cout << "Ingrese el puerto: ";
    //cin >> puerto;

    crearSocket();
    attachSocket();
    attributes();
    socketName();
    listen();

    char *valor;

    while(1){

        cout << "waiting for a client..." << endl << endl;
        close(new_socket);
        accept();

        if(!fork()){


            recibir();


            if(strcmp(buffer, "1") == 0){ //1

                cout << "Receiving pointers..." << endl;
                enviar("Server: ready to get pointers"); //2

                recibir(); //3
                enviar("Server: The pointers has been reicived"); //4


            }

            if(strcmp(buffer, "2") == 0){

                cout << "opcion 2" << endl;
                enviar("recibido2");

            }

        }

        close(new_socket);
        limpiarBuffer();

    }
}
