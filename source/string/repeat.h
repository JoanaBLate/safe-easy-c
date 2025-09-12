// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

String createStringRepeat(String* string, long count) 
{
    if (string->size == 0) { return createEmptyString(); }
    
    if (count < 1) { return createEmptyString(); }
    
    long bufferSize = count * string->size;

    char* buffer = _allocateHeap(bufferSize);
    
    for (long turn = 0; turn < count; turn++) 
    { 
        memcpy(&buffer[turn * string->size], string->address, (unsigned long) string->size); 
    }

    return _makeStructString(buffer, bufferSize);
}

