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

#include "body.h"
#include <libiff/rawchunk.h>
#include <libiff/util.h>

IFF_Chunk *_8SVX_createBodyChunk(const IFF_ID chunkId, const IFF_Long chunkSize)
{
    return IFF_createRawChunk(chunkId, chunkSize);
}

_8SVX_Body *_8SVX_createBody(const IFF_Long chunkSize)
{
    return (_8SVX_Body*)_8SVX_createBodyChunk(_8SVX_ID_BODY, chunkSize);
}

IFF_Bool _8SVX_readBody(FILE *file, IFF_Chunk *chunk, const IFF_ChunkRegistry *chunkRegistry, IFF_Long *bytesProcessed)
{
    return IFF_readRawChunk(file, chunk, chunkRegistry, bytesProcessed);
}

IFF_Bool _8SVX_writeBody(FILE *file, const IFF_Chunk *chunk, const IFF_ChunkRegistry *chunkRegistry, IFF_Long *bytesProcessed)
{
    return IFF_writeRawChunk(file, chunk, chunkRegistry, bytesProcessed);
}

IFF_Bool _8SVX_checkBody(const IFF_Chunk *chunk, const IFF_ChunkRegistry *chunkRegistry)
{
    return TRUE;
}

void _8SVX_freeBody(IFF_Chunk *chunk, const IFF_ChunkRegistry *chunkRegistry)
{
    IFF_freeRawChunk(chunk, chunkRegistry);
}

void _8SVX_printBody(const IFF_Chunk *chunk, const unsigned int indentLevel, const IFF_ChunkRegistry *chunkRegistry)
{
    _8SVX_Body *body = (_8SVX_Body*)chunk;
    IFF_Long i;
    IFF_Byte byte;

    IFF_printIndent(stdout, indentLevel, "values = \n");
    IFF_printIndent(stdout, indentLevel + 1, "");

    for(i = 0; i < body->chunkSize; i++)
    {
        if((i > 0) && (i % 10) == 0)
        {
            printf("\n");
            IFF_printIndent(stdout, indentLevel + 1, "");
        }

        byte = body->chunkData[i];

        printf("%d ", byte);
    }

    printf("\n");
    IFF_printIndent(stdout, indentLevel, ";\n");
}

IFF_Bool _8SVX_compareBody(const IFF_Chunk *chunk1, const IFF_Chunk *chunk2, const IFF_ChunkRegistry *chunkRegistry)
{
    return IFF_compareRawChunk(chunk1, chunk2, chunkRegistry);
}
