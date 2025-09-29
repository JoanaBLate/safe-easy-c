// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void bufferAppendString(Buffer* buffer, String* chunk)
{    
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferAppendString"); }
    if (chunk->address  == NULL) { _errorAlreadyReleased("bufferAppendString"); }
    
    if (chunk->size == 0)  { return; }
    
    bufferMaybeExpandCapacity(buffer, chunk->size);
    
    memcpy(buffer->address + buffer->margin + buffer->size, chunk->address, (size_t) chunk->size);
    
    buffer->size += chunk->size;
}

//void bufferInsertString(Buffer* buffer, String* chunk, long position)
//{
//    if (string->address == NULL) { _errorAlreadyReleased("bufferInsertString"); }
//    if (chunk->address  == NULL) { _errorAlreadyReleased("bufferInsertString"); }
//    
//    if (chunk->size == 0) { return; }
//    
//    if (position <= 0) { bufferReplaceStart(buffer, 0, chunk); return }
//
//    if (position >= buffer->size) { bufferAppendString(buffer, chunk); return; }
//    
//    
//    
//    
//    
//
//    *UNDER CONSTRUCTION*
//    
//    
//    
//    
//    
//    
//    
//    
//    long bufferSize = string->size + chunk->size;
//    
//    char* buffer = _allocateHeap(bufferSize);
//
//    for (long index = 0; index < position; index++) { buffer[index] = string->address[index]; }
//
//    for (long index = 0; index < chunk->size; index++) { buffer[position + index] = chunk->address[index]; }
//
//    for (long index = position; index < string->size; index++) { buffer[index + chunk->size] = string->address[index]; }
//    
//    return _makeStructString(buffer, bufferSize);
//}

