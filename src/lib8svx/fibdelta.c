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

#include "fibdelta.h"
#include <stdlib.h>
#include <ifftypes.h>
#include <rawchunk.h>

#define CODE_TO_DELTA_SIZE 16

static IFF_Byte codeToDelta[] = {-34, -21, -13, -8, -5, -3, -2, -1, 0, 1, 2, 3, 5, 8, 13, 21};

void _8SVX_unpackFibonacciDelta(_8SVX_Instrument *instrument)
{
    if(instrument->voice8Header->sCompression == _8SVX_CMP_FIBDELTA)
    {
	_8SVX_Body *body = instrument->body;
	unsigned int bytesToDecompress = (body->chunkSize - 2) * 2;
	unsigned int chunkSize = bytesToDecompress + 1;
	IFF_Byte *compressedBodyData = body->chunkData;
	IFF_Byte *uncompressedBodyData = (IFF_Byte*)malloc(chunkSize * sizeof(IFF_Byte));
	unsigned int i;
	
	/* First byte of compressed data is padding, second is not compressed */
	uncompressedBodyData[0] = compressedBodyData[1];
	
	/* Decompress all the other bytes */
	for(i = 0; i < bytesToDecompress; i++)
	{
	    IFF_UByte compressedByte = compressedBodyData[i / 2 + 2];
	    unsigned int code;
	    
	    if(i % 2 == 0)
		code = compressedByte >> 4; /* Take high word for even offsets */
	    else
		code = compressedByte & 0xf; /* Take low word for odd offsets */
	    
	    uncompressedBodyData[i + 1] = uncompressedBodyData[i] + codeToDelta[code];
	}
	
	/* Free the compressed data */
	free(body->chunkData);
	
	/* Attach uncompressed data to the body chunk */
	IFF_setRawChunkData((IFF_RawChunk*)body, (IFF_UByte*)uncompressedBodyData, chunkSize);
	
	/* Recursively update the chunk sizes */
	IFF_updateChunkSizes((IFF_Chunk*)body);
	
	/* Change compression flag, since the body is no longer compressed anymore */
	instrument->voice8Header->sCompression = _8SVX_CMP_NONE;
    }
}

void _8SVX_packFibonacciDelta(_8SVX_Instrument *instrument)
{
    if(instrument->voice8Header->sCompression == _8SVX_CMP_NONE)
    {
	_8SVX_Body *body = instrument->body;
	unsigned int chunkSize = 2 + (body->chunkSize - 1) / 2;
	IFF_Byte *uncompressedBodyData = body->chunkData;
	IFF_Byte *compressedBodyData = (IFF_Byte*)malloc(chunkSize * sizeof(IFF_Byte));
	unsigned int i;
	unsigned int count = 2;
	IFF_Byte previousValue;
	
	/* First byte is padding */
	compressedBodyData[0] = '\0';
	
	/* Next byte is the first byte of the uncompressed data */
	compressedBodyData[1] = uncompressedBodyData[0];
	
	/* Compress the remaining bytes */
	
	previousValue = uncompressedBodyData[0];
	
	for(i = 1; i < body->chunkSize; i++)
	{
	    int delta = uncompressedBodyData[i] - previousValue; /* Determine the difference relative to the previous sample */
	    unsigned int code = CODE_TO_DELTA_SIZE / 2;
	    
	    if(delta != 0)
	    {
		unsigned int minDifference = abs(delta);
		
		if(delta < 0)
		{
		    /* Decide which negative value from the table is closest to the delta */
		    
		    int j;
		
		    for(j = CODE_TO_DELTA_SIZE / 2 - 1; j >= 0; j--)
		    {
			unsigned int difference = abs(codeToDelta[j] - delta);
		    
			if(difference < minDifference)
			{
			    minDifference = difference;
			    code = j;
			}
		    }
		}
		else if(delta > 0)
		{
		    /* Decide which positive value from the table is closest to the delta */
		
		    unsigned int j;
		
		    for(j = CODE_TO_DELTA_SIZE / 2 + 1; j < CODE_TO_DELTA_SIZE; j++)
		    {
			unsigned int difference = abs(codeToDelta[j] - delta);
		    
			if(difference < minDifference)
			{
			    minDifference = difference;
			    code = j;
			}
		    }
		}
	    }
	    
	    /* Write the code word into the first or second part of the compressed byte */
	    
	    if(i % 2 == 0)
	    {
		compressedBodyData[count] |= code;
		count++; /* For each even value, raise the compressed chunk counter */
	    }
	    else
		compressedBodyData[count] = code << 4;
	    
	    previousValue += codeToDelta[code]; /* We have to use this in order to determine the next delta */
	}
	
	/* Free the uncompressed data */
	free(body->chunkData);
	
	/* Attach compressed data to the body chunk */
	IFF_setRawChunkData((IFF_RawChunk*)body, (IFF_UByte*)compressedBodyData, chunkSize);
	
	/* Recursively update the chunk sizes */
	IFF_updateChunkSizes((IFF_Chunk*)body);
	
	/* Change compression flag, since the body is compressed now */
	instrument->voice8Header->sCompression = _8SVX_CMP_FIBDELTA;
    }
}
