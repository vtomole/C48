#include <stdio.h>
#define MAX_LENGTH 200
#include <string.h>
#include <stdlib.h>


//Linked list implementation taken from: http://www.zentut.com/c-tutorial/c-linked-list/
typedef struct node{
    int data;
    struct node* next;
}node;



/*
    display a node
*/
void display(node* n)
{
    if(n != NULL)
        printf("%d ", n->data);
}
//Global variables
int command = 0;
    int data;
 
    node* head = NULL;
    node* tmp = NULL;
    


typedef void (*callback)(node* data);
 
/*
    create a new node
    initialize the data and next field
 
    return the newly created node
*/
node* create(int data,node* next)
{
    node* new_node = (node*)malloc(sizeof(node));
    if(new_node == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }
    new_node->data = data;
    new_node->next = next;
 
    return new_node;
}
 
/*
    add a new node at the beginning of the list
*/
node* prepend(node* head,int data)
{
    node* new_node = create(data,head);
    head = new_node;
    return head;
}
 
/*
    add a new node at the end of the list
*/
node* append(node* head, int data)
{
    if(head == NULL)
        return NULL;
    /* go to the last node */
    node *cursor = head;
    while(cursor->next != NULL)
        cursor = cursor->next;
 
    /* create a new node */
    node* new_node =  create(data,NULL);
    cursor->next = new_node;
 
    return head;
}
 
/*
    insert a new node after the prev node
*/
node* insert_after(node *head, int data, node* prev)
{
    if(head == NULL || prev == NULL)
        return NULL;
    /* find the prev node, starting from the first node*/
    node *cursor = head;
    while(cursor != prev)
        cursor = cursor->next;
 
    if(cursor != NULL)
    {
        node* new_node = create(data,cursor->next);
        cursor->next = new_node;
        return head;
    }
    else
    {
        return NULL;
    }
}
 
/*
    insert a new node before the nxt node
*/
node* insert_before(node *head, int data, node* nxt)
{
    if(nxt == NULL || head == NULL)
        return NULL;
 
    if(head == nxt)
    {
        head = prepend(head,data);
        return head;
    }
 
    /* find the prev node, starting from the first node*/
    node *cursor = head;
    while(cursor != NULL)
    {
        if(cursor->next == nxt)
            break;
        cursor = cursor->next;
    }
 
    if(cursor != NULL)
    {
        node* new_node = create(data,cursor->next);
        cursor->next = new_node;
        return head;
    }
    else
    {
        return NULL;
    }
}
 
/*
    traverse the linked list
*/
void traverse(node* head,callback f)
{
    node* cursor = head;
    while(cursor != NULL)
    {
        f(cursor);
        cursor = cursor->next;
    }
}
/*
    remove node from the front of list
*/
node* remove_front(node* head)
{
    if(head == NULL)
        return NULL;
    node *front = head;
    head = head->next;
    front->next = NULL;
    /* is this the last node in the list */
    if(front == head)
        head = NULL;
    free(front);
    return head;
}
 
/*
    remove node from the back of the list
*/
node* remove_back(node* head)
{
    if(head == NULL)
        return NULL;
 
    node *cursor = head;
    node *back = NULL;
    while(cursor->next != NULL)
    {
        back = cursor;
        cursor = cursor->next;
    }
 
    if(back != NULL)
        back->next = NULL;
 
    /* if this is the last node in the list*/
    if(cursor == head)
        head = NULL;
 
    free(cursor);
 
    return head;
}
 
/*
    remove a node from the list
*/
node* remove_any(node* head,node* nd)
{
    if(nd == NULL)
        return NULL;
    /* if the node is the first node */
    if(nd == head)
        return remove_front(head);
 
    /* if the node is the last node */
    if(nd->next == NULL)
        return remove_back(head);
 
    /* if the node is in the middle */
    node* cursor = head;
    while(cursor != NULL)
    {
        if(cursor->next == nd)
            break;
        cursor = cursor->next;
    }
 
    if(cursor != NULL)
    {
        node* tmp = cursor->next;
        cursor->next = tmp->next;
        tmp->next = NULL;
        free(tmp);
    }
    return head;
 
}

 
/*
    Search for a specific node with input data
 
    return the first matched node that stores the input data,
    otherwise return NULL
*/
node* search(node* head,int data)
{
 
    node *cursor = head;
    while(cursor!=NULL)
    {
        if(cursor->data == data)
            return cursor;
        cursor = cursor->next;
    }
    return NULL;
}
 
/*
    remove all element of the list
*/
void dispose(node *head)
{
    node *cursor, *tmp;
 
    if(head != NULL)
    {
        cursor = head->next;
        head->next = NULL;
        while(cursor != NULL)
        {
            tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
    }
}
/*
    return the number of elements in the list
*/
int count(node *head)
{
    node *cursor = head;
    int c = 0;
    while(cursor != NULL)
    {
        c++;
        cursor = cursor->next;
    }
    return c;
}
/*
    sort the linked list using insertion sort
*/
node* insertion_sort(node* head)
{
    node *x, *y, *e;
 
    x = head;
    head = NULL;
 
    while(x != NULL)
    {
        e = x;
        x = x->next;
        if (head != NULL)
        {
            if(e->data > head->data)
            {
                y = head;
                while ((y->next != NULL) && (e->data> y->next->data))
                {
                    y = y->next;
                }
                e->next = y->next;
                y->next = e;
            }
            else
            {
                e->next = head;
                head = e ;
            }
        }
        else
        {
            e->next = NULL;
            head = e ;
        }
    }
    return head;
}
 
/*
    reverse the linked list
*/
node* reverse(node* head)
{
    node* prev    = NULL;
    node* current = head;
    node* next;
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

int repl(){
  char str[20];
  while (1){
    printf("sky>");
    fgets (str, 20, stdin);
    printf("=>");
    
    int first = 0;
    int second = 0;
    // int ans =0;
    float ans = 0;
    char op;
    // for(int i=0; i <strlen(str); i++){
    //printf("%c\n", str[i]);
   
    first = str[3]-'0';
    op = str[1];
    second = str[5]-'0';

    if(op == '*'){
      ans = first * second;
    }
    else if(op == '+'){
      ans = first + second;
    }
    else if(op == '-'){
      ans = first - second;
    }
    else if(op == '/'){
      ans = first / (float)second;
    }
    
    printf("%.2f\n",ans);
  }
  return 0;
}

typedef struct pair{
    void *car;
    void *cdr;
}pair;


pair* create1(void* car,void* cdr)
{
  //pair* pair = (pair*)malloc(sizeof(pair));
  pair* pair = malloc(sizeof(pair));
    if(pair == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }
    pair->car = car;
    pair->cdr = cdr;
 
    return pair;
}
pair read(char *program){
  pair pair1;
  pair pair2;

  char * program_1;
 
  int b = 20;
  int c = 30;

 pair* head;

 
 if(program[0] != '('){
  

 }
 else{
  const char s[2] = " ";
  const char s1[2] = "(";
  char *token;
   
   /* get the first token */
   token = strtok(program, s);

   
   /* walk through other tokens */
   while( token != NULL ) 
   {
     if(token[0] == '('){
        token = strtok(program, s1);
	printf("Token should not have parentheses %s\n", token);
	head = create1 (&token, &pair2);
     }
     //printf( " %s\n", token );
    
      token = strtok(NULL, s);
   }

 }
   
  pair1.car = &b;
  pair1.cdr = &pair2;
  //pair1.cdr = &c;
  pair2.car = &c;
  callback disp = display;

  head = create1 (&b, &pair2);

  printf("I'm up here  should be 20  %d\n",  *(int*)head->car);
  head =  (pair*)head->cdr;
 

  printf("I'm up here  should be 30  %d\n",  *(int*)head->car);
  
 
  //printf("I'm up here  should be 30  %d\n",   *(int *)pair1->cdr->car);

 

  data = 2;

  /*head = prepend(head,data);
    traverse(head,disp);*/
  return pair1;
}

char  *apply(char operator, int arguments[]){

  // char answer[10];
  int i;
  char* answer = (char*)malloc(8 * sizeof(char));
  switch(operator){
  case '+':
    sprintf(answer, "%d", arguments[0] + arguments[1]);
	return answer;
      break;
    case '-':
      printf("It's a b\n");
      break;
    case '*':
      printf("It's an I\n");
      break;
    default:
	printf("Your char is not in this variable\n");
	}

 

}

char *eval(pair head){

  // printf("I'm down here  should be 20  %d\n",   *(int *)head.car);

  char *answer;
  char operator = '+';
  int arguments[2] = {1,2};

   answer = apply(operator, arguments);

  //char *answer = "Hello";
  return answer;
}


int main(char *argc, char **argv[]){

  char str[20];
  // while(1){
    printf("repl>");
    fgets (str, 20, stdin);
    printf("=>");
    // printf("%s\n" ,str);
    printf("%s\n", eval(read(str)));

    //}
  return 0;
  
  }
