// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

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

String readTextFile(String* filename)
{
    if (filename->size == 0) {    
        printf("\nERROR: cannot read text file: file name is blank\n");
        exit(1);     
    }

    // c filename
    char* cFilename = malloc((size_t) filename->size + 1);
    memcpy(cFilename, filename->address, (size_t) filename->size);
    cFilename[filename->size] = 0;
    
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

