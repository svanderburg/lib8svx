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
#include <libiff/field.h>
#include <libiff/io.h>
#include <libiff/util.h>
#include "8svx.h"

IFF_Chunk *_8SVX_createPLEnvelope(const IFF_ID chunkId, const IFF_Long chunkSize)
{
    _8SVX_PLEnvelope *plEnvelope = (_8SVX_PLEnvelope*)IFF_createChunk(chunkId, chunkSize, sizeof(_8SVX_PLEnvelope));

    if(plEnvelope != NULL)
    {
        plEnvelope->egPointLength = 0;
        plEnvelope->egPoint = NULL;
    }

    return (IFF_Chunk*)plEnvelope;
}

static _8SVX_EGPoint *allocatePointInPLEnvelope(_8SVX_PLEnvelope *plEnvelope)
{
    _8SVX_EGPoint *egPoint;

    plEnvelope->egPoint = (_8SVX_EGPoint*)realloc(plEnvelope->egPoint, (plEnvelope->egPointLength + 1) * sizeof(_8SVX_EGPoint));
    egPoint = &plEnvelope->egPoint[plEnvelope->egPointLength];
    plEnvelope->egPointLength++;

    return egPoint;
}

_8SVX_EGPoint *_8SVX_addToPLEnvelope(_8SVX_PLEnvelope *plEnvelope)
{
    _8SVX_EGPoint *egPoint = allocatePointInPLEnvelope(plEnvelope);
    plEnvelope->chunkSize += sizeof(IFF_UWord) + sizeof(IFF_Long);

    return egPoint;
}

IFF_Bool _8SVX_readPLEnvelope(FILE *file, IFF_Chunk *chunk, const IFF_ChunkRegistry *chunkRegistry, IFF_Long *bytesProcessed)
{
    _8SVX_PLEnvelope *plEnvelope = (_8SVX_PLEnvelope*)chunk;
    IFF_FieldStatus status;

    while(*bytesProcessed < plEnvelope->chunkSize)
    {
        _8SVX_EGPoint *egPoint = allocatePointInPLEnvelope(plEnvelope);

        if((status = IFF_readUWordField(file, &egPoint->duration, chunk, "duration", bytesProcessed)) != IFF_FIELD_MORE)
            return IFF_deriveSuccess(status);

        if((status = IFF_readLongField(file, &egPoint->dest, chunk, "dest", bytesProcessed)) != IFF_FIELD_MORE)
            return IFF_deriveSuccess(status);
    }

    return TRUE;
}

IFF_Bool _8SVX_writePLEnvelope(FILE *file, const IFF_Chunk *chunk, const IFF_ChunkRegistry *chunkRegistry, IFF_Long *bytesProcessed)
{
    const _8SVX_PLEnvelope *plEnvelope = (const _8SVX_PLEnvelope*)chunk;
    IFF_FieldStatus status;
    unsigned int i;

    for(i = 0; i < plEnvelope->egPointLength; i++)
    {
        _8SVX_EGPoint *egPoint = &plEnvelope->egPoint[i];

        if((status = IFF_writeUWordField(file, egPoint->duration, chunk, "duration", bytesProcessed)) != IFF_FIELD_MORE)
            return IFF_deriveSuccess(status);

        if((status = IFF_writeLongField(file, egPoint->dest, chunk, "dest", bytesProcessed)) != IFF_FIELD_MORE)
            return IFF_deriveSuccess(status);
    }

    return TRUE;
}

IFF_Bool _8SVX_checkPLEnvelope(const IFF_Chunk *chunk, const IFF_ChunkRegistry *chunkRegistry)
{
    return TRUE;
}

void _8SVX_freePLEnvelope(IFF_Chunk *chunk, const IFF_ChunkRegistry *chunkRegistry)
{
    _8SVX_PLEnvelope *plEnvelope = (_8SVX_PLEnvelope*)chunk;
    free(plEnvelope->egPoint);
}

void _8SVX_printPLEnvelope(const IFF_Chunk *chunk, const unsigned int indentLevel, const IFF_ChunkRegistry *chunkRegistry)
{
    const _8SVX_PLEnvelope *plEnvelope = (const _8SVX_PLEnvelope*)chunk;
    unsigned int i;

    for(i = 0; i < plEnvelope->egPointLength; i++)
    {
        _8SVX_EGPoint *egPoint = &plEnvelope->egPoint[i];
        IFF_printIndent(stdout, indentLevel, "{ duration = %u, dest = %d }\n", egPoint->duration, egPoint->dest);
    }
}

IFF_Bool _8SVX_comparePLEnvelope(const IFF_Chunk *chunk1, const IFF_Chunk *chunk2, const IFF_ChunkRegistry *chunkRegistry)
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
