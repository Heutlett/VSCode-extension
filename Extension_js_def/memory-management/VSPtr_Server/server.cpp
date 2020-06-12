#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "garbageCollector.h"
#include "pointerParser.h"
#define PORT 8080
#define SIZE 100000
using namespace std;


int server_fd, new_socket, valread;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);
char buffer[SIZE] = {0};

void limpiarBuffer(){

    for(int i = 0; i < SIZE; i++){

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
    limpiarBuffer();
    valread = read( new_socket , buffer, SIZE);
    printf("Recibi: %s\n",buffer );

}

void enviar(string e){
    limpiarBuffer();
    send(new_socket , e.data() , e.size() , 0 );
    printf("Mensaje enviado: %s\n",e.c_str());

}

int createVSPTR(string type){

    if(type.compare("i")==0){
        VSPointer<int> * ptr = new VSPointer<int>(1);
        return ptr->remoteId;
    }
    if(type.compare("b")==0){
        VSPointer<bool> * ptr = new VSPointer<bool>(1);
        return ptr->remoteId;
    }
    if(type.compare("c")==0){
        VSPointer<char> * ptr = new VSPointer<char>(1);
        return ptr->remoteId;
    }
    if(type.compare("s")==0){
        VSPointer<short> * ptr = new VSPointer<short>(1);
        return ptr->remoteId;
    }
    if(type.compare("l")==0){
        VSPointer<long> * ptr = new VSPointer<long>(1);
        return ptr->remoteId;
    }
    if(type.compare("x")==0){
        VSPointer<long long> * ptr = new VSPointer<long long>(1);
        return ptr->remoteId;
    }
    if(type.compare("f")==0){
        VSPointer<float> * ptr = new VSPointer<float>(1);
        return ptr->remoteId;
    }
    if(type.compare("d")==0){
        VSPointer<double> * ptr = new VSPointer<double>(1);
        return ptr->remoteId;
    }
    if(type.compare("e")==0){
        VSPointer<long double> * ptr = new VSPointer<long double>(1);
        return ptr->remoteId;
    }

}


void updateAssignAux(char type, string newValue, int remoteId){

    garbageElement * g = garbageCollector::getInstance()->getGarbageElement(remoteId);
    garbageCollector::getInstance()->deletePtrTotalList(g->ptrData);

    if(type == 'i'){

        int *a = (int*)malloc(sizeof(int));
        *a = stoi(newValue);

        g->ptrData = (void*)a;
        garbageCollector::getInstance()->garbageTotalList->push_back(g->ptrData);
    }

    if(type == 'b'){
        if(newValue.compare("1")==0){

            bool * a = (bool*)malloc(sizeof(bool));
            *a = true;

            g->ptrData = (void*)a;
            garbageCollector::getInstance()->garbageTotalList->push_back(g->ptrData);

        }else{

            bool * a = (bool*)malloc(sizeof(bool));
            *a = false;

            g->ptrData = (void*)a;
            garbageCollector::getInstance()->garbageTotalList->push_back(g->ptrData);
        }
    }
    if(type == 'c'){
        char * a = (char*)malloc(sizeof(char));
        char b = stoi(newValue);
        *a = b;

        g->ptrData = (void*)a;
        garbageCollector::getInstance()->garbageTotalList->push_back(g->ptrData);
    }
    if(type == 's'){

        short *a = (short*)malloc(sizeof(short));
        *a = stoi(newValue);

        g->ptrData = (void*)a;
        garbageCollector::getInstance()->garbageTotalList->push_back(g->ptrData);
    }
    if(type == 'l'){
        long *a = (long*)malloc(sizeof(long));
        *a = stol(newValue);

        g->ptrData = (void*)a;
        garbageCollector::getInstance()->garbageTotalList->push_back(g->ptrData);
    }
    if(type == 'x'){
        long long *a = (long long*)malloc(sizeof(long long));
        *a = stoll(newValue);

        g->ptrData = (void*)a;
        garbageCollector::getInstance()->garbageTotalList->push_back(g->ptrData);
    }
    if(type == 'f'){
        float *a = (float*)malloc(sizeof(float));
        *a = stof(newValue);

        g->ptrData = (void*)a;
        garbageCollector::getInstance()->garbageTotalList->push_back(g->ptrData);
    }
    if(type == 'd'){
        double *a = (double*)malloc(sizeof(double));
        *a = stod(newValue);

        g->ptrData = (void*)a;
        garbageCollector::getInstance()->garbageTotalList->push_back(g->ptrData);
    }
    if(type == 'e'){
        long double *a = (long double*)malloc(sizeof(long double));
        *a = stold(newValue);

        g->ptrData = (void*)a;
        garbageCollector::getInstance()->garbageTotalList->push_back(g->ptrData);
    }

}

string getValue(int remoteID){

    return garbageCollector::getInstance()->getValue(remoteID);

}

int main(int argc, char const *argv[])
{
    int i;
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
        //close(new_socket);
        accept();

        //if(!fork()){

        recibir();

        if(strcmp(buffer, "1") == 0){ //1

            cout << "Receiving pointers..." << endl;
            enviar("Server: ready to get pointers"); //2

            recibir(); //3
            importPointerFromString(buffer);
            cout << endl <<"Printing al imported vspointers" << endl << endl;
            garbageCollector::getInstance()->printElements();
            enviar("Server: The pointers has been reicived"); //4
            cout << endl << "generating json" << endl;
            cout << "el ultimo remote id sera: " << garbageElement::countRemoteId <<  endl;
            //garbageCollector::getInstance()->generarJSON();

        }

        if(strcmp(buffer, "2") == 0){ //1
            garbageCollector::getInstance()->printElements();

            enviar("recibido2"); //2

            recibir();//3
            int remoteId = createVSPTR(buffer);

            string s = to_string(remoteId);
            enviar(s);//4

        }

        if(strcmp(buffer, "3") == 0){ //1
            garbageCollector::getInstance()->printElements();

            enviar("recibido3"); //2

            recibir();//3
            string s = getValue(stoi(buffer));

            enviar(s);//4
        }

        if(strcmp(buffer, "4") == 0){ //1
            garbageCollector::getInstance()->printElements();

            enviar("recibido4"); //2

            cout << "waiting for this remote id" << endl;
            recibir();//3
            int thisRemoteId = stoi(buffer);

            enviar("request other remote id");//4

            recibir();//5

            int otherRemoteId = stoi(buffer);

            garbageElement * thisG = garbageCollector::getInstance()->getGarbageElement(thisRemoteId);
            garbageElement * otherG = garbageCollector::getInstance()->getGarbageElement(otherRemoteId);

            thisG->ptrData = otherG->ptrData;
            garbageCollector::getInstance()->updateReference(thisG->id, otherG->id, thisG->vsptrAdress);
            thisG->id = otherG->id;

            enviar("listo");//4

            garbageCollector::getInstance()->printElements();
        }

        if(strcmp(buffer, "5") == 0){ //1
            garbageCollector::getInstance()->printElements();

            enviar("recibido5"); //2

            recibir();//3

            string type = buffer;

            enviar("listo"); //4

            recibir();//5

            string value = buffer;

            enviar("listo");//6

            recibir();//7


            int remoteId = stoi(buffer);

            updateAssignAux(type.at(1), value, remoteId);

        }

        if(strcmp(buffer, "6") == 0){ //1
            garbageCollector::getInstance()->printElements();

            enviar("recibido6"); //2

            recibir();//3
            string s = garbageCollector::getInstance()->generateStringJSON();
            garbageCollector::getInstance()->clearGC();
            enviar(s);//4
        }

        //}

        //close(new_socket);
        limpiarBuffer();

    }
}
