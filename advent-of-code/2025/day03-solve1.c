// solution for https://adventofcode.com/2025/day/3 part 1

#include "../safe-easy-c.h"

long processBank(String* bank)
{
    int offA = stringSize(bank) - 1;
    int offB = offA + 1;
    
    char bestA = ' ';
    
    int home = 0;
    
    for (int indexA = 0; indexA < offA; indexA++) 
    {    
        char byteA = stringByteAt(bank, indexA);
        
        if (byteA > bestA) { bestA = byteA; home = indexA; }
    }
    
    char bestB = ' ';
    
    for (int indexB = home + 1; indexB < offB; indexB++) 
    {        
        char byteB = stringByteAt(bank, indexB);
        
        if (byteB > bestB) { bestB = byteB; }
    }
    
    long a = bestA - '0';
    long b = bestB - '0';
    
    return (10 * a) + b;
}

int main() 
{
    String filename = createStringFromLiteral("day03-input.txt");

    String _puzzleInput = readTextFile(&filename);
    
    Buffer puzzleInput = convertStringIntoBuffer(&_puzzleInput); 
    
    bufferTrim(&puzzleInput);
    
    long result = 0;
    
    while (true) 
    {    
        String line = bufferEatLine(&puzzleInput);
        
        if (stringSize(&line) == 0) { deleteString(&line); break; }
        
        result += processBank(&line);
        
        deleteString(&line); 
    }

    printf("answer: %li\n", result);

    deleteString(&filename);
    deleteBuffer(&puzzleInput);

    return 0;
}

