//
// Created by heutlett on 4/6/20.
//

#ifndef VSPTR_DYNAMICLIBRARY_LIST_H
#define VSPTR_DYNAMICLIBRARY_LIST_H


#include <iostream>
#include "Node.h"
using namespace std;

template <class T> class CustomLinkedList
{

    Node<T> *head, *tail;

public:
    /**
     * @brief constructor de la lista enlazada
     */
    CustomLinkedList()
    {
        head = NULL;
        tail = NULL;
    }
    /**
     * @brief destructor de la lista enlazada
     */
    ~CustomLinkedList()
    {

    }
    /**
     * @brief agrega un elemento a la lista
     * @param info
     */
    void push_back(T info)
    {
        if(head == NULL)
        {
            head = new Node<T>;
            head->data = info;
            tail = head;
        }
        else
        {
            Node<T>* temp = new Node<T>;
            temp->data = info;
            temp->next = NULL;
            tail->next = temp;
            tail = tail->next;
        }
    }
    /**
     * @brief retorna el inicio de la lista;
     * @return
     */
    int begin(){
        return 0;
    }
    /**
     * @brief elimina un elemento de la lista
     * @param position
     */
    void erase(int position){

        Node<T>* temp = head;

        if (position == 0)
        {
            head = temp->next;
            free(temp);
            return;
        }

        for (int i=0; temp!=NULL && i<position-1; i++)
            temp = temp->next;


        if (temp == NULL || temp->next == NULL)
            return;

        Node<T> *next = temp->next->next;
        free(temp->next);
        temp->next = next;
    }
    /**
     * @brief devuelve el elemento que se encuentra en el indice pasado por paramatero
     * @param position
     * @return
     */
    T at(int position){

        Node<T>* temp = head;

        for(int i = 0; i < position; i++){
                temp = temp->next;

        }
        return temp->data;

    }
    /**
     * @brief retorna el tamano de la lista
     * @return
     */
    int size()
    {
        int count = 0;
        Node<T>* current = head;
        while (current != NULL)
        {
            count++;
            current = current->next;
        }
        return count;
    }
    /**
     * @brief imprimite todos los ementtos.
     */
    void printlist(){

        Node<T>* temp = head;

        while(temp != NULL){

            cout << temp->data << endl;
            temp = temp->next;

        }
    }
};


#endif //VSPTR_DYNAMICLIBRARY_LIST_H
