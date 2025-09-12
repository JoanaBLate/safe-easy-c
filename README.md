# SafeEasyC (UNDER CONSTRUCTION!)

SafeEasyC is a C library that provides a safe, high-level approach to working with strings and other data structures. 

It prevents common errors such as
- use-after-free
- segmentation fault
- out-of-bounds access
<!-- - using a non-initialized variable -->

Because SafeEasyC provides so much safety, it is around 15% slower than pure C.

SafeEasyC makes C programming much easier for beginners.

Just download the file **safe-easy-c.h**, it contains the whole SafeEasyC library in it.

*Currently* SafeEasyC is for **LINUX ONLY!**

### Hello World

~~~ C

#include "safe-easy-c.h"

int main()
{
    // in SafeEasyC the type String is a struct
    String hello = createStringFromLiteral("∆  Hello World!  ∆"); 
    
    // SafeEasyC structs must be passed by reference (using '&')
    printlnString(&hello); 

    releaseHeap(&hello);
    
    return 0;
}
~~~ 

### No use-after-free in SafeEasyC functions

~~~ C

#include "safe-easy-c.h"

int main()
{
    String hello = createStringFromLiteral("Hello!");
       
    releaseHeap(&hello);
    
    // ERROR: trying to use already released object in function 'createStringClone'
    String hello2 = createStringClone(&hello);
    
    return 0;
}
~~~


### No use-after-free in your own functions

~~~ C

void myFunction(String* myString)
{
    // the function name will appear in eventual error message
    assureNotReleased(myString, "myFunction");
       
    printlnString(myString);
}
~~~ 

### Private functions

The names of *private* functions in the SafeEasyC library start with uderscore (*_name*). Never call those functions.

### Size limits

Many SafeEasyC functions parameters are of the type *long* (where theoretically they should be *size_t*). 

This is very useful for preventing many nasty bugs, but comes at the cost that you *MUST NOT* use the library for big data (size equal/greater to the max positive value of the type *long* - which exact number depends on your operating system).

For more information, search in the folder examples about this subject.

<!-- At the moment the library is comprehensive enough to solve all the puzzles of the Advent of Code. -->


