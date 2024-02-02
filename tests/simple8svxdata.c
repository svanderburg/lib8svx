#include "simple8svxdata.h"
#include <math.h>
#include <stdlib.h>
#include <8svxinstrument.h>

#define SAMPLE_LENGTH 5000

static _8SVX_Voice8Header *createTestVoice8Header(void)
{
    _8SVX_Voice8Header *voice8Header = _8SVX_createVoice8Header();

    voice8Header->oneShotHiSamples = SAMPLE_LENGTH;
    voice8Header->repeatHiSamples = 0;
    voice8Header->samplesPerHiCycle = 0;
    voice8Header->samplesPerSec = SAMPLE_LENGTH;
    voice8Header->ctOctave = 1;
    voice8Header->sCompression = _8SVX_CMP_NONE;
    voice8Header->volume = _8SVX_MAX_VOLUME;

    return voice8Header;
}

static _8SVX_Name *createTestName(void)
{
    _8SVX_Name *name = _8SVX_createName();
    IFF_setTextData((IFF_RawChunk*)name, "Wave");
    return name;
}

static _8SVX_Copyright *createTestCopyright(void)
{
    _8SVX_Copyright *copyright = _8SVX_createCopyright();
    IFF_setTextData((IFF_RawChunk*)copyright, "Copyright 2012 Sander van der Burg");
    return copyright;
}

static _8SVX_Author *createTestAuthor(void)
{
    _8SVX_Author *author = _8SVX_createAuthor();
    IFF_setTextData((IFF_RawChunk*)author, "Sander van der Burg");
    return author;
}

static _8SVX_Annotation *createTestAnnotation(void)
{
    _8SVX_Annotation *annotation = _8SVX_createAnnotation();
    IFF_setTextData((IFF_RawChunk*)annotation, "Annotation");
    return annotation;
}

static _8SVX_PlaybackEnvelope *createTestPlaybackEnvelope(void)
{
    _8SVX_PlaybackEnvelope *playbackEnvelope = _8SVX_createPlaybackEnvelope();

    _8SVX_EGPoint *egPoint = _8SVX_addToPlaybackEnvelope(playbackEnvelope);
    egPoint->duration = 10;
    egPoint->dest = 1;

    return playbackEnvelope;
}

static _8SVX_VolumeControl *createTestVolumeControl(void)
{
    _8SVX_VolumeControl *volumeControl = _8SVX_createVolumeControl();

    _8SVX_EGPoint *egPoint = _8SVX_addToVolumeControl(volumeControl);
    egPoint->duration = 20;
    egPoint->dest = 2;

    return volumeControl;
}

static _8SVX_Body *createTestBody(void)
{
    _8SVX_Body *body = _8SVX_createBody();
    IFF_Byte *bodyData = (IFF_Byte*)malloc(SAMPLE_LENGTH * sizeof(IFF_Byte));
    unsigned int i;

    for(i = 0; i < SAMPLE_LENGTH; i++)
        bodyData[i] = (IFF_Byte)(127 * sin(i / 2.0));

    IFF_setRawChunkData((IFF_RawChunk*)body, (IFF_UByte*)bodyData, SAMPLE_LENGTH);

    return body;
}

static _8SVX_Instrument *createTestInstrument(void)
{
    /* Define annotation */
    _8SVX_Annotation *annotation = createTestAnnotation();

    /* Create instrument */
    _8SVX_Instrument *instrument = _8SVX_createInstrument();

    instrument->voice8Header = createTestVoice8Header();
    instrument->name = createTestName();
    instrument->copyright = createTestCopyright();
    instrument->author = createTestAuthor();
    instrument->playbackEnvelope = createTestPlaybackEnvelope();
    instrument->volumeControl = createTestVolumeControl();
    instrument->body = createTestBody();

    _8SVX_addAnnotationToInstrument(instrument, annotation);

    /* Return generated instrument */
    return instrument;
}

IFF_Form *_8SVX_createTestForm(void)
{
    _8SVX_Instrument *instrument = createTestInstrument();
    IFF_Form *form = _8SVX_convertInstrumentToForm(instrument); /* Convert instrument to form */

    /* Free stuff */
    _8SVX_freeInstrument(instrument);

    return form;
}
