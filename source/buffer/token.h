// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

String bufferEatLine(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferEatLine"); }
    
    if (buffer->size == 0) { return createEmptyString(); }
        
    long nIndex = -1; // '\n'
    long rIndex = -1; // '\r'

    for (long index = 0; index < buffer->size; index++)
    {
        char c = buffer->address[buffer->margin + index];
        
        if (c == '\r') { rIndex = index; }
        
        if (c == '\n') { nIndex = index; break; }
    }
    
    // no EOL was found
    if (nIndex == -1) { String s = createStringFromBuffer(buffer); buffer->size = 0; return s; } 
    
    long sizeWithEOL = nIndex + 1;
    
    long sizeWithoutEOL = sizeWithEOL - ((rIndex == nIndex - 1) ? 2 : 1); // may remove '\r' (for Windows EOL)
    
    String result = _createStringFromInfo(buffer->address + buffer->margin, sizeWithoutEOL);
    
    buffer->margin += sizeWithEOL;
    buffer->size -= sizeWithEOL;
    
    return result; 
}

