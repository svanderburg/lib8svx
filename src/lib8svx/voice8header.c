/**
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
#include <io.h>
#include <util.h>
#include <error.h>
#include "8svx.h"

#define CHUNKID "VHDR"

_8SVX_Voice8Header *_8SVX_createVoice8Header(void)
{
    _8SVX_Voice8Header *voice8Header = (_8SVX_Voice8Header*)IFF_allocateChunk(CHUNKID, sizeof(_8SVX_Voice8Header));
    
    if(voice8Header != NULL)
	voice8Header->chunkSize = 3 * sizeof(IFF_ULong) + sizeof(IFF_UWord) + sizeof(IFF_UByte) + sizeof(IFF_UByte) + sizeof(IFF_Long);
    
    return voice8Header;
}

IFF_Chunk *_8SVX_readVoice8Header(FILE *file, const IFF_Long chunkSize)
{
    _8SVX_Voice8Header *voice8Header = _8SVX_createVoice8Header();
    
    if(voice8Header != NULL)
    {
	IFF_UByte byte;
	
	if(!IFF_readULong(file, &voice8Header->oneShotHiSamples, CHUNKID, "oneShotHiSamples"))
	{
	    _8SVX_free((IFF_Chunk*)voice8Header);
	    return NULL;
	}
	
	if(!IFF_readULong(file, &voice8Header->repeatHiSamples, CHUNKID, "repeatHiSamples"))
	{
	    _8SVX_free((IFF_Chunk*)voice8Header);
	    return NULL;
	}
	
	if(!IFF_readULong(file, &voice8Header->samplesPerHiCycle, CHUNKID, "samplesPerHiCycle"))
	{
	    _8SVX_free((IFF_Chunk*)voice8Header);
	    return NULL;
	}
	
	if(!IFF_readUWord(file, &voice8Header->samplesPerSec, CHUNKID, "samplesPerSec"))
	{
	    _8SVX_free((IFF_Chunk*)voice8Header);
	    return NULL;
	}
	
	if(!IFF_readUByte(file, &voice8Header->ctOctave, CHUNKID, "ctOctave"))
	{
	    _8SVX_free((IFF_Chunk*)voice8Header);
	    return NULL;
	}
	
	if(!IFF_readUByte(file, &byte, CHUNKID, "sCompression"))
	{
	    _8SVX_free((IFF_Chunk*)voice8Header);
	    return NULL;
	}
	
	voice8Header->sCompression = byte;
	
	if(!IFF_readLong(file, &voice8Header->volume, CHUNKID, "volume"))
	{
	    _8SVX_free((IFF_Chunk*)voice8Header);
	    return NULL;
	}
    }
    
    return (IFF_Chunk*)voice8Header;
}

int _8SVX_writeVoice8Header(FILE *file, const IFF_Chunk *chunk)
{
    _8SVX_Voice8Header *voice8Header = (_8SVX_Voice8Header*)chunk;
    
    if(!IFF_writeULong(file, voice8Header->oneShotHiSamples, CHUNKID, "oneShotHiSamples"))
	return FALSE;

    if(!IFF_writeULong(file, voice8Header->repeatHiSamples, CHUNKID, "repeatHiSamples"))
	return FALSE;
    
    if(!IFF_writeULong(file, voice8Header->samplesPerHiCycle, CHUNKID, "samplesPerHiCycle"))
	return FALSE;
    
    if(!IFF_writeUWord(file, voice8Header->samplesPerSec, CHUNKID, "samplesPerSec"))
	return FALSE;

    if(!IFF_writeUByte(file, voice8Header->ctOctave, CHUNKID, "ctOctave"))
	return FALSE;
    
    if(!IFF_writeUByte(file, voice8Header->sCompression, CHUNKID, "sCompression"))
	return FALSE;
    
    if(!IFF_writeLong(file, voice8Header->volume, CHUNKID, "volume"))
	return FALSE;
    
    return TRUE;
}

int _8SVX_checkVoice8Header(const IFF_Chunk *chunk)
{
    _8SVX_Voice8Header *voice8Header = (_8SVX_Voice8Header*)chunk;
    
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
    _8SVX_Voice8Header *voice8Header = (_8SVX_Voice8Header*)chunk;
    
    IFF_printIndent(stdout, indentLevel, "oneShotHiSamples = %d;\n", voice8Header->oneShotHiSamples);
    IFF_printIndent(stdout, indentLevel, "repeatHiSamples = %d;\n", voice8Header->repeatHiSamples);
    IFF_printIndent(stdout, indentLevel, "samplesPerHiCycle = %d;\n", voice8Header->samplesPerHiCycle);
    IFF_printIndent(stdout, indentLevel, "samplesPerSec = %d;\n", voice8Header->samplesPerSec);
    IFF_printIndent(stdout, indentLevel, "ctOctave = %d;\n", voice8Header->ctOctave);
    IFF_printIndent(stdout, indentLevel, "sCompression = %d;\n", voice8Header->sCompression);
    IFF_printIndent(stdout, indentLevel, "volume = %d;\n", voice8Header->volume);
}
