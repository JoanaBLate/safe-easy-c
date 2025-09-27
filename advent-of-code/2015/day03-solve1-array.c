// solution for https://adventofcode.com/2015/day/3 part 1

#include "../safe-easy-c.h"

typedef struct
{
    int north;
    int south;
    int west;
    int east;

} Coordinates;

void findEdges(String puzzleInput, Coordinates* coords)
{
    long coordX = 0;
    long coordY = 0;
        
    for (long index = 0; index < puzzleInput.size; index++)
    {        
        char step = puzzleInput.address[index];
    
        if (step == '>') { coordX += 1; }
        
        else if (step == '<') { coordX -= 1; }
        
        else if (step == '^') { coordY += 1; }
        
        else if (step == 'v') { coordY -= 1; }
        
        else { printf("error"); exit(1); }
        
        if (coordX > coords->east) { coords->east = coordX; }
        if (coordX < coords->west) { coords->west = coordX; }
        
        if (coordY > coords->north) { coords->north = coordY; }
        if (coordY < coords->south) { coords->south = coordY; }
    }

    coords->south *= -1; coords->west *= -1;
}

long walkSanta(String puzzleInput, char* map, long horizontal, long santaX, long santaY)
{
    long homeIndex = santaY * horizontal + santaX;
    
    map[homeIndex] = 1;
    
    long total = 1;
    
    for (long index = 0; index < puzzleInput.size; index++)
    {        
        char step = puzzleInput.address[index];
    
        if (step == '>') { santaX += 1; }
        
        else if (step == '<') { santaX -= 1; }
        
        else if (step == '^') { santaY += 1; }
        
        else if (step == 'v') { santaY -= 1; }
        
        else { printf("error"); exit(1); }
        
        long house = santaY * horizontal + santaX;
        
        if (map[house] == 0) { map[house] = 1; total += 1; }
    }
    
    return total;
}

int main() 
{     
    String filename = createStringFromLiteral("day03-input.txt");

    String _puzzleInput = readTextFile(&filename);
    
    String puzzleInput = stringTrim(&_puzzleInput);
    
    Coordinates coords = { 0 };
    
    findEdges(puzzleInput, &coords);
    
    long vertical = coords.north + 1 + coords.south; // +1 for the base house Y coordinate
    
    long horizontal = coords.east + 1 + coords.west; // +1 for the base house X coordinate   
    
    long houses = vertical * horizontal; // smallest possible map
    
    char* map = calloc((unsigned long) houses, sizeof(char)); // coords 0,0 means the northwestern corner
 
    long santaX = coords.west;  // adjusted
    long santaY = coords.south; // adjusted
    
    long total = walkSanta(puzzleInput, map, horizontal, santaX, santaY);
    
    printf("answer: %li\n", total);
    
    deleteString(&filename);
    deleteString(&_puzzleInput);
    deleteString(&puzzleInput);
    free(map);

    return 0;
}    

