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

#include "voice8header.h"
#include <libiff/field.h>
#include <libiff/io.h>
#include <libiff/util.h>
#include <libiff/error.h>
#include "8svx.h"

IFF_Chunk *_8SVX_createVoice8Header(const IFF_Long chunkSize)
{
    _8SVX_Voice8Header *voice8Header = (_8SVX_Voice8Header*)IFF_allocateChunk(_8SVX_ID_VHDR, chunkSize, sizeof(_8SVX_Voice8Header));

    if(voice8Header != NULL)
    {
        voice8Header->oneShotHiSamples = 0;
        voice8Header->repeatHiSamples = 0;
        voice8Header->samplesPerHiCycle = 0;
        voice8Header->samplesPerSec = 0;
        voice8Header->ctOctave = '\0';
        voice8Header->sCompression = '\0';
        voice8Header->volume = 0;
    }

    return (IFF_Chunk*)voice8Header;
}

IFF_Bool _8SVX_readVoice8Header(FILE *file, IFF_Chunk *chunk, IFF_Long *bytesProcessed)
{
    _8SVX_Voice8Header *voice8Header = (_8SVX_Voice8Header*)chunk;
    IFF_FieldStatus status;

    if((status = IFF_readULongField(file, &voice8Header->oneShotHiSamples, chunk, "oneShotHiSamples", bytesProcessed)) != IFF_FIELD_MORE)
        return IFF_deriveSuccess(status);

    if((status = IFF_readULongField(file, &voice8Header->repeatHiSamples, chunk, "repeatHiSamples", bytesProcessed)) != IFF_FIELD_MORE)
        return IFF_deriveSuccess(status);

    if((status = IFF_readULongField(file, &voice8Header->samplesPerHiCycle, chunk, "samplesPerHiCycle", bytesProcessed)) != IFF_FIELD_MORE)
        return IFF_deriveSuccess(status);

    if((status = IFF_readUWordField(file, &voice8Header->samplesPerSec, chunk, "samplesPerSec", bytesProcessed)) != IFF_FIELD_MORE)
        return IFF_deriveSuccess(status);

    if((status = IFF_readUByteField(file, &voice8Header->ctOctave, chunk, "ctOctave", bytesProcessed)) != IFF_FIELD_MORE)
        return IFF_deriveSuccess(status);

    if((status = IFF_readUByteField(file, &voice8Header->sCompression, chunk, "sCompression", bytesProcessed)) != IFF_FIELD_MORE)
        return IFF_deriveSuccess(status);

    if((status = IFF_readLongField(file, &voice8Header->volume, chunk, "volume", bytesProcessed)) != IFF_FIELD_MORE)
        return IFF_deriveSuccess(status);

    return TRUE;
}

IFF_Bool _8SVX_writeVoice8Header(FILE *file, const IFF_Chunk *chunk, IFF_Long *bytesProcessed)
{
    const _8SVX_Voice8Header *voice8Header = (const _8SVX_Voice8Header*)chunk;
    IFF_FieldStatus status;

    if((status = IFF_writeULongField(file, voice8Header->oneShotHiSamples, chunk, "oneShotHiSamples", bytesProcessed)) != IFF_FIELD_MORE)
        return IFF_deriveSuccess(status);

    if((status = IFF_writeULongField(file, voice8Header->repeatHiSamples, chunk, "repeatHiSamples", bytesProcessed)) != IFF_FIELD_MORE)
        return IFF_deriveSuccess(status);

    if((status = IFF_writeULongField(file, voice8Header->samplesPerHiCycle, chunk, "samplesPerHiCycle", bytesProcessed)) != IFF_FIELD_MORE)
        return IFF_deriveSuccess(status);

    if((status = IFF_writeUWordField(file, voice8Header->samplesPerSec, chunk, "samplesPerSec", bytesProcessed)) != IFF_FIELD_MORE)
        return IFF_deriveSuccess(status);

    if((status = IFF_writeUByteField(file, voice8Header->ctOctave, chunk, "ctOctave", bytesProcessed)) != IFF_FIELD_MORE)
        return IFF_deriveSuccess(status);

    if((status = IFF_writeUByteField(file, voice8Header->sCompression, chunk, "sCompression", bytesProcessed)) != IFF_FIELD_MORE)
        return IFF_deriveSuccess(status);

    if((status = IFF_writeLongField(file, voice8Header->volume, chunk, "volume", bytesProcessed)) != IFF_FIELD_MORE)
        return IFF_deriveSuccess(status);

    return TRUE;
}

IFF_Bool _8SVX_checkVoice8Header(const IFF_Chunk *chunk)
{
    const _8SVX_Voice8Header *voice8Header = (const _8SVX_Voice8Header*)chunk;

    if(voice8Header->sCompression < _8SVX_CMP_NONE || voice8Header->sCompression > _8SVX_CMP_FIBDELTA)
    {
        IFF_error("Invalid 'VHDR'.sCompression value!");
        return FALSE;
    }

    return TRUE;
}

void _8SVX_freeVoice8Header(IFF_Chunk *chunk)
{
}

void _8SVX_printVoice8Header(const IFF_Chunk *chunk, const unsigned int indentLevel)
{
    const _8SVX_Voice8Header *voice8Header = (const _8SVX_Voice8Header*)chunk;

    IFF_printIndent(stdout, indentLevel, "oneShotHiSamples = %u;\n", voice8Header->oneShotHiSamples);
    IFF_printIndent(stdout, indentLevel, "repeatHiSamples = %u;\n", voice8Header->repeatHiSamples);
    IFF_printIndent(stdout, indentLevel, "samplesPerHiCycle = %u;\n", voice8Header->samplesPerHiCycle);
    IFF_printIndent(stdout, indentLevel, "samplesPerSec = %u;\n", voice8Header->samplesPerSec);
    IFF_printIndent(stdout, indentLevel, "ctOctave = %u;\n", voice8Header->ctOctave);
    IFF_printIndent(stdout, indentLevel, "sCompression = %u;\n", voice8Header->sCompression);
    IFF_printIndent(stdout, indentLevel, "volume = %d;\n", voice8Header->volume);
}

IFF_Bool _8SVX_compareVoice8Header(const IFF_Chunk *chunk1, const IFF_Chunk *chunk2)
{
    const _8SVX_Voice8Header *voice8Header1 = (const _8SVX_Voice8Header*)chunk1;
    const _8SVX_Voice8Header *voice8Header2 = (const _8SVX_Voice8Header*)chunk2;

    if(voice8Header1->oneShotHiSamples != voice8Header2->oneShotHiSamples)
        return FALSE;

    if(voice8Header1->repeatHiSamples != voice8Header2->repeatHiSamples)
        return FALSE;

    if(voice8Header1->samplesPerHiCycle != voice8Header2->samplesPerHiCycle)
        return FALSE;

    if(voice8Header1->samplesPerSec != voice8Header2->samplesPerSec)
        return FALSE;

    if(voice8Header1->ctOctave != voice8Header2->ctOctave)
        return FALSE;

    if(voice8Header1->sCompression != voice8Header2->sCompression)
        return FALSE;

    if(voice8Header1->volume != voice8Header2->volume)
        return FALSE;

    return TRUE;
}
