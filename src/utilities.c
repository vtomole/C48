
/* Return number of nodes in the code tree*/
int count (pair* cursor){
  int c = 0;
  while(cursor != NULL){
    c++;
    cursor = cursor->cdr;
  }
  return c;
}
