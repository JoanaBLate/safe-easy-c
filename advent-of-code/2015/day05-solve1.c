// solution for https://adventofcode.com/2015/day/5 part 1

#include "../safe-easy-c.h"

bool vowelsOk(String* line)
{
    long vowels = 0;
    
    long size = stringSize(line);

    for (long index = 0; index < size; index++) 
    { 
        const char c = stringByteAt(line, index);
        
        if (c == 'a') { vowels += 1; continue; }
        if (c == 'e') { vowels += 1; continue; }
        if (c == 'i') { vowels += 1; continue; }
        if (c == 'o') { vowels += 1; continue; }
        if (c == 'u') { vowels += 1; continue; }
    }
    
    return vowels > 2;
}

bool twiceOk(String* line)
{
    long size = stringSize(line);
    
    for (long index = 0; index < size - 1; index++) // last character cannot start a pair
    {
        const char a = stringByteAt(line, index);
        const char b = stringByteAt(line, index + 1);
        
        if (a == b) { return true; }
    }
    
    return false;
}

bool forbiddenOk(String* line)
{
    long size = stringSize(line);
    
    for (long index = 0; index < size - 1; index++) // last character cannot start a pair
    {
        const char a = stringByteAt(line, index);
        const char b = stringByteAt(line, index + 1);
        
        if (a == 'a'  &&  b == 'b') { return false; }
        if (a == 'c'  &&  b == 'd') { return false; }
        if (a == 'p'  &&  b == 'q') { return false; }
        if (a == 'x'  &&  b == 'y') { return false; }
    }

    return true;
}

bool lineIsOk(String* line)
{
    if (! vowelsOk(line)) { return false; }

    if (! twiceOk(line))  { return false; }

    if (! forbiddenOk(line)) { return false; }

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

