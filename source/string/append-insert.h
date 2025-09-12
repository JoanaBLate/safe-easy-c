// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

String createStringAppend(String* string, String* chunk)
{    
    if (string->size == 0) { return createStringClone(chunk); }
    
    if (chunk->size == 0)  { return createStringClone(string); }
    
    long bufferSize = string->size + chunk->size;
    
    char* buffer = _allocateHeap(bufferSize);
    
    memcpy(buffer, string->address, (unsigned long) string->size);
    
    memcpy(&buffer[string->size], chunk->address, (unsigned long) chunk->size);
    
    return _makeStructString(buffer, bufferSize);
}

String createStringInsert(String* string, String* chunk, long position)
{
    if (string->size == 0) { return createStringClone(chunk); }
    
    if (chunk->size == 0) { return createStringClone(string); }
    
    if (position <= 0) { return createStringAppend(chunk, string); }

    if (position >= string->size) { return createStringAppend(string, chunk); }
    
    long bufferSize = string->size + chunk->size;
    
    char* buffer = _allocateHeap(bufferSize);

    for (long index = 0; index < position; index++) { buffer[index] = string->address[index]; }

    for (long index = 0; index < chunk->size; index++) { buffer[position + index] = chunk->address[index]; }

    for (long index = position; index < string->size; index++) { buffer[index + chunk->size] = string->address[index]; }
    
    return _makeStructString(buffer, bufferSize);
}

