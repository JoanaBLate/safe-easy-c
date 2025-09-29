// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

// may preserve margin or not
void bufferPadStart(Buffer* buffer, String* chunk, long count)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferPadStart"); }
    if (chunk->address  == NULL) { _errorAlreadyReleased("bufferPadStart"); }
    
    long padLength = count * chunk->size;
        
    if (padLength < 1) { return; }

    // margin is big enough
    if (buffer->margin >= padLength)
    {
        buffer->margin -= padLength;
        
        buffer->size += padLength;
    }
    // margin is small and will not be touched
    else
    {
        bufferMaybeExpandCapacity(buffer, padLength);
                
        long origin = 0;
        
        long length = buffer->size; // dimension buffer->size is big enough for all cases 
        
        long destiny = origin + padLength;
        
        buffer->size += padLength;
        
        bufferMoveRange(buffer, origin, length, destiny);
    }
    
    for (long n = 0; n < count; n++)
    {
        long start = buffer->margin + (n * chunk->size);
    
        for (long index = 0; index < chunk->size; index++) { buffer->address[start + index] = chunk->address[index]; }
    }
}

// preserves margin
void bufferPadEnd(Buffer* buffer, String* chunk, long count)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferPadEnd"); }
    if (chunk->address  == NULL) { _errorAlreadyReleased("bufferPadEnd"); }
    
    long padLength = count * chunk->size;
        
    if (padLength < 1) { return; }
    
    bufferMaybeExpandCapacity(buffer, padLength);
    
    buffer->size += padLength;
   
    for (long n = 0; n < count; n++)
    {
        long start = buffer->margin + buffer->size - padLength + (n * chunk->size);
  
        for (long index = 0; index < chunk->size; index++) { buffer->address[start + index] = chunk->address[index]; }
    }
}

