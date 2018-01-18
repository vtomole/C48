//Preliminary File for the implementation of Garbage collection
#include <unistd.h>

#define MIN_ALLOC_SIZE 4096 //size of a page in memory, smallest size we can use.

/**
 *header_gc is a header struct used to keep blocks of memory aligned
 * Parameters:
 * - size, used to show the size a block of memory
 * - next, pointer to the next block of free memory
 */
typedef struct header {
  unsigned int size;  
  struct block *next; 
}header_gc;


static header_gc  base; //empty list of memory blocks
static header_gc *free_list = NULL; //start of the list of available free memory blocks


/**
 *add_to_free_list updates the list of free blocks of memory
 * Parameters:
 * -bp, 
 */
static void add_to_free_list(header_gc *bp){

}

/**
 *more_core is used to request more memory from the machine
 *- this implementation only works on linux machines 
 * Parameters:
 * - num_units, the amount of memory we are requesting
 * Returns:
 * -NULL, if we are unable to aquire more memory.
 * -free_list, an updated free list with more blocks of memory
 */
static header_gc *more_core(size_t num_units){

  void *void_ptr;
  header_gc *up;

  if(num_units < MIN_ALLOC_SIZE)//if we are requesting less 1 page of memory
    num_units = MIN_ALLOC_SIZE / sizeof(header_gc);//set request size to 1 page 

  if((void_ptr = sbrk(num_units * sizeof(header_gc))) == (void *) -1)//UNIX method to reques memory from kernal
    return NULL;
  
  up = (header_gc *)void_ptr;
  up->size = num_units;
  //add_to_free_list(up);
  return free_list;
}

void *malloc_gc(size_t alloc_size){
  size_t num_units;
  header_gc *p, *prevp;//position, previous position
  
  num_units = (alloc_size + sizeof(header_gc) - 1)/sizeof(header_t) + 1;
  prevp = free_list;

  for(p = prevp->next; ; prevp = p, p = p->next){
    if(p->size >= num_units){
      if(p->size == num_units)
	prevp->next= p->next;
      else{
	p->size -= num_units;
	p += p->size;
	p->size = num_units;
      }
      free_list = prevp;
      return (void *)(p+1);
    }
    if(p == free_list)
      if((p = more_core(num_units)) == NULL)
	return NULL;
  }//end of for loop
}//end of malloc_gc
