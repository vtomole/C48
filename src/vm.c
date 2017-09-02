//implementation from https://www.tutorialspoint.com/data_structures_algorithms/stack_program_in_c.htm


/*
  const-x-push a constant on the stack
  lvar-i,j-push local variable's value
  gvar-sym-push a global variable's value
  lset-i,j- store top-of-stack in a local variable


*/

int MAXSIZE = 8;
int stack[8];
int top = -1;


int isEmpty() {
  if (top == -1){
    return 1;
  }
  else{
    return 0;
  }
}


int isFull(){
  if (top == MAXSIZE){
    return 1;
  }
  else{
    return 0;
  }
}


int peek() {
  return stack[top];
}

int pop(){
  int data;
  if(!isEmpty()){
    data = stack[top];
    top = top - 1;
    return data;
  }
  else{
    printf("Stack is empty\n");
  }
}

int push (int data) {
  if (!isFull()) {
    top = top + 1;
    stack[top] = data;
  }
  else {
    printf ("Stack is full\n");
  }
}


void machine (int code[]){
  int op = code[0];
  switch(op){
  case 1:
    //push constant onto the stack
    push (code[1]);
    break;
  case 2:
     push (code[1]);
    break;
  case 3:
    push (code[1]);
    break;
  case 4:
    push (code[1]);
    break;
  case 5:
     push (code[1]);
    break;
  case 6:
     push (code[1]);
    break;
  case 7:
     push (code[1]);
    break;
  case 8:
     push (code[1]);
    break;
  case 9:
     push (code[1]);
    break;
  case 10:
     push (code[1]);
    break;
  case 11:
     push (code[1]);
    break;
  case 12:
     push (code[1]);
    break;
  case 13:
     push (code[1]);
    break;
  default:
    printf("Your char is not in this variable\n");
  }

}

