// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

bool _bufferMaybeExpandCapacity(Buffer* buffer, long neededSpace)
{
 // if (buffer->address == NULL) { _errorAlreadyReleased("_bufferMaybeExpandCapacity"); } // private function
    
    long hiddenSpace = buffer->capacity - buffer->size;
    
    long neededExpansion = neededSpace - hiddenSpace;
 
    if (neededExpansion <= 0) { return false; }

    long newCapacity = buffer->capacity + neededExpansion;
    
    buffer->address = _reallocateHeap(buffer->address, newCapacity); 
        
    buffer->capacity = newCapacity;
    
    return true;
}
     
