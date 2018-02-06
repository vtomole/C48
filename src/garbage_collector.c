//Preliminary File for the implementation of Garbage collector
//#include "./parser.c"

/**
* gc_mark is the function we use to mark when and where we have called malloc
* Parameters:
* - root, the starting point of the code tree we are sweeping over 
*/
void gc_mark(object root)
{
	struct Allocation *a;
	a = (struct Allocation *)
		((char *) root.value.pair
			- offsetof(struct Allocation, pair));

	if (a->mark)
		return;

	a->mark = 1;

	gc_mark(car(root));
	gc_mark(cdr(root));
}
/**
* gc is function that collects free memory by calling free on the unused marked locations
*
*/
void gc()
{
	struct Allocation *a, **p;
	/*gc_mark(sym_table); we dont have a sym table */
	/* Free unmarked allocations */
	p = &global_allocations;
	while (*p != NULL) {
		a = *p;
		if (!a->mark) {
			*p = a->next;
			free(a);
		} else {
			p = &a->next;
		}
	}

	/* Clear marks */
	a = global_allocations;
	while (a != NULL) {
		a->mark = 0;
		a = a->next;
	}
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
