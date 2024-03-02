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

#ifndef __8SVX_VOICE8HEADER_H
#define __8SVX_VOICE8HEADER_H

#include <stdio.h>
#include <libiff/ifftypes.h>
#include <libiff/group.h>
#include <libiff/chunk.h>
#include <libiff/id.h>

#define _8SVX_MAX_VOLUME 0x10000

#define _8SVX_ID_VHDR IFF_MAKEID('V', 'H', 'D', 'R')

#define _8SVX_VHDR_DEFAULT_SIZE (3 * sizeof(IFF_ULong) + sizeof(IFF_UWord) + sizeof(IFF_UByte) + sizeof(IFF_UByte) + sizeof(IFF_Long))

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    _8SVX_CMP_NONE = 0,
    _8SVX_CMP_FIBDELTA = 1
}
_8SVX_Compression;

typedef struct
{
    IFF_Group *parent;

    IFF_ID chunkId;
    IFF_Long chunkSize;

    IFF_ULong oneShotHiSamples, repeatHiSamples, samplesPerHiCycle;
    IFF_UWord samplesPerSec;
    IFF_UByte ctOctave;
    IFF_UByte sCompression;
    IFF_Long volume;
}
_8SVX_Voice8Header;

IFF_Chunk *_8SVX_createVoice8HeaderChunk(const IFF_ID chunkId, const IFF_Long chunkSize);

_8SVX_Voice8Header *_8SVX_createVoice8Header(void);

IFF_Bool _8SVX_readVoice8Header(FILE *file, IFF_Chunk *chunk, const IFF_ChunkRegistry *chunkRegistry, IFF_Long *bytesProcessed);

IFF_Bool _8SVX_writeVoice8Header(FILE *file, const IFF_Chunk *chunk, const IFF_ChunkRegistry *chunkRegistry, IFF_Long *bytesProcessed);

IFF_Bool _8SVX_checkVoice8Header(const IFF_Chunk *chunk, const IFF_ChunkRegistry *chunkRegistry);

void _8SVX_freeVoice8Header(IFF_Chunk *chunk, const IFF_ChunkRegistry *chunkRegistry);

void _8SVX_printVoice8Header(const IFF_Chunk *chunk, const unsigned int indentLevel, const IFF_ChunkRegistry *chunkRegistry);

IFF_Bool _8SVX_compareVoice8Header(const IFF_Chunk *chunk1, const IFF_Chunk *chunk2, const IFF_ChunkRegistry *chunkRegistry);

#ifdef __cplusplus
}
#endif

#endif
