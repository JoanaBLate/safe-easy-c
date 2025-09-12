// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

// helper function only
// expects that heap allocation is already resolved
String _makeStructString(char* address, long size) 
{
    String string = { address, size };
    
    return string;
}

// does not allocate on heap
// address NULL is only for heap released objects
// the empty string check is made on the string size (not address)
String createEmptyString() 
{
    return _makeStructString(FAKENULL, 0); 
}

String createStringFromByte(int n)
{   
    if (n < 0  ||  n > 255) { return createEmptyString(); }

    char* buffer = _allocateHeap(1);

    buffer[0] = n;
    
    return _makeStructString(buffer, 1);
}

String _createStringFromInfo(char* sourceAddress, long sourceSize)
{
    long bufferSize = sourceSize;
    
    if (bufferSize == 0) { return createEmptyString(); }
    
    char* buffer = _allocateHeap(bufferSize);

    memcpy(buffer, sourceAddress, (unsigned long) bufferSize);
    
    return _makeStructString(buffer, bufferSize);
}

String createStringFromLiteral(char* cString) // argument not checked
{
    unsigned long size = strlen(cString);
    
    return _createStringFromInfo(cString, (long) size);
}

String createStringClone(String* string)
{
    if (string->address == NULL) { _errorAlreadyReleased("createStringClone"); }

    return _createStringFromInfo(string->address, string->size);
}

String createStringFromBuffer(Buffer* buffer)
{   
    if (buffer->address == NULL) { _errorAlreadyReleased("createStringFromBuffer"); }
    
    return _createStringFromInfo(buffer->address + buffer->margin, buffer->size);
}

String createStringFromLong(long number)
{
    char array[30]; // stack allocation 
    
    sprintf(array, "%li", number);
    
    unsigned long size = strlen(array);
    
    return _createStringFromInfo(array, (long) size);
}

