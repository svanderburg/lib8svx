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

#include "8svxinstrument.h"
#include <stdlib.h>
#include <form.h>
#include <util.h>
#include <error.h>
#include "8svx.h"

_8SVX_Instrument *_8SVX_createInstrument()
{
    return (_8SVX_Instrument*)calloc(1, sizeof(_8SVX_Instrument));
}

_8SVX_Instrument **_8SVX_extractInstruments(IFF_Chunk *chunk, unsigned int *instrumentsLength)
{
    unsigned int _8svxFormsLength;
    IFF_Form **_8svxForms = IFF_searchForms(chunk, "8SVX", &_8svxFormsLength);
    *instrumentsLength = _8svxFormsLength;
    
    if(_8svxFormsLength == 0)
    {
	IFF_error("No form with formType: '8SVX' found!\n");
	return NULL;
    }
    else
    {
	_8SVX_Instrument **instruments = (_8SVX_Instrument**)malloc(_8svxFormsLength * sizeof(_8SVX_Instrument*));
	unsigned int i;
	
	for(i = 0; i < _8svxFormsLength; i++)
	{
	    IFF_Form *_8svxForm = _8svxForms[i];
	    _8SVX_Instrument *instrument = (_8SVX_Instrument*)malloc(sizeof(_8SVX_Instrument));
	    
	    instrument->voice8Header = (_8SVX_Voice8Header*)IFF_getChunkFromForm(_8svxForm, "VHDR");
	    instrument->name = (_8SVX_Name*)IFF_getChunkFromForm(_8svxForm, "NAME");
	    instrument->copyright = (_8SVX_Name*)IFF_getChunkFromForm(_8svxForm, "(c) ");
	    instrument->author = (_8SVX_Author*)IFF_getChunkFromForm(_8svxForm, "AUTH");
	    instrument->annotation = (_8SVX_Annotation**)IFF_getChunksFromForm(_8svxForm, "ANNO", &instrument->annotationLength);
	    instrument->volumeControl = (_8SVX_VolumeControl*)IFF_getChunkFromForm(_8svxForm, "ATAK");
	    instrument->playbackEnvelope = (_8SVX_PlaybackEnvelope*)IFF_getChunkFromForm(_8svxForm, "RLSE");
	    instrument->body = (_8SVX_Body*)IFF_getChunkFromForm(_8svxForm, "BODY");
	    
	    instruments[i] = instrument;
	}
	
	return instruments;
    }
}

_8SVX_Sample *_8SVX_extractSamples(_8SVX_Instrument *instrument, unsigned int *samplesLength)
{
    _8SVX_Sample *samples;
    
    if(instrument->voice8Header == NULL || instrument->body == NULL)
    {
	*samplesLength = 0;
	samples = NULL;
    }
    else
    {
	IFF_UByte ctOctave = instrument->voice8Header->ctOctave;
	unsigned int numOfSamples = instrument->voice8Header->oneShotHiSamples + instrument->voice8Header->repeatHiSamples;
	unsigned int offset = 0;
	unsigned int i;
	
	*samplesLength = ctOctave;
	samples = (_8SVX_Sample*)malloc(ctOctave * sizeof(_8SVX_Sample));
	
	for(i = 0; i < ctOctave; i++)
	{
	    _8SVX_Sample *sample = &samples[i];
    
	    sample->sampleSize = numOfSamples;
	    sample->body = instrument->body->chunkData + offset;
	    
	    offset += numOfSamples;
	    numOfSamples *= 2;
	}
    }
    
    return samples;
}

IFF_Form *_8SVX_convertInstrumentToForm(_8SVX_Instrument *instrument)
{
    IFF_Form *form = IFF_createForm("8SVX");
    unsigned int i;
    
    if(instrument->voice8Header != NULL)
	IFF_addToForm(form, (IFF_Chunk*)instrument->voice8Header);

    if(instrument->name != NULL)
	IFF_addToForm(form, (IFF_Chunk*)instrument->name);

    if(instrument->copyright != NULL)
	IFF_addToForm(form, (IFF_Chunk*)instrument->copyright);

    if(instrument->author != NULL)
	IFF_addToForm(form, (IFF_Chunk*)instrument->author);

    for(i = 0; i < instrument->annotationLength; i++)
	IFF_addToForm(form, (IFF_Chunk*)instrument->annotation[i]);

    if(instrument->volumeControl != NULL)
	IFF_addToForm(form, (IFF_Chunk*)instrument->volumeControl);

    if(instrument->playbackEnvelope != NULL)
	IFF_addToForm(form, (IFF_Chunk*)instrument->playbackEnvelope);

    if(instrument->body != NULL)
	IFF_addToForm(form, (IFF_Chunk*)instrument->body);

    return form;
}

void _8SVX_freeInstrument(_8SVX_Instrument *instrument)
{
    free(instrument->annotation);
    free(instrument);
}

void _8SVX_freeInstruments(_8SVX_Instrument **instruments, const unsigned int instrumentsLength)
{
    unsigned int i;
    
    for(i = 0; i < instrumentsLength; i++)
	_8SVX_freeInstrument(instruments[i]);

    free(instruments);
}

int _8SVX_checkInstrument(const _8SVX_Instrument *instrument)
{
    if(instrument->voice8Header == NULL)
    {
	IFF_error("Error: no voice8header defined!\n");
	return FALSE;
    }
    
    if(instrument->body == NULL)
    {
	IFF_error("Error: no body defined!\n");
	return FALSE;
    }
    
    return TRUE;
}

int _8SVX_checkInstruments(const IFF_Chunk *chunk, _8SVX_Instrument **instruments, const unsigned int instrumentsLength)
{
    unsigned int i;
    
    /* First, check the 8SVX file for corectness */
    if(!_8SVX_check(chunk))
	return FALSE;
    
    /* Check the individual instruments inside the IFF file */
    for(i = 0; i < instrumentsLength; i++)
    {
	if(!_8SVX_checkInstrument(instruments[i]))
	    return FALSE;
    }
    
    /* Everything seems to be correct */
    return TRUE;
}

void _8SVX_addAnnotationToInstrument(_8SVX_Instrument *instrument, _8SVX_Annotation *annotation)
{
    instrument->annotation = (_8SVX_Annotation**)realloc(instrument->annotation, (instrument->annotationLength + 1) * sizeof(_8SVX_Instrument*));
    instrument->annotation[instrument->annotationLength] = annotation;
    instrument->annotationLength++;
}
