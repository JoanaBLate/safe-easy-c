// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

// replace target once ////////////////////////////////////////////////////////

// preserves margin
bool _bufferReplace(Buffer* buffer, String* target, String* chunk, long position) 
{        
    if (position == -1) { return false; } // target not found
    
    long absolutePosition = buffer->margin + position;
    
    // just enough room
    if (target->size == chunk->size) 
    {
        // do nothing
    }
    // more than enough room
    else if (target->size > chunk->size) 
    {
        long origin = position + target->size;

        long length = buffer->size - origin;

        long destiny = position + chunk->size;

        bufferMoveRange(buffer, origin, length, destiny);

        buffer->size += chunk->size - target->size; // must come after 'bufferMoveRange'
    }
    // not enough room
    else
    {
        long deltaSize = chunk->size - target->size; // positive number        
        
        bufferMaybeExpandCapacity(buffer, deltaSize);
        
        long origin = position + target->size;
        
        long length = buffer->size - origin;
        
        long destiny = position + chunk->size;
      
        buffer->size += deltaSize; // must come before 'bufferMoveRange'
        
        bufferMoveRange(buffer, origin, length, destiny);
    }
    
    memcpy(buffer->address + absolutePosition, chunk->address, (size_t) chunk->size);
    
    return true;
}
   
bool bufferReplace(Buffer* buffer, String* target, String* chunk) 
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferReplace"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferReplace"); }
    if (chunk->address  == NULL) { _errorAlreadyReleased("bufferReplace"); }      
    
    long position = bufferIndexOf(buffer, target);
    
    return _bufferReplace(buffer, target, chunk, position);
}

bool bufferReplaceLast(Buffer* buffer, String* target, String* chunk) 
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferReplaceLast"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferReplaceLast"); }
    if (chunk->address  == NULL) { _errorAlreadyReleased("bufferReplaceLast"); }  
        
    long position = bufferLastIndexOf(buffer, target);
    
    return _bufferReplace(buffer, target, chunk, position);
}

// replace target all /////////////////////////////////////////////////////////

bool bufferReplaceAll(Buffer* buffer, String* target, String* chunk) 
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferReplaceAll"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferReplaceAll"); }  
    if (chunk->address  == NULL) { _errorAlreadyReleased("bufferReplaceAll"); }    
    
    long count = bufferCountOf(buffer, target);
    
    if (count == 0) { return false; }
    
    if (target->size < chunk->size)
    {
        long deltaSize = count * (chunk->size - target->size);
        
        bufferMaybeExpandCapacity(buffer, deltaSize);
    }
     
     while (bufferReplace(buffer, target, chunk)) { }
     
     return true;
}

