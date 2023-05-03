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

// CERTIFIED
template<typename dType> 
void FTBDLL<dType>::reserve(int reserve_size){
    for (auto i = 0; i < reserve_size; i++){
        // std::cout << "Reserved: "+ n_reserved );
        Node<dType> *temp = new Node<dType>;
        if (!this->n_reserved){
            this->head_node = temp;
            this->present = temp;
            this->tail_node = temp;
        }else{
            this->tail_node->next = temp; // allocate node after last node
            temp->prev = this->tail_node; // link the prev pointer to the previous tail
            this->tail_node = temp; // update the pointer to the last node
            this->tail_node->next = nullptr;
        }
        this->n_reserved++;
        
    }
}

template<typename dType> 
bool FTBDLL<dType>::insertPresent(dType data, int expand){ // O(1)

    if (this->present == this->head_node && this->size == 0){
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
            if (expand){
                this->reserve(expand);
                this->insertPresent(data, expand);
            }
            return false;
        }
    }
}

template<typename dType> 
bool FTBDLL<dType>::insertPast(dType data, int expand){ // O(1)
    if (this->size < this->n_reserved){
        if (this->present == this->tail_node){
            if (this->present->prev){
                this->present = this->present->prev;
            }
        }
        
        this->tail_node->next = this->head_node; // stitch tail and head
        this->head_node->prev = this->tail_node;

        this->head_node = this->tail_node; // make head the previous tail
        this->tail_node = this->tail_node->prev;
        this->tail_node->next = nullptr; // detach tail from its prev node

        this->head_node->prev = nullptr; // detach prev node from head

        this->head_node->data = data;
        
        this->size++;

        return true;
    }else{
        std::cout << "List is FULL" << "\n";
        if (expand){
            std::cout << "Expanding" << "\n";
            this->reserve(expand);
            this->insertPast(data, expand);
        }
        return false;
    }
}

template<typename dType>
void FTBDLL<dType>::clear(Node<dType> *node){ // O(1)

    if (node->prev){
        if (this->present == node)
        {
            this->present = this->present->prev;
        }
        if (node != this->tail_node){
            node->prev->next = node->next;
        }       
    }

    if (node->next) {
        node->next->prev = node->prev;
        if (this->head_node == node){
            if (this->head_node == this->present){
                this->present = this->present->next;
            }
            this->head_node = this->head_node->next;
        }    
    }

    node->next = nullptr;
    if(node != this->tail_node){ // Make sure it's not the tail to prevent a self reference and detachment
        node->prev = this->tail_node;
        this->tail_node->next = node;
        this->tail_node = node;
    }
    node->data = dType();
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
// -------------------------------


    if (older_node->prev){
        if (this->present == older_node)
        {
            this->present = this->present->prev;
        }
        if (recent_node != this->tail_node){
            older_node->prev->next = node->next;
        }       
    }

    if (recent_node->next) {
        recent_node->next->prev = older_node->prev;
        if (this->head_node == older_node){
            if (this->head_node == this->present){
                this->present = this->present->next;
            }
            this->head_node = this->head_node->next;
        }    
    }

    recent_node->next = nullptr;
    if(recent_node != this->tail_node){ // Make sure it's not the tail to prevent a self reference and detachment
        older_node->prev = this->tail_node;
        this->tail_node->next = older_node;
        this->tail_node = recent_node;
    }

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
        std::cout << long(i) % 100 <<":"<<(i==this->present ? "[" : "")<<"("<<i->data <<")" << (i==this->present ? "]" : "");
        if (i->next != nullptr){
            std::cout << "->";
        }
        i = i->next;
    }
    std::cout << " Occ: " << this->size <<" Avb: " << this->n_reserved-this->size << "\n";
}

template<typename dType>
int FTBDLL<dType>::getSize(){ // O(1)
    return this->size;
}

template<typename dType> // CERTIFIED
bool FTBDLL<dType>::isFull(){ // O(1)
    return this->present == this->tail_node && this->size == this->n_reserved;
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


template<typename dType>
void FTBDLL<dType>::clearPast() {
    this->clear(this->head_node);
}


template<typename dType>
void FTBDLL<dType>::clearPresent() {
    this->clear(this->present);

}

template<typename dType>
bool FTBDLL<dType>::areLinked(Node<dType> *older_node, Node<dType> *recent_node){

}