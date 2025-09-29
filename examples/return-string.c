
#include "safe-easy-c.h"

String getMessage()
{
    return createStringFromLiteral("∆  Hello World!  ∆");
}

int main()
{
    String message = getMessage();
    
    printlnString(&message); 

    deleteString(&message);
    
    return 0;
}
