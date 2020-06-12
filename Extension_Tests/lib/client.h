//
// Created by heutlett on 11/6/20.
//

#ifndef VSPTR_DYNAMICLIBRARY_CLIENT_H
#define VSPTR_DYNAMICLIBRARY_CLIENT_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>
#include <string>

using namespace std;

#define PORT 8080
#define SIZE 100000
//
int sock = 0, valread;
struct sockaddr_in serv_addr;
char buffer[SIZE] = {0};

/**
 * @brief
 *
 */
void iniciarCliente();
/**
 * @brief Limpia el buffer que se utiliza para comunicarse con el servidor
 */
void limpiarBuffer(){

    for(int i = 0; i < SIZE; i++){

        buffer[i] = NULL;

    }

}
/**
 * @brief Recibe un mensaje del servidor y lo almacena en el buffer
 */
void recibir(){

    limpiarBuffer();
    valread = read( sock , buffer, SIZE);
    //printf("Recibido: %s\n",buffer );

}
/**
 * @brief Envia un string al servidor
 * @param string con mensaje a enviar
 */
void enviar(string msg){

    limpiarBuffer();
    send(sock , msg.data() , msg.size() , 0 );
    //printf("Enviado: %s\n",msg.c_str());

}
/**
 * @brief Actualiza el grafo del servidor
 * @return Devuelve el grafo en modo string
 */
void sendPointers(string pointers){

    limpiarBuffer();
    iniciarCliente();

    enviar("1"); //1
    recibir(); //2

    cout << "Sending pointers to server." << endl;
    enviar(pointers); //3

    recibir();//4
    close(sock);

}
/**
 * @brief Pide al servidor el algoritmo dijkstra de un nodo en especifico pasado por parametro
 * @param string que contiene el numero del vertice que se quiere analizar la ruta mas corta
 * @return Devuelve la ruta mas corta del vertice pasado por parametro
 */
int createVSPTR(string type){

    limpiarBuffer();
    iniciarCliente();

    enviar("2"); //1
    recibir(); //2

    enviar(type);//3


    recibir();//4
    close(sock);

    int ia = buffer[0] - '0';

    return ia;

}

string getValue(int remoteID){

    limpiarBuffer();
    iniciarCliente();

    enviar("3"); //1
    recibir(); //2

    enviar(to_string(remoteID));//3
    recibir();//4
    close(sock);
    return buffer;

}

void updateReferenceServer(int thisRemoteId, int otherRemoteId){

    limpiarBuffer();
    iniciarCliente();

    enviar("4"); //1
    recibir(); //2

    enviar(to_string(thisRemoteId));//3
    recibir();//4

    enviar(to_string(otherRemoteId));//5

    recibir();
    close(sock);

}
/**
 * @brief Crea el socket del cliente
 */
void crearSocket(){

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
    }

}
/**
 * @brief Define los atributos del socket
 */
void atributos(){

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

}
/**
 * @brief Convierte direcciones IPv4 y IPv6 de texto a forma binaria
 */
void hostName(){

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
    }

}
/**
 * @brief Se conecta con el servidor
 */
void conectar(){

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
    }

}
/**
 * @brief Inicia el socket del cliente
 */
void iniciarCliente()
{
    crearSocket();
    atributos();
    hostName();
    conectar();
}



#endif //VSPTR_DYNAMICLIBRARY_CLIENT_H
