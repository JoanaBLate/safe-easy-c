// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

typedef struct
{
    String key;    
    long value;
    void* next; // linked item that has the same hashcode
} HashmapLongItem;

typedef struct
{
    long capacity;
    long count;
    HashmapLongItem** pointers;
} HashmapLong;

HashmapLong createHashmapLong(long capacity) 
{
    if (capacity < 10) { capacity = 10; }
    
    HashmapLong map = { capacity, 0, NULL };
    
    map.pointers = _allocateHeapClean(capacity * (long) sizeof(HashmapLongItem*));

    return map;
}

long hashmapLongCount(HashmapLong* map)
{
    if (map->pointers == NULL) {  _errorAlreadyReleased("hashmapLongCount"); }
    
    return map->count;
}

// all items are allocated directly on the heap
HashmapLongItem* _hashmapLongCreateItem(String* key, long value)
{
    // key was already checked
    // if (key->address == NULL) { _errorAlreadyReleased("_hashmapLongCreateItem"); }
 
    HashmapLongItem* item = _allocateHeap(sizeof(HashmapLongItem));

    item->key = createStringClone(key);
    
    item->value = value;
    
    item->next = NULL;
    
    return item;
}

bool hashmapLongKeyExists(HashmapLong* map, String* key)
{
    if (map->pointers == NULL) { _errorAlreadyReleased("hashmapLongKeyExists"); }    
    if (key->address == NULL)  { _errorAlreadyReleased("hashmapLongKeyExists"); }
    
    long hashcode = makeHashCode(key, map->capacity);
    
    HashmapLongItem* item = map->pointers[hashcode];

    if (item == NULL) { return false; }
        
    if (stringsAreEqual(key, &item->key)) { return true; }
    
    while (true) // searching in the chain
    {    
        HashmapLongItem* nextItem = item->next;
    
        if (nextItem == NULL) { break; }
        
        if (stringsAreEqual(key, &nextItem->key)) { return true; }
        
        item = nextItem;
    }

    return false; 
}

// program exits if the key doesn't exist
// that is better than return NULL and the
// developer takes it as zero because forgot
// to call 'hashmapLongKeyExists'
long hashmapLongGet(HashmapLong* map, String* key)
{
    if (map->pointers == NULL) { _errorAlreadyReleased("hashmapLongGet"); }    
    if (key->address == NULL)  { _errorAlreadyReleased("hashmapLongGet"); }
    
    long hashcode = makeHashCode(key, map->capacity);
    
    HashmapLongItem* item = map->pointers[hashcode];

    if (item == NULL) { _errorHashmapKey(key, "hashmapLongGet"); }
        
    if (stringsAreEqual(key, &item->key)) { return item->value; }
    
    while (true) // searching in the chain
    {    
        HashmapLongItem* nextItem = item->next;
    
        if (nextItem == NULL) { break; }
        
        if (stringsAreEqual(key, &nextItem->key)) { return nextItem->value; }
        
        item = nextItem;
    }

    _errorHashmapKey(key, "hashmapLongGet"); 
    
    return (long) NULL; // pleasing the compiler ;)
}

// updates or creates new item
// returns true when makes new item
bool hashmapLongSet(HashmapLong* map, String* key, long value) 
{
    if (map->pointers == NULL) { _errorAlreadyReleased("hashmapLongSet"); }
    if (key->address == NULL)  { _errorAlreadyReleased("hashmapLongSet"); }
    
    long hashcode = makeHashCode(key, map->capacity);
    
    HashmapLongItem* item = map->pointers[hashcode];

    if (item == NULL) // ADDING new item (directly in the array 'pointers')
    {     
        map->pointers[hashcode] = _hashmapLongCreateItem(key, value);
        
        map->count += 1;

        return true;
    }   
  
    if (stringsAreEqual(key, &item->key)) { item->value = value; return false; } // SETTING item value
    
    while (true) // searching in the chain
    {    
        HashmapLongItem* nextItem = item->next;
    
        if (nextItem == NULL) { break; }
        
        if (stringsAreEqual(key, &nextItem->key)) { nextItem->value = value; return false; } // SETTING item value
        
        item = nextItem;
    }
    
    // ADDING new item in the chain
    
    item->next = _hashmapLongCreateItem(key, value);
    
    map->count += 1;
 
    return true;
}

bool hashmapLongDelete(HashmapLong* map, String* key)
{
    if (map->pointers == NULL) { _errorAlreadyReleased("hashmapLongDelete"); }
    if (key->address == NULL)  { _errorAlreadyReleased("hashmapLongDelete"); }
    
    long hashcode = makeHashCode(key, map->capacity);
    
    HashmapLongItem* item = map->pointers[hashcode];

    if (item == NULL) { return false; }
        
    if (stringsAreEqual(key, &item->key)) 
    { 
        map->pointers[hashcode] = item->next;
        
        map->count -= 1;
        
        deleteString(&item->key);        
        free(item);
        
        return true;
    }
    
    while (true) // searching in the chain
    {    
        HashmapLongItem *nextItem = item->next;
    
        if (nextItem == NULL) { return false; }
        
        if (! stringsAreEqual(key, &nextItem->key)) { item = nextItem; continue; }
        
        item->next = nextItem->next;
        
        map->count -= 1;
        
        deleteString(&item->key);        
        free(item);
        
        return true;
    } 
    
    return false; // unreachable
}

void hashmapLongClearAll(HashmapLong* map)
{
    if (map->pointers == NULL) {  _errorAlreadyReleased("hashmapLongClearAll"); }
    
    for (long index = 0; index < map->capacity; index++)
    {    
        HashmapLongItem* item = map->pointers[index];
        
        if (item == NULL) { continue; }
        
        map->pointers[index] = NULL;
        
        HashmapLongItem* nextItem = item->next;
  
        deleteString(&item->key);        
        free(item);
        map->count -= 1;
        
        while (nextItem != NULL)
        {
            item = nextItem;
        
            nextItem = item->next;
            
            deleteString(&item->key);            
            free(item);
            map->count -= 1;
        }
    }
}    

void deleteHashmapLong(HashmapLong* map)
{
    if (map->pointers == NULL) {  _errorAlreadyReleased("hashmapLongDeleteAll"); }
    
    hashmapLongClearAll(map);
    
    free(map->pointers); 
}

long long hashmapLongSum(HashmapLong* map)
{
    if (map->pointers == NULL) {  _errorAlreadyReleased("hashmapLongSum"); }
    
    long long result = 0;
            
    for (long index = 0; index < map->capacity; index++)
    {            
        HashmapLongItem* item = map->pointers[index];
        
        if (item == NULL) { continue; }
  
        result += item->value;
        
        HashmapLongItem* nextItem = item->next;
        
        while (nextItem != NULL)
        {
            item = nextItem;
            
            result += item->value;
            
            nextItem = item->next;
        }
    }
    return result; 
}

void hashmapLongPrintAll(HashmapLong* map)
{
    if (map->pointers == NULL) {  _errorAlreadyReleased("hashmapLongPrintAll"); }
    
    printf("{hashmap count: %li}", hashmapLongCount(map));
        
    for (long index = 0; index < map->capacity; index++)
    {            
        HashmapLongItem* item = map->pointers[index];
        
        if (item == NULL) { continue; }
  
        printf("   [");
        printString(&item->key);
        printf(": %li]", item->value);
        
        HashmapLongItem* nextItem = item->next;
        
        while (nextItem != NULL)
        {
            item = nextItem;
            
            printf("   [");
            printString(&item->key);
            printf(": %li]", item->value);
        
            nextItem = item->next;
        }
    }
    printf("\n"); 
}    

/* TODO: must wait ArrayList is ready
ArrayList* hashmapLongGetKeys(HashmapLong* map)
{    
    if (map->pointers == NULL) {  _errorAlreadyReleased("hashmapLongGetKeys"); }
    
    ArrayList* list = newArrayList(map->count);
        
    for (long mapIndex = 0; mapIndex < map->capacity; mapIndex++)
    {    
        HashmapLongItem* item = map->pointers[mapIndex];
        
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
    
