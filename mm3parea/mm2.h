#ifndef _MM2_H
#define _MM2_H

#include "stdlib.h"
#include "stdio.h"
#include "assert.h"

#define END_FUNCTION(a,b,c) c
#define BEGIN_FUNCTION(a,b)
#define ASSERT(a) assert(a);
#define DEBUG_DUMP_INT(a,b)
#define DEBUG_DUMP_CHAR(a,b)
#define DEBUG_DUMP_PLEAF(a,b)
#define EXIT_(a) exit(a);

typedef struct mm2_tag0
{
  /*log2 of size*/
  unsigned long mm2_log2size;
  /*bound count*/
  long mm2_count;
  /*storage location*/
  void* mm2_location;
  /*next free in list*/
  struct mm2_tag0* mm2_next_free; 
  /*unit of storage*/
  /*DOC_TYPEDEF(mm2_unit_t DG_MM2)*/
} mm2_unit_t;

/*log2size of variable*/
/*DOC_DEFINE(MM2_LOG_SIZE DG_MM2)*/
#define MM2_LOG_SIZE(s) ( ( (mm2_unit_t*)(s->mm_handle) )->mm2_log2size)
/*size of variable in bytes*/
/*DOC_DEFINE(MM2_SIZE DG_MM2)*/
#define MM2_SIZE(s) ( 1<<( (mm2_unit_t*)(s->mm_handle) )->mm2_log2size)

void mm2_close(void);
long mm2_sum_used(void);
#if !defined NDEBUG || (defined ASSERT_IN_ANY_CASE && ASSERT_IN_ANY_CASE==1)
long mm2_check_state(void);
#endif
extern long mm2_bound_new_forbidden;
void mm2_create(void);
long mm2_unbound_mem(void * handle);
unsigned long mm2_calculate_log2(unsigned long size);
extern void *  mm2_bound_new_mem(unsigned long size);
extern void mm2_bound_mem(void * loc_ptr);
extern void * mm2_handle;
extern void * mm_handle;

/* OLD INTERFACE */
void unbound_mem_from_handle(void * handle);
//void unbound_mem(void * loc_ptr);
extern void *  bound_new_mem(unsigned int size);

#endif
