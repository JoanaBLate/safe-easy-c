// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void* _allocateHeap(long size)
{
    if (size < 1) { return NULL; }
    
    void* address = malloc((size_t) size);
    
    if (address != NULL) { return address; }

    printf("\nERROR: failed to allocate %lu bytes in heap\n", size);
    
    exit(1);
}

void* _allocateHeapClean(long size)
{
    if (size < 1) { return NULL; }
    
    void* address = calloc(1, (size_t)  size);
    
    if (address != NULL) { return address; }

    printf("\nERROR: failed to allocate %lu bytes in heap\n", size);
    
    exit(1);
}

void* _reallocateHeap(void* address, long size)
{
    if (size < 1) { return NULL; }
    
    void* newAddress = realloc(address, (size_t) size);
    
    if (newAddress != NULL) { return newAddress; }

    printf("\nERROR: failed to allocate %lu bytes in heap\n", size);
    
    exit(1);
}

void releaseHeap(void* voidStruct)
{
    AddressStruct* genericStruct = (AddressStruct*) voidStruct;
    
    if (genericStruct->address == FAKENULL) { return; } // for empty strings
    
    free(genericStruct->address); // no problem to "free again"
    
    genericStruct->address = NULL;
}

void _errorAlreadyReleased(char* funcName)
{
    printf("\nERROR: trying to use already released object in function '%s'\n", funcName);
    
    exit(1);
}

void assureNotReleased(void* voidStruct, char* funcName)
{
    AddressStruct* genericStruct = (AddressStruct*) voidStruct;
    
    if (genericStruct->address == NULL) { _errorAlreadyReleased(funcName); }
}

