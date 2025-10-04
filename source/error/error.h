// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

// many errors are processed without using this midule

void _errorAlreadyReleased(char* funcName)
{
    printf("\nERROR: trying to use deleted object in function '%s'\n", funcName);
    
    exit(1);
}

void _errorIndexOutOfBounds(char* funcName, long index)
{
    printf("\nERROR: index (%li) out of bounds in function '%s'\n", index, funcName);
    
    exit(1);
}

void _errorEmptyContainerAccess(char* funcName)
{
    printf("\nERROR: trying to access data in empty container in function '%s'\n", funcName);
    
    exit(1);
}

// unused
void _errorNullArgument(char* funcName)
{
    printf("\nERROR: null argument received in function '%s'\n", funcName);
    
    exit(1);
}


