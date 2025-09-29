// solution for https://adventofcode.com/2015/day/6 part 1

#include "../safe-easy-c.h"

const long DIM = 1000;

String on;
String off;
String toggle;

void actionOff(Buffer* grid, long rowA, long rowB, long colA, long colB)
{
    for (long row = rowA; row <= rowB; row++)
    {
        for (long col = colA; col <= colB; col++)
        {
            long index = row * DIM + col;
            
            bufferSetByte(grid, index, 0);
        }
    }
}
     
void actionOn(Buffer* grid, long rowA, long rowB, long colA, long colB)
{
    for (long row = rowA; row <= rowB; row++)
    {
        for (long col = colA; col <= colB; col++)
        {
            long index = row * DIM + col;
            
            bufferSetByte(grid, index, 1);
        }
    }
}
     
void actionToggle(Buffer* grid, long rowA, long rowB, long colA, long colB)
{
    for (long row = rowA; row <= rowB; row++)
    {
        for (long col = colA; col <= colB; col++)
        {
            long index = row * DIM + col;
            
            char byte = (bufferByteAt(grid, index) == 0) ? 1 : 0;
                
            bufferSetByte(grid, index, byte);
        }
    }
}   

void processLine(Buffer* line, Buffer* grid)
{   
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
        actionOn(grid, rowA, rowB, colA, colB);
    }
    else if (stringsAreEqual(&action, &off))
    { 
        actionOff(grid, rowA, rowB, colA, colB);
    }
    else 
    { 
        actionToggle(grid, rowA, rowB, colA, colB);
    }

    deleteString(&action);  
}

long countLitLights(Buffer* grid)
{
    long count = 0;
    
    long capacity = bufferCapacity(grid);
        
    for (long index = 0; index < capacity; index++)
    {
        if (bufferByteAt(grid, index) != 0) { count += 1; }
    }

    return count;
}

int main() 
{    
    String filename = createStringFromLiteral("day06-input.txt");
    
    String _puzzleInput = readTextFile(&filename);
    
    Buffer puzzleInput = convertStringIntoBuffer(&_puzzleInput);
    
    bufferTrim(&puzzleInput);

    Buffer grid = createBuffer(DIM * DIM); 
    
    on = createStringFromLiteral("on");
    off = createStringFromLiteral("off");
    toggle = createStringFromLiteral("toggle");
    
    while (true)
    {
        String _line = bufferEatLine(&puzzleInput);
        
        Buffer line = convertStringIntoBuffer(&_line);
        
        bufferTrim(&line);
        
        if (bufferSize(&line) == 0) { deleteBuffer(&line); break; }

        processLine(&line, &grid);
        
        deleteBuffer(&line);
    }
        
    printf("answer: %li\n", countLitLights(&grid));
    
    deleteString(&filename);
    deleteString(&on);
    deleteString(&off);
    deleteString(&toggle);
    deleteBuffer(&puzzleInput);
    deleteBuffer(&grid);

    return 0;
} 

