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

void linkListLongPushFront(LinkListLong* linkList, long value)
{
    linkList->count += 1;
    
    LinkListLongItem* newItem = _linkListLongCreateItem(value);
    
    if (linkList->count == 1) { linkList->first = newItem; linkList->last = newItem; return; }
    
    LinkListLongItem* oldFirst = linkList->first; // granted to exist
    
    newItem->next = oldFirst;
    
    oldFirst->previous = newItem;
    
    linkList->first = newItem;
}

void linkListLongPush(LinkListLong* linkList, long value)
{
    linkList->count += 1;
    
    LinkListLongItem* newItem = _linkListLongCreateItem(value);
    
    if (linkList->count == 1) { linkList->first = newItem; linkList->last = newItem; return; }
    
    LinkListLongItem* oldLast = linkList->last; // granted to exist
    
    newItem->previous = oldLast;
    
    oldLast->next = newItem;
    
    linkList->last = newItem;
}

void linkListLongInsert(LinkListLong* linkList, long index, long value)
{
    if (index < 1) { linkListLongPushFront(linkList, value); return; }
    
    if (index >= linkList->count) { linkListLongPush(linkList, value); return; }
    
    LinkListLongItem* currentItem = _linkListLongGetItemAt(linkList, index); // granted to exist
    
    linkList->count += 1; // messes with '_linkListLongGetItemAt'
    
    LinkListLongItem* previousItem = currentItem->previous; // granted to exist
    
    LinkListLongItem* newItem = _linkListLongCreateItem(value);
    
    previousItem->next = newItem; 
    
    newItem->previous = previousItem;
        
    newItem->next = currentItem;
    
    currentItem->previous = newItem;
}
    
long linkListLongPopFront(LinkListLong* linkList)
{
    if (linkList->count == 0) { _errorEmptyContainerAccess("linkListLongPopFront"); }
    
    LinkListLongItem* removed = linkList->first;
    
    long value = removed->value;

    linkList->count -= 1;
    
    if (linkList->count == 0) 
    { 
        linkList->first = NULL; 
        linkList->last = NULL;     
    }
    else // if (linkList->count >= 1)
    {    
        linkList->first = removed->next;

        linkList->first->previous = NULL;
    }
        
    free(removed);
    
    return value;
}

long linkListLongPop(LinkListLong* linkList)
{
    if (linkList->count == 0) { _errorEmptyContainerAccess("linkListLongPop"); }
    
    LinkListLongItem* removed = linkList->last;
    
    long value = removed->value;

    linkList->count -= 1;
    
    if (linkList->count == 0) 
    { 
        linkList->first = NULL; 
        linkList->last = NULL;     
    }
    else // if (linkList->count >= 1)
    {
        linkList->last = removed->previous;
        
        linkList->last->next = NULL;
    }
     
    free(removed);
    
    return value;
}

long linkListLongRemoveAt(LinkListLong* linkList, long index)
{
    if (index < 0  ||  index >= linkList->count) { _errorIndexOutOfBounds("linkListLongRemoveAt", index); } 
    
    if (index == 0) { return linkListLongPopFront(linkList); }
    
    if (index == linkList->count - 1) { return linkListLongPop(linkList); }
    
    LinkListLongItem* removed = _linkListLongGetItemAt(linkList, index); // not the first and not the last
    
    LinkListLongItem* previous = removed->previous; // granted to exist

    LinkListLongItem* next = removed->next; // granted to exist

    previous->next = next;

    next->previous = previous;
    
    linkList->count -= 1; // messes with '_linkListLongGetItemAt'  
    
    long value = removed->value;
    
    free(removed);
    
    return value;
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

void linkListLongClearAll(LinkListLong* linkList)
{
    LinkListLongItem* item = linkList->first;
        
    while (item != NULL) { item->value = 0; item = item->next; } 
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

