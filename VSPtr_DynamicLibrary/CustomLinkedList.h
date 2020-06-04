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

    CustomLinkedList()
    {
        head = NULL;
        tail = NULL;
    }

    ~CustomLinkedList()
    {

    }

    //Method adds info to the end of the list
    void push_back(T info)
    {
        if(head == NULL) //if our list is currently empty
        {
            head = new Node<T>; //Create new node of type T
            head->data = info;
            tail = head;
        }
        else //if not empty push_back to the end and move the tail
        {
            Node<T>* temp = new Node<T>;
            temp->data = info;
            temp->next = NULL;
            tail->next = temp;
            tail = tail->next;
        }
    }

    int begin(){
        return 0;
    }

    void erase(int position){

        Node<T>* temp = head;

        // If head needs to be removed
        if (position == 0)
        {
            head = temp->next;   // Change head
            free(temp);               // free old head
            return;
        }


        // Find previous node of the node to be deleted
        for (int i=0; temp!=NULL && i<position-1; i++)
            temp = temp->next;

        // If position is more than number of ndoes
        if (temp == NULL || temp->next == NULL)
            return;

        // Node temp->next is the node to be deleted
        // Store pointer to the next of node to be deleted
        Node<T> *next = temp->next->next;

        // Unlink the node from linked list
        free(temp->next);  // Free memory

        temp->next = next;  // Unlink the deleted node from list
    }

    T at(int position){

        Node<T>* temp = head;

        for(int i = 0; i < position; i++){
                temp = temp->next;

        }
        return temp->data;

    }

    int size()
    {
        int count = 0; // Initialize count
        Node<T>* current = head; // Initialize current
        while (current != NULL)
        {
            count++;
            current = current->next;
        }
        return count;
    }


    void printlist(){

        Node<T>* temp = head;

        while(temp != NULL){

            cout << temp->data << endl;
            temp = temp->next;

        }
    }

    //print method omitted
};


#endif //VSPTR_DYNAMICLIBRARY_LIST_H
