// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #
/*
typedef struct {
    long   capacity;
    long   count;
    void** items;
} ArrayList;

ArrayList* newArrayList(long capacity)
{
    ArrayList* list = _allocateHeap(1 * (long) sizeof(ArrayList));
    
    list->capacity = capacity;
    
    list->count = 0;
    
    list->items = _allocateHeap(capacity * (long) sizeof(void**));

    return list;
}

void arrayListInclude(ArrayList* list, void* item)
{
    if (list->count >= list->capacity) 
    { 
        printf("\nERROR in function 'arrayListInclude': ArrayList was already full\n"); exit(1);
    }

    list->items[list->count] = item;
    
    list->count += 1;
}

// TODO void arrayListRemove // one base

void arrayListUnorderedRemove(ArrayList* list, long index) // one base
{
    if (index < 1  ||  index > list->count) 
    { 
        printf("\nERROR in function 'arrayListUnorderedRemove': index (%li) out of bounds\n", index); exit(1);
    }

    index -= 1; // adjusting to zero base
    
    long indexOfLast = list->count - 1; // zero base

    list->items[index] = list->items[indexOfLast]; // sometimes index == indexOfLast
    
    list->items[indexOfLast] = NULL;
    
    list->count -= 1;
}
*/
