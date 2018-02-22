//
// Created by jrstringfellow on 2/12/18.
//

#include <stdlib.h>
#include "heap.h"


HEAP *newHEAP(
        void (*display)(void *,FILE *),    //display
        int (*compare)(void *,void *),     //compare
        void (*free)(void *)){
    HEAP *newHeap = malloc(sizeof(HEAP));
    newHeap->value=0;
    newHeap->left=0;
    newHeap->right=0;
    newHeap->parent=0;
}          //free
void insertHEAP(HEAP *h,void *value){}
void buildHEAP(HEAP *h){}
void *peekHEAP(HEAP *h){}
void *extractHEAP(HEAP *h){}
int  sizeHEAP(HEAP *h){}
void displayHEAP(HEAP *h,FILE *fp){}
void displayHEAPdebug(HEAP *h,FILE *fp){}
void freeHEAP(HEAP *h){}