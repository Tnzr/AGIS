#pragma once

template<typename dType> struct Node
{
    dType data;
    Node<dType> *next;
    Node<dType> *prev;
    bool occupied = false;
    Node(){
        this->next = nullptr;
        this->prev = nullptr;
        this->data = false;
    }
    Node(dType data, Node<dType> *next, Node<dType> *prev){
        this->data = data;
        this->next = next;
        this->prev = prev;
        this->data = true;

    }
};
