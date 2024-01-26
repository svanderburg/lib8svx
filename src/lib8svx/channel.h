/*
 * Copyright (c) 2019 C.W. Betts
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

#ifndef __8SVX_CHAN_H
#define __8SVX_CHAN_H

#include <stdio.h>
#include <libiff/ifftypes.h>
#include <libiff/group.h>
#include <libiff/chunk.h>

#ifdef __cplusplus
extern "C" {
#endif

// IFF_Long
typedef enum
{
    _8SVX_CHANNEL_RIGHT = 4,
    _8SVX_CHANNEL_LEFT = 2,
    _8SVX_CHANNEL_STEREO = 6
}
_8SVX_SoundChannel;


typedef struct
{
    IFF_Group *parent;

    IFF_ID chunkId;
    IFF_Long chunkSize;

    _8SVX_SoundChannel playbackChannel;
}
_8SVX_Channel;

_8SVX_Channel *_8SVX_createChannel(void);

IFF_Chunk *_8SVX_readChannel(FILE *file, const IFF_Long chunkSize);

int _8SVX_writeChannel(FILE *file, const IFF_Chunk *chunk);

int _8SVX_checkChannel(const IFF_Chunk *chunk);

void _8SVX_freeChannel(IFF_Chunk *chunk);

void _8SVX_printChannel(const IFF_Chunk *chunk, const unsigned int indentLevel);

int _8SVX_compareChannel(const IFF_Chunk *chunk1, const IFF_Chunk *chunk2);

#ifdef __cplusplus
}
#endif

#endif
