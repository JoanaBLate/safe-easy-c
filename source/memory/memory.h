// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

// pointer must be unsigned long, because must be able to access all RAM bytes

void* _allocateHeap(long size)
{
    if (size < 1) { return NULL; }
    
    unsigned long* address = malloc(size);
    
    if (address != NULL) { return address; }

    printf("\nERROR: failed to allocate %lu bytes in heap\n", size);
    
    exit(1);
}

void* _allocateHeapClean(long size)
{
    if (size < 1) { return NULL; }
    
    unsigned long* address = calloc(1, size);
    
    if (address != NULL) { return address; }

    printf("\nERROR: failed to allocate %lu bytes in heap\n", size);
    
    exit(1);
}

void* _reallocateHeap(void* address, long size)
{
    if (size < 1) { return NULL; }
    
    unsigned long* newAddress = realloc(address, size);
    
    if (newAddress != NULL) { return newAddress; }

    printf("\nERROR: failed to allocate %lu bytes in heap\n", size);
    
    exit(1);
}

void releaseHeap(void* voidStruct)
{
    AddressStruct* genericStruct = (AddressStruct*) voidStruct;
    
    free(genericStruct->address); // no problem to free(NULL)
    
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

