//
// Created by jrstringfellow on 2/5/18.
//

#ifndef __QUEUE_INCLUDED__
#define __QUEUE_INCLUDED__

#include <stdio.h>
#include "sll.h"

typedef struct queue{
    SLL *list;
    void (*display)(void *, FILE *);
    void (*free)(void *);
} QUEUE;

extern QUEUE *newQUEUE(void (*d)(void *,FILE *),void (*f)(void *));
extern void enqueue(QUEUE *items,void *value);
extern void *dequeue(QUEUE *items);
extern void *peekQUEUE(QUEUE *items);
extern int sizeQUEUE(QUEUE *items);
extern void displayQUEUE(QUEUE *items,FILE *);
extern void displayQUEUEdebug(QUEUE *items,FILE *);
extern void freeQUEUE(QUEUE *items);

#endif