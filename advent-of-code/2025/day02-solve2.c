// solution for https://adventofcode.com/2025/day/2 part 2

#include "../safe-easy-c.h"

long result = 0;

bool checkNumberBy(char buffer[30], int home, int size, int segmentSize)
{ 
    if (size == segmentSize) { return false; }
    
    if (size % segmentSize != 0) { return false; }

    int numberOfSegments = size / segmentSize;
    
    int off = home + segmentSize;
    
    for (int index = home; index < off; index++)
    {
        char digit = buffer[index];
        
        for (int n = 1; n < numberOfSegments; n++)
        {
            char candidate = buffer[index + (n * segmentSize)];
    
            if (candidate != digit) { return false; }
        }
    }
    
    return true;
}

void checkNumber(long originalNumber) 
{
    long number = originalNumber;
    
    if (number == 0) { return; }
        
    char buffer[30];
    
    int cursor = 30;
    
    while (number > 0)
    {
        cursor -= 1;
        
        int digit = number % 10;
        
        buffer[cursor] = digit;
        
        number -= digit;
        
        if (number > 9) { number /= 10; }
    }
    
    int size = 30 - cursor; 
    
    if (checkNumberBy(buffer, cursor, size, 1)) { result += originalNumber; return; }
    if (checkNumberBy(buffer, cursor, size, 2)) { result += originalNumber; return; }
    if (checkNumberBy(buffer, cursor, size, 3)) { result += originalNumber; return; }
    if (checkNumberBy(buffer, cursor, size, 4)) { result += originalNumber; return; }
    if (checkNumberBy(buffer, cursor, size, 5)) { result += originalNumber; return; }
    if (checkNumberBy(buffer, cursor, size, 6)) { result += originalNumber; return; }
    if (checkNumberBy(buffer, cursor, size, 7)) { result += originalNumber; return; }
}

void processPair(long begin, long end)
{
     for (long number = begin; number <= end; number++) { checkNumber(number); }
}

int main() 
{
    String filename = createStringFromLiteral("day02-input.txt");

    String _puzzleInput = readTextFile(&filename);
    
    Buffer puzzleInput = convertStringIntoBuffer(&_puzzleInput); 
    
    bufferTrim(&puzzleInput);
    
    String trace = createStringFromLiteral("-");
    String comma = createStringFromLiteral(",");
    
    long index, begin, end;
    
    String token;
    
    NullLong nullableNumber;
    
    bool foundEndOfData = false;
    
    while (true) 
    {    
        index = bufferIndexOf(&puzzleInput, &trace);
        
        token = bufferEatStart(&puzzleInput, index);
        
        nullableNumber = stringParseLong(&token);
        
        begin = nullableNumber.value; // assuming value is good
        
        deleteString(&token);
        
        bufferBiteStart(&puzzleInput, 1); // '-' biting returns nothing
        
        //
        
        index = bufferIndexOf(&puzzleInput, &comma);
        
        if (index == -1) { index = bufferSize(&puzzleInput); foundEndOfData = true; }
        
        token = bufferEatStart(&puzzleInput, index);
                
        nullableNumber = stringParseLong(&token);
        
        end = nullableNumber.value; // assuming value is good
        
        deleteString(&token);
        
        processPair(begin, end);
        
        if (foundEndOfData) { break; }
        
        bufferBiteStart(&puzzleInput, 1); // ',' biting returns nothing
    }

    printf("answer: %li\n", result);

    deleteString(&trace);
    deleteString(&comma);
    deleteString(&filename);
    deleteBuffer(&puzzleInput);

    return 0;
}

