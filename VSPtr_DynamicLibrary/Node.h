//
// Created by heutlett on 4/6/20.
//

#ifndef VSPTR_DYNAMICLIBRARY_NODE_H
#define VSPTR_DYNAMICLIBRARY_NODE_H

template <class T> class Node
{
public:
    T data; //the object information
    Node* next; //pointer to the next node element
};

#endif //VSPTR_DYNAMICLIBRARY_NODE_H
