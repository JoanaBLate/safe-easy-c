// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

// the exact order of the statements of this function is crucial!
void bufferMoveRange(Buffer* buffer, long origin, long count, long destiny)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferMoveRange"); }
    
    if (count < 1) { return; }
    
    // destiny
    long destinyStart = destiny;
    
    if (destinyStart >= buffer->size) { return; }

    long destinyEnd = destinyStart + count - 1;
    
    if (destinyEnd < 0) { return; }
    
    if (destinyEnd >= buffer->size) { destinyEnd = buffer->size - 1; }
    
    long deltaForOriginStart = 0;
    
    if (destinyStart < 0) { 
        
        deltaForOriginStart = -destinyStart; 
    
        destinyStart = 0; 
    }
    
    long destinySize = destinyEnd - destinyStart + 1;

    // origin    
    long originStart = origin;
        
    long originEnd = originStart + count - 1;

    if (originEnd < 0) { return; }
    
    if (originEnd >= buffer->size) { originEnd = buffer->size - 1; }
    
    if (originStart < 0) { originStart = 0; }
    
    originStart += deltaForOriginStart; // adjusting to negative destinyStart
    
    if (originStart >= buffer->size) { return; }
    
    long originSize = originEnd - originStart + 1;    
    
    // size
    long size = originSize;
    
    if (destinySize < size) { size = destinySize; }
    
    // copy
    if (originStart > destinyStart)
    { 
        for (long n = buffer->margin; n < (buffer->margin + size); n++)
        {
            long indexOrigin  = originStart  + n;
            long indexDestiny = destinyStart + n;
            
            buffer->address[indexDestiny] = buffer->address[indexOrigin];
        }
    }    
    else if (originStart < destinyStart)
    { 
        for (long n = (buffer->margin + size - 1); n > (buffer->margin - 1); n--) // runs backwards
        {
            long indexOrigin  = originStart  + n;
            long indexDestiny = destinyStart + n;
            
            buffer->address[indexDestiny] = buffer->address[indexOrigin];
        }
    }
 // else if (originStart == destinyStart) { return; }
}

