/*
 * Copyright (c) 2012 Sander van der Burg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "copyright.h"

IFF_Chunk *_8SVX_createCopyrightChunk(const IFF_ID chunkId, const IFF_Long chunkSize)
{
    return IFF_createRawChunk(_8SVX_ID_C, chunkSize);
}

_8SVX_Copyright *_8SVX_createCopyright(const IFF_Long chunkSize)
{
    return (_8SVX_Copyright*)_8SVX_createCopyrightChunk(_8SVX_ID_C, chunkSize);
}

IFF_Bool _8SVX_readCopyright(FILE *file, IFF_Chunk *chunk, const IFF_ChunkRegistry *chunkRegistry, IFF_Long *bytesProcessed)
{
    return IFF_readRawChunk(file, chunk, chunkRegistry, bytesProcessed);
}

IFF_Bool _8SVX_writeCopyright(FILE *file, const IFF_Chunk *chunk, const IFF_ChunkRegistry *chunkRegistry, IFF_Long *bytesProcessed)
{
    return IFF_writeRawChunk(file, chunk, chunkRegistry, bytesProcessed);
}

IFF_Bool _8SVX_checkCopyright(const IFF_Chunk *chunk, const IFF_ChunkRegistry *chunkRegistry)
{
    return TRUE;
}

void _8SVX_freeCopyright(IFF_Chunk *chunk, const IFF_ChunkRegistry *chunkRegistry)
{
    IFF_freeRawChunk(chunk, chunkRegistry);
}

void _8SVX_printCopyright(const IFF_Chunk *chunk, const unsigned int indentLevel, const IFF_ChunkRegistry *chunkRegistry)
{
    IFF_printText((IFF_RawChunk*)chunk, indentLevel);
}

IFF_Bool _8SVX_compareCopyright(const IFF_Chunk *chunk1, const IFF_Chunk *chunk2, const IFF_ChunkRegistry *chunkRegistry)
{
    return IFF_compareRawChunk(chunk1, chunk2, chunkRegistry);
}
