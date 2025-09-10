// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

// char* for storing text
// unsigned char for raw byte values
// int for functions that return character codes + need a sentinel

long getStringSize(String* string)
{        
    return string->size;
}

// the same pattern as the C standard library
int stringCharCodeAt(String* string, long index)
{     
    if (index < 0  ||  index >= string->size) { return -1; } // out of bounds
    
    return (int) ((unsigned char) string->address[index]);
}

bool stringsAreEqual(String* stringA, String* stringB)
{
    if (stringA->size != stringB->size) { return false; };
    
    for (long index = 0; index < stringA->size; index ++)
    {
        if (stringA->address[index] != stringB->address[index]) { return false; }
    }
    return true;
}

char stringsCompare(String* stringA, String* stringB)
{
    long size = stringA->size;
    
    if (stringB->size < size) { size = stringB->size; }    
        
    for (long index = 0; index < size; index ++)
    {
        if (stringA->address[index] < stringB->address[index]) { return -1; }
        if (stringA->address[index] > stringB->address[index]) { return +1; }
    }
    
    if (stringA->size < stringB->size) { return -1; }
    if (stringA->size > stringB->size) { return +1; }

    return 0;
}

bool stringStartsWith(String* string, String* target)
{    
    if (target->size == 0) { return false; }
    
    if (target->size > string->size) { return false; }
    
    for (long index = 0; index < target->size; index++)
    {
        if (string->address[index] != target->address[index]) { return false; }
    }
    return true;
}

bool stringEndsWith(String* string, String* target)
{    
    if (target->size == 0) { return false; }
    
    if (target->size > string->size) { return false; }
    
    long pad = string->size - target->size;
    
    for (long index = 0; index < target->size; index++)
    {
        if (string->address[pad + index] != target->address[index]) { return false; }
    }
    return true;
}

long stringIndexOf(String* string, String* target)
{    
    if (target->size == 0) { return -1; }
    
    if (target->size > string->size) { return -1; }
    
    long off = string->size - target->size + 1;
    
    for (long index = 0; index < off; index++)
    {
        bool match = true;
        
        for (long targetIndex = 0; targetIndex < target->size; targetIndex++)
        {
            if (string->address[index + targetIndex] != target->address[targetIndex]) { match = false; break; }
        }
        
        if (match) { return index; }
    }
    return -1;
}

long stringIndexOfAfter(String* string, String* target, long usedIndex)
{    
    if (string->size == 0) { return -1; }

    if (target->size > string->size) { return -1; }
        
    if (usedIndex >= string->size) { return -1; }
    
    if (usedIndex < 1) { return stringIndexOf(string, target); }
    
    long startIndex = usedIndex;
    
    long maxIndex = string->size - target->size;
    
    for (long index = startIndex; index <= maxIndex; index++) 
    {
        bool match = true;
        
        for (long targetIndex = 0; targetIndex < target->size; targetIndex++)
        {
            if (string->address[index + targetIndex] != target->address[targetIndex]) { match = false; break; }
        }
        
        if (match) { return index; }
    }
    return -1;
}

long stringLastIndexOf(String* string, String* target)
{    
    if (target->size == 0) { return -1; }
    
    if (target->size > string->size) { return -1; }
    
    long startIndex = string->size - target->size;
    
    for (long index = startIndex; index > -1; index--) // runs backwards
    {
        bool match = true;
        
        for (long targetIndex = 0; targetIndex < target->size; targetIndex++)
        {
            if (string->address[index + targetIndex] != target->address[targetIndex]) { match = false; break; }
        }
        
        if (match) { return index; }
    }
    return -1;
}

long stringLastIndexOfBefore(String* string, String* target, long usedIndex)
{    
    if (target->size == 0) { return -1; }

    if (target->size > string->size) { return -1; }
    
    if (usedIndex <= 1) { return -1; }
    
    if (usedIndex >= string->size) { return stringLastIndexOf(string, target); }
       
    long maxIndex = (usedIndex - 1) - target->size;
    
    for (long index = maxIndex; index > -1; index--) // runs backwards
    {
        bool match = true;
        
        for (long targetIndex = 0; targetIndex < target->size; targetIndex++)
        {
            if (string->address[index + targetIndex] != target->address[targetIndex]) { match = false; break; }
        }
        
        if (match) { return index; }
    }
    return -1;
}

bool stringContains(String* string, String* target)
{    
    return (stringIndexOf(string, target) != -1);
}

long stringCountOf(String* string, String* target)
{
    long count = 0;

    long index = -target->size;
    
    while (true) {
    
        index = stringIndexOfAfter(string, target, index + target->size - 1);
    
        if (index == -1) { break; } else { count += 1; }
    
    }
    return count;
}

long stringMarginCount(String* string) // 'count' instead of 'length' because TAB effect is undefined
{
    long count = 0;
    
    for (long index = 0; index < string->size; index++)
    {

        if (string->address[index] == ' ')  { count += 1; continue; }
        if (string->address[index] == '\t') { count += 1; continue; }
        
        break;
   }
    
    return count; 
}

