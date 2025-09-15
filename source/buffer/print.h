// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void printBufferBytes(Buffer* buffer)
{    
    if (buffer->address == NULL) { _errorAlreadyReleased("printBufferBytes"); }
    
    String string = _makePseudoStringFromBuffer(buffer);
    
    printStringBytes(&string);
}

void printlnBufferBytes(Buffer* buffer)
{    
    if (buffer->address == NULL) { _errorAlreadyReleased("printlnBufferBytes"); }
    
    String string = _makePseudoStringFromBuffer(buffer);
    
    printlnStringBytes(&string);
}

void printBuffer(Buffer* buffer)
{    
    if (buffer->address == NULL) { _errorAlreadyReleased("printBuffer"); }
    
    String string = _makePseudoStringFromBuffer(buffer);
    
    printString(&string);
}

void printlnBuffer(Buffer* buffer)
{    
    if (buffer->address == NULL) { _errorAlreadyReleased("printlnBuffer"); }
    
    String string = _makePseudoStringFromBuffer(buffer);
    
    printlnString(&string);
}

void displayBuffer(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("displayBuffer"); }
    
    printf("[");
    printBuffer(buffer);
    printf("]  margin: %li   size: %li  capacity: %li\n",  buffer->margin, buffer->size, buffer->capacity);
}

