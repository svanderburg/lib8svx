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

#include "pack.h"
#include <stdio.h>
#include <stdlib.h>
#include "8svx.h"
#include "8svxinstrument.h"
#include "fibdelta.h"

int pack(const char *inputFilename, const char *outputFilename, const IFF_Bool compress)
{
    IFF_Chunk *chunk = _8SVX_read(inputFilename);

    if(chunk == NULL)
    {
        fprintf(stderr, "Error parsing 8SVX file!\n");
        return 1;
    }
    else
    {
        unsigned int instrumentsLength;
        _8SVX_Instrument **instruments = _8SVX_extractInstruments(chunk, &instrumentsLength);
        int status = 0;

        if(!_8SVX_checkInstruments(chunk, instruments, instrumentsLength))
        {
            fprintf(stderr, "Invalid 8SVX file!\n");
            status = 1;
        }
        else if(instrumentsLength == 0)
        {
            fprintf(stderr, "No 8SVX instruments found in IFF file!\n");
            status = 1;
        }
        else
        {
            unsigned int i;

            for(i = 0; i < instrumentsLength; i++)
            {
                _8SVX_Instrument *instrument = instruments[i];

                if(compress)
                    _8SVX_packFibonacciDelta(instrument);
                else
                    _8SVX_unpackFibonacciDelta(instrument);
            }

            if(!_8SVX_write(outputFilename, chunk))
            {
                fprintf(stderr, "Error writing 8SVX file!\n");
                status = 1;
            }

            _8SVX_freeInstruments(instruments, instrumentsLength);
        }

        _8SVX_free(chunk);

        /* Everything has succeeded */
        return status;
    }
}
