// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

// C recomends an unsigned type for size, but many functions
// of the standard library return a signed type because that
// type must be able to return -1 (meaning failure). 
// But a signed version of a type can only store ***HALF*** the 
// value that its unsigned version can store!!!
//
// A function of the kind "indexOf" may return wrong result when
// searching a very big array!!!
//
// The correct way is stop using the sentinel -1 for failure, 
// and return a struct of the kind { long index, bool failed }
//
// This library will not go into that because this is not the only 
// C flaw. A function expecting to receive an unsigned integer would 
// generate a huge bug when called with a negative integer, because C
// automatically converts the (small) negative argument into a (very
// big) unsigned value. 
//
// There is no way of stopping C of doing that. It would be necessary 
// a new programing language, more restrictive about types.
//
// C is flawed!!!
//
// This library uses **unsigned types** for sizes, indexes and
// parameters. So it is BUG FREE, *excepting* objects which size
// is greater than the max positive integer of the type "long",
// for shuch big objects you MUST NOT use this library.

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

