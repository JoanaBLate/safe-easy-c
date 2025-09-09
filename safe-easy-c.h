///////////////////////////////////////////////////////////////////////////////
///                             SafeEasyC Library                           ///
///                                                                         ///
///                     DO   **NOT**   EDIT   THIS   FILE!                  ///
///                                                                         ///
///                 https://github.com/JoanaBLate/safe-easy-c               ///
///////////////////////////////////////////////////////////////////////////////

// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



// file: types/types.h //

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



// file: memory/memory.h //

// pointer must be unsigned long, because must be able to access all RAM bytes

void* _allocateHeap(long size)
{
    if (size < 1) { return NULL; }

    unsigned long* address = malloc(size);

    if (address != NULL) { return address; }

    printf("\nERROR: failed to allocate %lu bytes in heap\n", size);

    exit(1);
}

void* _allocateHeapClean(long size)
{
    if (size < 1) { return NULL; }

    unsigned long* address = calloc(1, size);

    if (address != NULL) { return address; }

    printf("\nERROR: failed to allocate %lu bytes in heap\n", size);

    exit(1);
}

void* _reallocateHeap(void* address, long size)
{
    if (size < 1) { return NULL; }

    unsigned long* newAddress = realloc(address, size);

    if (newAddress != NULL) { return newAddress; }

    printf("\nERROR: failed to allocate %lu bytes in heap\n", size);

    exit(1);
}

void releaseHeap(void* voidStruct)
{
    AddressStruct* genericStruct = (AddressStruct*) voidStruct;

    if (genericStruct->address == FAKENULL) { return; }

    free(genericStruct->address); // no problem to free(NULL)

    genericStruct->address = NULL;
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



// file: string/info.h //

long getStringSize(String* string)
{
    return string->size;
}

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

    memcpy(buffer, sourceAddress, bufferSize);

    return _makeStructString(buffer, bufferSize);
}

String createStringFromLiteral(char* cString) // argument not checked
{
    long size = strlen(cString);

    return _createStringFromInfo(cString, size);
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

    long size = strlen(array);

    return _createStringFromInfo(array, size);
}


// file: string/repeat.h //

String createStringRepeat(String string, long count)
{
    if (string.size == 0) { return createEmptyString(); }

    if (count <= 0) { return createEmptyString(); }

    long bufferSize = count * string.size;

    char* buffer = _allocateHeap(bufferSize);

    for (long turn = 0; turn < count; turn++)
    {
        memcpy(&buffer[turn * string.size], string.address, string.size);
    }

    return _makeStructString(buffer, bufferSize);
}


// file: string/append-insert.h //

String createStringAppend(String* string, String* chunk)
{
    if (string->size == 0) { return createStringClone(chunk); }

    if (chunk->size == 0)  { return createStringClone(string); }

    long bufferSize = string->size + chunk->size;

    char* buffer = _allocateHeap(bufferSize);

    memcpy(buffer, string->address, string->size);

    memcpy(&buffer[string->size], chunk->address, chunk->size);

    return _makeStructString(buffer, bufferSize);
}

String createStringInsert(String* string, String* chunk, long position)
{
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
    return createSubstring(string, 0, count);
}

String createSubstringEnd(String* string, long count)
{
    if (count < 1) { return createEmptyString(); }

    long start = string->size - count;

    return createSubstring(string, start, count);
}


// file: string/lower-reverse-sort.h //

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


// file: string/pad.h //

String createStringPadStart(String* string, String* chunk, long count)
{
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

    memcpy(&buffer[index + 1], string->address, string->size);

    return _makeStructString(buffer, bufferSize);
}

String createStringPadEnd(String* string, String* chunk, long count)
{
    if (count < 1) { return createStringClone(string); }

    if (chunk->size == 0) { return createStringClone(string); }

    long bufferSize = (count * chunk->size) + string->size;

    char* buffer = _allocateHeap(bufferSize);

    memcpy(buffer, string->address, string->size);

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


// file: string/print.h //

void printStringBytes(String* string)
{
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
    printStringBytes(string);

    printf("\n");
}

void printStringChars(String* string)
{
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
    printStringChars(string);

    printf("\n");
}

void printString(String* string)
{
    char substitute = 26;

    char token[5];

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

        token[1] = string->address[index];

        // 2-byte sequence
        if ((c & 0xE0) == 0xC0) { token[2] = 0; printf("%s", token); continue; }

        index += 1;
        if (index == string->size) { putchar(substitute); index -= 2; continue; } // corrupted data

        token[2] = string->address[index];

        // 3-byte sequence
        if ((c & 0xF0) == 0xE0) { token[3] = 0; printf("%s", token); continue; }

        index += 1;
        if (index == string->size) { putchar(substitute); index -= 3; continue; } // corrupted data

        token[3] = string->address[index];

        // 4-byte sequence
        if ((c & 0xF8) == 0xF0) { token[4] = 0; printf("%s", token); continue; }

        // not encoded:

        putchar(substitute);
        index -= 3;
    }
}

void printlnString(String* string)
{
    printString(string);

    printf("\n");
}


// file: string/replace.h //

// replace by position ////////////////////////////////////////////////////////

String createStringReplaceStart(String* string, long count, String* chunk)
{
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
    long position = stringIndexOf(string, target);

    if (position == -1) { return createStringClone(string); } // target not found

    if (position == 0) { return createStringReplaceStart(string, target->size, chunk); }

    if (position + target->size == string->size) { return createStringReplaceEnd(string, target->size, chunk); }

    return _createStringReplace(string, target, chunk, position);
}

String createStringReplaceLast(String* string, String* target, String* chunk)
{
    long position = stringLastIndexOf(string, target);

    if (position == -1) { return createStringClone(string); } // target not found

    if (position == 0) { return createStringReplaceStart(string, target->size, chunk); }

    if (position + target->size == string->size) { return createStringReplaceEnd(string, target->size, chunk); }

    return _createStringReplace(string, target, chunk, position);
}

// replace all by target //////////////////////////////////////////////////////

String createStringReplaceAll(String* string, String* target, String* chunk)
{
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
    String empty = createEmptyString();

    return createStringReplace(string, target, &empty);
}

String createStringRemoveLast(String* string, String* target)
{
    String empty = createEmptyString();

    return createStringReplaceLast(string, target, &empty);
}

String createStringRemoveAll(String* string, String* target)
{
    String empty = createEmptyString();

    return createStringReplaceAll(string, target, &empty);
}


// file: string/trim.h //

String stringTrimStart(String* string)
{
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

//#include "buffer/info.h"
//#include "buffer/print.h"
//#include "buffer/create-from-release.h"
//#include "buffer/expand.h"
//#include "buffer/move-range.h"
//#include "buffer/copy-range.h"
//#include "buffer/lower-reverse-sort.h"
//#include "buffer/trim.h"
//#include "buffer/eat-start-end.h"
//#include "buffer/replace-start-end.h"
//#include "buffer/replace-target-all.h"
//#include "buffer/remove.h"
//#include "buffer/pad.h"
//#include "buffer/reset-clear-fill.h"

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
    long bytesRead = fread(buffer, 1, fileSize, fp);
    if (bytesRead != fileSize)
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
    char* cFilename = malloc(filename.size + 1);
    memcpy(cFilename, filename.address, filename.size);
    cFilename[filename.size] = 0;

    long fileSize = cGetFileSize(cFilename);

    char* buffer = _allocateHeap(fileSize);

    cReadFile(cFilename, buffer, fileSize);

    // checking if is good string
    for (long index = 0; index < fileSize; index++)
    {
        unsigned char c = buffer[index];
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

