#pragma once

template<typename dType> struct Node
{
    dType data;
    Node<dType> *next;
    Node<dType> *prev;

    Node(){
        this->next = nullptr;
        this->prev = nullptr;
    }
    Node(dType data, Node<dType> *next, Node<dType> *prev){
        this->data = data;
        this->next = next;
        this->prev = prev;
    }
};
