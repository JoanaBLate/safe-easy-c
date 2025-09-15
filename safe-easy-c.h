///////////////////////////////////////////////////////////////////////////////
///                            SafeEasyC Library                            ///
///                                                                         ///
///                    DO   **NOT**   EDIT   THIS   FILE!                   ///
///                                                                         ///
///                https://github.com/JoanaBLate/safe-easy-c                ///
///////////////////////////////////////////////////////////////////////////////

// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



// file: types/types.h //

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



// file: memory/memory.h //

void* _allocateHeap(long size)
{
    if (size < 1) { return NULL; }

    void* address = malloc((size_t) size);

    if (address != NULL) { return address; }

    printf("\nERROR: failed to allocate %lu bytes in heap\n", size);

    exit(1);
}

void* _allocateHeapClean(long size)
{
    if (size < 1) { return NULL; }

    void* address = calloc(1, (size_t)  size);

    if (address != NULL) { return address; }

    printf("\nERROR: failed to allocate %lu bytes in heap\n", size);

    exit(1);
}

void* _reallocateHeap(void* address, long size)
{
    if (size < 1) { return NULL; }

    void* newAddress = realloc(address, (size_t) size);

    if (newAddress != NULL) { return newAddress; }

    printf("\nERROR: failed to allocate %lu bytes in heap\n", size);

    exit(1);
}

void releaseHeap(void* voidStruct)
{
    AddressStruct* genericStruct = (AddressStruct*) voidStruct;

    if (genericStruct->address == NULL) { return; } // avoiding double free

    // empty strings (fakenull address) must not be freed
    if (genericStruct->address != FAKENULL) { free(genericStruct->address); }

    genericStruct->address = NULL;
}

bool objectExists(void* voidStruct)
{
    AddressStruct* genericStruct = (AddressStruct*) voidStruct;

    return genericStruct->address != NULL;
}

void _errorAlreadyReleased(char* funcName)
{
    printf("\nERROR: trying to use already released object in function '%s'\n", funcName);

    exit(1);
}

void assureNotReleased(void* voidStruct, char* funcName)
{
    AddressStruct* genericStruct = (AddressStruct*) voidStruct;

    if (genericStruct->address == NULL) { _errorAlreadyReleased(funcName); }
}

void _errorNullArgument(char* funcName)
{
    printf("\nERROR: null argument received in function '%s'\n", funcName);

    exit(1);
}



// file: string/print.h //

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


// file: string/info.h //

// char* for storing text
// unsigned char for raw byte values
// int for functions that return character codes + need a sentinel

long getStringSize(String* string)
{
    if (string->address == NULL) { _errorAlreadyReleased("getStringSize"); }

    return string->size;
}

// the same pattern as the C standard library
int stringCharCodeAt(String* string, long index)
{
    if (string->address == NULL) { _errorAlreadyReleased("stringCharCodeAt"); }

    if (index < 0  ||  index >= string->size) { return -1; } // out of bounds

    return (int) ((unsigned char) string->address[index]);
}

bool stringsAreEqual(String* stringA, String* stringB)
{
    if (stringA->address == NULL) { _errorAlreadyReleased("stringsAreEqual"); }
    if (stringB->address == NULL) { _errorAlreadyReleased("stringsAreEqual"); }

    if (stringA->size != stringB->size) { return false; };

    for (long index = 0; index < stringA->size; index ++)
    {
        if (stringA->address[index] != stringB->address[index]) { return false; }
    }
    return true;
}

char stringsCompare(String* stringA, String* stringB)
{
    if (stringA->address == NULL) { _errorAlreadyReleased("stringsCompare"); }
    if (stringB->address == NULL) { _errorAlreadyReleased("stringsCompare"); }

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
    if (string->address == NULL) { _errorAlreadyReleased("stringStartsWith"); }
    if (target->address == NULL) { _errorAlreadyReleased("stringStartsWith"); }

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
    if (string->address == NULL) { _errorAlreadyReleased("stringEndsWith"); }
    if (target->address == NULL) { _errorAlreadyReleased("stringEndsWith"); }

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
    if (string->address == NULL) { _errorAlreadyReleased("stringIndexOf"); }
    if (target->address == NULL) { _errorAlreadyReleased("stringIndexOf"); }

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
    if (string->address == NULL) { _errorAlreadyReleased("stringIndexOfAfter"); }
    if (target->address == NULL) { _errorAlreadyReleased("stringIndexOfAfter"); }

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
    if (string->address == NULL) { _errorAlreadyReleased("stringLastIndexOf"); }
    if (target->address == NULL) { _errorAlreadyReleased("stringLastIndexOf"); }

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
    if (string->address == NULL) { _errorAlreadyReleased("stringLastIndexOfBefore"); }
    if (target->address == NULL) { _errorAlreadyReleased("stringLastIndexOfBefore"); }

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
    if (string->address == NULL) { _errorAlreadyReleased("stringContains"); }
    if (target->address == NULL) { _errorAlreadyReleased("stringContains"); }

    return (stringIndexOf(string, target) != -1);
}

long stringCountOf(String* string, String* target)
{
    if (string->address == NULL) { _errorAlreadyReleased("stringCountOf"); }
    if (target->address == NULL) { _errorAlreadyReleased("stringCountOf"); }

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
    if (string->address == NULL) { _errorAlreadyReleased("stringMarginCount"); }

    long count = 0;

    for (long index = 0; index < string->size; index++)
    {

        if (string->address[index] == ' ')  { count += 1; continue; }
        if (string->address[index] == '\t') { count += 1; continue; }

        break;
   }

    return count;
}


// file: string/create.h //

// helper function only
// expects that heap allocation is already resolved
String _makeStructString(char* address, long size)
{
    String string = { address, size };

    return string;
}

// does not allocate on heap
// address NULL is only for heap released objects
// the empty string check is made on the string size (not address)
String createEmptyString()
{
    return _makeStructString(FAKENULL, 0);
}

String createStringFromByte(int n)
{
    if (n < 0  ||  n > 255) { return createEmptyString(); }

    char* buffer = _allocateHeap(1);

    buffer[0] = n;

    return _makeStructString(buffer, 1);
}

String _createStringFromInfo(char* sourceAddress, long sourceSize)
{
    long bufferSize = sourceSize;

    if (bufferSize == 0) { return createEmptyString(); }

    char* buffer = _allocateHeap(bufferSize);

    memcpy(buffer, sourceAddress, (unsigned long) bufferSize);

    return _makeStructString(buffer, bufferSize);
}

String createStringFromLiteral(char* cString)
{
    if (cString == NULL) { return createEmptyString(); }

    unsigned long size = strlen(cString);

    return _createStringFromInfo(cString, (long) size);
}

String createStringFromCString(char* cString)
{
    return createStringFromLiteral(cString);
}

String createStringClone(String* string)
{
    if (string->address == NULL) { _errorAlreadyReleased("createStringClone"); }

    return _createStringFromInfo(string->address, string->size);
}

String createStringFromBuffer(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("createStringFromBuffer"); }

    return _createStringFromInfo(buffer->address + buffer->margin, buffer->size);
}

String createStringFromLong(long number)
{
    char array[30]; // stack allocation

    sprintf(array, "%li", number);

    unsigned long size = strlen(array);

    return _createStringFromInfo(array, (long) size);
}


// file: string/repeat.h //

String createStringRepeat(String* string, long count)
{
    if (string->address == NULL) { _errorAlreadyReleased("createStringRepeat"); }

    if (string->size == 0) { return createEmptyString(); }

    if (count < 1) { return createEmptyString(); }

    long bufferSize = count * string->size;

    char* buffer = _allocateHeap(bufferSize);

    for (long turn = 0; turn < count; turn++)
    {
        memcpy(&buffer[turn * string->size], string->address, (unsigned long) string->size);
    }

    return _makeStructString(buffer, bufferSize);
}


// file: string/append-insert.h //

String createStringAppend(String* string, String* chunk)
{
    if (string->address == NULL) { _errorAlreadyReleased("createStringAppend"); }

    if (string->size == 0) { return createStringClone(chunk); }

    if (chunk->size == 0)  { return createStringClone(string); }

    long bufferSize = string->size + chunk->size;

    char* buffer = _allocateHeap(bufferSize);

    memcpy(buffer, string->address, (unsigned long) string->size);

    memcpy(&buffer[string->size], chunk->address, (unsigned long) chunk->size);

    return _makeStructString(buffer, bufferSize);
}

String createStringInsert(String* string, String* chunk, long position)
{
    if (string->address == NULL) { _errorAlreadyReleased("createStringInsert"); }

    if (string->size == 0) { return createStringClone(chunk); }

    if (chunk->size == 0) { return createStringClone(string); }

    if (position <= 0) { return createStringAppend(chunk, string); }

    if (position >= string->size) { return createStringAppend(string, chunk); }

    long bufferSize = string->size + chunk->size;

    char* buffer = _allocateHeap(bufferSize);

    for (long index = 0; index < position; index++) { buffer[index] = string->address[index]; }

    for (long index = 0; index < chunk->size; index++) { buffer[position + index] = chunk->address[index]; }

    for (long index = position; index < string->size; index++) { buffer[index + chunk->size] = string->address[index]; }

    return _makeStructString(buffer, bufferSize);
}


// file: string/substring.h //

String createSubstring(String* string, long start, long count)
{
    if (string->address == NULL) { _errorAlreadyReleased("createSubstring"); }

    if (count < 1) { return createEmptyString(); }

    long off = start + count;

    if (off > string->size) { off = string->size; }

    if (start < 0) { start = 0; }

    long size = off - start;

    if (size <= 0) { return createEmptyString(); }

    return _createStringFromInfo(string->address + start, size);
}

String createSubstringStart(String* string, long count)
{
    if (string->address == NULL) { _errorAlreadyReleased("createSubstringStart"); }

    return createSubstring(string, 0, count);
}

String createSubstringEnd(String* string, long count)
{
    if (string->address == NULL) { _errorAlreadyReleased("createSubstringEnd"); }

    if (count < 1) { return createEmptyString(); }

    long start = string->size - count;

    return createSubstring(string, start, count);
}


// file: string/lower-reverse-sort.h //

String createStringToLower(String* string)
{
    if (string->address == NULL) { _errorAlreadyReleased("createStringToLower"); }

    String newString = createStringClone(string);

    for (long index = 0; index < newString.size; index++)
    {
        newString.address[index] = tolower(newString.address[index]);
    }

    return newString;
}

String createStringToUpper(String* string)
{
    if (string->address == NULL) { _errorAlreadyReleased("createStringToUpper"); }

    String newString = createStringClone(string);

    for (long index = 0; index < newString.size; index++)
    {
        newString.address[index] = toupper(newString.address[index]);
    }

    return newString;
}

String createStringToOppositeCase(String* string)
{
    if (string->address == NULL) { _errorAlreadyReleased("createStringToOppositeCase"); }

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
    if (string->address == NULL) { _errorAlreadyReleased("createStringReverse"); }

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
    if (string->address == NULL) { _errorAlreadyReleased("createStringSort"); }

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


// file: string/pad.h //

String createStringPadStart(String* string, String* chunk, long count)
{
    if (string->address == NULL) { _errorAlreadyReleased("createStringPadStart"); }
    if (chunk->address == NULL)  { _errorAlreadyReleased("createStringPadStart"); }

    if (count < 1) { return createStringClone(string); }

    if (chunk->size == 0) { return createStringClone(string); }

    long bufferSize = (count * chunk->size) + string->size;

    char* buffer = _allocateHeap(bufferSize);

    long index = -1;

    while (count > 0) {

        count -= 1;

        for (long n = 0; n < chunk->size; n++) {

            index += 1;

            buffer[index] = chunk->address[n];
        }
    }

    memcpy(&buffer[index + 1], string->address, (unsigned long) string->size);

    return _makeStructString(buffer, bufferSize);
}

String createStringPadEnd(String* string, String* chunk, long count)
{
    if (string->address == NULL) { _errorAlreadyReleased("createStringPadEnd"); }
    if (chunk->address == NULL)  { _errorAlreadyReleased("createStringPadEnd"); }

    if (count < 1) { return createStringClone(string); }

    if (chunk->size == 0) { return createStringClone(string); }

    long bufferSize = (count * chunk->size) + string->size;

    char* buffer = _allocateHeap(bufferSize);

    memcpy(buffer, string->address, (unsigned long) string->size);

    long index = string->size - 1;

    while (count > 0) {

        count -= 1;

        for (long n = 0; n < chunk->size; n++) {

            index += 1;

            buffer[index] = chunk->address[n];
        }
    }

    return _makeStructString(buffer, bufferSize);
}


// file: string/replace.h //

// replace by position ////////////////////////////////////////////////////////

String createStringReplaceStart(String* string, long count, String* chunk)
{
    if (string->address == NULL) { _errorAlreadyReleased("createStringReplaceStart"); }
    if (chunk->address == NULL)  { _errorAlreadyReleased("createStringReplaceStart"); }

    if (count < 1) { return createStringInsert(string, chunk, 0); }

    if (count >= string->size) { return createStringClone(chunk); }

    long stringRightArmStart = count;
    long stringRightArmSize = string->size - count;

    long bufferSize = chunk->size + stringRightArmSize;

    char* buffer = _allocateHeap(bufferSize);

    // buffer left arm
    for (long index = 0; index < chunk->size; index++) { buffer[index] = chunk->address[index]; }

    // buffer right arm
    for (long index = 0; index < stringRightArmSize; index++)
    {
        buffer[chunk->size + index] = string->address[stringRightArmStart + index];
    }

    return _makeStructString(buffer, bufferSize);
}

String createStringReplaceEnd(String* string, long count, String* chunk)
{
    if (string->address == NULL) { _errorAlreadyReleased("createStringReplaceEnd"); }
    if (chunk->address == NULL)  { _errorAlreadyReleased("createStringReplaceEnd"); }

    if (count < 1) { return createStringAppend(string, chunk); }

    if (count >= string->size) { return createStringClone(chunk); }

 // long stringLeftArmStart = 0;
    long stringLeftArmSize = string->size - count;

    long bufferSize = stringLeftArmSize + chunk->size;

    char* buffer = _allocateHeap(bufferSize);

    // buffer left arm
    for (long index = 0; index < stringLeftArmSize; index++) { buffer[index] = string->address[index]; }

    // buffer right arm
    for (long index = 0; index < chunk->size; index++) { buffer[stringLeftArmSize + index] = chunk->address[index]; }

    return _makeStructString(buffer, bufferSize);
}

// replace by target //////////////////////////////////////////////////////////

String _createStringReplace(String* string, String* target, String* chunk, long position)
{
 // unnecessary, private function
 // if (string->address == NULL) { _errorAlreadyReleased("_createStringReplace"); }
 // if (target->address == NULL) { _errorAlreadyReleased("_createStringReplace"); }
 // if (chunk->address  == NULL) { _errorAlreadyReleased("_createStringReplace"); }

 // long stringLeftArmStart = 0;
    long stringLeftArmSize = position;

    long stringRightArmStart = position + target->size;
    long stringRightArmSize = string->size - stringLeftArmSize - target->size;

    long bufferSize = stringLeftArmSize + chunk->size + stringRightArmSize;

    char* buffer = _allocateHeap(bufferSize);

    // buffer left arm
    for (long index = 0; index < stringLeftArmSize; index++) { buffer[index] = string->address[index]; }

    // buffer middle
    for (long index = 0; index < chunk->size; index++) { buffer[position + index] = chunk->address[index]; }

    // buffer right arm
    for (long index = 0; index < stringRightArmSize; index++)
    {
        buffer[position + chunk->size + index] = string->address[stringRightArmStart + index];
    }

    return _makeStructString(buffer, bufferSize);
}

String createStringReplace(String* string, String* target, String* chunk)
{
    if (string->address == NULL) { _errorAlreadyReleased("createStringReplace"); }
    if (target->address == NULL) { _errorAlreadyReleased("createStringReplace"); }
    if (chunk->address  == NULL) { _errorAlreadyReleased("createStringReplace"); }

    long position = stringIndexOf(string, target);

    if (position == -1) { return createStringClone(string); } // target not found

    if (position == 0) { return createStringReplaceStart(string, target->size, chunk); }

    if (position + target->size == string->size) { return createStringReplaceEnd(string, target->size, chunk); }

    return _createStringReplace(string, target, chunk, position);
}

String createStringReplaceLast(String* string, String* target, String* chunk)
{
    if (string->address == NULL) { _errorAlreadyReleased("createStringReplaceLast"); }
    if (target->address == NULL) { _errorAlreadyReleased("createStringReplaceLast"); }
    if (chunk->address  == NULL) { _errorAlreadyReleased("createStringReplaceLast"); }

    long position = stringLastIndexOf(string, target);

    if (position == -1) { return createStringClone(string); } // target not found

    if (position == 0) { return createStringReplaceStart(string, target->size, chunk); }

    if (position + target->size == string->size) { return createStringReplaceEnd(string, target->size, chunk); }

    return _createStringReplace(string, target, chunk, position);
}

// replace all by target //////////////////////////////////////////////////////

String createStringReplaceAll(String* string, String* target, String* chunk)
{
    if (string->address == NULL) { _errorAlreadyReleased("createStringReplaceAll"); }
    if (target->address == NULL) { _errorAlreadyReleased("createStringReplaceAll"); }
    if (chunk->address  == NULL) { _errorAlreadyReleased("createStringReplaceAll"); }

    long count = stringCountOf(string, target);

    if (count == 0) { return createStringClone(string); }

    long bufferSize = string->size + count * (chunk->size - target->size);

    if (bufferSize == 0) { return createEmptyString(); }

    char* buffer = _allocateHeap(bufferSize);

    long bufferIndex = -1;

    String temp = _makeStructString(string->address, string->size);

    while (temp.size > 0) {

        bool startsNormal = true;

        if (temp.address[0] == target->address[0])
        {
            startsNormal = ! stringStartsWith(&temp, target); // avoiding always call the function
        }

        if (startsNormal) {

            bufferIndex += 1;
            buffer[bufferIndex] = temp.address[0];

            temp.size -= 1;
            temp.address += 1;

            continue;
        }

        // skipping the target
        temp.size -= target->size;
        temp.address += target->size;

        // inserting the chunk
        for (long index = 0; index < chunk->size; index++)
        {
            bufferIndex += 1;
            buffer[bufferIndex] = chunk->address[index];
        }
    }

    return _makeStructString(buffer, bufferSize);
}


// file: string/remove.h //

String createStringRemove(String* string, String* target)
{
    if (string->address == NULL) { _errorAlreadyReleased("createStringRemove"); }
    if (target->address == NULL) { _errorAlreadyReleased("createStringRemove"); }

    String empty = createEmptyString();

    return createStringReplace(string, target, &empty);
}

String createStringRemoveLast(String* string, String* target)
{
    if (string->address == NULL) { _errorAlreadyReleased("createStringRemoveLast"); }
    if (target->address == NULL) { _errorAlreadyReleased("createStringRemoveLast"); }

    String empty = createEmptyString();

    return createStringReplaceLast(string, target, &empty);
}

String createStringRemoveAll(String* string, String* target)
{
    if (string->address == NULL) { _errorAlreadyReleased("createStringRemoveAll"); }
    if (target->address == NULL) { _errorAlreadyReleased("createStringRemoveAll"); }

    String empty = createEmptyString();

    return createStringReplaceAll(string, target, &empty);
}


// file: string/trim.h //

String stringTrimStart(String* string)
{
    if (string->address == NULL) { _errorAlreadyReleased("stringTrimStart"); }

    long margin = 0;
    long size = string->size;

    while (true)
    {
        if (size == 0) { return createEmptyString(); }

        if ((unsigned char) string->address[margin] > ' ') { break; }

        margin += 1; size -= 1;
    }

    return _createStringFromInfo(string->address + margin, size);
}

String stringTrimEnd(String* string)
{
    if (string->address == NULL) { _errorAlreadyReleased("stringTrimEnd"); }

    long size = string->size;

    while (true)
    {
        if (size == 0) { return createEmptyString(); }

        long index = size - 1;

        if ((unsigned char) string->address[index] > ' ') { break; }

        size -= 1;
    }

    return _createStringFromInfo(string->address, size);
}

String stringTrim(String* string)
{
    if (string->address == NULL) { _errorAlreadyReleased("stringTrim"); }

    long margin = 0;
    long size = string->size;

    while (true) // trims end
    {
        if (size == 0) { return createEmptyString(); }

        long index = size - 1;

        if ((unsigned char) string->address[index] > ' ') { break; }

        size -= 1;
    }

    while (true) // trims start
    {
        if (size == 0) { return createEmptyString(); }

        if ((unsigned char) string->address[margin] > ' ') { break; }

        margin += 1; size -= 1;
    }

    return _createStringFromInfo(string->address + margin, size);
}


// file: string/number.h //

// function 'createStringFromLong' is in file 'create-from-release.h'

// the parsers here stop parsing when find a separator (comma)!!

long _stringLengthOfDigits(String* string, long start)
{
 // unnecessary: private function
 // if (string->address == NULL) { _errorAlreadyReleased("_stringLengthOfDigits"); }

    long length = 0;

    for (long index = start; index < string->size; index++)
    {
        if (string->address[index] < '0') { break; }
        if (string->address[index] > '9') { break; }

        length += 1;
    }

    return length;
}

// *NOT* CHECKING FOR TOO BIG NUMBER
double _stringParseIntSegment(String* string, long start, long length)
{
 // unnecessary: private function
 // if (string->address == NULL) { _errorAlreadyReleased("_stringParseIntSegment"); }

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

double _stringParseFractionalSegment(String* string, long start, long length, int signal)
{
 // unnecessary: private function
 // if (string->address == NULL) { _errorAlreadyReleased("_stringParseFractionalSegment"); }

    if (length > 12) { length = 12; }

    double divisor = 1;

    for (int n = 0; n < length; n++) { divisor *= 10; }

    return signal * _stringParseIntSegment(string, start, length) / divisor;
}

///////////////////////////////////////////////////////////////////////////////

// *NOT* CHECKING FOR TOO BIG NUMBER
NullLong stringParseLong(String* string)
{
    if (string->address == NULL) { _errorAlreadyReleased("_errorAlreadyReleased"); }

    int signal = 0; // zero means signal not found

    long start = stringMarginCount(string);

    if (start == string->size) { return makeNullLong(0, true); }

    if (string->address[start] == '-') { signal = -1; start += 1; }

    else if (string->address[start] == '+') { signal = +1; start += 1; }

    else { signal = +1; }

    long length = _stringLengthOfDigits(string, start);

    if (length == 0) { return makeNullLong(0, true); }

    long value = _stringParseIntSegment(string, start, length);

    return makeNullLong(signal * value, false);
}

///////////////////////////////////////////////////////////////////////////////

// *NOT* CHECKING FOR TOO BIG NUMBER
NullDouble stringParseDouble(String* string)
{
    if (string->address == NULL) { _errorAlreadyReleased("stringParseDouble"); }

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

        double fractional = _stringParseFractionalSegment(string, start, length, signal);

        return makeNullDouble(fractional, false);
    }

    long length = _stringLengthOfDigits(string, start);

    if (length == 0) { return makeNullDouble(0, true); }

    double integerPart = signal * _stringParseIntSegment(string, start, length);

    start += length;

    if (start == string->size) { return makeNullDouble(integerPart, false); }

    if (string->address[start] != DOT_OR_COMMA) { return makeNullDouble(integerPart, false); }

    start += 1; // skips DOT_OR_COMMA

    length = _stringLengthOfDigits(string, start);

    if (length == 0) { return makeNullDouble(integerPart, false); }

    double fractional = _stringParseFractionalSegment(string, start, length, signal);

    return makeNullDouble(integerPart + fractional, false);
}



// file: buffer/pseudo-string.h //

// doesn't allocate memory
// allows buffer to use String functions
String _makePseudoStringFromBuffer(Buffer* buffer)
{
    return _makeStructString(buffer->address + buffer->margin, buffer->size);
}


// file: buffer/print.h //

void printBufferBytes(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("printBufferBytes"); }

    String string = _makePseudoStringFromBuffer(buffer);

    printStringBytes(&string);
}

void printlnBufferBytes(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("printlnBufferBytes"); }

    String string = _makePseudoStringFromBuffer(buffer);

    printlnStringBytes(&string);
}

void printBuffer(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("printBuffer"); }

    String string = _makePseudoStringFromBuffer(buffer);

    printString(&string);
}

void printlnBuffer(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("printlnBuffer"); }

    String string = _makePseudoStringFromBuffer(buffer);

    printlnString(&string);
}

void displayBuffer(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("displayBuffer"); }

    printf("[");
    printBuffer(buffer);
    printf("]  margin: %li   size: %li  capacity: %li\n",  buffer->margin, buffer->size, buffer->capacity);
}


// file: buffer/info.h //

long getBufferCapacity(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("getBufferCapacity"); }

    return buffer->capacity;
}

long getBufferMargin(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("getBufferMargin"); }

    return buffer->margin;
}

long getBufferSize(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("getBufferSize"); }

    return buffer->size;
}

// the same pattern as the C standard library
int bufferByteAt(Buffer* buffer, long index)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferByteAt"); }

    if (index < 1  ||  index > buffer->size) { return -1; } // out of bounds

    return (int) (unsigned char) buffer->address[buffer->margin + index - 1];
}

bool buffersAreEqual(Buffer* bufferA, Buffer* bufferB)
{
    if (bufferA->address == NULL) { _errorAlreadyReleased("buffersAreEqual"); }
    if (bufferB->address == NULL) { _errorAlreadyReleased("buffersAreEqual"); }

    String stringA = _makePseudoStringFromBuffer(bufferA);
    String stringB = _makePseudoStringFromBuffer(bufferB);

    return stringsAreEqual(&stringA, &stringB);
}

char buffersCompare(Buffer* bufferA, Buffer* bufferB)
{
    if (bufferA->address == NULL) { _errorAlreadyReleased("buffersCompare"); }
    if (bufferB->address == NULL) { _errorAlreadyReleased("buffersCompare"); }

    String stringA = _makePseudoStringFromBuffer(bufferA);
    String stringB = _makePseudoStringFromBuffer(bufferB);

    return stringsCompare(&stringA, &stringB);
}

bool bufferStartsWith(Buffer* buffer, String* target)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferStartsWith"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferStartsWith"); }

    String string = _makePseudoStringFromBuffer(buffer);

    return stringStartsWith(&string, target);
}

bool bufferEndsWith(Buffer* buffer, String* target)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferEndsWith"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferEndsWith"); }

    String string = _makePseudoStringFromBuffer(buffer);

    return stringEndsWith(&string, target);
}

long bufferIndexOf(Buffer* buffer, String* target)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferIndexOf"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferIndexOf"); }

    String string = _makePseudoStringFromBuffer(buffer);

    return stringIndexOf(&string, target);
}

long bufferIndexOfAfter(Buffer* buffer, String* target, long usedIndex)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferIndexOfAfter"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferIndexOfAfter"); }

    String string = _makePseudoStringFromBuffer(buffer);

    return stringIndexOfAfter(&string, target, usedIndex);
}

long bufferLastIndexOf(Buffer* buffer, String* target)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferLastIndexOf"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferLastIndexOf"); }

    String string = _makePseudoStringFromBuffer(buffer);

    return stringLastIndexOf(&string, target);
}

long bufferLastIndexOfBefore(Buffer* buffer, String* target, long usedIndex)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferLastIndexOfBefore"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferLastIndexOfBefore"); }

    String string = _makePseudoStringFromBuffer(buffer);

    return stringLastIndexOfBefore(&string, target, usedIndex);
}

bool bufferContains(Buffer* buffer, String* target)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferContains"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferContains"); }

    String string = _makePseudoStringFromBuffer(buffer);

    return stringContains(&string, target);
}

long bufferCountOf(Buffer* buffer, String* target)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferCountOf"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferCountOf"); }

    String string = _makePseudoStringFromBuffer(buffer);

    return stringCountOf(&string, target);
}


// file: buffer/create.h //

Buffer createEmptyBuffer()
{
    char* address = _allocateHeap(1);

    Buffer buffer = { address, 1, 0, 0 };

    buffer.address[0] = 0;

    return buffer;
}

Buffer createBuffer(long capacity)
{
    if (capacity < 1) { return createEmptyBuffer(); }

    char* address = _allocateHeap(capacity);

    Buffer buffer = { address, capacity, 0, 0 };

    return buffer;
}

Buffer createBufferFromLiteral(char* cString)
{
    if (cString == NULL) { return createEmptyBuffer(); }

    long size = (long) strlen(cString);

    long capacity = size;

    if (capacity < 1) { return createEmptyBuffer(); }

    char* address = _allocateHeap(capacity);

    Buffer buffer = { address, capacity, 0, size };

    memcpy(buffer.address, cString, (size_t) size);

    return buffer;
}

Buffer createBufferFromCString(char* cString)
{
    return createBufferFromLiteral(cString);
}

Buffer createBufferFromString(String* string)
{
    if (string->address == NULL) { _errorAlreadyReleased("createBufferFromString"); }

    long capacity = string->size;

    Buffer buffer = createBuffer(capacity);

    if (capacity < 1) { return buffer; }

    buffer.size = capacity;

    memcpy(buffer.address, string->address, (size_t) string->size);

    return buffer;
}


// file: buffer/expand.h //

bool bufferMaybeExpandCapacity(Buffer* buffer, long neededSpace)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferMaybeExpandCapacity"); }

    long hiddenSpace = buffer->capacity - buffer->size;

    long neededExpansion = neededSpace - hiddenSpace;

    if (neededExpansion <= 0) { return false; }

    long newCapacity = buffer->capacity + neededExpansion;

    buffer->address = _reallocateHeap(buffer->address, newCapacity);

    buffer->capacity = newCapacity;

    return true;
}


// file: buffer/move-range.h //

// the exact order of the statements of this function is crucial!
void bufferMoveRange(Buffer* buffer, long origin, long count, long destiny)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferMoveRange"); }

    if (count < 1) { return; }

    // destiny
    long destinyStart = destiny;

    if (destinyStart >= buffer->size) { return; }

    long destinyEnd = destinyStart + count - 1;

    if (destinyEnd < 0) { return; }

    if (destinyEnd >= buffer->size) { destinyEnd = buffer->size - 1; }

    long deltaForOriginStart = 0;

    if (destinyStart < 0) {

        deltaForOriginStart = -destinyStart;

        destinyStart = 0;
    }

    long destinySize = destinyEnd - destinyStart + 1;

    // origin
    long originStart = origin;

    long originEnd = originStart + count - 1;

    if (originEnd < 0) { return; }

    if (originEnd >= buffer->size) { originEnd = buffer->size - 1; }

    if (originStart < 0) { originStart = 0; }

    originStart += deltaForOriginStart; // adjusting to negative destinyStart

    if (originStart >= buffer->size) { return; }

    long originSize = originEnd - originStart + 1;

    // size
    long size = originSize;

    if (destinySize < size) { size = destinySize; }

    // copy
    if (originStart > destinyStart)
    {
        for (long n = buffer->margin; n < (buffer->margin + size); n++)
        {
            long indexOrigin  = originStart  + n;
            long indexDestiny = destinyStart + n;

            buffer->address[indexDestiny] = buffer->address[indexOrigin];
        }
    }
    else if (originStart < destinyStart)
    {
        for (long n = (buffer->margin + size - 1); n > (buffer->margin - 1); n--) // runs backwards
        {
            long indexOrigin  = originStart  + n;
            long indexDestiny = destinyStart + n;

            buffer->address[indexDestiny] = buffer->address[indexOrigin];
        }
    }
 // else if (originStart == destinyStart) { return; }
}


// file: buffer/copy-range.h //

// the exact order of the statements of this function is crucial!
void bufferCopyRange(Buffer* originBuffer, long originPosition, long count, Buffer* destinyBuffer, long destinyPosition)
{
    if (originBuffer->address == NULL) { _errorAlreadyReleased("bufferCopyRange"); }

    if (destinyBuffer->address == NULL) { _errorAlreadyReleased("bufferCopyRange"); }

    if (count < 1) { return; }

    if (originBuffer->address == destinyBuffer->address)
    {
        bufferMoveRange(destinyBuffer, originPosition, count, destinyPosition); return; // 'destinyBuffer' OK
    }

    // destiny
    long destinyStart = destinyPosition;

    if (destinyStart >= destinyBuffer->size) { return; }

    long destinyEnd = destinyStart + count - 1;

    if (destinyEnd < 0) { return; }

    if (destinyEnd >= destinyBuffer->size) { destinyEnd = destinyBuffer->size - 1; }

    long deltaForOriginStart = 0;

    if (destinyStart < 0) {

        deltaForOriginStart = -destinyStart;

        destinyStart = 0;
    }

    long destinySize = destinyEnd - destinyStart + 1;

    // origin
    long originStart = originPosition;

    long originEnd = originStart + count - 1;

    if (originEnd < 0) { return; }

    if (originEnd >= originBuffer->size) { originEnd = originBuffer->size - 1; }

    if (originStart < 0) { originStart = 0; }

    originStart += deltaForOriginStart; // adjusting to negative destinyStart

    if (originStart >= originBuffer->size) { return; }

    long originSize = originEnd - originStart + 1;

    // size
    long size = originSize;

    if (destinySize < size) { size = destinySize; }

    // copying (expecting no overlapping, buffers are different)
    for (long n = 0; n < size; n++)
    {
        long indexOrigin  = originBuffer->margin + originStart  + n;
        long indexDestiny = destinyBuffer->margin + destinyStart + n;

        destinyBuffer->address[indexDestiny] = originBuffer->address[indexOrigin];
    }
}


// file: buffer/lower-reverse-sort.h //

void bufferToLower(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferToLower"); }

    long start = buffer->margin;
    long off = buffer->margin + buffer->size;

    for (long index = start; index < off; index++)
    {
        buffer->address[index] = tolower(buffer->address[index]);
    }
}

void bufferToUpper(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferToUpper"); }

    long start = buffer->margin;
    long off = buffer->margin + buffer->size;

    for (long index = start; index < off; index++)
    {
        buffer->address[index] = toupper(buffer->address[index]);
    }
}

void bufferToOppositeCase(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferToOppositeCase"); }

    long start = buffer->margin;
    long off = buffer->margin + buffer->size;

    for (long index = start; index < off; index++)
    {
        buffer->address[index] = tolower(buffer->address[index]);

        char c = buffer->address[index];

        if (isupper(c))
        {
            buffer->address[index] = tolower(c);
        }
        else if (islower(c))
        {
            buffer->address[index] = toupper(c);
        }
    }
}

void bufferReverse(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferReverse"); }

    long halfLength = buffer->size / 2;

    for (long position = 0; position < halfLength; position++)
    {
        long indexA = buffer->margin + position;

        long indexB = buffer->margin + (buffer->size - 1 - position);

        char temp = buffer->address[indexA];

        buffer->address[indexA] = buffer->address[indexB];

        buffer->address[indexB] = temp;
    }
}

void bufferSort(Buffer* buffer) // TODO: make it fast
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferSort"); }

    for (long positionA = 0; positionA < buffer->size - 1; positionA++)
    {
        for (long positionB = positionA + 1; positionB < buffer->size; positionB++)
        {
            long indexA = buffer->margin + positionA;

            long indexB = buffer->margin + positionB;

            if (buffer->address[indexA] <= buffer->address[indexB]) { continue; }

            char temp = buffer->address[indexA];

            buffer->address[indexA] = buffer->address[indexB];

            buffer->address[indexB] = temp;
        }
    }
}


// file: buffer/trim.h //

bool bufferTrimStart(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferTrimStart"); }

    bool changed = false;

    while (true)
    {
        if (buffer->size == 0) { return changed; }

        if ((unsigned char) buffer->address[buffer->margin] > ' ') { break; }

        buffer->margin += 1; buffer->size -= 1;

        changed = true;
    }

    return changed;
}

bool bufferTrimEnd(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferTrimEnd"); }

    bool changed = false;

    while (true)
    {
        if (buffer->size == 0) { return changed; }

        long index = buffer->margin + buffer->size - 1;

        if ((unsigned char) buffer->address[index] > ' ') { break; }

        buffer->size -= 1;

        changed = true;
    }

    return changed;
}

bool bufferTrim(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferTrim"); }

    bool changed = false;

    if (bufferTrimStart(buffer)) { changed = true; }

    if (bufferTrimEnd(buffer)) { changed = true; }

    return changed;
}

///////////////////////////////////////////////////////////////////////////////

bool bufferTrimStartTarget(Buffer* buffer, String* target)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferTrimStartTarget"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferTrimStartTarget"); }

    bool changed = false;

    while (true)
    {
        String virtual = _makePseudoStringFromBuffer(buffer);

        if (! stringStartsWith(&virtual, target)) { break; }

        buffer->margin += target->size; buffer->size -= target->size;

        changed = true;
    }

    return changed;
}

bool bufferTrimEndTarget(Buffer* buffer, String* target)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferTrimEndTarget"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferTrimEndTarget"); }

    bool changed = false;

    while (true)
    {
        String virtual = _makePseudoStringFromBuffer(buffer);

        if (! stringEndsWith(&virtual, target)) { break; }

        buffer->size -= target->size;

        changed = true;
    }

    return changed;
}

bool bufferTrimTarget(Buffer* buffer, String* target)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferTrimTarget"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferTrimTarget"); }

    bool changed = false;

    if (bufferTrimStartTarget(buffer, target)) { changed = true; }

    if (bufferTrimEndTarget(buffer, target)) { changed = true; }

    return changed;
}

///////////////////////////////////////////////////////////////////////////////

bool bufferTrimStartAny(Buffer* buffer, String* sample)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferTrimStartAny"); }
    if (sample->address == NULL) { _errorAlreadyReleased("bufferTrimStartAny"); }

    bool changed = false;

    while (buffer->size > 0)
    {
        char* bufferHead = buffer->address + buffer->margin;

        bool modified = false;

        for (int n = 0; n < sample->size; n++)
        {
            char c = sample->address[n];

            if (*bufferHead != c) { continue; }

            buffer->margin += 1; buffer->size -= 1; modified = true; changed = true; break;
        }

        if (! modified) { break; }
    }

    return changed;
}

bool bufferTrimEndAny(Buffer* buffer, String* sample)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferTrimEndAny"); }
    if (sample->address == NULL) { _errorAlreadyReleased("bufferTrimEndAny"); }

    bool changed = false;

    while (buffer->size > 0)
    {
        char* bufferTail = buffer->address + buffer->margin + buffer->size - 1;

        bool modified = false;

        for (int n = 0; n < sample->size; n++)
        {
            char c = sample->address[n];

            if (*bufferTail != c) { continue; }

            buffer->size -= 1; modified = true; changed = true; break;
        }

        if (! modified) { break; }
    }

    return changed;
}

bool bufferTrimAny(Buffer* buffer, String* sample)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferTrimAny"); }
    if (sample->address == NULL) { _errorAlreadyReleased("bufferTrimAny"); }

    bool changed = false;

    if (bufferTrimStartAny(buffer, sample)) { changed = true; }

    if (bufferTrimEndAny(buffer, sample)) { changed = true; }

    return changed;
}


// file: buffer/eat-start-end.h //

String bufferEatStart(Buffer* buffer, long count)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferEatStart"); }

    if (count < 1) { return createEmptyString(); }

    long size = count;

    if (size > buffer->size) { size = buffer->size; }

    String token = _createStringFromInfo(buffer->address + buffer->margin, size);

    buffer->margin += size; buffer->size -= size;

    return token;
}

String bufferEatEnd(Buffer* buffer, long count)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferEatEnd"); }

    if (count < 1) { return createEmptyString(); }

    long size = count;

    if (size > buffer->size) { size = buffer->size; }

    String token = _createStringFromInfo(buffer->address + buffer->margin + buffer->size - size, size);

    buffer->size -= size;

    return token;
}


// file: buffer/replace-start-end.h //

void bufferReplaceStart(Buffer* buffer, long count, String* chunk)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferReplaceStart"); }

    if (count < 1) { count = 0; }

    else if (count > buffer->size) { count = buffer->size; }

    // eating the start
    buffer->size -= count;
    buffer->margin += count;

    if (chunk->size <= buffer->margin)
    {
        buffer->margin -= chunk->size;

        memcpy(buffer->address + buffer->margin, chunk->address, (size_t) chunk->size);

        buffer->size += chunk->size;

        return;
    }

    bufferMaybeExpandCapacity(buffer, chunk->size);

    // now capacity is enough but margin is not enough: must move bytes to right

    long delta = chunk->size - buffer->margin;

    buffer->size += delta;

    bufferMoveRange(buffer, 1, buffer->size - delta, delta);

    buffer->size += buffer->margin;

    buffer->margin = 0;

    // pasting the chunk

    memcpy(buffer->address, chunk->address, (size_t) chunk->size);
}

void bufferReplaceEnd(Buffer* buffer, long count, String* chunk)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferReplaceEnd"); }

    if (count < 1) { count = 0; }

    else if (count > buffer->size) { count = buffer->size; }

    // eating the end
    buffer->size -= count;

    long hiddenTail = buffer->capacity - buffer->margin - buffer->size;

    if (chunk->size <= hiddenTail)
    {
        memcpy(buffer->address + buffer->margin + buffer->size, chunk->address, (size_t) chunk->size);

        buffer->size += chunk->size;

        return;
    }

    bufferMaybeExpandCapacity(buffer, chunk->size);

    hiddenTail = buffer->capacity - buffer->margin - buffer->size;

    long delta = chunk->size - hiddenTail;

    if (delta == 0) // no need to displace data
    {
        memcpy(buffer->address + buffer->margin + buffer->size, chunk->address, (size_t) chunk->size);

        buffer->size += chunk->size;

        return;
    }

    // must use the margin: moving bytes to left

    long position = buffer->margin + buffer->size - delta;

    buffer->margin -= delta;

    buffer->size += delta;

    bufferMoveRange(buffer, 1 + delta, buffer->size, 0);

    memcpy(buffer->address + position, chunk->address, (size_t) chunk->size);

    buffer->size += chunk->size - delta;
}


// file: buffer/replace-target-all.h //

// replace target once ////////////////////////////////////////////////////////

bool _bufferReplace(Buffer* buffer, String* target, String* chunk, long relativePosition)
{
    if (relativePosition == 0) { return false; } // target not found

    long absolutePosition = buffer->margin + relativePosition;

    // just enough room
    if (target->size == chunk->size)
    {
        memcpy(buffer->address + absolutePosition, chunk->address, (size_t) chunk->size);

        return true;
    }

    // more than enough room
    if (target->size > chunk->size)
    {
        memcpy(buffer->address + absolutePosition, chunk->address, (size_t) chunk->size);

        long delta = target->size - chunk->size;
        long start = absolutePosition + chunk->size;
        long off = buffer->margin + buffer->size - delta;

        for (long index = start; index < off; index++)
        {
            buffer->address[index] = buffer->address[index + delta];
        }

        buffer->size -= delta;

        return true;
    }

    long neededSpace = chunk->size - target->size;

    bufferMaybeExpandCapacity(buffer, neededSpace);

    // moving to the right (maybe)
    long hiddenTail = buffer->capacity - buffer->margin - buffer->size;

    long deltaRight = neededSpace;

    if (deltaRight > hiddenTail) { deltaRight = hiddenTail; }

    if (deltaRight > 0)
    {
        buffer->size += deltaRight;

        long a = relativePosition + target->size;

        long b = a + deltaRight;

        bufferMoveRange(buffer, a, buffer->size, b);

        neededSpace -= deltaRight;
    }

    // moving to the left (maybe)
    long deltaLeft = neededSpace;

 // if (deltaLeft > buffer->margin) { deltaLeft = buffer->margin; } // unnecessary

    if (deltaLeft > 0)
    {
        buffer->margin -= deltaLeft;

        buffer->size += deltaLeft;

        bufferMoveRange(buffer, 1 + deltaLeft, buffer->size, 1);

        absolutePosition -= deltaLeft;
    }

    // copying the chunk
    memcpy(buffer->address + absolutePosition, chunk->address, (size_t) chunk->size);

    return true;
}

bool bufferReplace(Buffer* buffer, String* target, String* chunk)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferReplace"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferReplace"); }
    if (chunk->address == NULL)  { _errorAlreadyReleased("bufferReplace"); }

    long position = bufferIndexOf(buffer, target);

    return _bufferReplace(buffer, target, chunk, position);
}

bool bufferReplaceLast(Buffer* buffer, String* target, String* chunk)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferReplaceLast"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferReplaceLast"); }
    if (chunk->address == NULL)  { _errorAlreadyReleased("bufferReplaceLast"); }

    long position = bufferLastIndexOf(buffer, target);

    return _bufferReplace(buffer, target, chunk, position);
}

// replace target all /////////////////////////////////////////////////////////

bool bufferReplaceAll(Buffer* buffer, String* target, String* chunk)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferReplaceAll"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferReplaceAll"); }
    if (chunk->address == NULL)  { _errorAlreadyReleased("bufferReplaceAll"); }

    long count = bufferCountOf(buffer, target);

    if (count == 0) { return false; }

    if (target->size < chunk->size)
    {
        long neededSpace = count * (chunk->size - target->size);

        bufferMaybeExpandCapacity(buffer, neededSpace);
    }

     while (bufferReplace(buffer, target, chunk)) { }

     return true;
}


// file: buffer/remove.h //

void bufferRemove(Buffer* buffer, String* target)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferRemove"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferRemove"); }

    String empty = createEmptyString();

    bufferReplace(buffer, target, &empty);
}

void bufferRemoveLast(Buffer* buffer, String* target)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferRemoveLast"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferRemoveLast"); }

    String empty = createEmptyString();

    bufferReplaceLast(buffer, target, &empty);
}

void bufferRemoveAll(Buffer* buffer, String* target)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferRemoveAll"); }
    if (target->address == NULL) { _errorAlreadyReleased("bufferRemoveAll"); }

    String empty = createEmptyString();

    bufferReplaceAll(buffer, target, &empty);
}


// file: buffer/pad.h //

void bufferPadStart(Buffer* buffer, String* chunk, long count)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferPadStart"); }
    if (chunk->address == NULL)  { _errorAlreadyReleased("bufferPadStart"); }

    long padLength = count * chunk->size;

    if (padLength < 1) { return; }

    bufferMaybeExpandCapacity(buffer, padLength);

    if (buffer->margin >= padLength)
    {
        buffer->margin -= padLength;

        buffer->size += padLength;
    }
    else
    {
        long deltaRight = padLength - buffer->margin;

        long origin = buffer->margin + 1;

        long length = buffer->size;

        long destiny = origin + deltaRight;

        buffer->margin = 0;

        buffer->size += padLength;

        bufferMoveRange(buffer, origin, length, destiny);
    }

    for (long n = 0; n < count; n++)
    {
        long start = buffer->margin + (n * chunk->size);

        for (long index = 0; index < chunk->size; index++) { buffer->address[start + index] = chunk->address[index]; }
    }
}

void bufferPadEnd(Buffer* buffer, String* chunk, long count)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferPadEnd"); }
    if (chunk->address == NULL)  { _errorAlreadyReleased("bufferPadEnd"); }

    long padLength = count * chunk->size;

    if (padLength < 1) { return; }

    bufferMaybeExpandCapacity(buffer, padLength);

    long hiddenTail = buffer->capacity - buffer->margin - buffer->size;

    if (hiddenTail >= padLength)
    {
        buffer->size += padLength;
    }
    else
    {
        long length = buffer->size;

        long deltaLeft = padLength - hiddenTail;

        buffer->margin -= deltaLeft;

        buffer->size += deltaLeft; // temporary

        long origin = 1 + deltaLeft;

        long destiny = 1;

        bufferMoveRange(buffer, origin, length, destiny);

        buffer->size = length + padLength; // definitive
    }

    for (long n = 0; n < count; n++)
    {
        long start = buffer->margin + buffer->size - padLength + (n * chunk->size);

        for (long index = 0; index < chunk->size; index++) { buffer->address[start + index] = chunk->address[index]; }
    }
}


// file: buffer/reset-clear-fill.h //

void bufferReset(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferReset"); }

    buffer->margin = 0;

    buffer->size = buffer->capacity;
}

void bufferClear(Buffer* buffer)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferClear"); }

    for (long index = 0; index < buffer->size; index++)
    {
        buffer->address[buffer->margin + index] = 0;
    }
}

void bufferFill(Buffer* buffer, String* chunk)
{
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferFill"); }
    if (chunk->address == NULL) { _errorAlreadyReleased("bufferFill"); }

    if (chunk->size == 0) { return; } // necessary

    long bufferIndex = -1;

    while (true)
    {
        for (long chunkIndex = 0; chunkIndex < chunk->size; chunkIndex++)
        {
            bufferIndex += 1;

            if (bufferIndex == buffer->size) { return; }

            buffer->address[buffer->margin + bufferIndex] = chunk->address[chunkIndex];
        }
    }
}

//#include "array/array.h"

//#include "array-list/array-list.h"

//#include "linked-list/linked-list.h"

//#include "hashmap/hashmap-helper.h"
//#include "hashmap/hashmap-long.h"
//#include "hashmap/hashmap-string.h"



// file: file/read.h //

long cGetFileSize(char* filename)
{
    FILE* fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("\nERROR: while trying to read text file '%s': ", filename);
        printf("unknown file\n");
        fclose(fp);
        exit(1);
    }

    if (fseek(fp, 0, SEEK_END) < 0)
    {
        printf("\nERROR: while reading text file '%s': ", filename);
        printf("failed to read the entire file\n");
        fclose(fp);
        exit(1);
    }

    long size = ftell(fp);

    if (size < 0)
    {
        printf("\nERROR: while reading text file '%s': ", filename);
        printf("failed to read the entire file\n");
        fclose(fp);
        exit(1);
    }

    fclose(fp);
    return size;
}

// function cReadFile does NOT include extra byte for the NULL/terminator character
void cReadFile(char* filename, char* buffer, long fileSize)
{
    FILE* fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("\nERROR: while trying to read text file '%s': ", filename);
        printf("unknown file\n");
        fclose(fp);
        exit(1);
    }

    // Read the entire file into the buffer
    size_t bytesRead = fread(buffer, 1, (size_t) fileSize, fp);
    if (bytesRead != (size_t) fileSize)
    {
        printf("\nERROR: while reading text file '%s': ", filename);
        printf("failed to read the entire file\n");
        fclose(fp);
        exit(1);
    }

    fclose(fp);
}

///////////////////////////////////////////////////////////////////////////////

String readTextFile(String filename)
{
    if (filename.size == 0) {
        printf("\nERROR: cannot read text file: file name is blank\n");
        exit(1);
    }

    // c filename
    char* cFilename = malloc((size_t) filename.size + 1);
    memcpy(cFilename, filename.address, (size_t) filename.size);
    cFilename[filename.size] = 0;

    long fileSize = cGetFileSize(cFilename);

    char* buffer = _allocateHeap(fileSize);

    cReadFile(cFilename, buffer, fileSize);

    // checking if is good string
    for (long index = 0; index < fileSize; index++)
    {
        unsigned char c = (unsigned char) buffer[index];
        if (c > 31) { continue; }
        if (c == '\n') { continue; }
        if (c == '\r') { continue; }
        if (c == '\t') { continue; }

        printf("\nERROR: while reading text file '%s': ", cFilename);
        printf("found invalid character (code %d) at position %li\n", c, index);
        free(cFilename);
        exit(1);
    }

    free(cFilename);

    String string = _makeStructString(buffer, fileSize);

    return string;
}

