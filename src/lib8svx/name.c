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

#include "name.h"

_8SVX_Name *_8SVX_createName(void)
{
    return (_8SVX_Name*)IFF_createRawChunk(_8SVX_ID_NAME);
}

IFF_Chunk *_8SVX_readName(FILE *file, const IFF_Long chunkSize)
{
    return (IFF_Chunk*)IFF_readRawChunk(file, _8SVX_ID_NAME, chunkSize);
}

IFF_Bool _8SVX_writeName(FILE *file, const IFF_Chunk *chunk)
{
    return IFF_writeRawChunk(file, (const IFF_RawChunk*)chunk);
}

IFF_Bool _8SVX_checkName(const IFF_Chunk *chunk)
{
    return TRUE;
}

void _8SVX_freeName(IFF_Chunk *chunk)
{
    IFF_freeRawChunk((IFF_RawChunk*)chunk);
}

void _8SVX_printName(const IFF_Chunk *chunk, const unsigned int indentLevel)
{
    IFF_printText((const IFF_RawChunk*)chunk, indentLevel);
}

IFF_Bool _8SVX_compareName(const IFF_Chunk *chunk1, const IFF_Chunk *chunk2)
{
    return IFF_compareRawChunk((const IFF_RawChunk*)chunk1, (const IFF_RawChunk*)chunk2);
}
