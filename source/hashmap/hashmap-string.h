// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

typedef struct
{
    String key;    
    String value;
    void* next; // linked item that has the same hashcode
} HashmapStringItem;

typedef struct
{
    long capacity;
    long count;
    HashmapStringItem** pointers;
} HashmapString;

HashmapString createHashmapString(long capacity) 
{
    if (capacity < 10) { capacity = 10; }
    
    HashmapString map = { capacity, 0, NULL };
    
    map.pointers = _allocateHeapClean(capacity * (long) sizeof(HashmapStringItem*));

    return map;
}

long hashmapStringCount(HashmapString* map)
{
    if (map->pointers == NULL) {  _errorAlreadyReleased("hashmapStringCount"); }
    
    return map->count;
}

// all items are allocated directly on the heap
HashmapStringItem* _hashmapStringCreateItem(String* key, String* value)
{
    // key was already checked
    // if (key->address == NULL) { _errorAlreadyReleased("_hashmapStringCreateItem"); }
 
    HashmapStringItem* item = _allocateHeap(sizeof(HashmapStringItem));

    item->key = createStringClone(key);
    
    item->value = createStringClone(value);
    
    item->next = NULL;
    
    return item;
}

bool hashmapStringKeyExists(HashmapString* map, String* key)
{
    if (map->pointers == NULL) { _errorAlreadyReleased("hashmapStringKeyExists"); }    
    if (key->address == NULL)  { _errorAlreadyReleased("hashmapStringKeyExists"); }
    
    long hashcode = makeHashCode(key, map->capacity);
    
    HashmapStringItem* item = map->pointers[hashcode];

    if (item == NULL) { return false; }
        
    if (stringsAreEqual(key, &item->key)) { return true; }
    
    while (true) // searching in the chain
    {    
        HashmapStringItem* nextItem = item->next;
    
        if (nextItem == NULL) { break; }
        
        if (stringsAreEqual(key, &nextItem->key)) { return true; }
        
        item = nextItem;
    }

    return false; 
}

// program exits if the key doesn't exist
// that is better than return NULL and the
// developer takes it as zero because forgot
// to call 'hashmapStringKeyExists'
// (in case of HashmapLong)
String hashmapStringGet(HashmapString* map, String* key)
{
    if (map->pointers == NULL) { _errorAlreadyReleased("hashmapStringGet"); }    
    if (key->address == NULL)  { _errorAlreadyReleased("hashmapStringGet"); }
    
    long hashcode = makeHashCode(key, map->capacity);
    
    HashmapStringItem* item = map->pointers[hashcode];

    if (item == NULL) { _errorHashmapKey(key, "hashmapStringGet"); }
        
    if (stringsAreEqual(key, &item->key)) { return createStringClone(&item->value); }
    
    while (true) // searching in the chain
    {    
        HashmapStringItem* nextItem = item->next;
    
        if (nextItem == NULL) { break; }
        
        if (stringsAreEqual(key, &nextItem->key)) { return createStringClone(&nextItem->value); }
        
        item = nextItem;
    }

    _errorHashmapKey(key, "hashmapStringGet"); 
    
    return createEmptyString(); // pleasing the compiler ;)
}

// updates or creates new item
// returns true when makes new item
bool hashmapStringSet(HashmapString* map, String* key, String* value) 
{
    if (map->pointers == NULL) { _errorAlreadyReleased("hashmapStringSet"); }
    if (key->address == NULL)  { _errorAlreadyReleased("hashmapStringSet"); }
    
    long hashcode = makeHashCode(key, map->capacity);
    
    HashmapStringItem* item = map->pointers[hashcode];

    if (item == NULL) // ADDING new item (directly in the array 'pointers')
    {     
        map->pointers[hashcode] = _hashmapStringCreateItem(key, value);
        
        map->count += 1;

        return true;
    }   
  
    if (stringsAreEqual(key, &item->key)) // SETTING item value
    { 
        deleteString(&item->value);
        item->value = createStringClone(value);
        return false; 
    } 
    
    while (true) // searching in the chain
    {    
        HashmapStringItem* nextItem = item->next;
    
        if (nextItem == NULL) { break; }
        
        if (stringsAreEqual(key, &nextItem->key)) // SETTING item value
        { 
            deleteString(&nextItem->value);
            nextItem->value = createStringClone(value); 
            return false; 
        } 
        item = nextItem;
    }
    
    // ADDING new item in the chain
    
    item->next = _hashmapStringCreateItem(key, value);
    
    map->count += 1;
 
    return true;
}

bool hashmapStringDelete(HashmapString* map, String* key)
{
    if (map->pointers == NULL) { _errorAlreadyReleased("hashmapStringDelete"); }
    if (key->address == NULL)  { _errorAlreadyReleased("hashmapStringDelete"); }
    
    long hashcode = makeHashCode(key, map->capacity);
    
    HashmapStringItem* item = map->pointers[hashcode];

    if (item == NULL) { return false; }
        
    if (stringsAreEqual(key, &item->key)) 
    { 
        map->pointers[hashcode] = item->next;
        
        map->count -= 1;
        
        deleteString(&item->key);
        deleteString(&item->value);        
        free(item);
        
        return true;
    }
    
    while (true) // searching in the chain
    {    
        HashmapStringItem *nextItem = item->next;
    
        if (nextItem == NULL) { return false; }
        
        if (! stringsAreEqual(key, &nextItem->key)) { item = nextItem; continue; }
        
        item->next = nextItem->next;
        
        map->count -= 1;
        
        deleteString(&item->key); 
        deleteString(&item->value);       
        free(item);
        
        return true;
    } 
    
    return false; // unreachable
}

void hashmapStringClearAll(HashmapString* map)
{
    if (map->pointers == NULL) {  _errorAlreadyReleased("hashmapStringClearAll"); }
    
    for (long index = 0; index < map->capacity; index++)
    {    
        HashmapStringItem* item = map->pointers[index];
        
        if (item == NULL) { continue; }
        
        map->pointers[index] = NULL;
        
        HashmapStringItem* nextItem = item->next;
  
        deleteString(&item->key); 
        deleteString(&item->value);       
        free(item);
        map->count -= 1;
        
        while (nextItem != NULL)
        {
            item = nextItem;
        
            nextItem = item->next;
            
            deleteString(&item->key); 
            deleteString(&item->value);           
            free(item);
            map->count -= 1;
        }
    }
}    

void deleteHashmapString(HashmapString* map)
{
    if (map->pointers == NULL) {  _errorAlreadyReleased("hashmapStringDeleteAll"); }
    
    hashmapStringClearAll(map);
    
    free(map->pointers); 
}

void hashmapStringPrintAll(HashmapString* map)
{
    if (map->pointers == NULL) {  _errorAlreadyReleased("hashmapStringPrintAll"); }
    
    int counter = 0;
    
    for (long index = 0; index < map->capacity; index++)
    {            
        HashmapStringItem* item = map->pointers[index];
        
        if (item == NULL) { continue; }
  
        if (counter > 0) { printf("  "); }
        printf("[");
        printString(&item->key);
        printf(": "); 
        printString(&item->value);
        printf("]");
        counter += 1;
        
        HashmapStringItem* nextItem = item->next;
        
        while (nextItem != NULL)
        {
            item = nextItem;
            
            if (counter > 0) { printf("  "); }
            printf("[");
            printString(&item->key);
            printf(": "); 
            printString(&item->value);
            printf("]");
            counter += 1;
        
            nextItem = item->next;
        }
    }
     printf("\nhashmap count: %li\n", hashmapStringCount(map)); 
 //  printf("\nhashmap count: %li    printed objects: %d\n", hashmapStringCount(map), counter);
}    

/* TODO: must wait ArrayList is ready
ArrayList* hashmapStringGetKeys(HashmapString* map)
{    
    if (map->pointers == NULL) {  _errorAlreadyReleased("hashmapStringGetKeys"); }
    
    ArrayList* list = newArrayList(map->count);
        
    for (long mapIndex = 0; mapIndex < map->capacity; mapIndex++)
    {    
        HashmapStringItem* item = map->pointers[mapIndex];
        
        if (item == NULL) { continue; }
        
        arrayListInclude(list, &item->key);
        
        while (item->next != NULL)
        {
            item = item->next;
            
            arrayListInclude(list, &item->key);
        }
    }

    return list;
}
*/

