
////////  Token  ////////

struct token{
  char* name;
  char* value;
  //struct token* next;
}token;


struct object{
  char* type;
  char* value;
}type;
  

typedef struct token_list {
  struct token data;
  struct token_list* next;
  /*tok_eof = -1,
  tok_def = -2,
  tok_identifier = -4,
  tok_number = -5,*/
}token_list;

token_list* create_token(struct token token, token_list* next)
{
    token_list* new_node = (token_list*)malloc(sizeof(token_list));
    if(new_node == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }
    new_node->data = token;
    new_node->next = next;
 
    return new_node;
}

token_list* prepend(struct token token, token_list* head)
{
  token_list* new_node = create_token(token,head);
    head = new_node;
    return head;
}

int count_tokenlist(token_list *head)
{
    token_list *cursor = head;
    int c = 0;
    while(cursor != NULL)
    {
        c++;
        cursor = cursor->next;
    }
    return c;
}

token_list* reverse_tokenlist(token_list* head)
{
    token_list* prev    = NULL;
    token_list* current = head;
    token_list* next;
    while (current != NULL)
    {
        next  = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
    return head;
}

////////  Pair ////////


typedef struct pair_cell{
  void *car;
  void *cdr;
}pair_cell;

typedef struct pair_token{
  struct object val;
  struct pair1 *next;
}pair_token;

void print(struct pair_token* list){
  if(list){
    printf("%s\n", car(list));
    print(cdr(list));
  }
}

pair_cell* create1(void* car,void* cdr)
{
  pair_cell* pair = malloc(sizeof(pair));
  if(pair == NULL)
    {
      printf("Error creating a new node.\n");
      exit(0);
    }
  pair->car = car;
  pair->cdr = cdr;
 
  return pair;
}


char* car (struct pair_token *list){
  if(list){
    return list->val.value;
  }
  return 0;
}

pair_token* cdr(struct pair_token* list){
  return list -> next;
}

pair_token* cons(void *car, pair_token* cdr)
{
 
  pair_token* new_pair = create1(car,cdr);
  car = new_pair;
  return car;
}

pair_cell* cons1(struct object val, struct pair_cell *cdr)
{
  pair_cell* pair = malloc(sizeof(pair));
  if(pair == NULL)
    {
      printf("Error creating a new node.\n");
      exit(0);
    }
  pair->val = val;
  pair->next = cdr;
 
  return pair;
}

int count_nodes1(pair_cell *head)
{
    pair_cell *cursor = head;
    int c = 0;
    while(cursor != NULL)
    {
        c++;
        cursor = cursor->next;
    }
    return c;
}

int count_nodes(pair_token *head)
{
    pair_token *cursor = head;
    int c = 0;
    while(cursor != NULL)
    {
        c++;
        cursor = cursor->cdr;
    }
    return c;
}

pair_cell* reverse_code_tree(pair_cell* head)
{
    pair_cell* prev    = NULL;
    pair_cell* current = head;
    pair_cell* next;
    while (current != NULL)
    {
        next  = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
    return head;
}

pair_cell* remove_front(pair_cell* head)
{
    if(head == NULL)
        return NULL;
    pair_cell *front = head;
    head = head->next;
    front->next = NULL;
    /* is this the last node in the list */
    if(front == head)
        head = NULL;
    free(front);
    return head;
}

pair_cell* read_from_tokens (struct pair_cell* token_list){

char*  token_value = token_list-> val.value;
 struct object token = token_list->val;
 pair_cell* empty_list;
  
  
  
 if(token_list == NULL){
   printf("IM HERE\n");
  
 }
 else  if(cdr(token_list) == NULL){
   return empty_list;
 }
 else{
   pair_cell *l;
   // printf("PRINTING THE TOKEN VALUE %s\n", token_value);
   //printf("NUMBER %d\n", strcmp(token_value, "closed_paren"));
  //if(strcmp(token_value, "open_paren") == 0){
  // while(strcmp(token_value, "closed_paren") != 0){
   
  /print(token_list);
   //printf("NEW\n");
   //l = cons1(token, read_from_tokens(cdr(token_list)));
 // }
 // }
 return l;

 }
 // printf("Number of node %d\n", count_nodes(token_list));

 // printf("Token %s\n",token_value);
 // print(token_list);
 //printf("After\n");
 // printf("CAR %s\n", car (token_list));
 //print(token_list->next);
 //printf("NEW\n");
 //print(cdr (token_list));
 /* if(strcmp(token_value, "open_paren") == 0){
   // printf("I'm here\n");
   struct pair1* l;
      while(strcmp(token_value, "closed_paren") != 0){

	l= read_from_tokens(cdr(cdr(token_list)));
	//	printf("I'm here\n");
	//	l =  read_from_tokens (cdr(token_list));
     // print(l);
	//printf("Token value: %s\n", token_value);
     
}
   l = remove_front(l);
   return l;
 }
   else{

     // printf("I'm in else\n");
     return cons1(token,empty_list);

     }*/
 
}




