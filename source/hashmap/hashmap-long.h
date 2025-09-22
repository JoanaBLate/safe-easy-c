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
    HashmapLongItem** items;
} HashmapLong;

HashmapLongItem* createHashmapLongItem(String* key, long value)
{
    if (key->address == NULL) { _errorAlreadyReleased("createHashmapLongItem"); }
 
    HashmapLongItem* item = _allocateHeap(sizeof(HashmapLongItem));

    item->key = createStringClone(key);
    
    item->value = value;
    
    item->next = NULL;
    
    return item;
}

HashmapLong* createHashmapLong(long capacity) 
{
    HashmapLong* map = _allocateHeap(1 * (long) sizeof(HashmapLong));
    
    map->capacity = capacity;
    
    map->count = 0;
    
    map->items = _allocateHeapClean(capacity * (long) sizeof(HashmapLongItem*));

    return map;
}

bool addItemToHashmapLongOrSetValue(HashmapLong* map, String* key, long value) // returns true when makes new item
{
    if (key->address == NULL) { _errorAlreadyReleased("addItemToHashmapLongOrSetValue"); }
    
    long hashcode = makeHashCode(key, map->capacity);
    
    HashmapLongItem* item = map->items[hashcode];

    if (item == NULL) // ADDING new item directly to the items array
    {     
        map->items[hashcode] = createHashmapLongItem(key, value);
        
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
    
    item->next = createHashmapLongItem(key, value);
    
    map->count += 1;
 
    return true;
}

HashmapLongItem* getItemFromHashmapLong(HashmapLong* map, String* key)
{
    if (key->address == NULL) { _errorAlreadyReleased("getItemFromHashmapLong"); }
    
    long hashcode = makeHashCode(key, map->capacity);
    
    HashmapLongItem* item = map->items[hashcode];

    if (item == NULL) { return NULL; }
        
    if (stringsAreEqual(key, &item->key)) { return item; }
    
    while (true) // searching in the chain
    {    
        HashmapLongItem* nextItem = item->next;
    
        if (nextItem == NULL) { break; }
        
        if (stringsAreEqual(key, &nextItem->key)) { return nextItem; }
        
        item = nextItem;
    }

    return NULL; 
}

bool deleteItemFromHashmapLong(HashmapLong* map, String* key)
{
    if (key->address == NULL) { _errorAlreadyReleased("deleteItemFromHashmapLong"); }
    
    long hashcode = makeHashCode(key, map->capacity);
    
    HashmapLongItem* item = map->items[hashcode];

    if (item == NULL) { return false; }
        
    if (stringsAreEqual(key, &item->key)) 
    { 
        map->items[hashcode] = item->next;
        
        map->count -= 1;
        
        releaseHeap(&item->key);        
        releaseHeap(item);
        
        return true;
    }
    
    while (true) // searching in the chain
    {    
        HashmapLongItem *nextItem = item->next;
    
        if (nextItem == NULL) { return false; }
        
        if (! stringsAreEqual(key, &nextItem->key)) { item = nextItem; continue; }
        
        item->next = nextItem->next;
        
        map->count -= 1;
        
        releaseHeap(&item->key);        
        releaseHeap(item);
        
        return true;
    } 
    
    return false; // unreachable
}

void deleteHashmapLong(HashmapLong* map)
{
    for (long mapIndex = 0; mapIndex < map->capacity; mapIndex++)
    {    
        HashmapLongItem* item = map->items[mapIndex];
        
        if (item == NULL) { continue; }
        
        HashmapLongItem* nextItem = item->next;
        
        releaseHeap(&item->key);        
        releaseHeap(item);
        
        while (nextItem != NULL)
        {
            item = nextItem;
        
            nextItem = item->next;
            
            releaseHeap(&item->key);            
            releaseHeap(item);
        }
    }
    
    releaseHeap(map->items);    
    releaseHeap(map);
}
/* TODO: must wait ArrayList is ready
ArrayList* getHashmapLongKeys(HashmapLong* map)
{    
    ArrayList* list = newArrayList(map->count);
        
    for (long mapIndex = 0; mapIndex < map->capacity; mapIndex++)
    {    
        HashmapLongItem* item = map->items[mapIndex];
        
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

