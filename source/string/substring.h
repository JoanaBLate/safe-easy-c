// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

String createSubstring(String* string, long start, long count)  
{
    if (string->address == NULL) { _errorAlreadyReleased("createSubstring"); }
    
    if (count < 1) { return createEmptyString(); }
    
    long off = start + count;
    
    if (off > string->size) { off = string->size; }
    
    if (start < 0) { start = 0; }
    
    long size = off - start;
    
    if (size <= 0) { return createEmptyString(); }
    
    return _createStringFromInfo(string->address + start, size);
}

String createSubstringStart(String* string, long count) 
{    
    if (string->address == NULL) { _errorAlreadyReleased("createSubstringStart"); }
    
    return createSubstring(string, 0, count);
}

String createSubstringEnd(String* string, long count) 
{    
    if (string->address == NULL) { _errorAlreadyReleased("createSubstringEnd"); }
    
    if (count < 1) { return createEmptyString(); }
    
    long start = string->size - count;
    
    return createSubstring(string, start, count);
}

