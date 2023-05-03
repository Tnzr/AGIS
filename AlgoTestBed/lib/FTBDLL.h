#pragma once
#include "Node.h"
// #include <iomanip>
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
        bool insertPresent(dType data, int expand = 0); // after last valid node
        bool insertPast(dType data, int expand = 0); // before head node
        void clear(Node<dType> *node); // clear data and stitch sorrounding nodes
        void clear(Node<dType> *older_node, Node<dType> *recent_node); // 
        void detach(Node<dType> *node); // clear data and stitch sorrounding
        void detach(Node<dType> *older_node, Node<dType> *recent_node);
        bool isFull();
        void clearPast();
        void clearPresent();
        void emptyList();
        int getSize();
        static bool areLinked(Node<dType> *older_node, Node<dType> *recent_node);

};

#include "FTBDLL.tpp"
