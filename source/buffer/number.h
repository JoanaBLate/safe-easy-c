// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

// *NOT* CHECKING FOR TOO BIG NUMBER
NullLong bufferEatLong(Buffer* buffer) 
{  
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferEatLong"); }
    
    while (buffer->size > 0) 
    {         
        char c = buffer->address[buffer->margin];
        
        if (c != ' ') { break; }

        buffer->margin += 1;
        buffer->size -= 1;
    }
    
    if (buffer->size == 0) { return makeNullLong(0, true); }
       
    int signal = 0; // zero means signal not found
    
    char c = buffer->address[buffer->margin];

    if (c == '-') 
    { 
        signal = -1; 
    }
    else if (c == '+') 
    { 
        signal = +1; 
    }
    else if (c < '0'  ||  c > '9')
    {
        return makeNullLong(0, true);
    }
    
    if (signal != 0)
    {
        if (buffer->size == 1) { return makeNullLong(0, true); }
        
        char c = buffer->address[buffer->margin + 1];
        
        if (c < '0'  ||  c > '9') { return makeNullLong(0, true); } 
         
        buffer->margin += 1;
        buffer->size -= 1;  
    }
    else
    {
        signal = +1; 
    }
    
    // expecting digit(s) now
    
    int length = 0;
    
    while (buffer->size > 0) 
    {         
        char c = buffer->address[buffer->margin];
        
        if (c < '0'  ||  c > '9') { break; }

        buffer->margin += 1;
        buffer->size -= 1;
        
        length += 1;
    }
  
    long value = 0;
    
    long factor = 1;
    
    long end = buffer->margin - 1;
    
    long start = end - length + 1;
    
    for (int index = end; index >= start; index--) // runs backwards
    {
        value += (buffer->address[index] - '0') * factor;
        
        factor *= 10;
    }
    return makeNullLong(signal * value, false);
}

