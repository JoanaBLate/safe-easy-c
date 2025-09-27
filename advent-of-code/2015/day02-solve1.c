// solution for https://adventofcode.com/2015/day/2 part 1

#include "../safe-easy-c.h"

long processPackage(Buffer* puzzleInput)
{       
    String _line = bufferEatLine(puzzleInput);
    
    Buffer line = convertStringIntoBuffer(&_line);
      
    long length = bufferEatLong(&line).value;
    
    bufferBiteStart(&line, 1); // 'x'
    
    long width = bufferEatLong(&line).value;
    
    bufferBiteStart(&line, 1); // 'x'
    
    long height = bufferEatLong(&line).value;
      
    // surfaces
    long top   = width * length;
    long side  = height * length;
    long front = height * width;

    long smallest = top;    
    if (side < smallest)  { smallest = side; }    
    if (front < smallest) { smallest = front; }

    deleteBuffer(&line);
    
    return 2 * (front + side + top) + smallest;
}

int main() 
{     
    String filename = createStringFromLiteral("day02-input.txt");

    String _puzzleInput = readTextFile(&filename);
    
    Buffer puzzleInput = convertStringIntoBuffer(&_puzzleInput);
    
    bufferTrim(&puzzleInput);
     
    long totalPaper = 0;
 
    while (true)
    {
        if (bufferIsEmpty(&puzzleInput)) { break; }
        
        totalPaper += processPackage(&puzzleInput);
    } 
    
    printf("answer: %li\n", totalPaper);
    
    deleteString(&filename);
    deleteBuffer(&puzzleInput);

    return 0;
}

