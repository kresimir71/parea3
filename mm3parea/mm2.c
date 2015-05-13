#include "stdlib.h"
#include "stdio.h"
#include "mm2.h"



#ifndef ASSERT
#define ASSERT(x)\
  if (x) {}else{fprintf(stderr,"assert: %s \n%s %d",#x,__FILE__,__LINE__);exit(1);}
#endif

#define NUMBER_OF_MEMORY_SIZES (31)

#define MAXIMAL_DEMAND (sizeof(long)==8? (((unsigned long)1)<<(NUMBER_OF_MEMORY_SIZES-1)):(((unsigned long)1)<<31))

/*user defined calloc*/
/*DOC_FUNC_DEF(mm2_calloc DG_MM2)*/
void *(*mm2_calloc) (size_t nmemb, size_t size)  =calloc;/*NULL;*/

/*user defined free*/
/*DOC_FUNC_DEF(mm2_free DG_MM2)*/
void (*mm2_free) (void *mem)  =free ; /*NULL;*/

typedef struct mm2_tag2
{
  /*a calloc result on stack*/
void * mm2_calloc_chunk;
  /*next in array of calloc results*/
struct mm2_tag2*mm2_next_chunk;
  /*a stack of calloc results*/
  /*DOC_TYPEDEF(mm2_calloc_stack_t DG_MM2)*/
} mm2_calloc_stack_t;

/*active indicator */
/*DOC_VARIABLE(mm2_is_created DG_MM2)*/
static long mm2_is_created=0;
/*calloc stack */
/*DOC_VARIABLE(mm2_calloc_stack DG_MM2)*/
static mm2_calloc_stack_t* mm2_calloc_stack=NULL;
/*indicates no new bound is allowed */
long mm2_bound_new_forbidden=0;
/*free storage*/
/*DOC_VARIABLE(free_mem DG_MM2)*/
static mm2_unit_t* free_mem[NUMBER_OF_MEMORY_SIZES];
/*count of free storage*/
/*DOC_VARIABLE(free_mem_count DG_MM2)*/
static unsigned long free_mem_count[NUMBER_OF_MEMORY_SIZES];
/*count of used storage*/
/*DOC_VARIABLE(used_mem_count DG_MM2)*/
static unsigned long used_mem_count[NUMBER_OF_MEMORY_SIZES];
/*tag to indicate recursion*/
/*DOC_VARIABLE(mm2_recursion_count DG_MM2)*/
static long mm2_recursion_count =0;
/*handle of current storage*/
void * mm2_handle;
void * mm_handle;
static void mm2_push_calloc_stack(void*p);
static void mm2_place_in_free_list(mm2_unit_t* location);
static mm2_unit_t * mm2_fetch_from_free_list(unsigned long size);

/*push new allocated chunk to stack*/
/*DOC_FUNC_DEF(mm2_push_calloc_stack DG_MM2)*/
static void mm2_push_calloc_stack(void*p)
{
      mm2_calloc_stack_t*old_top=mm2_calloc_stack;
      if ((mm2_calloc_stack =  (mm2_calloc_stack_t*) mm2_calloc (1,sizeof(mm2_calloc_stack_t))) == 0) 
	{    
	  fprintf (stderr,"internal error: malloc failed: %s %s\n","(mm2_calloc_stack_t*)","mm2_calloc_stack");    
	  exit(1);  
	}
      mm2_calloc_stack->mm2_next_chunk=old_top;
      mm2_calloc_stack->mm2_calloc_chunk=p;
}
/*finalizes mm2*/
/*DOC_FUNC_DEF(mm2_close DG_MM2)*/
void mm2_close(void)
{
  ASSERT(mm2_is_created);
  mm2_is_created=0;
  while(mm2_calloc_stack)
    {
      mm2_calloc_stack_t*old_top=mm2_calloc_stack;
      mm2_free(mm2_calloc_stack->mm2_calloc_chunk);
      mm2_calloc_stack=old_top->mm2_next_chunk;
      mm2_free(old_top);
    }
  mm2_calloc=NULL;
}
/*initializes mm2*/
/*DOC_FUNC_DEF(mm2_create DG_MM2)*/
void mm2_create()
{
  long i;
  mm2_is_created=1;
  if (!mm2_calloc) mm2_calloc=calloc;
  if (!mm2_free) mm2_free=free;

  for (i=0;i<NUMBER_OF_MEMORY_SIZES;i++) {free_mem[i] = 0;free_mem_count[i]=0;}
#if !defined NDEBUG || (defined ASSERT_IN_ANY_CASE && ASSERT_IN_ANY_CASE==1)
  for (i=0;i<NUMBER_OF_MEMORY_SIZES;i++) {used_mem_count[i]=0;}
#endif
/*   for (i=0;i<MM2_NR_OF_OWN_FREE_MEM_SIZES;i++) {own_free_mem_count[i] = 0;} */
/*   for (i=0;i<MM2_NR_OF_OWN_FREE_MEM_SIZES;i++) {own_free_mem[i].last_free = 0;own_free_mem[i].size = 0;own_free_mem[i].current = 0;} */
#if !defined NDEBUG || (defined ASSERT_IN_ANY_CASE && ASSERT_IN_ANY_CASE==1)
  /*  for (i=0;i<MM2_NR_OF_OWN_FREE_MEM_SIZES;i++) {own_used_mem_count[i] = 0;} */
#endif
}
/*bounds storage*/
/*DOC_FUNC_DEF(mm2_bound_mem DG_MM2)*/
void mm2_bound_mem(void * handle)
{
  mm2_unit_t *location;
  ASSERT(mm2_is_created);
  mm2_recursion_count++;
  location = (mm2_unit_t*)handle;
  ASSERT(mm2_recursion_count==1);
  ASSERT(location && (location->mm2_count)>0);
  ASSERT(!(location->mm2_count<1));
  (location->mm2_count)++;
  mm2_recursion_count--;
}
/*unbounds storage from heap*/
/*DOC_FUNC_DEF(mm2_unbound_mem DG_MM2)*/
long mm2_unbound_mem(void * handle)
{
  mm2_unit_t *location;
  ASSERT(mm2_is_created);
  mm2_recursion_count++;
  ASSERT(mm2_recursion_count==1);
  location = (mm2_unit_t*)handle;
  ASSERT(location);
  (location->mm2_count)--;
  ASSERT(location->mm2_count>-1);
  if(!location->mm2_count)
    {
      mm2_place_in_free_list(location);  
#if !defined NDEBUG || (defined ASSERT_IN_ANY_CASE && ASSERT_IN_ANY_CASE==1)
      {
	used_mem_count[location->mm2_log2size]--;
      }
#endif
    }
  mm2_recursion_count--;
  return location->mm2_count;
}

/*places storage in free list*/
/*DOC_FUNC_DEF(mm2_place_in_free_list DG_MM2)*/
static void mm2_place_in_free_list(mm2_unit_t* location)
{
  location->mm2_next_free= free_mem[location->mm2_log2size];
  free_mem[location->mm2_log2size]= location;
}
/*bounds new storage*/
/*DOC_FUNC_DEF(mm2_bound_new_mem DG_MM2)*/
void *  mm2_bound_new_mem(unsigned long size)
{
  void* result;
  if (size>MAXIMAL_DEMAND){
    {
      fprintf(stderr,"error:memory allocation failed, size exceeds MAXIMAL_DEMAND\n");
      exit (1);
    }
  }
  ASSERT(mm2_is_created);
  if (mm2_bound_new_forbidden)
    {
      fprintf(stderr,"%s","error:memory allocation failed\n");
      exit (1);
    }
  mm2_recursion_count++;
  if(mm2_recursion_count>1)
    {
      fprintf(stderr,"%s","error:mm2_recursion_count>1\n");
      exit (1);
    }
  else
    {
      mm2_handle = (void*)(mm2_fetch_from_free_list(size));
      mm_handle=mm2_handle;
      result = ((mm2_unit_t *) mm2_handle)->mm2_location;
#if !defined NDEBUG || (defined ASSERT_IN_ANY_CASE && ASSERT_IN_ANY_CASE==1)
      {
	long log2size=mm2_calculate_log2(size);
	used_mem_count[log2size]++;
      }
#endif
    }
  mm2_recursion_count--;
  return result;
}

/*calculates log2:provided as library interface, but internally the macro is used*/
/*DOC_FUNC_DEF(mm2_calculate_log2 DG_MM2)*/
unsigned long mm2_calculate_log2(unsigned long size)
{ 
  /*mm2_calculate_log2(1)=0*/
    /*mm2_calculate_log2(2)=1*/
    /*mm2_calculate_log2(3)=2*/
    /*mm2_calculate_log2(4)=2*/
    /*mm2_calculate_log2(5,6,7,8)=3*/
    /*mm2_calculate_log2(9,..,16)=4*/

  unsigned long res=1;
  if (size==0 || size==1) return 0;
  size--;
  while (size/=2) res++;
  return res;
}

/*fills the free list */
/*DOC_FUNC_DEF(mm2_fetch_from_free_list DG_MM2)*/
static void mm2_fill_free_list( long log2size_netto)
{
#define FILL_FRONT (8)/*must be a multiple of 8*/
#define FILL_MIDDLE (16)/*must be a multiple of 8*/
#define FILL_END (24) /*must be a multiple of 8 */
  char* new_mem;
  unsigned long  log2sizeexp2 = 1 << log2size_netto;
  unsigned long mm2_unit_t_offset=(sizeof( mm2_unit_t)/8+1)*8; /*round on 8 bytes*/
    unsigned long total_size01=FILL_FRONT+mm2_unit_t_offset+FILL_MIDDLE+log2sizeexp2+FILL_END;/*added in order of apperiance*/

  long nr,i;
  /* 10% more than currently*/
  nr = free_mem_count[log2size_netto]/10+1;
  free_mem_count[log2size_netto]+=nr;

  /*allocate*/
  if ((new_mem =  (char*) mm2_calloc (nr,total_size01)) == 0) 
    {    
      fprintf (stderr,"internal error: calloc failed: %s %s\n","(char*)","new_mem");
      exit(1);  
    }

  /* record on stack for the final free*/
  mm2_push_calloc_stack(new_mem);

  /* put each part in the free list*/
  for (i=0;i<nr;i++)
    {
      mm2_unit_t* new_unit = ( mm2_unit_t*) (new_mem+i*total_size01+FILL_FRONT);
      new_unit->mm2_log2size = log2size_netto;/*mm2_calculate_log2(size); //keep it netto for user*/
      new_unit->mm2_count =0;
      new_unit->mm2_next_free =0; 
      new_unit->mm2_location = new_mem+i*total_size01+FILL_FRONT+mm2_unit_t_offset+FILL_MIDDLE;
      mm2_place_in_free_list(new_unit);
    }
  return;
}

/*fills the free list if necessary and fetches storage from free list*/
/*DOC_FUNC_DEF(mm2_fetch_from_free_list DG_MM2)*/
static mm2_unit_t * mm2_fetch_from_free_list(unsigned long size)
{
  mm2_unit_t * top;
  long log2size_netto=mm2_calculate_log2(size); 
  top = free_mem[log2size_netto];
  if (!top)
    {
      mm2_fill_free_list(log2size_netto);
      /* take one new chunk*/
      top=free_mem[log2size_netto];
    }
  /* do pop from the free list*/
  free_mem[log2size_netto]=top->mm2_next_free;
  top->mm2_next_free=0;

  ASSERT(top->mm2_count==0);
  /* once bounded*/
  top->mm2_count=1;
  return top;
}

/*#if !defined APPL_MAIN_APPLICATION_IDENTIFIER_CPP2 || (defined ASSERT_IN_ANY_CASE && ASSERT_IN_ANY_CASE==1)*/
/*DOC_FUNC_DEF(mm2_sum_used DG_MM2)*/
long mm2_sum_used(void)
{
  long i;
  long sum =0;
  for (i=0;i<NUMBER_OF_MEMORY_SIZES;i++)
    {      
      if (1 || i==4)
	sum+=used_mem_count[i];
    }  
  return sum;
}
/*DOC_FUNC_DEF(mm2_check_state DG_MM2)*/
long mm2_check_state(void)
{
  long i;
  long wrong=0;
  long sum =0;
  return 1;
  /*These tests are not used anymore*/
#if 0   
  for (i=0;i<NUMBER_OF_MEMORY_SIZES;i++)
    {      
      wrong = (used_mem_count[i]!=0);
      if (wrong) break;
      sum+=free_mem_count[i];
    }  
  if (wrong/* ||sum!=own_used_mem_count[0] */)
    {
      for (i=0;i<NUMBER_OF_MEMORY_SIZES;i++)
	{
	  fprintf(stderr,"free/used_mem %x:%d/%d\n",1<<i,free_mem_count[i],used_mem_count[i]);
/* 	  if (i<MM2_NR_OF_OWN_FREE_MEM_SIZES) */
/* 	    { */
/* 	      fprintf(stderr,"own_free/used_mem %x:%d/%d\n",1<<i,own_free_mem_count[i],own_used_mem_count[i]); */
/* 	    } */
	}
      fprintf(stderr,"%s","warning:checksum wrong in 'free'\n");
      return 0;    
    }
  else
    {
      return 1;
    }
#endif
}

/* OLD INTERFACE */

/*unbounds storage from mm_handle*/
//DOC_FUNC_DEF(unbound_mem_from_handle DG_MM)
void unbound_mem_from_handle(void * handle)
{
  mm2_unbound_mem(handle);return;
}
/*bounds new storage*/
//DOC_FUNC_DEF(bound_new_mem DG_MM)
void *  bound_new_mem(unsigned int size)
{
  void* result;
  result= mm2_bound_new_mem(size);mm_handle=mm2_handle;return result;
}

/*#endif*/

