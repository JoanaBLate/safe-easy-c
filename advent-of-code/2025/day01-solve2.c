// solution for https://adventofcode.com/2025/day/1 part 2

#include "../safe-easy-c.h"

long result = 0;

long cursor = 50;

void processLeftRotation(long number) 
{        
    while (number >= 100) { number -= 100; result += 1; }
        
    if (number < cursor) { cursor -= number; return; }
    
    if (cursor == 0  &&  number == 0) { return; } // number may become zero when it was multiple of 100
    
    if (number == cursor) { cursor = 0; result += 1; return; }
    
    // number > cursor:

    if (cursor != 0) { result += 1; }

    cursor = cursor - number + 100;
}

void processRightRotation(long number) 
{
    while (number >= 100) { number -= 100; result += 1; }
        
    if (cursor + number < 100) { cursor += number; return; }
    
    if (cursor + number == 100) { cursor = 0; result += 1; return; }
    
    // cursor + number > 100:
    
    result += 1;
    
    cursor = cursor + number - 100;
}

int main() 
{
    String filename = createStringFromLiteral("day01-input.txt");

    String _puzzleInput = readTextFile(&filename);
    
    Buffer puzzleInput = convertStringIntoBuffer(&_puzzleInput); 
    
    bufferTrim(&puzzleInput);
    
    while (true) 
    {    
        String line = bufferEatLine(&puzzleInput);
        
        if (stringIsEmpty(&line)) { break; }
        
        int sign = (stringByteAt(&line, 0) == 'L') ? -1 : +1;
        
        String token = createSubstring(&line, 1, 9999); // excessive length is cut off
                
        NullLong nullableNumber = stringParseLong(&token);
        
        long number = nullableNumber.value; // assuming all values are good
        
        if (sign == -1) { processLeftRotation(number); } else { processRightRotation(number); } 
        
        deleteString(&line);
        deleteString(&token);
    }

    printf("answer: %li\n", result);

    deleteString(&filename);
    deleteBuffer(&puzzleInput);

    return 0;
}

