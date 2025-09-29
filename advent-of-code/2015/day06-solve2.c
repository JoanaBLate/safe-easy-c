// solution for https://adventofcode.com/2015/day/6 part 2

#include "../safe-easy-c.h"

long grid[1000 * 1000];

void actionOff(long rowA, long rowB, long colA, long colB)
{
    for (long row = rowA; row <= rowB; row++)
    {
        for (long col = colA; col <= colB; col++)
        {
            long index = row * 1000 + col;
            
            if (grid[index] > 0) {  grid[index] -= 1; }
        }
    }
}

void actionOn(long rowA, long rowB, long colA, long colB)
{
    for (long row = rowA; row <= rowB; row++)
    {
        for (long col = colA; col <= colB; col++)
        {
            long index = row * 1000 + col;
            
            grid[index] += 1;
        }
    }
}

void actionToggle(long rowA, long rowB, long colA, long colB)
{
    for (long row = rowA; row <= rowB; row++)
    {
        for (long col = colA; col <= colB; col++)
        {
            long index = row * 1000 + col;
            
            grid[index] += 2;
        }
    }
}  

void processLine(Buffer* line)
{   
    String on = createStringFromLiteral("on");
    String off = createStringFromLiteral("off");
    String toggle = createStringFromLiteral("toggle");

    String action = bufferEatToken(line);
    
    if (! stringsAreEqual(&action, &toggle)) { deleteString(&action); action = bufferEatToken(line); }
    
    long rowA = bufferEatLong(line).value;
    
    bufferBiteStart(line, 1); // ','
    
    long colA = bufferEatLong(line).value;
    
    bufferBiteToken(line); // 'through'
    
    long rowB = bufferEatLong(line).value;
    
    bufferBiteStart(line, 1); // ','
    
    long colB = bufferEatLong(line).value;
    
    if (stringsAreEqual(&action, &on))
    { 
        actionOn(rowA, rowB, colA, colB);
    }
    else if (stringsAreEqual(&action, &off))
    { 
        actionOff(rowA, rowB, colA, colB);
    }
    else 
    { 
        actionToggle(rowA, rowB, colA, colB);
    }
    
    deleteString(&on);
    deleteString(&off);
    deleteString(&toggle);
    deleteString(&action);
}

void clearGrid()
{
    for (long index = 0; index < 1000 * 1000; index++)
    {
        grid[index] = 0;
    }
}

long countLitLights()
{
    long count = 0;
    
    for (long index = 0; index < 1000 * 1000; index++)
    {
        count += grid[index];
    }

    return count;
}

int main() 
{    
    String filename = createStringFromLiteral("day06-input.txt");
    
    String _puzzleInput = readTextFile(&filename);
    
    Buffer puzzleInput = convertStringIntoBuffer(&_puzzleInput);
    
    bufferTrim(&puzzleInput);
        
    clearGrid();
    
    while (true)
    {
        String _line = bufferEatLine(&puzzleInput);
        
        Buffer line = convertStringIntoBuffer(&_line);
        
        bufferTrim(&line);
        
        if (bufferSize(&line) == 0) { deleteBuffer(&line); break; }

        processLine(&line);
        
        deleteBuffer(&line);
    }
        
    printf("answer: %li\n", countLitLights());
    
    deleteString(&filename);
    deleteBuffer(&puzzleInput);

    return 0;
} 

