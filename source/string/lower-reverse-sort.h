// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

String createStringToLower(String* string) 
{
    String newString = createStringClone(string);
    
    for (long index = 0; index < newString.size; index++)
    {
        newString.address[index] = tolower(newString.address[index]);
    }
    
    return newString;
}

String createStringToUpper(String* string) 
{
    String newString = createStringClone(string);
    
    for (long index = 0; index < newString.size; index++)
    {
        newString.address[index] = toupper(newString.address[index]);
    }
    
    return newString;
}

String createStringToOppositeCase(String* string) 
{
    String newString = createStringClone(string);
    
    for (long index = 0; index < newString.size; index++)
    {
        char c = newString.address[index];
        
        if (isupper(c)) 
        { 
            newString.address[index] = tolower(c);
        }
        else if (islower(c)) 
        { 
            newString.address[index] = toupper(c);
        }
    }
    
    return newString;
}

String createStringReverse(String* string) 
{
    String newString = createStringClone(string);
    
    long halfLength = newString.size / 2;

    for (long index = 0; index < halfLength; index++) 
    {     
        char temp = newString.address[index];
        
        newString.address[index] = newString.address[newString.size - 1 - index];
        
        newString.address[newString.size - 1 - index] = temp;
    }
    
    return newString;
}

String createStringSort(String* string) // TODO: slow  
{
    String newString = createStringClone(string);
    
    for (long indexA = 0; indexA < newString.size - 1; indexA++) 
    { 
        for (long indexB = indexA + 1; indexB < newString.size; indexB++) 
        { 
            if (newString.address[indexA] <= newString.address[indexB]) { continue; }
            
            char temp = newString.address[indexA];
            
            newString.address[indexA] = newString.address[indexB];
            
            newString.address[indexB] = temp;
        }
    }
    
    return newString;
}

