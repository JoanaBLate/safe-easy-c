
#include "safe-easy-c.h"

int main()
{
    String hello = createStringFromLiteral("Hello!");
       
    deleteString(&hello);
    
    // ERROR: trying to use already deleted object in function 'printlnString'
    printlnString(&hello);
    
    return 0;
}
