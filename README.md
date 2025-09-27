# SafeEasyC 

SafeEasyC is a C library that provides a safe, high-level approach to working with strings and other data structures. 

It prevents common errors such as
- double free
- use-after-free
- dangling pointers
- segmentation fault
- out-of-bounds access
<!-- - using a non-initialized variable -->

Because SafeEasyC provides so much safety, its performance is something between pure C and JavaScript (closer to pure C).

SafeEasyC makes C programming much easier for beginners.

Just download the file **safe-easy-c.h**, it contains the whole SafeEasyC library in it.

*Currently* SafeEasyC is for **LINUX ONLY!**

SafeEasyC is still evolving, but you can already use it. Check the **advent-of-code** folder.

### Hello World

~~~ C

#include "safe-easy-c.h"

int main()
{
    // in SafeEasyC the type String is a struct
    String hello = createStringFromLiteral("∆  Hello World!  ∆"); 
    
    // SafeEasyC structs must be passed by reference (using '&')
    printlnString(&hello); 

    deleteString(&hello);
    
    return 0;
}
~~~ 

### No use-after-free <!-- in SafeEasyC functions -->

~~~ C

#include "safe-easy-c.h"

int main()
{
    String hello = createStringFromLiteral("Hello!");
       
    deleteString(&hello);
    
    // ERROR: trying to use deleted object in function 'printlnString'
    printlnString(&hello);
    
    return 0;
}
~~~

### Private functions

The names of *private* functions in the SafeEasyC library start with uderscore (*_name*). Never call those functions.

### Size limits

The max size of any data structure (String, Buffer, Array...) is **9223372036854775807** bytes - which is the max positive value of the type **signed long** (in my computer), always preferred by the SafeEasyC functions.

#### Why signed types (1)

Safe Easy functions adopted *signed types* for parameters to avoid subtle and nasty bugs - [look at this example](examples/why-signed-parameters.c).

#### Why signed types (2)

The best practice tells that *unsigned types* should be used for size and index. Sounds good. 

But C uses the value -1 for indicating failure in functions of the kind *indexOf*, for example. 

So, that function must return a *signed type*. 

OK, but *signed types* have **half** the capacity of *unsigned types*. 

This means that, in case the data size is too big: BUG - that function cannot not search the whole data!!!

The index and the size must share the same type (*signed*)! 

