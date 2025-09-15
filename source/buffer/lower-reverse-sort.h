// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void bufferToLower(Buffer* buffer)
{    
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferToLower"); }
    
    long start = buffer->margin;
    long off = buffer->margin + buffer->size;
    
    for (long index = start; index < off; index++)   
    {
        buffer->address[index] = tolower(buffer->address[index]);
    }    
}

void bufferToUpper(Buffer* buffer)
{   
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferToUpper"); }
    
    long start = buffer->margin;
    long off = buffer->margin + buffer->size;
     
    for (long index = start; index < off; index++)   
    {
        buffer->address[index] = toupper(buffer->address[index]);
    }    
}

void bufferToOppositeCase(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferToOppositeCase"); }
    
    long start = buffer->margin;
    long off = buffer->margin + buffer->size;
    
    for (long index = start; index < off; index++)   
    {
        buffer->address[index] = tolower(buffer->address[index]);
    
        char c = buffer->address[index];
        
        if (isupper(c)) 
        { 
            buffer->address[index] = tolower(c);
        }
        else if (islower(c)) 
        { 
            buffer->address[index] = toupper(c);
        }
    }
}

void bufferReverse(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferReverse"); }
    
    long halfLength = buffer->size / 2;
     
    for (long position = 0; position < halfLength; position++) 
    {     
        long indexA = buffer->margin + position;
        
        long indexB = buffer->margin + (buffer->size - 1 - position);
        
        char temp = buffer->address[indexA];
        
        buffer->address[indexA] = buffer->address[indexB];
        
        buffer->address[indexB] = temp;
    }
}

void bufferSort(Buffer* buffer) // TODO: make it fast
{    
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferSort"); }
    
    for (long positionA = 0; positionA < buffer->size - 1; positionA++) 
    { 
        for (long positionB = positionA + 1; positionB < buffer->size; positionB++) 
        { 
            long indexA = buffer->margin + positionA;
            
            long indexB = buffer->margin + positionB;
            
            if (buffer->address[indexA] <= buffer->address[indexB]) { continue; }
            
            char temp = buffer->address[indexA];
            
            buffer->address[indexA] = buffer->address[indexB];
            
            buffer->address[indexB] = temp;
        }
    }
}

