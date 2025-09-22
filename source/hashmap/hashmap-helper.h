// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

long makeHashCode(String* string, long capacity)
{
    if (string->size == 0) { return 0; }
    
    int factors[21] = { 7, 11, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
    
    int factorIndex = -1; 

    long value = 0;

    for (int index = 0; index < string->size; index++)
    {
        unsigned char c = (unsigned char) string->address[index];
        
        factorIndex += 1;
        
        if (factorIndex == 21) { factorIndex = 0; };
        
        value += c * factors[factorIndex];
    }

    return value % capacity;
}

