//
// Created by jrstringfellow on 2/4/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dll.h"

//struct dll {
//    NODE *head;
//    NODE *tail;
//    int size;
//    void (*display)(void *, FILE *);
//    void *free;
//};

DLL *newDLL(void (*d)(void *,FILE *),void (*f)(void *))
{
    DLL *items = malloc(sizeof(DLL));
    assert(items != 0);
    items->head = 0;
    items->tail = 0;
    items->size = 0;
    items->display = d;
    items->free = f;
    return items;
}

NODE *newDLLnode(void *value){
    NODE *m_node = malloc(sizeof(NODE));
    assert(m_node != 0);
    m_node->value = value;
    m_node->next = 0;
    m_node->prev = 0;
    //printf("Created new node");
    return m_node;
}
void insertDLL(DLL *items,int index,void *value){
    assert(index >= 0 && index <= sizeDLL(items));
    NODE *node = newDLLnode(value);
    //printf("Inserting At Index %d\n", index);
    if (index == 0)
    {
//		puts("Im in insertDLL index == 0");
        // printf("Debug 1 index = %d\n", index);
        if(sizeDLL(items) != 0)
        {
            NODE *temp = items->head;
            node->next = items->head;
            temp->prev= node;
        }

        items->head = node;

    }
    else if(index == sizeDLL(items))
    {
        NODE * temp = items->tail;
        temp-> next = node;
        node->prev = items->tail;
    }
    else
    {
        NODE *curr = items->head;
        if (index<sizeDLL(items)/2){
            for(int i=0; i<index -1; i ++){
                curr = curr->next;
            }
        }
        else{
            curr = items->tail;
            for(int i=sizeDLL(items); i>index; i --){
                curr = curr->prev;
            }
        }
        node->next = curr->next;
        node->prev = curr;
        curr->next = node;
        node->next->prev = node;

    }
    if(index == sizeDLL(items))
    {
        items->tail = node;
    }

   // displayDLLdebug(items,stdout);
    items->size++;
}

void *removeDLL(DLL *items,int index)
{
    if (items->size == 0)
    {
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    NODE *curr = items->head;
    void * retValue;
    if(index == 0)
    {
        retValue = items->head->value;
        //printf("value is: %d\n\n", *(int*)ptr->value);
        if(sizeDLL(items) != 1)
        {
            items->head = curr->next;
            free(curr);
            items->head->prev = 0;
        }
        else
        {
            items->head = 0;
            items->tail = 0;
            free(curr);
        }
    }
    else if(index == sizeDLL(items) || index == sizeDLL(items) - 1)
    {
        //puts("\nim in index == sizeDLL(items");
        retValue = items->tail->value;

        if(sizeDLL(items) != 1)
        {
            items->tail = items->tail->prev;
            free(items->tail->next);
            items->tail->next = 0;
        }
        else
        {
            items->head = 0;
            items->tail = 0;
            free(curr);
        }
    }
    else
    {
        //puts("in for loop search");
        if (index<sizeDLL(items)/2){
            for(int i=0; i<index; i ++){
                curr = curr->next;
            }
        }
        else{
            curr = items->tail;
            for(int i=items->size; i>index+1; i --){
                curr = curr->prev;
            }
        }
        curr->next->prev= curr->prev;
        curr->prev->next = curr->next;

        retValue = curr->value;
        free(curr);
    }
    items->size--;
    return retValue;
}

void unionDLL(DLL *recipient,DLL *donor){
    if(recipient->head ==0 && recipient->tail ==0)
    {
        if(donor->head != 0 && donor->tail != 0)
        {
            recipient->head= donor->head;
            recipient->tail = donor->tail;
            recipient->size+= donor->size;
            donor->tail =0; donor->head = 0;
        }
    }
    else if(donor->head != 0 && donor->tail != 0){
//		puts("in donor->head != 0 && donor->tail != 0 statment");
        recipient->tail->next = donor->head;
        donor->head->prev = recipient->tail;
        recipient->tail = donor->tail;
        recipient->size+= donor->size;
        donor->tail =0; donor->head = 0;
    }
    donor->size = 0;

}

void *getDLL(DLL *items,int index){
    NODE *curr = items->head;
    if (index == sizeDLL(items)-1)
        return items->tail->value;
    if (index<sizeDLL(items)/2){
        for(int i=0; i<index; i ++){
            curr = curr->next;
        }
    }
    else{
        curr = items->tail;
        for(int i=sizeDLL(items); i>index +1; i --){
            curr = curr->prev;
        }
    }
    return curr->value;
}

void *setDLL(DLL *items,int index,void *value){
    assert(index >= 0 && index <= sizeDLL(items));
    NODE *curr = items->head;
    void *returnvalue=0;
    if (index == sizeDLL(items)){
        insertDLL(items,index,value);
        return NULL;
    }
    else
    {
        if (index<sizeDLL(items)/2){
            for(int i=0; i<index; i ++){
                curr = curr->next;
            }
        }
        else{
            curr = items->tail;
            for(int i=sizeDLL(items); i>index +1; i --){
                curr = curr->prev;
            }
        }
        returnvalue=curr->value;
        curr->value = value;
    }

    return returnvalue;
}

int sizeDLL(DLL *items){
    return items->size;
}

void displayDLL(DLL *items,FILE *fp){
    //printf("Beginning Display\n");
    if(items->head == 0)
    {
        fprintf(fp,"{{}}");
        return;
    }
    NODE *curr = items->head;
    fprintf(fp,"{{");
    for(int i = 0; i < items->size; i++)
    {
        if(i == items->size - 1 )
        {
            items->display( curr->value, fp);
        }
        else
        {
            items->display(curr->value, fp);
            fprintf(fp,",");
        }
        curr = curr->next;
    }
    fprintf(fp,"}}");
}

void displayFormats(DLL *items,FILE *fp){
    if(items->head == 0)
    {
        fprintf(fp,"||");
        return;
    }
    NODE *curr = items->head;
    fprintf(fp,"|");
    for(int i = 0; i < items->size; i++)
    {
        if(i == items->size - 1 )
        {
            items->display( curr->value, fp);
        }
        else
        {
            items->display(curr->value, fp);
            fprintf(fp,",");
        }
        curr = curr->next;
    }
    fprintf(fp,"|");
}
void displayDLLdebug(DLL *items,FILE *fp){
    if (items->size == 0) {
        fprintf(fp, "head->{{}},tail->{{}}");
    }
    else {
        NODE *curr = items->head;
        fprintf(fp, "head->{{");
        while (curr != 0) {
            items->display(curr->value, fp);
            if (curr->next != 0)
                fprintf(fp, ",");
            curr = curr->next;
        }
        fprintf(fp,"}},tail->{{");
        curr = items->tail;
        items->display(curr->value, fp);
        fprintf(fp, "}}");
    }
}
void freeDLL(DLL *items){
    NODE * curr;

    while (items->head != 0)
    {
        curr = items->head;
        items->head = items->head->next;
        if(items->free !=0)
            items->free(curr->value);
        free(curr);
    }
    items->tail=NULL;
    free(items);
}