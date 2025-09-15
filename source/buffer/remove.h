// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void bufferRemove(Buffer* buffer, String* target)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferRemove"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferRemove"); }
    
    String empty = createEmptyString();
    
    bufferReplace(buffer, target, &empty);
}

void bufferRemoveLast(Buffer* buffer, String* target)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferRemoveLast"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferRemoveLast"); }
    
    String empty = createEmptyString();
    
    bufferReplaceLast(buffer, target, &empty);
}

void bufferRemoveAll(Buffer* buffer, String* target)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferRemoveAll"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferRemoveAll"); }
    
    String empty = createEmptyString();
    
    bufferReplaceAll(buffer, target, &empty);
}

