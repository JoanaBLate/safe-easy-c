// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

// replace target once ////////////////////////////////////////////////////////

bool _bufferReplace(Buffer* buffer, String* target, String* chunk, long relativePosition) 
{        
    if (relativePosition == -1) { return false; } // target not found
    
    long absolutePosition = buffer->margin + relativePosition;
    
    // just enough room
    if (target->size == chunk->size) 
    {
        memcpy(buffer->address + absolutePosition, chunk->address, (size_t) chunk->size);
        
        return true;    
    }
    
    // more than enough room
    if (target->size > chunk->size) 
    {
        memcpy(buffer->address + absolutePosition, chunk->address, (size_t) chunk->size);
        
        long delta = target->size - chunk->size;
        long start = absolutePosition + chunk->size;
        long off = buffer->margin + buffer->size - delta;
        
        for (long index = start; index < off; index++)
        {
            buffer->address[index] = buffer->address[index + delta];
        }
        
        buffer->size -= delta;

        return true;    
    }

    long neededSpace = chunk->size - target->size;
    
    _bufferMaybeExpandCapacity(buffer, neededSpace);
    
    // moving to the right (maybe)    
    long hiddenTail = buffer->capacity - buffer->margin - buffer->size;  
    
    long deltaRight = neededSpace;
    
    if (deltaRight > hiddenTail) { deltaRight = hiddenTail; }

    if (deltaRight > 0)
    {
        buffer->size += deltaRight;
        
        long a = relativePosition + target->size;
        
        long b = a + deltaRight;
      
        bufferMoveRange(buffer, a, buffer->size, b);
        
        neededSpace -= deltaRight;
    }
    
    // moving to the left (maybe)
    long deltaLeft = neededSpace;
    
 // if (deltaLeft > buffer->margin) { deltaLeft = buffer->margin; } // unnecessary
    
    if (deltaLeft > 0)
    {
        buffer->margin -= deltaLeft;
        
        buffer->size += deltaLeft;
      
        bufferMoveRange(buffer, deltaLeft, buffer->size, 0);
    
        absolutePosition -= deltaLeft;
    }
    
    // copying the chunk
    memcpy(buffer->address + absolutePosition, chunk->address, (size_t) chunk->size);
    
    return true;
}
   
bool bufferReplace(Buffer* buffer, String* target, String* chunk) 
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferReplace"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferReplace"); }
    if (chunk->address == NULL)  { _errorAlreadyReleased("bufferReplace"); }      
    
    long position = bufferIndexOf(buffer, target);
    
    return _bufferReplace(buffer, target, chunk, position);
}

bool bufferReplaceLast(Buffer* buffer, String* target, String* chunk) 
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferReplaceLast"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferReplaceLast"); }
    if (chunk->address == NULL)  { _errorAlreadyReleased("bufferReplaceLast"); }  
        
    long position = bufferLastIndexOf(buffer, target);
    
    return _bufferReplace(buffer, target, chunk, position);
}

// replace target all /////////////////////////////////////////////////////////

bool bufferReplaceAll(Buffer* buffer, String* target, String* chunk) 
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferReplaceAll"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferReplaceAll"); }  
    if (chunk->address == NULL)  { _errorAlreadyReleased("bufferReplaceAll"); }    
    
    long count = bufferCountOf(buffer, target);
    
    if (count == 0) { return false; }
    
    if (target->size < chunk->size)
    {
        long neededSpace = count * (chunk->size - target->size);
    
        _bufferMaybeExpandCapacity(buffer, neededSpace);
    }
     
     while (bufferReplace(buffer, target, chunk)) { }
     
     return true;
}

