// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

// doesn't allocate memory
// allows buffer to use String functions
String _makePseudoStringFromBuffer(Buffer* buffer)
{        
    return _makeStructString(buffer->address + buffer->margin, buffer->size);
}

