// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void printStringBytes(String* string)
{    
    if (string->address == NULL) { _errorAlreadyReleased("printStringBytes"); }
    
    if (string->size == 0) { printf("{ }"); return; }

    bool expectingComma = false;

    printf("{");
    
    for (long index = 0; index < string->size; index++)
    {
        if (expectingComma) { printf(","); }
                
        unsigned char c = (unsigned char) string->address[index];

        printf(" %d", c);
        
        expectingComma = true;    
    }
    printf(" }");
}

void printlnStringBytes(String* string)
{
    if (string->address == NULL) { _errorAlreadyReleased("printlnStringBytes"); }
    
    printStringBytes(string);
    
    printf("\n");
}

void printStringChars(String* string)
{
    if (string->address == NULL) { _errorAlreadyReleased("printStringChars"); }
    
    char substitute = 26;
    
    long index = -1;
    
    while (true)
    {
        index += 1;
        
        if (index >= string->size) { return; }
    
        char c = string->address[index];
        
        if (c == 10) { putchar(c); continue; }
        if (c <  32) { putchar(substitute); continue; } // includes from 0 to -127
        putchar(c);
    }
}

void printlnStringChars(String* string)
{
    if (string->address == NULL) { _errorAlreadyReleased("printlnStringChars"); }
    
    printStringChars(string);
    
    printf("\n");
}

void printString(String* string)
{
    if (string->address == NULL) { _errorAlreadyReleased("printString"); }
    
    unsigned char substitute = 26;
    
    unsigned char token[5];
    
    long index = -1;

    while (true)
    {
        index += 1;
        
        if (index >= string->size) { return; }
    
        unsigned char c = (unsigned char) string->address[index];
        
        if (c == 10) { putchar(c); continue; }
        if (c <  32) { putchar(substitute); continue; }
        if (c < 128) { putchar(c); continue; }

        // unicode encoded (or not):

        token[0] = c;
        
        index += 1;
        if (index == string->size) { putchar(substitute); index -= 1; continue; } // corrupted data
        
        token[1] = (unsigned char) string->address[index];

        // 2-byte sequence
        if ((c & 0xE0) == 0xC0) { token[2] = 0; printf("%s", token); continue; }
        
        index += 1;
        if (index == string->size) { putchar(substitute); index -= 2; continue; } // corrupted data

        token[2] = (unsigned char) string->address[index];
        
        // 3-byte sequence
        if ((c & 0xF0) == 0xE0) { token[3] = 0; printf("%s", token); continue; }
        
        index += 1;
        if (index == string->size) { putchar(substitute); index -= 3; continue; } // corrupted data
        
        token[3] = (unsigned char) string->address[index];
        
        // 4-byte sequence
        if ((c & 0xF8) == 0xF0) { token[4] = 0; printf("%s", token); continue; }
        
        // not encoded:
        
        putchar(substitute);
        index -= 3;
    }
}

void printlnString(String* string)
{
    if (string->address == NULL) { _errorAlreadyReleased("printlnString"); }
    
    printString(string);
    
    printf("\n");
}

