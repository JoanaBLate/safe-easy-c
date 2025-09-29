// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

// preserves margin
bool bufferMaybeExpandCapacity(Buffer* buffer, long deltaSize)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferMaybeExpandCapacity"); } 
    
    long hiddenTail = buffer->capacity - (buffer->margin + buffer->size);
    
    long neededExpansion = deltaSize - hiddenTail;
 
    if (neededExpansion <= 0) { return false; }

    long newCapacity = buffer->capacity + neededExpansion;
    
    buffer->address = _reallocateHeap(buffer->address, newCapacity); 
        
    buffer->capacity = newCapacity;
    
    return true;
}
     
