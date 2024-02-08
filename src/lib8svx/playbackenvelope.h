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

#ifndef __8SVX_PLAYBACK_ENVELOPE
#define __8SVX_PLAYBACK_ENVELOPE

#include "plenvelope.h"
#include <libiff/id.h>

#define _8SVX_ID_RLSE IFF_MAKEID('R', 'L', 'S', 'E')

#define _8SVX_RLSE_DEFAULT_SIZE 0

#ifdef __cplusplus
extern "C" {
#endif

typedef _8SVX_PLEnvelope _8SVX_PlaybackEnvelope;

IFF_Chunk *_8SVX_createPlaybackEnvelope(const IFF_Long chunkSize);

_8SVX_EGPoint *_8SVX_addToPlaybackEnvelope(_8SVX_PlaybackEnvelope *playbackEnvelope);

IFF_Bool _8SVX_readPlaybackEnvelope(FILE *file, IFF_Chunk *chunk, IFF_Long *bytesProcessed);

IFF_Bool _8SVX_writePlaybackEnvelope(FILE *file, const IFF_Chunk *chunk, IFF_Long *bytesProcessed);

IFF_Bool _8SVX_checkPlaybackEnvelope(const IFF_Chunk *chunk);

void _8SVX_freePlaybackEnvelope(IFF_Chunk *chunk);

void _8SVX_printPlaybackEnvelope(const IFF_Chunk *chunk, const unsigned int indentLevel);

IFF_Bool _8SVX_comparePlaybackEnvelope(const IFF_Chunk *chunk1, const IFF_Chunk *chunk2);

#ifdef __cplusplus
}
#endif

#endif
