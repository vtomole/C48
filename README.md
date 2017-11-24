# c48
Contact: sdmay18-35@iastate.edu

**C48 tutorial**

1. c48/src$ cd src
2. c48/src$ make

Now that you have built the interpreter you can start writing programs.

Open up a file call hello.c48 and write this

```
/*The following line calls the print function "Hello World" as the parameter */
fun main(){
//This is how functions are defined, the main function is the first function that the interpreter calls
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





