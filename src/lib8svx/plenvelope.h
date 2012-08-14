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

#ifndef __8SVX_PLENVELOPE_H
#define __8SVX_PLENVELOPE_H

#include <stdio.h>
#include <libiff/ifftypes.h>
#include <libiff/group.h>
#include <libiff/chunk.h>

typedef struct
{
    IFF_UWord duration;
    IFF_Long dest;
}
_8SVX_EGPoint;

typedef struct
{
    IFF_Group *parent;
    
    IFF_ID chunkId;
    IFF_Long chunkSize;
    
    unsigned int egPointLength;
    _8SVX_EGPoint *egPoint;
}
_8SVX_PLEnvelope;

_8SVX_PLEnvelope *_8SVX_createPLEnvelope(const char *chunkId);

_8SVX_EGPoint *_8SVX_addToPLEnvelope(_8SVX_PLEnvelope *plEnvelope);

IFF_Chunk *_8SVX_readPLEnvelope(FILE *file, const IFF_Long chunkSize, const char *chunkId);

int _8SVX_writePLEnvelope(FILE *file, const IFF_Chunk *chunk);

int _8SVX_checkPLEnvelope(const IFF_Chunk *chunk);

void _8SVX_freePLEnvelope(IFF_Chunk *chunk);

void _8SVX_printPLEnvelope(const IFF_Chunk *chunk, const unsigned int indentLevel);

int _8SVX_comparePLEnvelope(const IFF_Chunk *chunk1, const IFF_Chunk *chunk2);

#endif
