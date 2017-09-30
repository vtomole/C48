struct env{
  enum type type;
  void* value;
}env;


int self_evaluatingp (object *exp){
  if(strcmp(exp->type, "number") == 0){
  
    return 1;
  }
  else if (strcmp(exp->type, "string") == 0){
    return 1;
  }
  else {
    return 0;
  }
}

int primitivep (object *exp){
  if(strcmp(exp->type, "primop") == 0){
  
    return 1;
  }
  
  else {
    return 0;
  }
}

object *apply_primitive_procedure(object *procedure , object* arguments){
  
  if(strcmp(procedure->variable, "+")== 0){
    //printf("ITS A PLUS\n");
    struct object *object1;
    int first,second,answer;
    object *test1 = malloc(sizeof(*object1));
    first = car1(arguments)->number;
    second = car1(cdr1(arguments))->number;
    answer = first+second;
    // printf("THE NUMBER %d\n", answer);
    procedure = create_number(answer);
  }
  else{
    printf("Procedure has not been implemented yet\n"); 
  }

  return procedure;

}

object  *apply(object *procedure , object* arguments){


   if (primitivep(procedure)){
     procedure = apply_primitive_procedure(procedure, arguments);
    }
   else{
     printf("Unkown apply procedure\n");
   }
 
  return procedure;

}

object *eval(object* exp, token_list* env ){
  if (self_evaluatingp(exp)){
   printf("SELFEVALUATING\n");
    }
   else{
     exp = apply(car1(exp), cdr1(exp));
   }

 
  return exp;
}
