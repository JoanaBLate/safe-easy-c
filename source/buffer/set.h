// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

//long bufferSetMargin(Buffer* buffer) // must change the size too!!!
//{        
//    if (buffer->address == NULL) { _errorAlreadyReleased("bufferSetMargin"); }
//
//    return buffer->margin;
//}
//
//long bufferSetSize(Buffer* buffer)
//{        
//    if (buffer->address == NULL) { _errorAlreadyReleased("bufferSetSize"); }
//
//    return buffer->size;
//}
//

bool bufferSetByte(Buffer* buffer, long index, char byte)
{ 
    if (buffer->address == NULL) { _errorAlreadyReleased("bufferSetByte"); }

    if (index < 0  ||  index >= buffer->size) { return false; } // out of bounds

    buffer->address[buffer->margin + index] = byte;
    
    return true;
}

