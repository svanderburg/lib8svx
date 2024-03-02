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

#include "volumecontrol.h"

IFF_Chunk *_8SVX_createVolumeControlChunk(const IFF_ID chunkId, const IFF_Long chunkSize)
{
    return _8SVX_createPLEnvelope(chunkId, chunkSize);
}

_8SVX_VolumeControl *_8SVX_createVolumeControl(void)
{
    return (_8SVX_VolumeControl*)_8SVX_createVolumeControlChunk(_8SVX_ID_ATAK, _8SVX_ATAK_DEFAULT_SIZE);
}

_8SVX_EGPoint *_8SVX_addToVolumeControl(_8SVX_VolumeControl *volumeControl)
{
    return _8SVX_addToPLEnvelope((_8SVX_PLEnvelope*)volumeControl);
}

IFF_Bool _8SVX_readVolumeControl(FILE *file, IFF_Chunk *chunk, const IFF_ChunkRegistry *chunkRegistry, IFF_Long *bytesProcessed)
{
    return _8SVX_readPLEnvelope(file, chunk, chunkRegistry, bytesProcessed);
}

IFF_Bool _8SVX_writeVolumeControl(FILE *file, const IFF_Chunk *chunk, const IFF_ChunkRegistry *chunkRegistry, IFF_Long *bytesProcessed)
{
    return _8SVX_writePLEnvelope(file, chunk, chunkRegistry, bytesProcessed);
}

IFF_Bool _8SVX_checkVolumeControl(const IFF_Chunk *chunk, const IFF_ChunkRegistry *chunkRegistry)
{
    return _8SVX_checkPLEnvelope(chunk, chunkRegistry);
}

void _8SVX_freeVolumeControl(IFF_Chunk *chunk, const IFF_ChunkRegistry *chunkRegistry)
{
    _8SVX_freePLEnvelope(chunk, chunkRegistry);
}

void _8SVX_printVolumeControl(const IFF_Chunk *chunk, const unsigned int indentLevel, const IFF_ChunkRegistry *chunkRegistry)
{
    _8SVX_printPLEnvelope(chunk, indentLevel, chunkRegistry);
}

IFF_Bool _8SVX_compareVolumeControl(const IFF_Chunk *chunk1, const IFF_Chunk *chunk2, const IFF_ChunkRegistry *chunkRegistry)
{
    return _8SVX_comparePLEnvelope(chunk1, chunk2, chunkRegistry);
}
