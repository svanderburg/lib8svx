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

#ifndef __8SVX_NAME_H
#define __8SVX_NAME_H

#include <stdio.h>
#include <libiff/chunk.h>
#include <libiff/rawchunk.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef IFF_RawChunk _8SVX_Name;

_8SVX_Name *_8SVX_createName(void);

IFF_Chunk *_8SVX_readName(FILE *file, const IFF_Long chunkSize);

IFF_Bool _8SVX_writeName(FILE *file, const IFF_Chunk *chunk);

IFF_Bool _8SVX_checkName(const IFF_Chunk *chunk);

void _8SVX_freeName(IFF_Chunk *chunk);

void _8SVX_printName(const IFF_Chunk *chunk, const unsigned int indentLevel);

IFF_Bool _8SVX_compareName(const IFF_Chunk *chunk1, const IFF_Chunk *chunk2);

#ifdef __cplusplus
}
#endif

#endif
