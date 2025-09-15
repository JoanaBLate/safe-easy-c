// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void bufferReplaceStart(Buffer* buffer, long count, String* chunk)
{   
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferReplaceStart"); }
     
    if (count < 1) { count = 0; }
     
    else if (count > buffer->size) { count = buffer->size; }
      
    // eating the start
    buffer->size -= count;
    buffer->margin += count; 
    
    if (chunk->size <= buffer->margin)
    {        
        buffer->margin -= chunk->size;
        
        memcpy(buffer->address + buffer->margin, chunk->address, (size_t) chunk->size);
        
        buffer->size += chunk->size;

        return;    
    }
    
    bufferMaybeExpandCapacity(buffer, chunk->size);
    
    // now capacity is enough but margin is not enough: must move bytes to right
    
    long delta = chunk->size - buffer->margin;
    
    buffer->size += delta;
    
    bufferMoveRange(buffer, 1, buffer->size - delta, delta);

    buffer->size += buffer->margin;
    
    buffer->margin = 0;
    
    // pasting the chunk
    
    memcpy(buffer->address, chunk->address, (size_t) chunk->size);
}

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
        
    hiddenTail = buffer->capacity - buffer->margin - buffer->size;
    
    long delta = chunk->size - hiddenTail;
    
    if (delta == 0) // no need to displace data
    {
        memcpy(buffer->address + buffer->margin + buffer->size, chunk->address, (size_t) chunk->size);
        
        buffer->size += chunk->size;
    
        return;    
    }     
    
    // must use the margin: moving bytes to left
    
    long position = buffer->margin + buffer->size - delta;
        
    buffer->margin -= delta;
    
    buffer->size += delta;
  
    bufferMoveRange(buffer, 1 + delta, buffer->size, 0);

    memcpy(buffer->address + position, chunk->address, (size_t) chunk->size);
    
    buffer->size += chunk->size - delta;
}

