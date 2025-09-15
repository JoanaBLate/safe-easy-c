// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

bool bufferTrimStart(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferTrimStart"); }
    
    bool changed = false;
    
    while (true)
    {
        if (buffer->size == 0) { return changed; }
        
        if ((unsigned char) buffer->address[buffer->margin] > ' ') { break; }
        
        buffer->margin += 1; buffer->size -= 1;
        
        changed = true;
    }
    
    return changed;
}

bool bufferTrimEnd(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferTrimEnd"); }
    
    bool changed = false;
    
    while (true)
    {
        if (buffer->size == 0) { return changed; }
        
        long index = buffer->margin + buffer->size - 1;
        
        if ((unsigned char) buffer->address[index] > ' ') { break; }
    
        buffer->size -= 1;  
        
        changed = true;
    }
    
    return changed;
}

bool bufferTrim(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferTrim"); }
    
    bool changed = false;
    
    if (bufferTrimStart(buffer)) { changed = true; }

    if (bufferTrimEnd(buffer)) { changed = true; }
    
    return changed;
}

///////////////////////////////////////////////////////////////////////////////

bool bufferTrimStartTarget(Buffer* buffer, String* target)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferTrimStartTarget"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferTrimStartTarget"); }
    
    bool changed = false;
    
    while (true)
    {
        String virtual = _makePseudoStringFromBuffer(buffer);
        
        if (! stringStartsWith(&virtual, target)) { break; }
        
        buffer->margin += target->size; buffer->size -= target->size;
        
        changed = true;
    }
    
    return changed;
}

bool bufferTrimEndTarget(Buffer* buffer, String* target)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferTrimEndTarget"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferTrimEndTarget"); }
    
    bool changed = false;
    
    while (true)
    {
        String virtual = _makePseudoStringFromBuffer(buffer);
        
        if (! stringEndsWith(&virtual, target)) { break; }
        
        buffer->size -= target->size;
        
        changed = true;
    }
    
    return changed;
}

bool bufferTrimTarget(Buffer* buffer, String* target)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferTrimTarget"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferTrimTarget"); }
    
    bool changed = false;
    
    if (bufferTrimStartTarget(buffer, target)) { changed = true; }

    if (bufferTrimEndTarget(buffer, target)) { changed = true; }
    
    return changed;
}

///////////////////////////////////////////////////////////////////////////////

bool bufferTrimStartAny(Buffer* buffer, String* sample)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferTrimStartAny"); }
    if (sample->address == NULL) { _errorAlreadyReleased("bufferTrimStartAny"); }
    
    bool changed = false;
    
    while (buffer->size > 0)
    {
        char* bufferHead = buffer->address + buffer->margin;
        
        bool modified = false;
        
        for (int n = 0; n < sample->size; n++)
        {
            char c = sample->address[n];
            
            if (*bufferHead != c) { continue; }
        
            buffer->margin += 1; buffer->size -= 1; modified = true; changed = true; break;
        }
        
        if (! modified) { break; }
    }
    
    return changed;
}

bool bufferTrimEndAny(Buffer* buffer, String* sample)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferTrimEndAny"); }
    if (sample->address == NULL) { _errorAlreadyReleased("bufferTrimEndAny"); }
    
    bool changed = false;
    
    while (buffer->size > 0)
    {
        char* bufferTail = buffer->address + buffer->margin + buffer->size - 1;
        
        bool modified = false;
        
        for (int n = 0; n < sample->size; n++)
        {
            char c = sample->address[n];
            
            if (*bufferTail != c) { continue; }
        
            buffer->size -= 1; modified = true; changed = true; break;
        }
        
        if (! modified) { break; }
    }
    
    return changed;
}

bool bufferTrimAny(Buffer* buffer, String* sample)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferTrimAny"); }
    if (sample->address == NULL) { _errorAlreadyReleased("bufferTrimAny"); }
    
    bool changed = false;
    
    if (bufferTrimStartAny(buffer, sample)) { changed = true; }
    
    if (bufferTrimEndAny(buffer, sample)) { changed = true; }
    
    return changed;
}

