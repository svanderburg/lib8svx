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

#include "8svx.h"
#include <libiff/iff.h>
#include <libiff/defaultregistry.h>
#include "copyright.h"
#include "annotation.h"
#include "author.h"
#include "volumecontrol.h"
#include "playbackenvelope.h"
#include "body.h"
#include "name.h"
#include "voice8header.h"

#define _8SVX_NUM_OF_FORM_CHUNK_TYPES 1
#define _8SVX_NUM_OF_CHUNK_TYPES 8

static IFF_ChunkType _8svxChunkTypes[] = {
    {_8SVX_ID_C, &_8SVX_createCopyrightChunk, &_8SVX_readCopyright, &_8SVX_writeCopyright, &_8SVX_checkCopyright, &_8SVX_freeCopyright, &_8SVX_printCopyright, &_8SVX_compareCopyright},
    {_8SVX_ID_ANNO, &_8SVX_createAnnotationChunk, &_8SVX_readAnnotation, &_8SVX_writeAnnotation, &_8SVX_checkAnnotation, &_8SVX_freeAnnotation, &_8SVX_printAnnotation, &_8SVX_compareAnnotation},
    {_8SVX_ID_ATAK, &_8SVX_createVolumeControlChunk, &_8SVX_readVolumeControl, &_8SVX_writeVolumeControl, &_8SVX_checkVolumeControl, &_8SVX_freeVolumeControl, &_8SVX_printVolumeControl, &_8SVX_compareVolumeControl},
    {_8SVX_ID_AUTH, &_8SVX_createAuthorChunk, &_8SVX_readAuthor, &_8SVX_writeAuthor, &_8SVX_checkAuthor, &_8SVX_freeAuthor, &_8SVX_printAuthor, &_8SVX_compareAuthor},
    {_8SVX_ID_BODY, &_8SVX_createBodyChunk, &_8SVX_readBody, &_8SVX_writeBody, &_8SVX_checkBody, &_8SVX_freeBody, &_8SVX_printBody, &_8SVX_compareBody},
    {_8SVX_ID_NAME, &_8SVX_createNameChunk, &_8SVX_readName, &_8SVX_writeName, &_8SVX_checkName, &_8SVX_freeName, &_8SVX_printName, &_8SVX_compareName},
    {_8SVX_ID_RLSE, &_8SVX_createPlaybackEnvelopeChunk, &_8SVX_readPlaybackEnvelope, &_8SVX_writePlaybackEnvelope, &_8SVX_checkPlaybackEnvelope, &_8SVX_freePlaybackEnvelope, &_8SVX_printPlaybackEnvelope, &_8SVX_comparePlaybackEnvelope},
    {_8SVX_ID_VHDR, &_8SVX_createVoice8HeaderChunk, &_8SVX_readVoice8Header, &_8SVX_writeVoice8Header, &_8SVX_checkVoice8Header, &_8SVX_freeVoice8Header, &_8SVX_printVoice8Header, &_8SVX_compareVoice8Header}
};

static IFF_ChunkTypesNode _8svxChunkTypesNode = {
    _8SVX_NUM_OF_CHUNK_TYPES, _8svxChunkTypes, NULL
};


static IFF_FormChunkTypes formChunkTypes[] = {
    {_8SVX_ID_8SVX, &_8svxChunkTypesNode}
};

static IFF_ChunkRegistry chunkRegistry = IFF_EXTEND_DEFAULT_REGISTRY_WITH_FORM_CHUNK_TYPES(_8SVX_NUM_OF_FORM_CHUNK_TYPES, formChunkTypes);

IFF_Chunk *_8SVX_readFd(FILE *file)
{
    return IFF_readFd(file, &chunkRegistry);
}

IFF_Chunk *_8SVX_readFile(const char *filename)
{
    return IFF_readFile(filename, &chunkRegistry);
}

IFF_Chunk *_8SVX_read(const char *filename)
{
    return IFF_read(filename, &chunkRegistry);
}

IFF_Bool _8SVX_writeFd(FILE *file, const IFF_Chunk *chunk)
{
    return IFF_writeFd(file, chunk, &chunkRegistry);
}

IFF_Bool _8SVX_writeFile(const char *filename, const IFF_Chunk *chunk)
{
    return IFF_writeFile(filename, chunk, &chunkRegistry);
}

IFF_Bool _8SVX_write(const char *filename, const IFF_Chunk *chunk)
{
    return IFF_write(filename, chunk, &chunkRegistry);
}

IFF_Bool _8SVX_check(const IFF_Chunk *chunk)
{
    return IFF_check(chunk, &chunkRegistry);
}

void _8SVX_free(IFF_Chunk *chunk)
{
    IFF_free(chunk, &chunkRegistry);
}

void _8SVX_print(const IFF_Chunk *chunk, const unsigned int indentLevel)
{
    IFF_print(chunk, indentLevel, &chunkRegistry);
}

IFF_Bool _8SVX_compare(const IFF_Chunk *chunk1, const IFF_Chunk *chunk2)
{
    return IFF_compare(chunk1, chunk2, &chunkRegistry);
}
