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

#include "playbackenvelope.h"

_8SVX_PlaybackEnvelope *_8SVX_createPlaybackEnvelope()
{
    return (_8SVX_PlaybackEnvelope*)_8SVX_createPLEnvelope(_8SVX_ID_RLSE);
}

_8SVX_EGPoint *_8SVX_addToPlaybackEnvelope(_8SVX_PlaybackEnvelope *playbackEnvelope)
{
    return _8SVX_addToPLEnvelope((_8SVX_PLEnvelope*)playbackEnvelope);
}

IFF_Chunk *_8SVX_readPlaybackEnvelope(FILE *file, const IFF_Long chunkSize)
{
    return _8SVX_readPLEnvelope(file, chunkSize, _8SVX_ID_RLSE);
}

IFF_Bool _8SVX_writePlaybackEnvelope(FILE *file, const IFF_Chunk *chunk)
{
    return _8SVX_writePLEnvelope(file, chunk);
}

IFF_Bool _8SVX_checkPlaybackEnvelope(const IFF_Chunk *chunk)
{
    return _8SVX_checkPLEnvelope(chunk);
}

void _8SVX_freePlaybackEnvelope(IFF_Chunk *chunk)
{
    _8SVX_freePLEnvelope(chunk);
}

void _8SVX_printPlaybackEnvelope(const IFF_Chunk *chunk, const unsigned int indentLevel)
{
    _8SVX_printPLEnvelope(chunk, indentLevel);
}

IFF_Bool _8SVX_comparePlaybackEnvelope(const IFF_Chunk *chunk1, const IFF_Chunk *chunk2)
{
    return _8SVX_comparePLEnvelope(chunk1, chunk2);
}
