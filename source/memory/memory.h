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

