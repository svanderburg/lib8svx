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

#ifndef __8SVX_INSTRUMENT_H
#define __8SVX_INSTRUMENT_H

#include <form.h>
#include "voice8header.h"
#include "name.h"
#include "copyright.h"
#include "author.h"
#include "annotation.h"
#include "volumecontrol.h"
#include "playbackenvelope.h"
#include "body.h"

typedef struct
{
    _8SVX_Voice8Header *voice8Header;
    
    _8SVX_Name *name;
    
    _8SVX_Copyright *copyright;
    
    _8SVX_Author *author;
    
    unsigned int annotationLength;
    _8SVX_Annotation **annotation;
    
    _8SVX_VolumeControl *volumeControl;
    
    _8SVX_PlaybackEnvelope *playbackEnvelope;
    
    _8SVX_Body *body;
}
_8SVX_Instrument;

_8SVX_Instrument *_8SVX_createInstrument(void);

_8SVX_Instrument **_8SVX_extractInstruments(IFF_Chunk *chunk, unsigned int *instrumentsLength);

IFF_Form *_8SVX_convertInstrumentToForm(_8SVX_Instrument *instrument);

void _8SVX_freeInstrument(_8SVX_Instrument *instrument);

void _8SVX_freeInstruments(_8SVX_Instrument **instruments, const unsigned int instrumentsLength);

int _8SVX_checkInstrument(const _8SVX_Instrument *instrument);

int _8SVX_checkInstruments(const IFF_Chunk *chunk, _8SVX_Instrument **instruments, const unsigned int instrumentsLength);

void _8SVX_addAnnotationToInstrument(_8SVX_Instrument *instrument, _8SVX_Annotation *annotation);

#endif
