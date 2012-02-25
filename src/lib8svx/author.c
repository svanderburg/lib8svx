/**
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

#include "author.h"

#define CHUNKID "AUTH"

_8SVX_Author *_8SVX_createAuthor(void)
{
    return (_8SVX_Author*)IFF_createRawChunk(CHUNKID);
}

IFF_Chunk *_8SVX_readAuthor(FILE *file, const IFF_Long chunkSize)
{
    return (IFF_Chunk*)IFF_readRawChunk(file, CHUNKID, chunkSize);
}

int _8SVX_writeAuthor(FILE *file, const IFF_Chunk *chunk)
{
    return IFF_writeRawChunk(file, (IFF_RawChunk*)chunk);
}

int _8SVX_checkAuthor(const IFF_Chunk *chunk)
{
    return TRUE;
}

void _8SVX_freeAuthor(IFF_Chunk *chunk)
{
    IFF_freeRawChunk((IFF_RawChunk*)chunk);
}

void _8SVX_printAuthor(const IFF_Chunk *chunk, const unsigned int indentLevel)
{
    IFF_printText((IFF_RawChunk*)chunk, indentLevel);
}
