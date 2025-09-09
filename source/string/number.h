// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

// function 'createStringFromLong' is in file 'create-from-release.h'

// the parsers here stop parsing when find a separator (comma)!!

long _stringLengthOfDigits(String* string, long start) // zero base index 
{
    long length = 0;
    
    for (long index = start; index < string->size; index++)
    {
        if (string->address[index] < '0') { break; }
        if (string->address[index] > '9') { break; }
        
        length += 1;
    }
    
    return length;
}

double _stringParseIntSegment(String* string, long start, long length) // zero base index
{    
    double value = 0;
    
    long factor = 1;
    
    long end = start + length - 1;
    
    for (int index = end; index >= start; index--) // runs backwards
    {
        value += (string->address[index] - '0') * factor;
        
        factor *= 10;
    }
    
    return value;
}

double _stringParseFractionalSegment(String* string, long start, long length, int signal) // zero base index
{    
    if (length > 12) { length = 12; }
    
    double divisor = 1;
    
    for (int n = 0; n < length; n++) { divisor *= 10; }
    
    return signal * _stringParseIntSegment(string, start, length) / divisor; // zero base index
}

///////////////////////////////////////////////////////////////////////////////

NullLong stringParseLong(String* string) // TODO: (?) checking if the number is not too (negative) big
{     
    int signal = 0; // zero means signal not found

    long start = stringMarginCount(string);
    
    if (start == string->size) { return makeNullLong(0, true); }
    
    if (string->address[start] == '-') { signal = -1; start += 1; }        
    
    else if (string->address[start] == '+') { signal = +1; start += 1; } 
    
    else { signal = +1; }
    
    long length = _stringLengthOfDigits(string, start);
    
    if (length == 0) { return makeNullLong(0, true); }
    
    long value = _stringParseIntSegment(string, start, length); // zero base index
      
    return makeNullLong(signal * value, false);
}

///////////////////////////////////////////////////////////////////////////////

NullDouble stringParseDouble(String* string) // TODO: (?) checking if the number is not too (negative) big
{   
    int signal = 0; // zero means signal not found
    
    long start = stringMarginCount(string);
    
    if (start == string->size) { return makeNullDouble(0, true); }
    
    if (string->address[start] == '-') { signal = -1; start += 1; }        
    
    else if (string->address[start] == '+') { signal = +1; start += 1; } 
    
    else { signal = +1; }
    
    if (string->address[start] == DOT_OR_COMMA) // fractional only
    { 
        start += 1; // skips DOT_OR_COMMA
        
        long length = _stringLengthOfDigits(string, start);
        
        if (length == 0) { return makeNullDouble(0, true); }
        
        double fractional = _stringParseFractionalSegment(string, start, length, signal); // zero base index
    
        return makeNullDouble(fractional, false);
    }
        
    long length = _stringLengthOfDigits(string, start);

    if (length == 0) { return makeNullDouble(0, true); }

    double integerPart = signal * _stringParseIntSegment(string, start, length); // zero base index

    start += length;

    if (start == string->size) { return makeNullDouble(integerPart, false); }

    if (string->address[start] != DOT_OR_COMMA) { return makeNullDouble(integerPart, false); }
    
    start += 1; // skips DOT_OR_COMMA
    
    length = _stringLengthOfDigits(string, start);
        
    if (length == 0) { return makeNullDouble(integerPart, false); }
        
    double fractional = _stringParseFractionalSegment(string, start, length, signal); // zero base index
    
    return makeNullDouble(integerPart + fractional, false);
}

