
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

