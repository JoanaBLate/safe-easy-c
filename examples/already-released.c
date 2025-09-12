
#include "safe-easy-c.h"

int main()
{
    String hello = createStringFromLiteral("Hello!");
       
    releaseHeap(&hello);
    
    // ERROR: trying to use already released object in function 'printlnString'
    printlnString(&hello);
    
    return 0;
}
