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

#define CHUNKID "ATAK"

_8SVX_VolumeControl *_8SVX_createVolumeControl()
{
    return (_8SVX_VolumeControl*)_8SVX_createPLEnvelope(CHUNKID);
}

_8SVX_EGPoint *_8SVX_addToVolumeControl(_8SVX_VolumeControl *volumeControl)
{
    return _8SVX_addToVolumeControl((_8SVX_PLEnvelope*)volumeControl);
}

IFF_Chunk *_8SVX_readVolumeControl(FILE *file, const IFF_Long chunkSize)
{
    return _8SVX_readPLEnvelope(file, chunkSize, CHUNKID);
}

int _8SVX_writeVolumeControl(FILE *file, const IFF_Chunk *chunk)
{
    return _8SVX_writePLEnvelope(file, chunk);
}

int _8SVX_checkVolumeControl(const IFF_Chunk *chunk)
{
    return _8SVX_checkPLEnvelope(chunk);
}

void _8SVX_freeVolumeControl(IFF_Chunk *chunk)
{
    _8SVX_freePLEnvelope(chunk);
}

void _8SVX_printVolumeControl(const IFF_Chunk *chunk, const unsigned int indentLevel)
{
    _8SVX_printPLEnvelope(chunk, indentLevel);
}

int _8SVX_compareVolumeControl(const IFF_Chunk *chunk1, const IFF_Chunk *chunk2)
{
    return _8SVX_comparePLEnvelope(chunk1, chunk2);
}
