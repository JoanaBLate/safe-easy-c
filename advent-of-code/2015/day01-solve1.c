// solution for https://adventofcode.com/2015/day/1 part 1

#include "../safe-easy-c.h"

int main() 
{    
    String filename = createStringFromLiteral("day01-input.txt");

    String puzzleInput = readTextFile(&filename);   
    
    long floor = 0;

    long index = -1;
    
    while (true)    
    {
        index += 1;
        int c = stringByteAt(&puzzleInput, index);
        
        if (c == '(') { floor += 1; continue; }
        if (c == ')') { floor -= 1; continue; }
        break;
    }
    
    deleteString(&filename);
    deleteString(&puzzleInput);
    
    printf("answer: %ld\n", floor);

    return 0;
}

