// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

// old version
//long makeHashCode(String* string, long capacity)
//{
//    if (string->size == 0) { return 0; }
//    
//    int factors[21] = { 7, 11, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
//    
//    long value = 0;
//
//    for (int index = 0; index < string->size; index++)
//    {
//        unsigned char c = (unsigned char) string->address[index];
//        
//        value += c * factors[index % 21];
//    }
//
//    return value % capacity;
//}

// FNV-1a 64 bit version
//long makeHashCode(String* string, long capacity)
//{
//    // FNV-1a 64-bit variant
//    unsigned long long hash = 1469598103934665603ULL;  // offset basis
//    const unsigned long long prime = 1099511628211ULL; // FNV prime
//
//    for (int i = 0; i < string->size; i++)
//    {
//        unsigned char c = (unsigned char) string->address[i];
//        hash ^= c;
//        hash *= prime;
//    }
//
//    return (long)(hash % capacity);
//}

// FNV-1a 32-bit variant
long makeHashCode(String* string, long capacity)
{
    unsigned int hash = 2166136261U; // offset basis
    const unsigned int prime = 16777619U; // FNV prime

    for (int index = 0; index < string->size; index++)
    {
        unsigned char c = (unsigned char) string->address[index];
        hash ^= c;
        hash *= prime;
    }

    return (long) (hash % capacity);
}

void _errorHashmapKey(String* key, char* funcName)
{
    printf("\nERROR: unknown hashmap key '");
    printString(key);
    printf("' in function '%s'\n", funcName);
    
    exit(1);
}

