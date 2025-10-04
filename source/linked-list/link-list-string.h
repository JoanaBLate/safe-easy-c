// # Copyright (c) 2024 - 2025 Feudal Code limitada - MIT license #
//
//typedef struct
//{
//    long value;
//    void* previous;
//    void* next; 
//} linkListLongItem;
//
//typedef struct
//{
//    long count;
//    linkListLongItem* current;
//} linkListLong;
//
//LinkListLong createLinkListLong() 
//{
//    linkListLong linkList = { 0, NULL };
//    
//    return linkList;
//}
//
//long linkListLongCount(LinkListLong* linkList)
//{
//    if (linkList->pointers == NULL) {  _errorAlreadyReleased("LinkListLongCount"); }
//    
//    return linkList->count;
//}
//
// all items are allocated directly on the heap
//LinkListLongItem* _LinkListLongCreateItem(String* key, long value)
//{
//    // key was already checked
//    // if (key->address == NULL) { _errorAlreadyReleased("_LinkListLongCreateItem"); }
// 
//    linkListLongItem* item = _allocateHeap(sizeof(LinkListLongItem));
//
//    item->key = createStringClone(key);
//    
//    item->value = value;
//    
//    item->next = NULL;
//    
//    return item;
//}
//
//bool linkListLongKeyExists(LinkListLong* linkList, String* key)
//{
//    if (linkList->pointers == NULL) { _errorAlreadyReleased("LinkListLongKeyExists"); }    
//    if (key->address == NULL)  { _errorAlreadyReleased("LinkListLongKeyExists"); }
//    
//    long hashcode = makeHashCode(key, linkList->capacity);
//    
//    linkListLongItem* item = linkList->pointers[hashcode];
//
//    if (item == NULL) { return false; }
//        
//    if (stringsAreEqual(key, &item->key)) { return true; }
//    
//    while (true) // searching in the chain
//    {    
//        linkListLongItem* nextItem = item->next;
//    
//        if (nextItem == NULL) { break; }
//        
//        if (stringsAreEqual(key, &nextItem->key)) { return true; }
//        
//        item = nextItem;
//    }
//
//    return false; 
//}
//
// program exits if the key doesn't exist
// that is better than return NULL and the
// developer takes it as zero because forgot
// to call 'LinkListLongKeyExists'
//long linkListLongGet(LinkListLong* linkList, String* key)
//{
//    if (linkList->pointers == NULL) { _errorAlreadyReleased("LinkListLongGet"); }    
//    if (key->address == NULL)  { _errorAlreadyReleased("LinkListLongGet"); }
//    
//    long hashcode = makeHashCode(key, linkList->capacity);
//    
//    linkListLongItem* item = linkList->pointers[hashcode];
//
//    if (item == NULL) { _errorLinkListKey(key, "LinkListLongGet"); }
//        
//    if (stringsAreEqual(key, &item->key)) { return item->value; }
//    
//    while (true) // searching in the chain
//    {    
//        linkListLongItem* nextItem = item->next;
//    
//        if (nextItem == NULL) { break; }
//        
//        if (stringsAreEqual(key, &nextItem->key)) { return nextItem->value; }
//        
//        item = nextItem;
//    }
//
//    _errorLinkListKey(key, "LinkListLongGet"); 
//    
//    return (long) NULL; // pleasing the compiler ;)
//}
//
// updates or creates new item
// returns true when makes new item
//bool linkListLongSet(LinkListLong* linkList, String* key, long value) 
//{
//    if (linkList->pointers == NULL) { _errorAlreadyReleased("LinkListLongSet"); }
//    if (key->address == NULL)  { _errorAlreadyReleased("LinkListLongSet"); }
//    
//    long hashcode = makeHashCode(key, linkList->capacity);
//    
//    linkListLongItem* item = linkList->pointers[hashcode];
//
//    if (item == NULL) // ADDING new item (directly in the array 'pointers')
//    {     
//        linkList->pointers[hashcode] = _LinkListLongCreateItem(key, value);
//        
//        linkList->count += 1;
//
//        return true;
//    }   
//  
//    if (stringsAreEqual(key, &item->key)) { item->value = value; return false; } // SETTING item value
//    
//    while (true) // searching in the chain
//    {    
//        linkListLongItem* nextItem = item->next;
//    
//        if (nextItem == NULL) { break; }
//        
//        if (stringsAreEqual(key, &nextItem->key)) { nextItem->value = value; return false; } // SETTING item value
//        
//        item = nextItem;
//    }
//    
//    // ADDING new item in the chain
//    
//    item->next = _LinkListLongCreateItem(key, value);
//    
//    linkList->count += 1;
// 
//    return true;
//}
//
//bool linkListLongDelete(LinkListLong* linkList, String* key)
//{
//    if (linkList->pointers == NULL) { _errorAlreadyReleased("LinkListLongDelete"); }
//    if (key->address == NULL)  { _errorAlreadyReleased("LinkListLongDelete"); }
//    
//    long hashcode = makeHashCode(key, linkList->capacity);
//    
//    linkListLongItem* item = linkList->pointers[hashcode];
//
//    if (item == NULL) { return false; }
//        
//    if (stringsAreEqual(key, &item->key)) 
//    { 
//        linkList->pointers[hashcode] = item->next;
//        
//        linkList->count -= 1;
//        
//        deleteString(&item->key);        
//        free(item);
//        
//        return true;
//    }
//    
//    while (true) // searching in the chain
//    {    
//        linkListLongItem *nextItem = item->next;
//    
//        if (nextItem == NULL) { return false; }
//        
//        if (! stringsAreEqual(key, &nextItem->key)) { item = nextItem; continue; }
//        
//        item->next = nextItem->next;
//        
//        linkList->count -= 1;
//        
//        deleteString(&item->key);        
//        free(item);
//        
//        return true;
//    } 
//    
//    return false; // unreachable
//}
//
//void linkListLongClearAll(LinkListLong* linkList)
//{
//    if (linkList->pointers == NULL) {  _errorAlreadyReleased("LinkListLongClearAll"); }
//    
//    for (long index = 0; index < linkList->capacity; index++)
//    {    
//        linkListLongItem* item = linkList->pointers[index];
//        
//        if (item == NULL) { continue; }
//        
//        linkList->pointers[index] = NULL;
//        
//        linkListLongItem* nextItem = item->next;
//  
//        deleteString(&item->key);        
//        free(item);
//        linkList->count -= 1;
//        
//        while (nextItem != NULL)
//        {
//            item = nextItem;
//        
//            nextItem = item->next;
//            
//            deleteString(&item->key);            
//            free(item);
//            linkList->count -= 1;
//        }
//    }
//}    
//
//void deleteLinkListLong(LinkListLong* linkList)
//{
//    if (linkList->pointers == NULL) {  _errorAlreadyReleased("LinkListLongDeleteAll"); }
//    
//    linkListLongClearAll(linkList);
//    
//    free(linkList->pointers); 
//}
//
//long long linkListLongSum(LinkListLong* linkList)
//{
//    if (linkList->pointers == NULL) {  _errorAlreadyReleased("LinkListLongSum"); }
//    
//    long long result = 0;
//            
//    for (long index = 0; index < linkList->capacity; index++)
//    {            
//        linkListLongItem* item = linkList->pointers[index];
//        
//        if (item == NULL) { continue; }
//  
//        result += item->value;
//        
//        linkListLongItem* nextItem = item->next;
//        
//        while (nextItem != NULL)
//        {
//            item = nextItem;
//            
//            result += item->value;
//            
//            nextItem = item->next;
//        }
//    }
//    return result; 
//}
//
//void linkListLongPrintAll(LinkListLong* linkList)
//{
//    if (linkList->pointers == NULL) {  _errorAlreadyReleased("LinkListLongPrintAll"); }
//    
//    printf("{LinkList count: %li}", linkListLongCount(linkList));
//        
//    for (long index = 0; index < linkList->capacity; index++)
//    {            
//        linkListLongItem* item = linkList->pointers[index];
//        
//        if (item == NULL) { continue; }
//  
//        printf("   [");
//        printString(&item->key);
//        printf(": %li]", item->value);
//        
//        linkListLongItem* nextItem = item->next;
//        
//        while (nextItem != NULL)
//        {
//            item = nextItem;
//            
//            printf("   [");
//            printString(&item->key);
//            printf(": %li]", item->value);
//        
//            nextItem = item->next;
//        }
//    }
//    printf("\n"); 
//}    
//
///* TODO: must wait ArrayList is ready
//ArrayList* linkListLongGetKeys(LinkListLong* linkList)
//{    
//    if (linkList->pointers == NULL) {  _errorAlreadyReleased("LinkListLongGetKeys"); }
//    
//    ArrayList* list = newArrayList(linkList->count);
//        
//    for (long linkListIndex = 0; linkListIndex < linkList->capacity; linkListIndex++)
//    {    
//        linkListLongItem* item = linkList->pointers[linkListIndex];
//        
//        if (item == NULL) { continue; }
//        
//        arrayListInclude(list, &item->key);
//        
//        while (item->next != NULL)
//        {
//            item = item->next;
//            
//            arrayListInclude(list, &item->key);
//        }
//    }
//
//    return list;
//}
//*/
//    
///*
//typedef struct {
//    long   capacity;
//    long   count;
//    void** items;
//} ArrayList;
//
//ArrayList* newArrayList(long capacity)
//{
//    ArrayList* list = _allocateHeap(1 * (long) sizeof(ArrayList));
//    
//    list->capacity = capacity;
//    
//    list->count = 0;
//    
//    list->items = _allocateHeap(capacity * (long) sizeof(void**));
//
//    return list;
//}
//
//void arrayListInclude(ArrayList* list, void* item)
//{
//    if (list->count >= list->capacity) 
//    { 
//        printf("\nERROR in function 'arrayListInclude': ArrayList was already full\n"); exit(1);
//    }
//
//    list->items[list->count] = item;
//    
//    list->count += 1;
//}
//
// TODO void arrayListRemove // one base
//
//void arrayListUnorderedRemove(ArrayList* list, long index) // one base
//{
//    if (index < 1  ||  index > list->count) 
//    { 
//        printf("\nERROR in function 'arrayListUnorderedRemove': index (%li) out of bounds\n", index); exit(1);
//    }
//
//    index -= 1; // adjusting to zero base
//    
//    long indexOfLast = list->count - 1; // zero base
//
//    list->items[index] = list->items[indexOfLast]; // sometimes index == indexOfLast
//    
//    list->items[indexOfLast] = NULL;
//    
//    list->count -= 1;
//}
//*/
