//
// Created by jrstringfellow on 2/5/18.
//
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


struct stack{
    DLL *list;
    void (*display)(void *, FILE *);
    void (*free)(void *);
}stack;

STACK *newSTACK(void (*d)(void *,FILE *),void (*f)(void *)){
    STACK *items =malloc(sizeof(STACK));
    items->list = newDLL(d,f);
    items->display = d;
    items->free = f;
    return items;
}
void push(STACK *items,void *value){
    insertDLL(items->list,0,value);
}
void *pop(STACK *items){
    void *value = removeDLL(items->list,0);
    return value;
}
void *peekSTACK(STACK *items){
    return getDLL(items->list,0);
}
int sizeSTACK(STACK *items){ return sizeDLL(items->list);}

void displaySTACK(STACK *items,FILE *fp){
    fprintf(fp,"|");
    for(int i=0; i<sizeSTACK(items); i++){
        items->display(getDLL(items->list,i),fp);
        if (i < sizeSTACK(items)-1)
            fprintf(fp,",");
    }
    fprintf(fp,"|");
}


void displaySTACKdebug(STACK *items,FILE *fp){displayDLLdebug(items->list,fp);}
void freeSTACK(STACK *items){freeDLL(items->list);
free(items);}