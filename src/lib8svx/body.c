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

#include "body.h"
#include <rawchunk.h>
#include <util.h>

#define CHUNKID "BODY"

_8SVX_Body *_8SVX_createBody(void)
{
    return (_8SVX_Body*)IFF_allocateChunk(CHUNKID, sizeof(_8SVX_Body));
}

IFF_Chunk *_8SVX_readBody(FILE *file, const IFF_Long chunkSize)
{
    return (IFF_Chunk*)IFF_readRawChunk(file, CHUNKID, chunkSize);
}

int _8SVX_writeBody(FILE *file, const IFF_Chunk *chunk)
{
    return IFF_writeRawChunk(file, (IFF_RawChunk*)chunk);
}

int _8SVX_checkBody(const IFF_Chunk *chunk)
{
    return TRUE;
}

void _8SVX_freeBody(IFF_Chunk *chunk)
{
    IFF_freeRawChunk((IFF_RawChunk*)chunk);
}

void _8SVX_printBody(const IFF_Chunk *chunk, const unsigned int indentLevel)
{
    _8SVX_Body *body = (_8SVX_Body*)chunk;
    unsigned int i;
    IFF_Byte byte;
	
    IFF_printIndent(stdout, indentLevel, "values = \n");
    IFF_printIndent(stdout, indentLevel + 1, "");
	
    for(i = 0; i < body->chunkSize; i++)
    {
	if(i > 0 && i % 10 == 0)
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
