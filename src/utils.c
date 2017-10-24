#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>

int equals(char *str1, char *str2){
  return strcmp(str1, str2) == 0;
}

/**
 * This function advance the pointer to a new location effectivly removing N character from the string
 * Parameters:
 * - the buffer to edit
 * - n the number of characters to chop off
 * Return Value:
 * - charBuffer with N characters chopped off 
 */ 
//Chop off first N characters
char* chopN(char *charBuffer, int n){   
  return charBuffer + n;   
}


/**
 * This function does ???
 * https://stackoverflow.com/questions/14259540/c-programming-strcat-using-pointer
 * Parameters:
 * - s ???
 * - t ???
 * Return Value:
 * - p ???
 * Example call:
 * 
 * expected return val: 
 */ 
char *scat(char *s,char *t){
  char *p=malloc(strlen(s)+strlen(t)+1);  /* 3: you will have to reserve memory to hold the copy. */
  int ptr =0, temp = 0;                   /* 4 initialise some helpers */

  while(s[temp]!='\0'){                   /* 5. use the temp to "walk" over string 1 */
    p[ptr++] = s[temp++];
  }

  temp=0;

  while(t[temp]!='\0'){                   /* and string two */
    p[ptr++]=t[temp++];
  }
  return p;
}

/**
 * This function checks if a given character is whitespace
 * Parameters:
 * - c the character to check
 * Return Value:
 * - 1 if the character is whitespace
 * - 0 otherwise 
 */ 
int iswhitespace (char c){
  if(c == '\n' || c == ' '){
    return 1;
  }else{
    return 0;
  }
}

/**
 * This function appends a given char to the end of the given string
 * Parameters:
 * - s the string to append characters to
 * - c the char to append
 * Return Value:
 * - a string with the given char at the end of the original string
 * Example call:
 * append("hello", '!');
 * expected return val: hello!
https://stackoverflow.com/questions/10279718/append-char-to-string-in-c 
 */ 
char* append(char* str, char c){
  
  if(str == NULL){
    str = "n";
    }
 
    size_t len = strlen(str);
    char *str2 = malloc(len + 1 + 1 ); /* one for extra char, one for trailing zero */
    strcpy(str2, str);
    str2[len] = c;
    str2[len + 1] = '\0';
    if(str2[0] == 'n'){      
      str2 = chopN(str2, 1);
      }
    return str2;
  }

/**
 * This function calculates the length of the given string
 * We are computing the length once at this point
 *  because it is a relatively lengthy operation,
 *  and we don't want to have to compute it anew
 *  every time the i < length condition is checked.
 * Parameters:
 * - program the string containing the code we will run
 * Return Value:
 * - a list of tokens created by iterating through program
 * Example call:
 * List_Lexer_tmp("( + 1 1)");
 * expected return val: tokenlist of length 5
 */
int count_chars(char* string, char ch)//is string here replaceable by program?
{
  int count = 0;
  int i;
  int length = strlen(string);

  for (i = 0; i < length; i++){
    if (string[i] == ch){
      count++;
    }
  }
  return count;
}

int our_isnumber (char *s){
  if(s == NULL || *s == '\0' || isspace(*s)){
    return 0;
  }
  else{
    char* p;
    strtod(s, &p);
    return *p == '\0';
  }
}
