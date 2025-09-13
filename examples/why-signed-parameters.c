
#include "safe-easy-c.h"

// when receives -1, converts it to 18446744073709551615 (my computer)
void wantSmallPositiveInteger(unsigned long smallPositiveInteger)
{
    printf("received %lu \n", smallPositiveInteger); 
}

int main()
{
    // the compiler might warn about
    // unsigned conversion from ‘int’ to ‘long unsigned int’,
    // but the compilation will happen
    // there is no way to prevent the programmer
    // of sending negative number,
    // that's why all SafeEasyC library functions
    // avoids unsigned parameters: very easy to
    // create a huge but subtle bug
    wantSmallPositiveInteger(-1);     
    
    return 0;
}



