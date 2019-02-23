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

#include "channel.h"
#include <libiff/chunk.h>
#include <libiff/rawchunk.h>
#include <libiff/io.h>
#include <libiff/util.h>
#include <libiff/error.h>
#include "8svx.h"

#define CHUNKID "CHAN"

_8SVX_Channel *_8SVX_createChannel(void)
{
    _8SVX_Channel* newVal =(_8SVX_Channel*)IFF_allocateChunk(CHUNKID, sizeof(_8SVX_Channel));
    if (newVal != NULL)
    {
        newVal->chunkSize = sizeof(IFF_Long);
    }
    return newVal;
}

IFF_Chunk *_8SVX_readChannel(FILE *file, const IFF_Long chunkSize)
{
    _8SVX_Channel *channel = _8SVX_createChannel();
    if (channel != NULL)
    {
        IFF_Long tmpChannel;
        if(!IFF_readLong(file, &tmpChannel, CHUNKID, "playbackChannel"))
        {
            _8SVX_free((IFF_Chunk*)channel);
            return NULL;
        }
        channel->playbackChannel = tmpChannel;
    }
    return (IFF_Chunk*)channel;
}

int _8SVX_writeChannel(FILE *file, const IFF_Chunk *chunk)
{
    const _8SVX_Channel *channel = (const _8SVX_Channel *)chunk;
    if(!IFF_writeLong(file, channel->playbackChannel, CHUNKID, "playbackChannel"))
    return FALSE;

    return TRUE;
}

int _8SVX_checkChannel(const IFF_Chunk *chunk)
{
    const _8SVX_Channel *channel = (const _8SVX_Channel *)chunk;
    
    if (channel->playbackChannel != _8SVX_CHANNEL_RIGHT &&
        channel->playbackChannel != _8SVX_CHANNEL_LEFT &&
        channel->playbackChannel != _8SVX_CHANNEL_STEREO)
    {
        IFF_error("Unsupported 'CHAN'.playbackChannel value: %u\n", channel->playbackChannel);
        return FALSE;
    }

    return TRUE;
}

void _8SVX_freeChannel(IFF_Chunk *chunk)
{

}

void _8SVX_printChannel(const IFF_Chunk *chunk, const unsigned int indentLevel)
{
    const _8SVX_Channel *channel = (const _8SVX_Channel *)chunk;

    IFF_printIndent(stdout, indentLevel, "playbackChannel = %d;\n", channel->playbackChannel);
}

int _8SVX_compareChannel(const IFF_Chunk *chunk1, const IFF_Chunk *chunk2)
{
    const _8SVX_Channel *channel1 = (const _8SVX_Channel *)chunk1;
    const _8SVX_Channel *channel2 = (const _8SVX_Channel *)chunk2;

    if(channel1->playbackChannel != channel2->playbackChannel)
    return FALSE;

    return TRUE;
}
