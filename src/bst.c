//
// Created by jrstringfellow on 2/15/18.
//

#include <stdlib.h>
#include "bst.h"

struct bstnode{
    void *value;
    BSTNODE *parent;
    BSTNODE *right;
    BSTNODE *left;
};

BSTNODE *newBSTNODE(void *v){
    BSTNODE *newNode = malloc(sizeof(BSTNODE));
    newNode->value = v;
    newNode->parent=newNode;
    newNode->right=NULL;
    newNode->left=NULL;
    return newNode;
}

void *getBSTNODEvalue(BSTNODE *n){
    if (n!= NULL)
        return n->value;
    return NULL;
}

void setBSTNODEvalue(BSTNODE *n,void *value){
    if (n != NULL)
        n->value = value;
}

BSTNODE *getBSTNODEleft(BSTNODE *n){
    if (n != NULL && n->left != NULL)
        return n->left;
    return NULL;
}

void setBSTNODEleft(BSTNODE *n,BSTNODE *replacement){
    replacement->parent = n;
    if (n->left != NULL){
        replacement->left = n->left->left;
        replacement->right = n->left->right;
        replacement->left->parent = replacement;
    }
    n->left = replacement;

}

BSTNODE *getBSTNODEright(BSTNODE *n){
    return n->right;
}

void setBSTNODEright(BSTNODE *n,BSTNODE *replacement){
    if (n->right != NULL){
        replacement->left = n->right->left;
        replacement->right = n->right->right;
        replacement->left->parent = replacement;
    }
    n->right = replacement;
}

BSTNODE *getBSTNODEparent(BSTNODE *n){
    return n->parent;
}

void setBSTNODEparent(BSTNODE *n,BSTNODE *replacement){
    //set the parent of node n
    if (n->parent->left == n){
        replacement->left = n;
        replacement->right = n->parent->right;
        replacement->parent = n->parent->parent;
        free(n->parent);
        n->parent = replacement;
    }
}

void freeBSTNODE(BSTNODE *n,void (*f)(void *)){
   // printf("Deleting node with value %d \n", *(int *)n->value);
    if (f)
        f(n->value);
    free(n);
}


struct bst{
    void (*display)(void *,FILE *);           //display
    int (*comparator)(void *,void *);           //comparator
    void (*swapper)(BSTNODE *,BSTNODE *);     //swapper
    void (*free)(void *);                 //free

    BSTNODE *root;
    int size;
};


BST *newBST(
        void (*display)(void *,FILE *),           //display
        int (*comparator)(void *,void *),            //comparator
        void (*swapper)(BSTNODE *,BSTNODE *),     //swapper
        void (*free)(void *)){
    BST *newBST = malloc(sizeof(BST));
    newBST->display = display;
    newBST->comparator = comparator;
    newBST->swapper = swapper;
    newBST->free = free;

    newBST->root = NULL;
    newBST->size = 0;

    return newBST;
}

BSTNODE *getBSTroot(BST *t){
    return t->root;
}

void setBSTroot(BST *t,BSTNODE *replacement){
    replacement ->right = t->root->right;
    replacement->left = t->root->left;
    free(t->root);
}

void setBSTsize(BST *t,int s){
    t->size = s;
}

BSTNODE *insert(BSTNODE *node, void *key, int (*compare)(void *, void *) ){
    if (node == NULL) return newBSTNODE(key);

    if (compare(key, node->value) < 0){
        BSTNODE *leftChild  = insert(node->left, key, compare);
        node->left = leftChild;
        leftChild->parent = node;

    }

    else if (compare(key, node->value) > 0){
        BSTNODE *rightChild = insert(node->right, key, compare);
        node->right =rightChild;
        rightChild->parent = rightChild;
    }


    return node;
}

BSTNODE *insertBST(BST *t,void *value){
    if(t->size == 0){
        BSTNODE *inserted = newBSTNODE(value);
        t->root = inserted;
        t->size++;
        return inserted;
    }
    t->size++;
    return insert(t->root, value, t->comparator);
}

BSTNODE *recuriveSearch(BSTNODE *current, void *value, int (*comparator)(void *,void * )){
    if (current == NULL)
        return NULL;
    if (comparator(current->value, value) == 0)
        return current;
    if(comparator(current->value,value) < 0)
        current = recuriveSearch(current->right, value, comparator);
    else if (comparator(current->value,value)>0)
        current = recuriveSearch(current->left, value, comparator);
    return current;
}

BSTNODE *findBST(BST *t,void *value){
    if (t->root == NULL)
        return NULL;
    BSTNODE *curr = t->root;
    return recuriveSearch(curr, value, t->comparator);
}



BSTNODE *deleteBST(BST *t,void *value){
    BSTNODE *deleted = findBST(t, value);
    deleted = swapToLeafBST(t, deleted);
    pruneLeafBST(t, deleted);
    return deleted;

}

BSTNODE *swapToLeafBST(BST *t,BSTNODE *node){
    BSTNODE *temp = node;
    if(node->left == 0 && node->right == 0)
    {
        return node;
    }
    else if(temp->left != 0)
    {
        temp = temp->left;
        while(temp->right != 0)
        {
            temp = temp->right;
        }
    }
    else if(temp->right != 0)
    {
        temp = temp->right;
        while(temp->left != 0)
        {
            temp = temp->left;
        }
    }
    void *tempVal = temp->value;
    temp->value = node->value;
    node->value = tempVal;

    return swapToLeafBST(t,temp);
}

void pruneLeafBST(BST *t,BSTNODE *node){
    if(node->parent != node)
    {
        if(node->parent->left != 0 && node->parent->left->value == node->value)
        {
            node->parent->left = 0;
        }
        else if(node->parent->right != 0 && node->parent->right->value == node->value)
        {
            node->parent->right = 0;
        }
    }
    else{
        t->root = 0;
    }
    t->size--;
}

int  sizeBST(BST *t){
    return t->size;
}

int findMin(BSTNODE *node)
{
    if(node == NULL)
    {
        return -1;
    }
    int i = findMin(node->left) + 1;
    int a = findMin(node->right) + 1;
    return i < a? i : a;
}

int findMax(BSTNODE *node)
{
    if(node == NULL)
    {
        return -1;
    }
    int i = findMax(node->left) + 1;
    int a = findMax(node->right) + 1;
    if(i>a)
        return i;
    return a;
}

void statisticsBST(BST *t,FILE *fp){
    fprintf(fp, "Nodes: %d\n", t->size);
    int max = findMax(t->root);
    int min = findMin(t->root);
    fprintf(fp, "Minimum depth: %d\n", min);
    fprintf(fp, "Maximum depth: %d\n", max);
}


void printPreorder(BSTNODE *node, BST *t, FILE *fp){
    /* first print data of node */
   // t->display(fp, node->value);
    if (node == NULL){
        return;
    }

    fprintf(fp,"[");
    t->display(node->value,fp);

    if (!node->left && !node ->right && node!=t->root )
        fprintf(fp,"]");
    /* then recur on left sutree */
    printPreorder(node->left, t, fp);

    /* now recur on right subtree */
    printPreorder(node->right, t, fp);
}

void displayBST(BST *t,FILE *fp){

    if (t->root == NULL)
        return;
    BSTNODE *current=t->root;
    printPreorder(current, t, fp);
    fprintf(fp,"]");

}

void displayBSTdebug(BST *t,FILE *fp){
    if ( t->size == 0 )
        return;

    BSTNODE *current= t->root;
    QUEUE *mqueue = newQUEUE(0,0);
    int height = findMax(current);
    enqueue(mqueue,current->value);
    for (int i=0; i<height; i++){
        if (current->left){
            enqueue(mqueue, current->left->value);
        }
        if(current->right){
            enqueue(mqueue, current->right->value);
        }
        current = findBST(t, peekQUEUE(mqueue));
    }
    while (sizeQUEUE(mqueue)) {
        t->display(dequeue(mqueue), fp);
        fprintf(fp,"\n");
    }

}


void freeBST(BST *t){
    //printf("Size of t = %d\n",sizeBST(t));
    free(t);
}
