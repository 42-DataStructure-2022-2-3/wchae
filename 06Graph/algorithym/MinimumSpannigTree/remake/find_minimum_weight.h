#ifndef _FIND_MINIMUM_WEIGHT_
# define _FIND_MINIMUM_WEIGHT_

#include "commonheader.h"
#include "heap/heap.h"
#include "linkedgraph/graphlinkedlist.h"
#include "linkedstack/linkedstack.h"
#include "linkedlist/linkedlist.h"
#include "linkeddequeue/linkeddeque.h"

 LinkedGraph    *kruskal(LinkedGraph *pGraph);
 LinkedGraph    *mstPrim(LinkedGraph *pGraph, int startVertex);


#endif