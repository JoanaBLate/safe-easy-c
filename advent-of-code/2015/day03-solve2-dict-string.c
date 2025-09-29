// solution for https://adventofcode.com/2015/day/3 part 2

#include "../safe-easy-c.h"

String mark;
    
void walkSanta(HashmapString* map, String* puzzleInput)
{
    long santaX = 0;    
    long santaY = 0;

    long robotX = santaX;
    long robotY = santaY;

    char cString[100] = "0~0\0";
    
    String key = createStringFromCString(cString);

    hashmapStringSet(map, &key, &mark);

    deleteString(&key);
    
    long off = stringSize(puzzleInput);
    
    bool isSantaTurn = true;
    
    for (long index = 0; index < off; index++)
    {        
        char step = stringByteAt(puzzleInput, index);
        
        long deltaX = 0;
        long deltaY = 0;
        
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
        
        hashmapStringSet(map, &key, &mark);
    
        deleteString(&key);
    }    
}

int main() 
{
    String filename = createStringFromLiteral("day03-input.txt");

    String _puzzleInput = readTextFile(&filename);
    
    String puzzleInput = stringTrim(&_puzzleInput);
        
    HashmapString map = createHashmapString(10000);
    
    mark = createStringFromLiteral("*");
    
    walkSanta(&map, &puzzleInput);
    
    printf("answer: %li\n", (long) hashmapStringCount(&map));
    
    deleteString(&filename);
    deleteString(&_puzzleInput);
    deleteString(&puzzleInput);
    deleteString(&mark);
    
    deleteHashmapString(&map);

    return 0;
}

