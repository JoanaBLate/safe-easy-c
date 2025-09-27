// solution for https://adventofcode.com/2015/day/5 part 2

#include "../safe-easy-c.h"

bool pairsOk(String* line)
{
    long size = stringSize(line);
    
    // last character cannot start a pair
    for (long indexA = 0; indexA < size - 1; indexA++) 
    {
        const char a = stringByteAt(line, indexA);
        const char b = stringByteAt(line, indexA + 1);
        
        for (long indexB = indexA + 2; indexB < size; indexB++) 
        {
            const char c = stringByteAt(line, indexB);
            const char d = stringByteAt(line, indexB + 1);
        
            if (a != c) { continue; }
            if (b != d) { continue; }
            
            return true;
        }
    }
        
    return false;
}

bool betweenOk(String* line)
{
    long size = stringSize(line);
    
    // penultimate (or last) character cannot start a trio
    for (long index = 0; index < size - 2; index++)
    {
        const char a = stringByteAt(line, index);
        const char c = stringByteAt(line, index + 2);
        
        if (a == c) { return true; }
    }

    return false;
}

bool lineIsOk(String* line)
{
    if (! pairsOk(line)) { return false; }

    if (! betweenOk(line))  { return false; }

    return true;
}

int main() 
{    
    String filename = createStringFromLiteral("day05-input.txt");

    String _puzzleInput = readTextFile(&filename);
    
    Buffer puzzleInput = convertStringIntoBuffer(&_puzzleInput);
    
    bufferTrimEnd(&puzzleInput);
    
    int count = 0;
    
    while (true)
    {
        String line = bufferEatLine(&puzzleInput);
        
        if (stringIsEmpty(&line)) { break; }

        if (lineIsOk(&line)) { count += 1; }
        
        deleteString(&line);
    }
    
    printf("answer: %i\n", count);
    
    deleteString(&filename);
    deleteString(&_puzzleInput);
    deleteBuffer(&puzzleInput);
    
    return 0;
} 

