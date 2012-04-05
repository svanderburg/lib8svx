#include <string.h>
#include "8svx.h"
#include "8svxinstrument.h"

#define SAMPLE_LENGTH 5000

int main(int argc, char *argv[])
{
    IFF_Chunk *chunk;
    unsigned int instrumentsLength;
    _8SVX_Instrument **instruments;
    int status = 0;
    
    chunk = _8SVX_read("wave.8SVX");
    
    if(chunk == NULL)
    {
	fprintf(stderr, "Cannot open 8SVX file!\n");
	return 1;
    }
    
    instruments = _8SVX_extractInstruments(chunk, &instrumentsLength);
    
    if(_8SVX_checkInstruments(chunk, instruments, instrumentsLength))
    {
	/* We should have exactly 1 8SVX instrument in this IFF file */
	
	if(instrumentsLength == 1)
	{
	    _8SVX_Instrument *instrument = instruments[0];
	    _8SVX_Voice8Header *voice8Header = instrument->voice8Header;
	    _8SVX_Name *name = instrument->name;
	    _8SVX_Copyright *copyright = instrument->copyright;
	    _8SVX_Author *author = instrument->author;
	    
	    /* Check voice 8 header properties */
	    
	    if(voice8Header->oneShotHiSamples != SAMPLE_LENGTH)
	    {
		fprintf(stderr, "'VHDR'.oneShotHiSamples should be %u\n", SAMPLE_LENGTH);
		status = 1;
	    }
	    
	    if(voice8Header->repeatHiSamples != 0)
	    {
		fprintf(stderr, "'VHDR'.repeatHiSamples should be 0\n");
		status = 1;
	    }
	    
	    if(voice8Header->samplesPerHiCycle != 0)
	    {
		fprintf(stderr, "'VHDR'.samplesPerHiCycle should be 0\n");
		status = 1;
	    }
	    
	    if(voice8Header->samplesPerSec != SAMPLE_LENGTH)
	    {
		fprintf(stderr, "'VHDR'.samplesPerSec should be %u\n", SAMPLE_LENGTH);
		status = 1;
	    }
	    
	    if(voice8Header->ctOctave != 1)
	    {
		fprintf(stderr, "'VHDR'.ctOctave should be 1\n");
		status = 1;
	    }
	    
	    if(voice8Header->sCompression != _8SVX_CMP_NONE)
	    {
		fprintf(stderr, "'VHDR'.sCompression should be %u\n", _8SVX_CMP_NONE);
		status = 1;
	    }
	    
	    if(voice8Header->volume != _8SVX_MAX_VOLUME)
	    {
		fprintf(stderr, "'VHDR'.volume should be %d\n", _8SVX_MAX_VOLUME);
		status = 1;
	    }
	    
	    /* Check name */
	    
	    if(strncmp((char*)name->chunkData, "Wave", name->chunkSize) != 0)
	    {
		fprintf(stderr, "'NAME' chunk contents is invalid!\n");
		status = 1;
	    }
	    
	    /* Check copyright */
	    
	    if(strncmp((char*)copyright->chunkData, "Copyright 2012 Sander van der Burg", copyright->chunkSize) != 0)
	    {
		fprintf(stderr, "'(c) ' chunk contents is invalid!\n");
		status = 1;
	    }
	    
	    /* Check author */
	    
	    if(strncmp((char*)author->chunkData, "Sander van der Burg", author->chunkSize) != 0)
	    {
		fprintf(stderr, "'AUTH' chunk contents is invalid!\n");
		status = 1;
	    }
	    
	    /* We should have exactly 1 annotation */
	    
	    if(instrument->annotationLength == 1)
	    {
		_8SVX_Annotation *annotation = instrument->annotation[0];
		
		/* Check annotation */
		
		if(strncmp((char*)annotation->chunkData, "Annotation", annotation->chunkSize) != 0)
		{
		    fprintf(stderr, "'ANNO' chunk contents is invalid!\n");
		    status = 1;
		}
	    }
	    else
	    {
		fprintf(stderr, "We should have exactly 1 annotation!\n");
		status = 1;
	    }
	}
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
