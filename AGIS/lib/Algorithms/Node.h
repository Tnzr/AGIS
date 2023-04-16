#pragma once

template<typename dType> struct Node
{
    dType data;
    struct Node<dType> *next;
    struct Node<dType> *prev;
};
