// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

// the exact order of the statements of this function is crucial!
void bufferCopyRange(Buffer* originBuffer, long originPosition, long count, Buffer* destinyBuffer, long destinyPosition)
{
    if (originBuffer->address == NULL)  { _errorAlreadyReleased("bufferCopyRange"); }    
    if (destinyBuffer->address == NULL) { _errorAlreadyReleased("bufferCopyRange"); }
    
    if (count < 1) { return; }
    
    if (originBuffer->address == destinyBuffer->address)
    {
        bufferMoveRange(destinyBuffer, originPosition, count, destinyPosition); return; // 'destinyBuffer' OK
    }
    
    // destiny
    long destinyStart = destinyPosition;
    
    if (destinyStart >= destinyBuffer->size) { return; }

    long destinyEnd = destinyStart + count - 1;
    
    if (destinyEnd < 0) { return; }
    
    if (destinyEnd >= destinyBuffer->size) { destinyEnd = destinyBuffer->size - 1; }
    
    long deltaForOriginStart = 0;
    
    if (destinyStart < 0) { 
        
        deltaForOriginStart = -destinyStart; 
    
        destinyStart = 0; 
    }
    
    long destinySize = destinyEnd - destinyStart + 1;

    // origin    
    long originStart = originPosition;
        
    long originEnd = originStart + count - 1;

    if (originEnd < 0) { return; }
    
    if (originEnd >= originBuffer->size) { originEnd = originBuffer->size - 1; }
    
    if (originStart < 0) { originStart = 0; }
    
    originStart += deltaForOriginStart; // adjusting to negative destinyStart
    
    if (originStart >= originBuffer->size) { return; }
    
    long originSize = originEnd - originStart + 1;    
    
    // size
    long size = originSize;
    
    if (destinySize < size) { size = destinySize; }
    
    // copying (expecting no overlapping, buffers are different)
    for (long n = 0; n < size; n++)
    {
        long indexOrigin  = originBuffer->margin + originStart  + n;
        long indexDestiny = destinyBuffer->margin + destinyStart + n;
        
        destinyBuffer->address[indexDestiny] = originBuffer->address[indexOrigin];
    }
}

