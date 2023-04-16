#include <FTBDLL.h>
#include <stdio.h>
template<typename dType> 
FTBDLL<dType>::FTBDLL(int reserve){ // FRONT TO BACK A DOUBLY LINKED LIST
    this->reserve(reserve);
    this->n_reserved = reserve;
}

template<typename dType> 
void FTBDLL<dType>::reserve(int reserve_size){
    while (n_reserved < reserve_size)
    {
        struct Node<dType> temp* = new Node<dType>;
        
        if (!n_reserved){
            this->head_node = temp;
            this->tail_node = temp;
        }else{
            this->tail_node.next = temp; // allocate node after last node
            this->tail_node = temp; // update the pointer to the last node
        }
        
        this->n_reserved++;
    }
}


template<typename dType> 
bool FTBDLL<dType>::push_back(dType data){ // O(1)
    if (this->present->next != nullptr){
        this->present->next->data = data;
        this->present = this->present->next;
        return true;
    }else{
        return false;
    }
}

template<typename dType> 
bool FTBDLL<dType>::push_front(dType data){ // O(1)
    if (this->n_reserved > this->size)
    {
        this->tail_node->next = this->head_node;
        this->head_node->prev = this->tail_node;
        this->head_node = this->tail_node;
        this->tail_node->prev->next = nullptr;
        this->tail_node = this->tail_node->prev;
        this->head_node->prev = nullptr;
        return true;
    }else{
        return false;
    }
}

template<typename dType>
void FTBDLL<dType>::clear(Node<dType> *node){ // O(1)
    if (node.prev)
    {
        node->prev->next = node->next;
    }
    if (node->next)
    {
        node->next->prev = node->prev;
    }
    node->next = nullptr;
    node->prev = this->tail_node;
    this->tail_node->next = node;
    this->tail_node = node;
    node->data = nullptr;
}


template<typename dType>
void FTBDLL<dType>::clear(Node<dType> *older_node, Node<dType> *recent_node){ // O(n)
    if (older_node->prev)  
        older_node->prev->next = recent_node->next;
    
    if (recent_node->next)
        recent_node->next->prev = older_node->prev;
    
    recent_node->next = nullptr; // free up recent next node

    older_node->prev = this->tail_node; // stitch older to tail
    this->tail_node->next = older_node;

    this->tail_node = recent_node; // update new tail

    Node<dType> *iterator = older_node; // set all data to null
    do
    {
        iterator->data = nullptr;
    } while (iterator != recent_node);

}

template<typename dType>
void FTBDLL<dType>::detach(Node<dType> *node){ // O(1)
    if (node.prev)
        node->prev->next = node->next;
    
    if (node->next)
        node->next->prev = node->prev;
    
    delete node;
}


