//Preliminary File for the implementation of Garbage collection
#include "./parser.c"
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
	//gc_mark(sym_table);
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
