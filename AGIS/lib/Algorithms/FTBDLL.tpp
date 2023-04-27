#include "FTBDLL.h"


template<typename dType> 
FTBDLL<dType>::FTBDLL(int reserve){ // FRONT TO BACK A DOUBLY LINKED LIST
    this->reserve(reserve);
    this->n_reserved = reserve;
    this->size = 0;
}

template<typename dType> 
FTBDLL<dType>::~FTBDLL(){ // FRONT TO BACK A DOUBLY LINKED LIST

}
template<typename dType> 
void FTBDLL<dType>::reserve(int reserve_size){
    for (auto i = 0; i < reserve_size; i++){
        // Serial.println("Reserved: "+ n_reserved );
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
          Serial.println("Head:"+String(long(this->head_node)));
          Serial.println("Present:"+String(long(this->present)));
          Serial.println("Tail:"+String(long(this->tail_node)));

    if (this->size == 0){
        Serial.println("Present:"+String(this->present->data));
        Serial.println("Size:"+String(this->size));

        this->present->data = data;


        this->size++;
        Serial.println("Present:"+String(this->present->data));
        Serial.println("Size:"+String(this->size));

        return true;
    } 
    else{
        if (this->present->next != nullptr){
            Serial.println("Size > 0");
            Serial.println("Present:"+String(this->present->data));
            Serial.println("Size:"+String(this->size));
            this->present = this->present->next;
            this->present->data = data;
            this->size++;
            Serial.println("Present:"+String(this->present->data));
            Serial.println("Size:"+String(this->size));

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
                    Serial.println("Size:"+this->size);

        this->size++;
            Serial.println("Size:"+this->size);

        return true;
    }else{
        return false;
    }
}

template<typename dType>
void FTBDLL<dType>::clear(Node<dType> *node){ // O(1)
    if (node.prev) 
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

    Node<dType> *iterator = older_node; // set all data to null
    do
    {
        iterator->data = nullptr;
        this->size--;

    } while (iterator != recent_node);
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
    
    Serial.println("List:");
    for(Node<dType>* i = this->head_node; i!=nullptr;){
    // for(Node<dType>* i = this->head_node; this->head_node!=this->tail_node;){
        Serial.print(String(long(i))+":"+String(i->data));
        if (i->next != nullptr){
            Serial.print("->");
        }
        i = i->next;
    }
    Serial.println(" Occ: "+String(this->size)+" Avb: "+String(this->n_reserved-this->size));
}

template<typename dType>
int FTBDLL<dType>::getSize(){ // O(1)
    return this->size;
}

template<typename dType>
bool FTBDLL<dType>::isFull(){ // O(1)
    return this->size==this->n_reserved;
}

