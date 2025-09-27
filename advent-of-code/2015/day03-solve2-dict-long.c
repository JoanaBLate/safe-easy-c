// solution for https://adventofcode.com/2015/day/3 part 2

#include "../safe-easy-c.h"

void walkSanta(HashmapLong* map, String* puzzleInput)
{
    long santaX = 0;    
    long santaY = 0;

    long robotX = santaX;
    long robotY = santaY;

    char cString[100] = "0~0\0";
    
    String key = createStringFromCString(cString);
    
    hashmapLongSet(map, &key, 1);
    
    deleteString(&key);
    
    bool isSantaTurn = true;
    
    long off = stringSize(puzzleInput);

    for (long index = 0; index < off; index++)
    {        
        long deltaX = 0;
        long deltaY = 0;
        
        char step = stringByteAt(puzzleInput, index);
    
        if (step == '>') { deltaX += 1; }
        
        else if (step == '<') { deltaX -= 1; }
        
        else if (step == '^') { deltaY += 1; }
        
        else if (step == 'v') { deltaY -= 1; }
        
        else { printf("error"); exit(1); }
        
        if (isSantaTurn)
        {
            isSantaTurn = false;
            santaX += deltaX;
            santaY += deltaY;
            sprintf(cString, "%li~%li", santaX, santaY);
        }
        else
        {
            isSantaTurn = true;         
            robotX += deltaX;
            robotY += deltaY;
            sprintf(cString, "%li~%li", robotX, robotY);    
        }
                
        String key = createStringFromCString(cString);       
        
        hashmapLongSet(map, &key, 1);
    
        deleteString(&key);
    }    
}

int main() 
{
    String filename = createStringFromLiteral("day03-input.txt");

    String _puzzleInput = readTextFile(&filename);
    
    String puzzleInput = stringTrim(&_puzzleInput);
        
    HashmapLong map = createHashmapLong(10000);
    
    walkSanta(&map, &puzzleInput);
    
    printf("answer: %li\n", hashmapLongCount(&map));
    
    deleteString(&filename);
    deleteString(&_puzzleInput);
    deleteString(&puzzleInput);
    
    deleteHashmapLong(&map);

    return 0;
}

