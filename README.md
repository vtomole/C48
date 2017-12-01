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



# Syntax
A c48 program is composed of tokens. A token can be a keyword, and identifier, a constant, a string, or a symbol
--**Comments** are ignored by the intepreter. They can start as // or /* */.

--**Identifiers** is a name used to indetify a variable, function, or anything else a user has defined. These are case sensitive

```
square x ascv hello 

```


--**Keywords** are reserved so that you cannot uses them as a constant or any other identifiers

```
case fun struct 
else if switch
for return while

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

# Conditions


# Structures

A structure is a type that allows a programmers to hold several data types of different kinds

```
struct node {
   int value;
   node next;
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

# Examples

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

```
fun quickSort(arr){
  less = [];
  pivotList = [];
  more = [];
  if(size(arr) <= 1){
    return arr;
  }
  else{
    pivot = arr[0];
    for (i=0; i < size(arr); i++){
      if (i < pivot){
	less.append(i);
      }
      else if (i > pivot){
	more.append(i);
      }
      else{
	pivotList.append(i);
      }
      less = quickSort(less);
      more = quickSort(more);
      return less + pivotList + more;
      }
    }
}

```



Reference: rosettacode.org/wiki/Category:Programming_Tasks