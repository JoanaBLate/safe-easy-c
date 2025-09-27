// solution for https://adventofcode.com/2015/day/1 part 2

#include "../safe-easy-c.h"

int main() 
{    
    String filename = createStringFromLiteral("day01-input.txt");

    String puzzleInput = readTextFile(&filename);
    
    long position = 0;
    
    long floor = 0;

    long index = -1;
    
    while (true)    
    {
        index += 1;
        int c = stringByteAt(&puzzleInput, index);
        
        if (c == '(') { floor += 1; }
        if (c == ')') { floor -= 1; }
        
        // NOT EXPECTING TO REACH THE END OF THE FILE!!!
        
        if (floor == -1) { position = index + 1; break; }
    }
    
    printf("answer: %ld\n", position);
    
    deleteString(&filename);
    deleteString(&puzzleInput);

    return 0;
}

