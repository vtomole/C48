
static char* indentifier_string;
static double number_value;


typedef struct eval_arguments_token{
  pair_token *head;
  hashtable_t *environment;
}eval_arguments_token;

typedef struct eval_arguments_cell{
  pair_cell *head;
  hashtable_t *environment;
}eval_arguments_cell;


struct eval_arguments1 parser (struct pair_cell* token_list){
  pair_cell* code_tree = NULL;
  pair* head;
  int num_elements = 0;
  
  hashtable_t *environment = ht_create(65);
  // printf("Number of elements %d\n", num_elements);
  eval_arguments1 exp_env = {code_tree,environment};
  
  //printf("Token list value %s\n", token_list-> val.value);
  //	 while(token_list != NULL)
  // {
  if(strcmp(token_list-> val.value, "open_paren") == 0){
    num_elements++;
    //code_tree = read_list(token_list, code_tree);
    //printf("I'm here\n");
    
    while (strcmp(token_list-> val.value, "closed_paren") != 0){
      exp_env = parser(cons1(token_list->val, code_tree));
      printf("I'm here\n");
    }
    
  }else{
    code_tree = cons1(token_list -> val, code_tree);
  }
  
  //printf("name %s\n", token_list->data.value);
  //  token_list = token_list->next;
  //}   
  return exp_env;
}


//pair == pair_token, pair1 == pair_cell
/*struct eval_arguments read(char *program){
  pair pair1;
  pair pair2;
  pair pair3;
  hashtable_t *environment = ht_create(65536);

  char * program_1;
  int i = 0;
  char operator = '+', char_quit = 'q';
  int b = 20,d;
  int c = 30;
  int count =0;
  char* token, substr;
  
  pair* head = NULL;
   
  const char s[2] = " ";
  const char s1[2] = "(";
    
   
  /* get the first token 
  token = strtok(program, s);

  printf("%s\n", token);
  if(strcmp(token, "q\n") == 0){
    //operator = 'q';
    operator = 'q';
    head = cons(&operator, head);
    //cons(&token ,head);
    //return head;
  }
  /* walk through other tokens 
  while( token != NULL ) 
    {	// can take if out
      if(token[0] == '(')
	{
	operator = token[1];
	}
      else if(token[strlen(token)- 2] == ')')
	{
	//printf("Right paren\n");
	for(i =0; i < strlen(token); i++)
	  {
	  // printf("Token at i %c\n", token[i]);
	  if(token[i] == ')')
	    {
	    token[i] = '\0';
	    // printf("I'm in here folks\n");
	    break;
	    }
	  else
	    {
	    token[i] = token[i];
	    }
	    
	}
	//printf("The token after %s\n", token);
	if(isnumber(token)){
	  b = atoi(token);
	  head = cons(&b,head);
	   
	  //type_array[count] = "integer";
	  count++;
	}
      }
      else{
	// printf( "The token at 0 %c\n", token[0]);
	c = token[0] - '0';
	//printf("that token as an int %d\n", c);

      }
      token = strtok(NULL, s);  

    }

  printf("value of operator %c\n", operator);
    printf("value of b(var 1) %d\n", b);
    printf("value of c(var 2) %d\n", c);
  
   
  pair1.car = &b;
  pair1.cdr = &pair2;
  
  //pair1.cdr = &c;
  pair2.car = &b;
  pair2.cdr = &pair3;
  
  
  head = cons(&b,head);
  head = cons(&c,head);
  head = cons(&operator, head);

   
  eval_arguments exp_env = {head,environment};

  return exp_env;


  }*/

/*pair1* read_list (struct pair1* token_list,  pair1* list_so_far){
  pair1* empty_list = NULL;
  char* token_value = token_list-> val.value;
  struct object token = token_list -> val;

  // printf("token_value: %s\n", token_value);
  //printf("The count %d\n", count_tokenlist(list_so_far));
   if(strcmp(token_value, "closed_paren") == 0){
     list_so_far = reverse_code_tree(list_so_far);
     printf("I'm here");
   }
   else if(strcmp(token_value, "open_paren") == 0){
     //printf("I'm here\n");
     //read_list(read-list(empty_list), list_so_far);
     read_list(cdr (token_list), cons1 (read_list (empty_list,list_so_far), list_so_far) list_so_far);

     //cons (read_list (empty_list)
     
   }
   else{
     // read_list(cons1 (token,list_so_far));
     //code_tree = cons(&list_so_far -> data, );
      read_list(cdr(token_list),cons1 (token, list_so_far));
   }

  return list_so_far;
  }*/

/*struct token* micro_read (token_list* token_list){
  
  //char* next_token = read_token(program);
  pair* head = NULL;
 struct token_list* list_so_far;

  struct token *next_token;
  //next_token = *token_list-> next;
  if(strcmp(token_list-> data.value, "open_paren") == 0){
    //printf("Left parentheses\n");

    read_list(list_so_far);

  }
  else{
    return next_token;
  }
// 

 //
//hashtable_t *environment = ht_create(65536);


//SIZE OF  ARRAY IS MINUS ONE FOR EXAMPLE IF MY ARRAY HAS 3 ELEMENTS THE SIZE IS 2
/*
[identifier, closed_paren] -> [identifier, closed_paren] ->[identifier, closed_paren] -> [variable, rate] -> [variable, initial] -> [operator, +] -> [identifier, open_paren] -> [variable, 60] -> [operator, *] -> [identifier, open_paren] -> [variable, position] ->[operator, set] -> [identifier, open_paren]

if (token == '('){

while tokens != ')'{

cons(token, head);

}
return head;
else if (token == ')'){
printf("Error");
}
else return atom(token)


1. Count the number of elements starting from the open parenthesis until you come to a dot or
close parenthesis (anything enclosed within parenthesis after the open parenthesis is
considered to be an element).

2. Draw a list of pairs equal in number to the quantity of counted elements.

3. Draw each element (in box & pointer diagram format) as the car of the corresponding pairs.

4. If there is a dot before the close parenthesis:
a. Draw the element (in box & pointer diagram format) as the cdr of the last pair.
b. Go to step 6

5. Draw an empty list as the cdr of the last pair
6. You are done.

(+ (+ 2 3) 7) => (cons '+ (cons (cons '+ (cons 2 (cons 3 '()))) (cons 7 '())))
head,head2,head3 = NULL
cons(+ cons (cons + (cons 2 (cons (cons 3 head)))) (cons 7 head2))
head1 = cons (7, NULL);
head2 = cons(3, NULL);
head3 = cons(head2, head1);
head4 = cons(2, head3);
head5 = cons(2 head4);
head6 = cons(+, head5);
head6 = cons


 


//head = cons(&b,head);
//don't increment num_elements while there is no closed paren

 //micro_read(token_list);
 // 

 //head = cons(&b,head);
 //cons("+" (cons (cons "+" (cons "2" (cons (cons "3" head)))) (cons "7" head2));

 
  }*/

//Parser//


 






