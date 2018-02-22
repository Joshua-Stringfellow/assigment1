//
// Created by jrstringfellow on 2/12/18.
//

#include "real.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

struct REAL
{
    double value;
};

REAL *
newREAL(double x)
{
    REAL *p = malloc(sizeof(REAL));
    assert(p != 0);
    p->value = x;
    return p;
}

double
getREAL(REAL *v)
{
    return v->value;
}

double
setREAL(REAL *v,double x)
{
    double old = v->value;
    v->value = x;
    return old;
}

void
displayREAL(void *v,FILE *fp)
{
    fprintf(fp,"%0.1f",getREAL((REAL *) v));
}

double
compareREAL(void *v,void *w)
{
    return getREAL(v) - getREAL(w);
}

void
freeREAL(void *v)
{
    free((REAL *) v);
}
