// solution for https://adventofcode.com/2015/day/2 part 2

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
      
    // perimeters:
    const long a = 2 * (width  + length);
    const long b = 2 * (height + length);
    const long c = 2 * (height + width);

    long perimeter = a;    
    if (b < perimeter) { perimeter = b; }    
    if (c < perimeter) { perimeter = c; }
    
    // for the bow
    const long volume = length * width * height;
    
    deleteBuffer(&line);

    return perimeter + volume;
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

