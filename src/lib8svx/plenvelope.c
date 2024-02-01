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

#include "plenvelope.h"
#include <stdlib.h>
#include <libiff/io.h>
#include <libiff/util.h>
#include "8svx.h"

_8SVX_PLEnvelope *_8SVX_createPLEnvelope(const IFF_ID chunkId)
{
    _8SVX_PLEnvelope *plEnvelope = (_8SVX_PLEnvelope*)IFF_allocateChunk(chunkId, sizeof(_8SVX_PLEnvelope));

    if(plEnvelope != NULL)
    {
        plEnvelope->egPointLength = 0;
        plEnvelope->egPoint = NULL;
    }

    return plEnvelope;
}

_8SVX_EGPoint *_8SVX_addToPLEnvelope(_8SVX_PLEnvelope *plEnvelope)
{
    _8SVX_EGPoint *egPoint;

    plEnvelope->egPoint = (_8SVX_EGPoint*)realloc(plEnvelope->egPoint, (plEnvelope->egPointLength + 1) * sizeof(_8SVX_EGPoint));
    egPoint = &plEnvelope->egPoint[plEnvelope->egPointLength];
    plEnvelope->egPointLength++;
    plEnvelope->chunkSize += sizeof(IFF_UWord) + sizeof(IFF_Long);

    return egPoint;
}

IFF_Chunk *_8SVX_readPLEnvelope(FILE *file, const IFF_Long chunkSize, const IFF_ID chunkId)
{
    _8SVX_PLEnvelope *plEnvelope = _8SVX_createPLEnvelope(chunkId);

    if(plEnvelope != NULL)
    {
        while(plEnvelope->chunkSize < chunkSize)
        {
            _8SVX_EGPoint *egPoint = _8SVX_addToPLEnvelope(plEnvelope);

            if(!IFF_readUWord(file, &egPoint->duration, chunkId, "duration"))
            {
                free(egPoint);
                _8SVX_free((IFF_Chunk*)plEnvelope);
            }

            if(!IFF_readLong(file, &egPoint->dest, chunkId, "dest"))
            {
                free(egPoint);
                _8SVX_free((IFF_Chunk*)plEnvelope);
            }
        }
    }

    return (IFF_Chunk*)plEnvelope;
}

IFF_Bool _8SVX_writePLEnvelope(FILE *file, const IFF_Chunk *chunk)
{
    const _8SVX_PLEnvelope *plEnvelope = (const _8SVX_PLEnvelope*)chunk;
    unsigned int i;

    for(i = 0; i < plEnvelope->egPointLength; i++)
    {
        _8SVX_EGPoint *egPoint = &plEnvelope->egPoint[i];

        if(!IFF_writeUWord(file, egPoint->duration, plEnvelope->chunkId, "duration"))
            return FALSE;

        if(!IFF_writeLong(file, egPoint->dest, plEnvelope->chunkId, "dest"))
            return FALSE;
    }

    return TRUE;
}

IFF_Bool _8SVX_checkPLEnvelope(const IFF_Chunk *chunk)
{
    return TRUE;
}

void _8SVX_freePLEnvelope(IFF_Chunk *chunk)
{
}

void _8SVX_printPLEnvelope(const IFF_Chunk *chunk, const unsigned int indentLevel)
{
    const _8SVX_PLEnvelope *plEnvelope = (const _8SVX_PLEnvelope*)chunk;
    unsigned int i;

    for(i = 0; i < plEnvelope->egPointLength; i++)
    {
        _8SVX_EGPoint *egPoint = &plEnvelope->egPoint[i];
        IFF_printIndent(stdout, indentLevel, "{ duration = %u, dest = %d }\n", egPoint->duration, egPoint->dest);
    }
}

IFF_Bool _8SVX_comparePLEnvelope(const IFF_Chunk *chunk1, const IFF_Chunk *chunk2)
{
    const _8SVX_PLEnvelope *plEnvelope1 = (const _8SVX_PLEnvelope*)chunk1;
    const _8SVX_PLEnvelope *plEnvelope2 = (const _8SVX_PLEnvelope*)chunk2;

    if(plEnvelope1->egPointLength == plEnvelope2->egPointLength)
    {
        unsigned int i;

        for(i = 0; i < plEnvelope1->egPointLength; i++)
        {
            _8SVX_EGPoint *egPoint1 = &plEnvelope1->egPoint[i];
            _8SVX_EGPoint *egPoint2 = &plEnvelope2->egPoint[i];

            if(egPoint1->duration != egPoint2->duration)
                return FALSE;

            if(egPoint1->dest != egPoint2->dest)
                return FALSE;
        }
    }
    else
        return FALSE;

    return TRUE;
}
