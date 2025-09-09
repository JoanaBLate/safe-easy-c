// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

String stringTrimStart(String* string) 
{
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

