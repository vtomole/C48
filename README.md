# c48
Contact: sdmay18-35@iastate.edu

# Getting started

1. c48/src$ cd src
2. c48/src$ make

Now that you have built the interpreter you can start writing programs.

Open up a file call hello.c48 and write this

```
//This is how functions are defined, the main function is the first function that the interpreter calls
fun main(){

//The following line calls the print function "Hello World" as the parameter
print("Hello World");
}
```

Now you can run this program through the interpreter to execute it

```
$ make

$ ./repl hello.c48
```

You should see
```
$ Hello World

```

Congratulations on running your first C48 program!

Every general purpose programming language usually contains:

- Functions
- Variables
- Expressions
- Comments

Comments are ignored by the compiler. They can start as // or /* */.



# Syntax

# Data types

# Strings

# Variables

# Loops

# Conditions

# Functions

# Arrays

# Lists

# Structs

# Recursion

Recursion is when a functions is defined in terms of itself. It is when a function calls itself. One recursive program is called the factorial. Here is the factorial in C48

```
fun factorial(i){
   if(i == 1) {
      return 1;
   }
   return i * factorial(i - 1);
}

fun main() { 
   i = 5;
   print (factorial(i));
}

```

This should give you the factorial of 5, which is 120.

# Examples

## Universal Turing Machine

## FizzBuzz
What is is: A program that prints integers from 1 to 100
- For multiples of 3, print Fizz instead of the number
- For multiples of 5 print Buzz instead of the number
- For multiples of 3 and 5 print FizzBuzz instead of the number

```
func main (){
  for(i = 0; i < 100; i++){
    if(i % 3 == 0){
      print("Fizz");
    }
    else if (i % 5 == 0){
      print("Buzz");
    }
    else if (i % 3 == 0 || i %5 == 0){
      print("FizzBuzz");
    }
    else{
      print(i);
    }
  }
}

```

## QuickSort

## MergeSort

## Breadth-first search

## Depth-first search

## Dijkstra's algorithm