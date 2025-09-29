// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

// may preserve margin or not
void bufferReplaceStart(Buffer* buffer, long count, String* chunk)
{   
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferReplaceStart"); }
     
    if (count < 1) { count = 0; }
     
    else if (count > buffer->size) { count = buffer->size; }
      
    // eating the start
    buffer->size -= count;
    buffer->margin += count; 
    
    // margin is big enough
    if (chunk->size <= buffer->margin)
    {        
        buffer->margin -= chunk->size;
        
        memcpy(buffer->address + buffer->margin, chunk->address, (size_t) chunk->size);
        
        buffer->size += chunk->size;

        return;    
    }
    
    // margin is small and will not be touched
    bufferMaybeExpandCapacity(buffer, chunk->size);
    
    buffer->size += chunk->size;
    
    bufferMoveRange(buffer, 0, buffer->size, chunk->size); // dimension buffer->size is big enough for all cases 

    memcpy(buffer->address + buffer->margin, chunk->address, (size_t) chunk->size); 
}

// preserves margin
void bufferReplaceEnd(Buffer* buffer, long count, String* chunk)
{    
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferReplaceEnd"); }
    
    if (count < 1) { count = 0; } 
    
    else if (count > buffer->size) { count = buffer->size; }
      
    // eating the end
    buffer->size -= count;
    
    long hiddenTail = buffer->capacity - buffer->margin - buffer->size;
    
    if (chunk->size <= hiddenTail)
    {        
        memcpy(buffer->address + buffer->margin + buffer->size, chunk->address, (size_t) chunk->size);
        
        buffer->size += chunk->size;
        
        return;    
    }
    
    bufferMaybeExpandCapacity(buffer, chunk->size);
    
    long position = buffer->margin + buffer->size;

    memcpy(buffer->address + position, chunk->address, (size_t) chunk->size);
    
    buffer->size += chunk->size;
}

