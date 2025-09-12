// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

String stringTrimStart(String* string) 
{
    if (string->address == NULL) { _errorAlreadyReleased("stringTrimStart"); }
    
    long margin = 0;
    long size = string->size;

    while (true)
    {
        if (size == 0) { return createEmptyString(); }
        
        if ((unsigned char) string->address[margin] > ' ') { break; }
        
        margin += 1; size -= 1;
    }
    
    return _createStringFromInfo(string->address + margin, size);
}

String stringTrimEnd(String* string) 
{
    if (string->address == NULL) { _errorAlreadyReleased("stringTrimEnd"); }
    
    long size = string->size;
    
    while (true)
    {
        if (size == 0) { return createEmptyString(); }
        
        long index = size - 1;
        
        if ((unsigned char) string->address[index] > ' ') { break; }
    
        size -= 1;          
    }
    
    return _createStringFromInfo(string->address, size);
}

String stringTrim(String* string) 
{
    if (string->address == NULL) { _errorAlreadyReleased("stringTrim"); }
    
    long margin = 0;
    long size = string->size;
    
    while (true) // trims end
    {
        if (size == 0) { return createEmptyString(); }
        
        long index = size - 1;
        
        if ((unsigned char) string->address[index] > ' ') { break; }
    
        size -= 1;          
    }

    while (true) // trims start
    {
        if (size == 0) { return createEmptyString(); } 
        
        if ((unsigned char) string->address[margin] > ' ') { break; }
        
        margin += 1; size -= 1;
    }
    
    return _createStringFromInfo(string->address + margin, size);
}

