//
// Created by josh on 1/21/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sll.h"


SLL *newSLL(void (*d)(void *,FILE *fp),void (*f)(void *items)) {
        SLL *items = malloc(sizeof(SLL));
        assert(items != 0);
        items->head = 0;
        items->tail = 0;
        items->size = 0;
        items->display = d;
        items->free = f;
        return items;
}
NODE *newnode(void *value){
    NODE *m_node = malloc(sizeof(NODE));
    assert(m_node != 0);
    m_node->value = value;
    m_node->next = 0;
    //printf("Created new node");
    return m_node;
}
void insertSLL(SLL *items,int index,void *value){
    assert(index >= 0 && index <= sizeSLL(items));
    NODE *node = newnode(value);
    //printf("Inserting At Index %d\n", index);
    if (index == 0)
    {
//		puts("Im in insertSLL index == 0");
       // printf("Debug 1 index = %d\n", index);
        if(sizeSLL(items) != 0)
        {
//			puts("Im in if sizeSLL(items) != 0");
            node->next = items->head;
            items->head = node;
        }
        else
        {
//			puts("in insert else statement");
//			printf("value =%d\n",(int *) value);
            items->head = node;
        }
    }
    else if(index == sizeSLL(items))
    {
        NODE * temp = items->tail;
        temp-> next = node;
    }
    else
    {
        int i = 0;
        NODE *current = items->head;
        for(i = 0; i < index - 1; i++)
        {
            current = current->next;
        }
        node->next = current->next;
        current->next = node;
    }
    if(index == sizeSLL(items))
    {
        items->tail = node;
    }
    items->size++;
}

void *removeSLL(SLL *items,int index){
    assert(sizeSLL(items) > 0 && index >= 0);
    NODE *curr = items->head;
    void *returnValue = 0;

    if (index == 0)
    {
        returnValue = curr->value;
//        printf("index equals head\n");
        if (sizeSLL(items) > 1)
        {
            items->head = curr->next;
//            items->head = curr;
            free(curr);
        }
        else
        {
            items->head = 0;
            items-> tail = 0;
            items->size = 0;
            free(curr);
            return returnValue;
        }

    }
    else
    {
//        printf("\nIndex equals %d\n", index);
        for (int i=0; i < index - 1; i++){
            curr = curr->next;
        }
        returnValue = curr->next->value;
        //printf("The return value is %f\n", *(double*) returnValue);
        if(index == sizeSLL(items) - 1)
        {
            items->tail = curr;
            free(curr->next);
            curr->next=0;
        }
        else
        {
            NODE *removedNode = curr->next;
            curr->next = removedNode->next;
            //free(curr->value);
            //free(curr);
            //curr->next= curr->next->next;
        }
    }

    items->size--;
    return returnValue;
}

void unionSLL(SLL *recipient,SLL *donor){

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
        recipient->tail = donor->tail;
        recipient->size+= donor->size;
        donor->tail =0; donor->head = 0;
    }
    donor->size = 0;
}

void *getSLL(SLL *items,int index){
    assert(index >= 0);
    NODE *node = items->head;
    if (index == sizeSLL(items)-1)
        return items->tail->value;
    for(int i = 0; i<index;i++)
    {
        node = node->next;
    }
    return node->value;
}

void *setSLL(SLL *items,int index,void *value){
    assert(index >= 0 && index <= sizeSLL(items));
    NODE *curr = items->head;
    void * returnvalue=0;
    if (index == sizeSLL(items)){
        insertSLL(items,index,value);
        return NULL;
    }
    else if(index == sizeSLL(items)-1){
        returnvalue=items->tail->value;
        items->tail->value = value;
    }
    else
    {
        for(int i=0; i<index; i ++){
            curr = curr->next;
        }
        returnvalue = curr->value;
        curr->value = value;
    }

    return returnvalue;
}

int sizeSLL(SLL *items){
    return items->size;
}

void displaySLL(SLL *items,FILE *fp){
    //printf("Beginning Display\n");
    if(items->head == 0)
    {
        fprintf(fp,"{}");
        return;
    }
    NODE *curr = items->head;
    fprintf(fp,"{");
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
    fprintf(fp,"}");
}

void displayFormatq(SLL *items,FILE *fp){
    if(items->head == 0)
    {
        fprintf(fp,"<>");
        return;
    }
    NODE *curr = items->head;
    fprintf(fp,"<");
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
    fprintf(fp,">");
}
void displaySLLdebug(SLL *items,FILE *fp){
    if (items->size == 0) {
        fprintf(fp, "head->{},tail->{}");
    }
    else {
        NODE *curr = items->head;
        fprintf(fp, "head->{");
        while (curr != 0) {
            items->display(curr->value, fp);
                if (curr->next != 0)
                    fprintf(fp, ",");
            curr = curr->next;
    }
        fprintf(fp,"},tail->{");
        //printf("Tail Value = %d", *(int*)items->tail->value);

        items->display(items->tail->value, fp);
        fprintf(fp, "}");
    }

}
void freeSLL(SLL *items){
    NODE * curr;

    while (items->head != 0)
    {
        curr = items->head;
        items->head = items->head->next;
        if (items->free != 0)
            items->free(curr->value);
        free(curr);
    }
    items->tail=NULL;
    free(items);
   }
