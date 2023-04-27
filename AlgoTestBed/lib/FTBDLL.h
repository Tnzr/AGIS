#pragma once
#include "Node.h"
#include <iomanip>
template<typename dType> 
class FTBDLL{ // Front to Back Doubly Linked List
    private:
        Node<dType> *head_node;
        Node<dType> *present;
        Node<dType> *tail_node;
        int n_reserved=0; // reserved instances
        int size=0; // in use
    public:
        FTBDLL(int reserve=1);
        ~FTBDLL();
        void reserve(int reserve_size=1);
        void display();
        bool push_back(dType data); // after last valid node
        bool push_front(dType data); // before head node
        void clear(Node<dType> *node); // clear data and stitch sorrounding nodes
        void clear(Node<dType> *older_node, Node<dType> *recent_node); // 
        void detach(Node<dType> *node); // clear data and stitch sorrounding
        void detach(Node<dType> *older_node, Node<dType> *recent_node);
        bool isFull();
        void emptyList();
        int getSize();

};
#include "FTBDLL.cpp"
