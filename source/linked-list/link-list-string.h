// # Copyright (c) 2024 - 2025 Feudal Code limitada - MIT license #

typedef struct
{
    String* pointer;
    void* previous;
    void* next; 
} LinkListStringItem;

typedef struct
{
    long count;
    LinkListStringItem* first;
    LinkListStringItem* last;
} LinkListString;

// all items are allocated directly on the heap
LinkListStringItem* _linkListStringCreateItem(String* string)
{
 // if (string->address == NULL) { _errorAlreadyReleased("_linkListStringCreateItem"); } // no need, inner function

    LinkListStringItem* item = _allocateHeap(sizeof(LinkListStringItem));
    
    item->pointer = _createStringCloneOnHeap(string);

    item->previous = NULL;
    
    item->next = NULL;
    
    return item;
}

LinkListString createLinkListString() 
{
    LinkListString linkList = { 0, NULL, NULL };
    
    return linkList;
}

long linkListStringCount(LinkListString* linkList)
{
    return linkList->count;
}

bool linkListStringIsEmpty(LinkListString* linkList)
{
    return linkList->count != 0;
}

LinkListStringItem* _linkListStringGetItemAt(LinkListString* linkList, long index)
{
 // private function, index already checked
 // if (index < 0  ||  index >= linkList->count) { _errorIndexOutOfBounds(_linkListStringGetItemAt, index); } 

    if (index < linkList->count / 2)
    {
        LinkListStringItem* item = linkList->first;
        
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
        LinkListStringItem* item = linkList->last;
        
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

bool linkListStringIndexExists(LinkListString* linkList, long index) 
{
    if (index < 0) { return false; }
    
    return index < linkList->count;
} 

String linkListStringGet(LinkListString* linkList, long index)
{
    if (index < 0  ||  index >= linkList->count) { _errorIndexOutOfBounds("linkListStringGet", index); }    

    String* pointer = _linkListStringGetItemAt(linkList, index)->pointer;
    
    return createStringClone(pointer);
}

String linkListStringGetFirst(LinkListString* linkList)
{
    if (linkList->count == 0) { _errorEmptyContainerAccess("linkListStringGetFirst"); }
    
    String* pointer = linkList->first->pointer;
    
    return createStringClone(pointer);
}
    
String linkListStringGetLast(LinkListString* linkList)
{
    if (linkList->count == 0) { _errorEmptyContainerAccess("linkListStringGetLast"); }
    
    String* pointer = linkList->last->pointer;
    
    return createStringClone(pointer);
}

void linkListStringSet(LinkListString* linkList, long index, String* string)
{
    if (index < 0  ||  index >= linkList->count) { _errorIndexOutOfBounds("linkListStringSet", index); } 
    
    LinkListStringItem* item = _linkListStringGetItemAt(linkList, index); 
    
    deleteString(item->pointer);

    free(item->pointer);

    item->pointer = _createStringCloneOnHeap(string);
}

void linkListStringPushFront(LinkListString* linkList, String* string)
{
    linkList->count += 1;
    
    LinkListStringItem* newItem = _linkListStringCreateItem(string);
    
    if (linkList->count == 1) { linkList->first = newItem; linkList->last = newItem; return; }
    
    LinkListStringItem* oldFirst = linkList->first; // granted to exist
    
    newItem->next = oldFirst;
    
    oldFirst->previous = newItem;
    
    linkList->first = newItem;
}

void linkListStringPush(LinkListString* linkList, String* string)
{
    linkList->count += 1;
    
    LinkListStringItem* newItem = _linkListStringCreateItem(string);
    
    if (linkList->count == 1) { linkList->first = newItem; linkList->last = newItem; return; }
    
    LinkListStringItem* oldLast = linkList->last; // granted to exist
    
    newItem->previous = oldLast;
    
    oldLast->next = newItem;
    
    linkList->last = newItem;
}

void linkListStringInsert(LinkListString* linkList, long index, String* string)
{
    if (index < 1) { linkListStringPushFront(linkList, string); return; }
    
    if (index >= linkList->count) { linkListStringPush(linkList, string); return; }
    
    LinkListStringItem* currentItem = _linkListStringGetItemAt(linkList, index); // granted to exist
    
    linkList->count += 1; // messes with '_linkListStringGetItemAt'
    
    LinkListStringItem* previousItem = currentItem->previous; // granted to exist
    
    LinkListStringItem* newItem = _linkListStringCreateItem(string);
    
    previousItem->next = newItem; 
    
    newItem->previous = previousItem;
        
    newItem->next = currentItem;
    
    currentItem->previous = newItem;
}

String linkListStringPopFront(LinkListString* linkList)
{
    if (linkList->count == 0) { _errorEmptyContainerAccess("linkListStringPopFront"); }
    
    LinkListStringItem* removed = linkList->first;
    
    String* pointer = removed->pointer;

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
    
    String result = _makeStructString(pointer->address, pointer->size);
    
    free(pointer);
    
    free(removed);
    
    return result;
}

String linkListStringPop(LinkListString* linkList)
{
    if (linkList->count == 0) { _errorEmptyContainerAccess("linkListStringPop"); }
    
    LinkListStringItem* removed = linkList->last;
    
    String* pointer = removed->pointer;

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
    
    String result = _makeStructString(pointer->address, pointer->size);
    
    free(pointer);
    
    free(removed);
    
    return result;
}

String linkListStringRemoveAt(LinkListString* linkList, long index)
{
    if (index < 0  ||  index >= linkList->count) { _errorIndexOutOfBounds("linkListStringRemoveAt", index); } 
    
    if (index == 0) { return linkListStringPopFront(linkList); }
    
    if (index == linkList->count - 1) { return linkListStringPop(linkList); }
    
    LinkListStringItem* removed = _linkListStringGetItemAt(linkList, index); // not the first and not the last
    
    LinkListStringItem* previous = removed->previous; // granted to exist

    LinkListStringItem* next = removed->next; // granted to exist

    previous->next = next;

    next->previous = previous;
    
    linkList->count -= 1; // messes with '_linkListStringGetItemAt'  
    
    String* pointer = removed->pointer;
    
    String result = _makeStructString(pointer->address, pointer->size);
    
    free(pointer);
    
    free(removed);
    
    return result;
}
 
void linkListStringDeleteAll(LinkListString* linkList)
{
    LinkListStringItem* item = linkList->first;
        
    while (item != NULL)
    {
        LinkListStringItem* next = item->next;            
        
        deleteString(item->pointer);
        
        free(item->pointer); // the struct String on the heap
        
        free(item);
    
        item = next;
    } 
    
    linkList->count = 0;
    linkList->first = NULL;
    linkList->last  = NULL;
}

void linkListStringClearAll(LinkListString* linkList)
{
    LinkListStringItem* item = linkList->first;
        
    while (item != NULL) { 
    
        deleteString(item->pointer);
        
        free(item->pointer);
    
        item->pointer = _createEmptyStringOnHeap(); 
        
        item = item->next; 
    } 
}

void linkListStringPrintAll(LinkListString* linkList)
{
    printf("{LinkListlong count: %li}\n", linkListStringCount(linkList));
        
    LinkListStringItem* item = linkList->first;
        
    while (item != NULL) { printf("\""); printString(item->pointer); printf("\"\n"); item = item->next; }     
}

