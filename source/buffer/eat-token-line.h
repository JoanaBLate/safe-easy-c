// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

// considers both (Linux and Windows) end-of-line
String bufferEatToken(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferEatToken"); }
        
    while (buffer->size > 0)
    {
        char c = buffer->address[buffer->margin];
        
        if (c != ' ') { break; }
        
        buffer->margin += 1;
        buffer->size -= 1;
    }
    
    if (buffer->size == 0) { return createEmptyString(); }
    
    long nIndex = -1; // '\n'
    long rIndex = -1; // '\r'
    long wIndex = -1; // white space

    for (long index = 0; index < buffer->size; index++)
    {
        char c = buffer->address[buffer->margin + index];
        
        if (c == ' ')  { wIndex = index; break; }

        if (c == '\r') { rIndex = index; }
        
        if (c == '\n') { nIndex = index; break; }
    }
    
    if (wIndex != -1) // wIndex matches the size of the token
    {
        String result = _createStringFromInfo(buffer->address + buffer->margin, wIndex);
        buffer->margin += wIndex; buffer->size -= wIndex;
        return result;
    }

    // no EOL was found
    if (nIndex == -1) 
    { 
        String result = createStringFromBuffer(buffer); 
        buffer->size = 0; 
        return result; 
    } 
    
    if (nIndex == 0)
    { 
        buffer->margin += 1; 
        buffer->size -= 1; 
        return createStringFromLiteral("\n"); 
    }
    
    if (rIndex == 0  &&  nIndex == 1) 
    { 
        buffer->margin += 2; 
        buffer->size -= 2; 
        return createStringFromLiteral("\r\n"); 
    }

    if (rIndex == nIndex - 1)  // rIndex matches the size of the token
    { 
        String result = _createStringFromInfo(buffer->address + buffer->margin, rIndex);
        buffer->margin += rIndex; 
        buffer->size -= rIndex; 
        return result; 
    }
    
    // nIndex matches the size of the token
    String result = _createStringFromInfo(buffer->address + buffer->margin, nIndex);
    buffer->margin += nIndex; 
    buffer->size -= nIndex; 
    return result; 
}

// considers both (Linux and Windows) end-of-line
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
    if (nIndex == -1) { String result = createStringFromBuffer(buffer); buffer->size = 0; return result; } 
    
    long sizeWithEOL = nIndex + 1;
    
    long sizeWithoutEOL = sizeWithEOL - ((rIndex == nIndex - 1) ? 2 : 1); // may remove '\r' (for Windows EOL)
    
    String result = _createStringFromInfo(buffer->address + buffer->margin, sizeWithoutEOL);
    
    buffer->margin += sizeWithEOL;
    buffer->size -= sizeWithEOL;
    
    return result; 
}

