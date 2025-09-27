// solution for https://adventofcode.com/2015/day/3 part 1

#include "../safe-easy-c.h"
    
String mark;
    
void walkSanta(HashmapString* map, String* puzzleInput)
{
    long santaX = 0;    
    long santaY = 0;

    char cString[100] = "0~0\0";
    
    String key = createStringFromCString(cString);

    hashmapStringSet(map, &key, &mark);

    deleteString(&key);
    
    long off = stringSize(puzzleInput);
    
    for (long index = 0; index < off; index++)
    {        
        char step = stringByteAt(puzzleInput, index);
    
        if (step == '>') { santaX += 1; }
        
        else if (step == '<') { santaX -= 1; }
        
        else if (step == '^') { santaY += 1; }
        
        else if (step == 'v') { santaY -= 1; }
        
        else { printf("error"); exit(1); }
        
        sprintf(cString, "%li~%li", santaY, santaX);
        
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

