#ifndef _RBT_SHORTCUTS_H
#define _RBT_SHORTCUTS_H
//#include "goals.h"
//#include "debug2.h"

/*create red-black tree*/
//DOC_DEFINE(RBT_CREATE_TREE DG_RBT)
#define RBT_CREATE_TREE(prop) createTree(prop ## _cmpLT,prop ## _cmpEQ,NULL,NULL,NULL,NULL)
     /*compare functions for ints*/
//DOC_DEFINE(RBT_CMP_FUNCTIONS_INT DG_RBT)
#define RBT_CMP_FUNCTIONS_INT(prop,prop_type,int_key) \
static long prop ## _cmpLT(void *a,void* b)\
{\
  return (\
	  ((prop_type*)a)->int_key\
	  <\
	  ((prop_type*)b)->int_key\
	  ) ;\
}\
\
static long prop ## _cmpEQ(void *a,void* b)\
{\
  return (\
	  ((prop_type*)a)->int_key\
	  ==\
	  ((prop_type*)b)->int_key\
	  ) ;\
}

     /*find function for ints*/
//DOC_DEFINE(RBT_FIND_KEY_INT DG_RBT)
#define RBT_FIND_KEY_INT(prop,prop_type,int_key,int_key_value,found) \
do\
{\
  prop_type to_search;\
  to_search.int_key = (int_key_value);\
  found = (prop_type*) findKey(prop,&to_search);\
} while (0)

     /*find function for strings*/
//DOC_DEFINE(RBT_FIND_KEY_STR DG_RBT)
#define RBT_FIND_KEY_STR(prop,prop_type,str_key,str_key_value,found) \
do\
{\
  prop_type to_search = {0};\
  if (to_search.str_key)\
  {\
    strcpy(to_search.str_key,str_key_value);\
  }\
  else\
  {\
    to_search.str_key = str_key_value;\
  }\
  found = (prop_type*) findKey(prop,&to_search);\
} while (0)

     /*delete functions for strings*/
//DOC_DEFINE(RBT_DEL_KEY_STR DG_RBT)
#define RBT_DEL_KEY_STR(prop,prop_type,str_key,str_key_value) \
do\
{\
  prop_type to_search = {0};\
  if (to_search.str_key)\
  {\
    strcpy(to_search.str_key,str_key_value);\
  }\
  else\
  {\
    to_search.str_key = str_key_value;\
  }\
  deleteKey(prop,&to_search,0);\
} while (0)

#define SHIFT(l,r) static void shift_##l(void *rbtreeptr, rm2_rbt_node_t *node_a) \
{\
  rm2_rbt_node_t *node_b = node_a->r;\
  node_a->r = node_b->l;\
  if (node_b->l != &((rbtree_t *)rbtreeptr)->leaf) node_b->l->p = node_a;\
  if (node_b != &((rbtree_t *)rbtreeptr)->leaf) node_b->p = node_a->p;\
  if (node_a->p) \
  {\
    if (node_a == node_a->p->l)\
      node_a->p->l = node_b;\
    else\
      node_a->p->r = node_b;\
  }\
  else\
  {\
    ((rbtree_t *)rbtreeptr)->root = node_b;\
  }\
  node_b->l = node_a;\
  if (node_a != &((rbtree_t *)rbtreeptr)->leaf) node_a->p = node_b;\
}
#define ADD_RESTORE(l,r) rm2_rbt_node_t *node_b = node_a->p->p->r;\
if (node_b->c == RM2_RBT_COLOR_RED) \
{\
  node_a->p->c = RM2_RBT_COLOR_BLACK;\
  node_a->p->p->c = RM2_RBT_COLOR_RED;\
  node_b->c = RM2_RBT_COLOR_BLACK;\
  node_a = node_a->p->p;\
} \
else \
{\
  if (node_a == node_a->p->r) \
  {\
    node_a = node_a->p;\
    shift_##l(((rbtree_t *)rbtreeptr),node_a);\
  }\
  node_a->p->p->c = RM2_RBT_COLOR_RED;\
  node_a->p->c = RM2_RBT_COLOR_BLACK;\
  shift_##r(((rbtree_t *)rbtreeptr),node_a->p->p);\
}
#define REMOVE_RESTORE(l,r) rm2_rbt_node_t *node_e = node_a->p->r;\
if (node_e->c == RM2_RBT_COLOR_RED) \
{\
  node_e->c = RM2_RBT_COLOR_BLACK;\
  node_a->p->c = RM2_RBT_COLOR_RED;\
  shift_##l (((rbtree_t *)rbtreeptr),\
             node_a->p);\
  node_e = node_a->p->r;\
}\
if (node_e->l->c == RM2_RBT_COLOR_BLACK && \
    node_e->r->c == RM2_RBT_COLOR_BLACK) \
{\
  node_e->c = RM2_RBT_COLOR_RED;\
  node_a = node_a->p;\
} \
else \
{\
  if (node_e->r->c == RM2_RBT_COLOR_BLACK) \
  {\
    node_e->l->c = RM2_RBT_COLOR_BLACK;\
    node_e->c = RM2_RBT_COLOR_RED;\
    shift_##r (((rbtree_t *)rbtreeptr),\
                node_e);\
    node_e = node_a->p->r;\
  }\
  node_e->c = node_a->p->c;\
  node_a->p->c = RM2_RBT_COLOR_BLACK;\
  node_e->r->c = RM2_RBT_COLOR_BLACK;\
  shift_##l (((rbtree_t *)rbtreeptr),\
             node_a->p);\
  node_a = ((rbtree_t *)rbtreeptr)->root;\
};
#endif
