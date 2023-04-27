#include "FTBDLL.h"

template<typename dType> 
FTBDLL<dType>::FTBDLL(int reserve){ // FRONT TO BACK A DOUBLY LINKED LIST
    this->reserve(reserve);
}

template<typename dType> 
FTBDLL<dType>::~FTBDLL(){ // FRONT TO BACK A DOUBLY LINKED LIST
    Node<dType>* it = this->head_node;
    Node<dType>* temp;
    while(it){
        temp = it;
        it = it->next;
        delete temp;
    }
}
template<typename dType> 
void FTBDLL<dType>::reserve(int reserve_size){
    for (auto i = 0; i < reserve_size; i++){
        // std::cout << "Reserved: "+ n_reserved );
        Node<dType> *temp = new Node<dType>;
        if (!n_reserved){
            this->head_node = temp;
            this->present = temp;
            this->tail_node = temp;
        }else{
            this->tail_node->next = temp; // allocate node after last node
            this->tail_node = temp; // update the pointer to the last node
            this->tail_node->next = nullptr;
        }
        this->n_reserved++;
        
    }
}

template<typename dType> 
bool FTBDLL<dType>::push_back(dType data){ // O(1)
//          std::cout << "Head:"<<this->head_node<< "Present:"<<long(this->present) << "\nTail:"+long(this->tail_node);

    if (this->size == 0){
        this->present->data = data;
        this->size++;
        return true;
    } 
    else{
        if (this->present->next != nullptr){

            this->present = this->present->next;
            this->present->data = data;
            this->size++;

            return true;
        }else{
            return false;
        }
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
        this->head_node->data = data;
                    std::cout << "Size:"+this->size << "\n";

        this->size++;
            std::cout << "Size:"+this->size << "\n";

        return true;
    }else{
        return false;
    }
}

template<typename dType>
void FTBDLL<dType>::clear(Node<dType> *node){ // O(1)
    if (node->prev)
        node->prev->next = node->next;
    if (node->next) 
        node->next->prev = node->prev;

    node->next = nullptr;
    node->prev = this->tail_node;
    this->tail_node->next = node;
    this->tail_node = node;
    node->data = nullptr;
    this->size--;

}


template<typename dType>
void FTBDLL<dType>::clear(Node<dType> *older_node, Node<dType> *recent_node){ // O(n)
    if (older_node->prev)  
        older_node->getPrev->getNext = recent_node->next;
    
    if (recent_node->next)
        recent_node->next->prev = older_node->prev;
    
    recent_node->next = nullptr; // free up recent next node

    older_node->prev = this->tail_node; // stitch older to tail
    this->tail_node->next = older_node;

    this->tail_node = recent_node; // update new tail

    for (Node<dType>* i = older_node; i!=recent_node ; ) {
        i->data = dType();
        this->size--;
        i = i->next;
    }

}

template<typename dType>
void FTBDLL<dType>::detach(Node<dType> *node){ // O(1)
    if (node->prev)
        node->prev->next = node->next;
    
    if (node->next)
        node->next->prev = node->prev;
    
    delete node;
}

template<typename dType>
void FTBDLL<dType>::display(){ // O(1)
    
    std::cout << "\nList:"<< "\n";
    for(Node<dType>* i = this->head_node; i!=nullptr;){
        std::cout << long(i) % 100 <<":"<<i->data;
        if (i->next != nullptr){
            std::cout << "->\n";
        }
        i = i->next;
    }
    std::cout << " Occ: " << this->size <<" Avb: " << this->n_reserved-this->size << "\n";
}

template<typename dType>
int FTBDLL<dType>::getSize(){ // O(1)
    return this->size;
}

template<typename dType>
bool FTBDLL<dType>::isFull(){ // O(1)
    return this->size==this->n_reserved;
}

template<typename dType>
void FTBDLL<dType>::detach(Node<dType> *older_node, Node<dType> *recent_node) {

}

template<typename dType>
void FTBDLL<dType>::emptyList() {
    for(Node<dType>* i = this->present; i!=nullptr;){
        i->data = dType();
        i = i->prev;
    }
    this->size = 0;
    this->present = this->head_node;
}
