# c48
Contact: vtomole@iastate.edu

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
$ ./c48 hello.c48
```

You should see
```
$ Hello World

```

Congratulations on running your first C48 program!


# Conditionals

Conditionals allow the programmer to specify one more condititons to be evaluated or tested by the program including the expressions to be executed if the condition is true or if the condition is false.

The following program prints that a is less than 10 because the if statement evaluated to ```true```.

```
a = 5;

if(a < 10){
  print("A is less than 10");
 }
 else{
   print("A is more than 10");
 }

```

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




