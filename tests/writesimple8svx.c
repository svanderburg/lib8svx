#include <math.h>
#include <stdlib.h>
#include <libiff/form.h>
#include <libiff/rawchunk.h>
#include "8svxinstrument.h"
#include "8svx.h"

#define SAMPLE_LENGTH 5000

int main(int argc, char *argv[])
{
    _8SVX_Voice8Header *voice8Header;
    _8SVX_Name *name;
    _8SVX_Copyright *copyright;
    _8SVX_Author *author;
    _8SVX_Annotation *annotation;
    _8SVX_Body *body;
    
    IFF_Byte *bodyData;
    _8SVX_Instrument *instrument;
    IFF_Form *form;
    unsigned int i;
    int status = 0;
    
    /* Define voice 8 header */
    voice8Header = _8SVX_createVoice8Header();
    
    voice8Header->oneShotHiSamples = SAMPLE_LENGTH;
    voice8Header->repeatHiSamples = 0;
    voice8Header->samplesPerHiCycle = 0;
    voice8Header->samplesPerSec = SAMPLE_LENGTH;
    voice8Header->ctOctave = 1;
    voice8Header->sCompression = _8SVX_CMP_NONE;
    voice8Header->volume = _8SVX_MAX_VOLUME;
    
    /* Define a name */
    
    name = _8SVX_createName();
    IFF_setTextData((IFF_RawChunk*)name, "Wave");
    
    /* Define copyright */
    
    copyright = _8SVX_createCopyright();
    IFF_setTextData((IFF_RawChunk*)copyright, "Copyright 2012 Sander van der Burg");
    
    /* Define author */
    
    author = _8SVX_createAuthor();
    IFF_setTextData((IFF_RawChunk*)author, "Sander van der Burg");
    
    /* Define annotation */
    
    annotation = _8SVX_createAnnotation();
    IFF_setTextData((IFF_RawChunk*)annotation, "Annotation");
    
    /* Create body */
    
    body = _8SVX_createBody();
    bodyData = (IFF_Byte*)malloc(SAMPLE_LENGTH * sizeof(IFF_Byte));
    
    for(i = 0; i < SAMPLE_LENGTH; i++)
	bodyData[i] = (IFF_Byte)(127 * sin(i / 2.0));
    
    IFF_setRawChunkData((IFF_RawChunk*)body, (IFF_UByte*)bodyData, SAMPLE_LENGTH);
    
    /* Create instrument */
    
    instrument = _8SVX_createInstrument();
    
    instrument->voice8Header = voice8Header;
    instrument->name = name;
    instrument->copyright = copyright;
    instrument->author = author;
    instrument->body = body;

    _8SVX_addAnnotationToInstrument(instrument, annotation);

    /* Convert instrument to form */
    form = _8SVX_convertInstrumentToForm(instrument);
    
    /* Write the form */
    
    if(!_8SVX_write("wave.8SVX", (IFF_Chunk*)form))
    {
	fprintf(stderr, "Error writing 8SVX file!\n");
	status = 1;
    }
    
    /* Free stuff */
    
    _8SVX_freeInstrument(instrument);
    _8SVX_free((IFF_Chunk*)form);
    
    return status;
}
