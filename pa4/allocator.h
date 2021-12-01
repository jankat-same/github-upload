//
//  allocator.h
//  pa4
//
//  Created by Jankat Yaşar on 1.06.2021.
//

#ifndef allocator_h
#define allocator_h

struct Node{
    Node * next;
    Node * prev;
    int id;
    int size;
    int index;
};

class allocator{
private:
    Node * head;
    Node * tail;
public:
    int initHeap(int size);
    int myMalloc(int ID, int size);
    int myFree(int ID, int index);
    void print();
};

#endif /* allocator_h */
