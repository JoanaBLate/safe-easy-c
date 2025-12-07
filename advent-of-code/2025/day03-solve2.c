// solution for https://adventofcode.com/2025/day/3 part 2

#include "../safe-easy-c.h"

int getBestBatteryIndex(String* bank, int from, int to) 
{
    char best = ' ';
    
    int position = 0;

    for (int index = from; index <= to; index++) 
    {    
        char digit = stringByteAt(bank, index);
        
        if (digit > best) { best = digit; position = index; }
    }
    
    return position;
}

double processBank(String* bank)
{
    Buffer buffer = createBuffer(12);
    
    int bankSize = (int) stringSize(bank);
    
    int maxBankIndex = bankSize - 1 - 12;
    
    int bankIndex = -1;
    
    for (int bufferIndex = 0; bufferIndex < 12; bufferIndex++)
    {
        maxBankIndex += 1;
        
        bankIndex = getBestBatteryIndex(bank, bankIndex + 1, maxBankIndex);
        
        char byte = stringByteAt(bank, bankIndex);  
        
        bufferSetByte(&buffer, bufferIndex, byte);
    }

    unsigned long number = bufferEatLong(&buffer).value; // assuming number is ok
    
    deleteBuffer(&buffer);
    
    return number;
}

int main() 
{
    String filename = createStringFromLiteral("day03-input.txt");

    String _puzzleInput = readTextFile(&filename);
    
    Buffer puzzleInput = convertStringIntoBuffer(&_puzzleInput); 
    
    bufferTrim(&puzzleInput);
    
    unsigned long result = 0;
    
    while (true) 
    {    
        String line = bufferEatLine(&puzzleInput);
        
        if (stringSize(&line) == 0) { break; } // need not to be deleted
        
        result += processBank(&line);
        
        deleteString(&line); 
    }

    printf("answer: %lu\n", result);

    deleteString(&filename);
    deleteBuffer(&puzzleInput);

    return 0;
}

