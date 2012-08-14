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

#include <stdio.h>
#include <8svx.h>
#include <8svxinstrument.h>
#include "simple8svxdata.h"

int main(int argc, char *argv[])
{
    IFF_Chunk *chunk = _8SVX_read("wave.8SVX");
    
    if(chunk == NULL)
    {
	fprintf(stderr, "Cannot open 8SVX file!\n");
	return 1;
    }
    else
    {
	unsigned int instrumentsLength;
	_8SVX_Instrument **instruments = _8SVX_extractInstruments(chunk, &instrumentsLength);
	int status = 0;
	
	if(_8SVX_checkInstruments(chunk, instruments, instrumentsLength))
	{
	    IFF_Form *form = _8SVX_createTestForm();
	    
	    if(!_8SVX_compare(chunk, (const IFF_Chunk*)form))
	    {
		fprintf(stderr, "The 8SVX file is not identical to the original!\n");
		status = 1;
	    }
	    
	    _8SVX_free((IFF_Chunk*)form);
	}
	else
	{
	    fprintf(stderr, "The IFF file containing 8SVX instruments is not valid!\n");
	    status = 1;
	}
	
	_8SVX_freeInstruments(instruments, instrumentsLength);
	_8SVX_free(chunk);
	
	return status;
    }
}
