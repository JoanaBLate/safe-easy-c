// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void bufferAppendString(Buffer* buffer, String* chunk)
{    
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferAppendString"); }
    if (chunk->address  == NULL) { _errorAlreadyReleased("bufferAppendString"); }
    
    if (chunk->size == 0)  { return; }
    
    bufferMaybeExpandCapacity(buffer, chunk->size);
    
    memcpy(buffer->address + buffer->margin + buffer->size, chunk->address, (size_t) chunk->size);
    
    buffer->size += chunk->size; // must come after 'memcpy'
}

void bufferInsertString(Buffer* buffer, String* chunk, long position)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferInsertString"); }
    if (chunk->address  == NULL) { _errorAlreadyReleased("bufferInsertString"); }
    
    if (chunk->size == 0) { return; }
    
    if (position <= 0) { bufferReplaceStart(buffer, 0, chunk); return; }

    if (position >= buffer->size) { bufferAppendString(buffer, chunk); return; }
    
    // creating room
    bufferMaybeExpandCapacity(buffer, chunk->size);
    
    long origin = position;

    long length = buffer->size - origin;

    long destiny = position + chunk->size;

    buffer->size += chunk->size; // must come before 'bufferMoveRange'

    bufferMoveRange(buffer, origin, length, destiny);

    // writing the chunk
    memcpy(buffer->address + buffer-> margin + position, chunk->address, (size_t) chunk->size);
}

