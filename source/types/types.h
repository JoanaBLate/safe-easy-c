// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

// why using 'long' for sizes instead of 'unsigned long' (size_t)?
//   'long' is big enough (half of the adressable memory)
//   unsigned integers are more complicated to handle (logical comparison with negative numbers)
//   SafeEasyC functions assure that size/capacity/length will never get negative value

// for the address of empty strings
// true NULL is reserved for released objects
char* FAKENULL = "fakenull"; 

const char DOT_OR_COMMA = '.';

typedef struct
{
    long value;
    bool isNull;
} NullLong;

typedef struct
{
    double value;
    bool isNull;
} NullDouble;

typedef struct // generic!
{
    char* address;
} AddressStruct;

typedef struct 
{
    char* address; 
    long size;
} String;

typedef struct 
{
    char* address; 
    long capacity;
    long margin;
    long size;
} Buffer;

// making /////////////////////////////////////////////////////////////////////

NullLong makeNullLong(long value, bool isNull)
{
    NullLong number = { value, isNull };
    
    return number;
}

NullDouble makeNullDouble(double value, bool isNull)
{
    NullDouble number = { value, isNull };
    
    return number;
}

