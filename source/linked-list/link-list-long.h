// # Copyright (c) 2024 - 2025 Feudal Code limitada - MIT license #

typedef struct
{
    long value;
    void* previous;
    void* next; 
} LinkListLongItem;

typedef struct
{
    long count;
    LinkListLongItem* first;
    LinkListLongItem* last;
} LinkListLong;

// all items are allocated directly on the heap
LinkListLongItem* _linkListLongCreateItem(long value)
{
    LinkListLongItem* item = _allocateHeap(sizeof(LinkListLongItem));
    
    item->value = value;

    item->previous = NULL;
    
    item->next = NULL;
    
    return item;
}

LinkListLong createLinkListLong() 
{
    LinkListLong linkList = { 0, NULL, NULL };
    
    return linkList;
}

long linkListLongCount(LinkListLong* linkList)
{
    return linkList->count;
}

long linkListLongIsEmpty(LinkListLong* linkList)
{
    return linkList->count != 0;
}

LinkListLongItem* _linkListLongGetItemAt(LinkListLong* linkList, long index)
{
 // private function, index already checked
 // if (index < 0  ||  index >= linkList->count) { _errorIndexOutOfBounds(_linkListLongGetItemAt, index); } 

    if (index < linkList->count / 2)
    {
        LinkListLongItem* item = linkList->first;
        
        long n = 0;
        
        while (true)
        {
            if (n == index) { return item; }
        
            n += 1;
            
            item = item->next;            
        }    
    }
    else // runs backwards
    {
        LinkListLongItem* item = linkList->last;
        
        long n =  linkList->count - 1;
        
        while (true)
        {
            if (n == index) { return item; }
        
            n -= 1;
            
            item = item->previous;            
        }    
    }
    return NULL; // pleasing the compiler ;)
}

bool linkListLongIndexExists(LinkListLong* linkList, long index) 
{
    if (index < 0) { return false; }
    
    return index < linkList->count;
} 

long linkListLongGet(LinkListLong* linkList, long index)
{
    if (index < 0  ||  index >= linkList->count) { _errorIndexOutOfBounds("linkListLongGet", index); }    

    return _linkListLongGetItemAt(linkList, index)->value;
}

long linkListLongGetFirst(LinkListLong* linkList)
{
    if (linkList->count == 0) { _errorEmptyContainerAccess("linkListLongGetFirst"); }
    
    return linkList->first->value; 
}
    
long linkListLongGetLast(LinkListLong* linkList)
{
    if (linkList->count == 0) { _errorEmptyContainerAccess("linkListLongGetLast"); }
    
    return linkList->last->value; 
}

void linkListLongSet(LinkListLong* linkList, long index, long value)
{
    if (index < 0  ||  index >= linkList->count) { _errorIndexOutOfBounds("linkListLongSet", index); }    

    _linkListLongGetItemAt(linkList, index)->value = value;
}

void linkListLongPushFirst(LinkListLong* linkList, long value)
{
    linkList->count += 1;
    
    LinkListLongItem* oldFirst = linkList->first;
    
    LinkListLongItem* newItem = _linkListLongCreateItem(value);
    
    linkList->first = newItem;
    
    if (linkList->count == 1) { return; }
    
    newItem->next = oldFirst;
    
    oldFirst->previous = newItem;
}

void linkListLongPush(LinkListLong* linkList, long value)
{
    linkList->count += 1;
    
    LinkListLongItem* oldLast = linkList->first;
    
    LinkListLongItem* newItem = _linkListLongCreateItem(value);
    
    linkList->last = newItem;
    
    if (linkList->count == 1) { return; }
    
    newItem->previous = oldLast;
    
    oldLast->next = newItem;
}

void linkListLongInsert(LinkListLong* linkList, long value, long index)
{
    if (index < 1) { linkListLongPushFirst(linkList, value); return; }
    
    if (index >= linkList->count) { linkListLongPush(linkList, value); return; }

    linkList->count += 1;
    
    LinkListLongItem* nextItem = _linkListLongGetItemAt(linkList, index);
    
    LinkListLongItem* previousItem = nextItem->previous;
    
    LinkListLongItem* newItem = _linkListLongCreateItem(value);
    
    if (previousItem != NULL) { previousItem->next = newItem; newItem->previous = previousItem; }
        
    newItem->next = nextItem;
    
    nextItem->previous = newItem;
}
    
long linkListLongPopFirst(LinkListLong* linkList)
{
    if (linkList->count == 0) { _errorEmptyContainerAccess("linkListLongPopFirst"); }

    linkList->count -= 1;
    
    LinkListLongItem* deleted = linkList->first;
    
    linkList->first = deleted->next;
    
    linkList->first->previous = NULL;
    
    long value = deleted->value;
    
    free(deleted);
    
    return value;
}

long linkListLongPop(LinkListLong* linkList)
{
    if (linkList->count == 0) { _errorEmptyContainerAccess("linkListLongPop"); }

    linkList->count -= 1;
    
    LinkListLongItem* deleted = linkList->last;
    
    linkList->last = deleted->previous;
    
    long value = deleted->value;
    
    free(deleted);
    
    return value;
}

long linkListLongRemoveAt(LinkListLong* linkList, long index)
{
    if (index < 0  ||  index >= linkList->count) { _errorIndexOutOfBounds("linkListLongRemoveAt", index); } 
    
    if (index == 0) { return linkListLongPopFirst(linkList); }
    
    if (index == linkList->count - 1) { return linkListLongPop(linkList); }
    
    linkList->count -= 1;  
    
    LinkListLongItem* deleted = _linkListLongGetItemAt(linkList, index);

    LinkListLongItem* previous = deleted->previous;

    LinkListLongItem* next = deleted->next;

    if (previous != NULL) { previous->next = next; }

    if (next != NULL) { next->previous = previous; }
    
    long value = deleted->value;
    
    free(deleted);
    
    return value;
}

void linkListLongClearAll(LinkListLong* linkList)
{
    LinkListLongItem* item = linkList->first;
        
    while (item != NULL) { item->value = 0; item = item->next; } 
}

void linkListLongDeleteAll(LinkListLong* linkList)
{
    LinkListLongItem* item = linkList->first;
        
    while (item != NULL)
    {
        LinkListLongItem* next = item->next;            
        
        free(item);
    
        item = next;
    } 
    
    linkList->count = 0;
    linkList->first = NULL;
    linkList->last  = NULL;
}

long long linkListLongSum(LinkListLong* linkList)
{
    long long result = 0;
            
    LinkListLongItem* item = linkList->first;
        
    while (item != NULL) { result += item->value; item = item->next; } 
    
    return result;
}

void linkListLongPrintAll(LinkListLong* linkList)
{
    printf("{LinkListLong count: %li}   [", linkListLongCount(linkList));
        
    LinkListLongItem* item = linkList->first;
        
    while (item != NULL) { printf("  %li", item->value); item = item->next; } 
    
    printf("  ]\n");
}

