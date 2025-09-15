// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

Buffer createEmptyBuffer() 
{
    char* address = _allocateHeap(1);
    
    Buffer buffer = { address, 1, 0, 0 };
    
    buffer.address[0] = 0;
    
    return buffer;
}

Buffer createBuffer(long capacity) 
{
    if (capacity < 1) { return createEmptyBuffer(); }
    
    char* address = _allocateHeap(capacity);
    
    Buffer buffer = { address, capacity, 0, 0 };
    
    return buffer;
}

Buffer createBufferFromLiteral(char* cString) 
{   
    if (cString == NULL) { return createEmptyBuffer(); }
    
    long size = (long) strlen(cString);
    
    long capacity = size;
    
    if (capacity < 1) { return createEmptyBuffer(); }
    
    char* address = _allocateHeap(capacity);
    
    Buffer buffer = { address, capacity, 0, size };

    memcpy(buffer.address, cString, (size_t) size);
    
    return buffer;
}

Buffer createBufferFromCString(char* cString) 
{   
    return createBufferFromLiteral(cString);
}

Buffer createBufferFromString(String* string) 
{   
    if (string->address == NULL) { _errorAlreadyReleased("createBufferFromString"); }
    
    long capacity = string->size;
    
    Buffer buffer = createBuffer(capacity);
    
    if (capacity < 1) { return buffer; }
    
    buffer.size = capacity;

    memcpy(buffer.address, string->address, (size_t) string->size);
    
    return buffer;
}

