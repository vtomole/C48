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

# Syntax
A c48 program is composed of tokens. A token can be a keyword, and identifier, a constant, a string, or a symbol.

--**Comments** are ignored by the intepreter. They can start as // or /* */.

--**Identifiers** is a name used to indetify a variable, function, or anything else a user has defined. These are case sensitive

```
square x ascv hello 

```


--**Keywords** are reserved so that you cannot uses them as a constant or any other identifiers

```
case fun struct 
else if switch
for return

```


# Data types
--**Booleans** are either ```True``` or ```False```

--**Numbers** can be integers(```1``` and ```2```)

--**Characters** are a single byte of an integer type. ```A```

--**Strings** are sequences of Unicode characters. ```"Hello World"```

--**Lists** are a linear collections of elements. ```(1, 2, 3, 4, 5)```

--**Arrays** Can store a collection of elements that can be identified by the index. ```int balance[5] = {1, 2.0, 3, 4, 5};```

--**Functions** are procedures that return values. ```int add (int x, int y) { return x + y}; ```

# Loops

Loops are for executing a block of code several times. The following loop prints "Hello C48" 10 times in a row.

```
for(i = 0; i < 10; i++){
  print("Hello C48");
 }		   

```

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




