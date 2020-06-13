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
#include "pointerParser.h"

using namespace std;

#define PORT 8080
#define SIZE 100000

int sock = 0, valread;
struct sockaddr_in serv_addr;
char buffer[SIZE] = {0};

/**
 * @brief inicia el socket
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

}
/**
 * @brief Envia un string al servidor
 * @param string con mensaje a enviar
 */
void enviar(string msg){

    limpiarBuffer();
    send(sock , msg.data() , msg.size() , 0 );

}
/**
 * @brief Envia los punteros de la memoria local en un string al servidor
 * @param pointers
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
 * @brief Usado como constructor vacio cuando se esta usando la remote memory
 * @param type
 * @return
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
/**
 * @brief Obtiene el valor de un puntero cuando se esta usando la remote memory
 * @param remoteID
 * @return
 */
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
/**
 * @brief Sobrecarga del operador (=) para cuando se esta usando la remote memory
 * @param thisRemoteId
 * @param otherRemoteId
 */
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
 * @brief Sobrecarga del operador (=) para cuando se esta usando la remote memory
 * @param type
 * @param value
 * @param remoteId
 */
void updateAssign(string type, string value, int remoteId){

    limpiarBuffer();
    iniciarCliente();

    enviar("5");//1
    recibir(); //2

    enviar(type);//3
    recibir();//4

    enviar(value); //5
    recibir();//6

    enviar(to_string(remoteId));//7
}
/**
 * @brief Obtiene los punteros del servidor en un string
 */
void getPointers(){

    limpiarBuffer();
    iniciarCliente();

    enviar("6");//1
    recibir();//2

    enviar("preparado");//3
    recibir();//4

    string json = buffer;

    importPointerFromString(json);
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
