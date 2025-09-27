// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

// doesn't return token
void bufferBiteStart(Buffer* buffer, long count)
{ 
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferBiteStart"); }
    
    if (count < 1) { return; }
    
    long size = count;
    
    if (size > buffer->size) { size = buffer->size; }
    
    buffer->margin += size; buffer->size -= size;
}

// doesn't return token
void bufferBiteEnd(Buffer* buffer, long count)
{ 
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferBiteEnd"); }
    
    if (count < 1) { return; }
    
    long size = count;
    
    if (size > buffer->size) { size = buffer->size; }
    
    buffer->size -= size;
}

// doesn't return token
// considers both (Linux and Windows) end-of-line
void bufferBiteToken(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferBiteToken"); }
        
    while (buffer->size > 0)
    {
        char c = buffer->address[buffer->margin];
        
        if (c != ' ') { break; }
        
        buffer->margin += 1;
        buffer->size -= 1;
    }
    
    if (buffer->size == 0) { return; }
    
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
    
    // wIndex matches the size of the token
    if (wIndex != -1) { buffer->margin += wIndex; buffer->size -= wIndex; return; }

    // no EOL was found
    if (nIndex == -1) { buffer->size = 0; return; } 
    
    if (nIndex == 0) { buffer->margin += 1; buffer->size -= 1; return; }
    
    if (rIndex == 0  &&  nIndex == 1) { buffer->margin += 2; buffer->size -= 2; return; }

    // rIndex matches the size of the token
    if (rIndex == nIndex - 1) { buffer->margin += rIndex; buffer->size -= rIndex; return; }
    
    // nIndex matches the size of the token
    buffer->margin += nIndex; 
    buffer->size -= nIndex; 
}

