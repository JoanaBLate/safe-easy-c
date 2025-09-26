// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

long getBufferCapacity(Buffer* buffer)
{        
    if (buffer->address == NULL) { _errorAlreadyReleased("getBufferCapacity"); }

    return buffer->capacity;
}

long getBufferMargin(Buffer* buffer)
{        
    if (buffer->address == NULL) { _errorAlreadyReleased("getBufferMargin"); }

    return buffer->margin;
}

long getBufferSize(Buffer* buffer)
{        
    if (buffer->address == NULL) { _errorAlreadyReleased("getBufferSize"); }

    return buffer->size;
}

bool bufferIsEmpty(Buffer* buffer)
{        
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferIsEmpty"); }

    return buffer->size == 0;
}

bool bufferWasDeleted(Buffer* buffer)
{        
    return (buffer->address == NULL);
}

// the same pattern as the C standard library
int bufferByteAt(Buffer* buffer, long index)
{ 
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferByteAt"); }

    if (index < 1  ||  index > buffer->size) { return -1; } // out of bounds

    return (int) (unsigned char) buffer->address[buffer->margin + index - 1];
}

bool buffersAreEqual(Buffer* bufferA, Buffer* bufferB) 
{
    if (bufferA->address == NULL) { _errorAlreadyReleased("buffersAreEqual"); }
    if (bufferB->address == NULL) { _errorAlreadyReleased("buffersAreEqual"); }

    String stringA = _makePseudoStringFromBuffer(bufferA);
    String stringB = _makePseudoStringFromBuffer(bufferB);

    return stringsAreEqual(&stringA, &stringB);
}

char buffersCompare(Buffer* bufferA, Buffer* bufferB)
{
    if (bufferA->address == NULL) { _errorAlreadyReleased("buffersCompare"); }
    if (bufferB->address == NULL) { _errorAlreadyReleased("buffersCompare"); }
    
    String stringA = _makePseudoStringFromBuffer(bufferA);
    String stringB = _makePseudoStringFromBuffer(bufferB);
    
    return stringsCompare(&stringA, &stringB);
}

bool bufferStartsWith(Buffer* buffer, String* target)
{  
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferStartsWith"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferStartsWith"); }
    
    String string = _makePseudoStringFromBuffer(buffer);  
    
    return stringStartsWith(&string, target);
}

bool bufferEndsWith(Buffer* buffer, String* target)
{  
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferEndsWith"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferEndsWith"); }

    String string = _makePseudoStringFromBuffer(buffer);  
    
    return stringEndsWith(&string, target);
}

long bufferIndexOf(Buffer* buffer, String* target)
{  
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferIndexOf"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferIndexOf"); }
    
    String string = _makePseudoStringFromBuffer(buffer);  
    
    return stringIndexOf(&string, target);
}

long bufferIndexOfAfter(Buffer* buffer, String* target, long usedIndex)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferIndexOfAfter"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferIndexOfAfter"); }
    
    String string = _makePseudoStringFromBuffer(buffer);  
    
    return stringIndexOfAfter(&string, target, usedIndex);
}

long bufferLastIndexOf(Buffer* buffer, String* target)
{  
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferLastIndexOf"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferLastIndexOf"); }
    
    String string = _makePseudoStringFromBuffer(buffer);  
    
    return stringLastIndexOf(&string, target);
}

long bufferLastIndexOfBefore(Buffer* buffer, String* target, long usedIndex)
{  
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferLastIndexOfBefore"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferLastIndexOfBefore"); }
    
    String string = _makePseudoStringFromBuffer(buffer);  
    
    return stringLastIndexOfBefore(&string, target, usedIndex);
}

bool bufferContains(Buffer* buffer, String* target)
{    
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferContains"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferContains"); }
    
    String string = _makePseudoStringFromBuffer(buffer); 
    
    return stringContains(&string, target);
}

long bufferCountOf(Buffer* buffer, String* target)
{    
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferCountOf"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferCountOf"); }
    
    String string = _makePseudoStringFromBuffer(buffer); 
    
    return stringCountOf(&string, target);
}

