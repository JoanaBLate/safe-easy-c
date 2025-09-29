// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

bool bufferSetByte(Buffer* buffer, long index, char byte)
{ 
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferSetByte"); }

    if (index < 0  ||  index >= buffer->size) { return false; } // out of bounds

    buffer->address[buffer->margin + index] = byte;
    
    return true;
}

void bufferMoveLeft(Buffer* buffer, long deltaPos)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferMoveLeft"); }
    
    if (deltaPos < 0) { return; }

    bufferMoveRange(buffer, deltaPos, buffer->size - deltaPos, 0);
}

void bufferMoveRight(Buffer* buffer, long deltaPos)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferMoveRight"); }
    
    if (deltaPos < 0) { return; }
    
    bufferMoveRange(buffer, 0, buffer->size - deltaPos, deltaPos);
}

// may change the capacity, allocating memory
void bufferAdjustHiddenEnds(Buffer* buffer, long newMargin, long newHiddenTail)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferAdjustHiddenEnds"); }
    
    if (newMargin < 0  ||  newHiddenTail< 0) { return; }
    
    long hiddenTail = buffer->capacity - (buffer->margin + buffer->size);

    if (buffer->margin  ==  newMargin  &&  hiddenTail == newHiddenTail) { return; }

    long newCapacity = newMargin + buffer->size + newHiddenTail;
    
    if (newCapacity != buffer->capacity)
    {
        Buffer newBuffer = createBufferDontClean(newCapacity);

        memcpy(newBuffer.address + newMargin, buffer->address + buffer->margin, (size_t) buffer->size);
        
        deleteBuffer(buffer);
        
        buffer->address = newBuffer.address;
        buffer->margin = newMargin;
        buffer->capacity = newCapacity;
    
        return;
    }

    long deltaMargin = newMargin - buffer->margin;
    
    if (deltaMargin < 0)
    {
        long start = buffer->margin;
    
        long off = buffer->margin + buffer->size;
        
        for (long index = start; index < off; index++)
        {
            buffer->address[index - deltaMargin] = buffer->address[index];
        }
    }
    else // if (deltaMargin > 0)
    {
        long start = buffer->margin + buffer->size - 1;
        
        long off = buffer->margin - 1;
        
        for (long index = start; index > off; index--) // runs backwards
        {
            buffer->address[index + deltaMargin] = buffer->address[index];
        }
    }

    buffer->margin = newMargin;    
}

