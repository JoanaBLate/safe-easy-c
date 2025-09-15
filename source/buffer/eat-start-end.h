// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

String bufferEatStart(Buffer* buffer, long count)
{ 
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferEatStart"); }
    
    if (count < 1) { return createEmptyString(); }
    
    long size = count;
    
    if (size > buffer->size) { size = buffer->size; }
    
    String token = _createStringFromInfo(buffer->address + buffer->margin, size);
    
    buffer->margin += size; buffer->size -= size;
    
    return token;
}

String bufferEatEnd(Buffer* buffer, long count)
{ 
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferEatEnd"); }
    
    if (count < 1) { return createEmptyString(); }
    
    long size = count;
    
    if (size > buffer->size) { size = buffer->size; }
    
    String token = _createStringFromInfo(buffer->address + buffer->margin + buffer->size - size, size);
    
    buffer->size -= size;
    
    return token;
}

