#include <iostream>

//using namespace std;

struct Node{
    Node * next;
    Node * prev;
    int id;
    int size;
    int index;
};

class HeapManager{
private:
    Node * head;
    Node * tail;
public:
    int initHeap(int size);
    int myMalloc(int ID, int size);
    int myFree(int ID, int index);
    void print();
};

int HeapManager::initHeap(int size){
    Node * node = new Node();
    node->id = -1;
    node->size = size;
    node->index = 0;
    head = node;
    tail = node;
    std::cout << "Memory initialized" << std::endl;
    std::cout << "[-1][" << size << "][0]" << std::endl;
    return 1;
}

int HeapManager::myMalloc(int ID, int size){
    Node * ptr = head;
    while(ptr != NULL){
        if(ptr->size > size && ptr->id == -1){
            break;
        }
        ptr = ptr->next;
    }
    if(ptr != nullptr){
        int currindex = ptr->index;
        std::cout << "Allocated for thread " << ID;
        if(ptr == head){
            Node * insertt = new Node();
            insertt->id = ID;
            insertt->size = size;
            insertt->index = 0;
            insertt->next = head;
            head->prev = insertt;
            head->index = size;
            head->size = head->size - size;
            head = insertt;
            return 0;
        }
        else{
            Node * insertt = new Node();
            insertt->id = ID;
            insertt->size = size;
            insertt->index = currindex;
            ptr->index = ptr->index + size;
            ptr->size = ptr->size - size;
            if(ptr->prev != nullptr){
                ptr->prev->next = insertt;
            }
            insertt->prev = ptr->prev;
            ptr->prev = insertt;
            insertt->next = ptr;
            return currindex;
        }
    }
    else{
        return -1;
    }
}

void HeapManager::print(){
    Node * ptr = head;
    while(ptr != nullptr){
        std::cout << "[" << ptr->id << "][" << ptr->size << "][" << ptr->index << "]\n";
    }
}

int HeapManager::myFree(int ID, int index){
    Node * ptr = head;
    while(ptr != nullptr){
        if(ptr->id == ID && ptr->index == index){
            break;
        }
        ptr = ptr->next;
    }
    if(ptr != nullptr){
        std::cout << "Freed for thread" << ID << std::endl;
        if(ptr->prev != nullptr && ptr->next != nullptr && ptr->prev->id == -1 && ptr->next->id == -1){ // sagi solu bossa birlescekken
            Node * temp = ptr->prev;
            temp->size = temp->size + ptr->size + ptr->next->size;
            temp->next = ptr->next->next;
            if(ptr->next->next != nullptr){
                ptr->next->next->prev = temp;
            }
            delete ptr->next;
            delete ptr;
        }
        else if(ptr->prev != nullptr && ptr->prev->id == -1){ //solla birlescekse
            Node * temp = ptr->prev;
            temp->size = temp->size + ptr->size;
            temp->next = ptr->next;
            if(ptr->next != nullptr){
                ptr->next->prev = temp;
            }
            delete ptr;
        }
        else if(ptr->next != nullptr && ptr->next->id == -1){// sag tarafla birlesecekse
            ptr->size = ptr->size + ptr->next->size;
            ptr->id = -1;
            Node * temp = ptr->next;
            ptr->next = temp->next;
            if(temp->next != nullptr){
                temp->next->prev = ptr;
            }
            delete temp;
        }
        else{
            ptr->id = -1;
        }
        print();
        return 1;
    }
    else{
        print();
        return -1;
    }
}
