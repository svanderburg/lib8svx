lib8svx
=======
`lib8svx` is a portable parser library built on top of `libiff`, for 8SVX
files containing digitally sampled audio voices consisting of 8-bit samples.
The 8SVX file format is frequently used on the Commodore Amiga. This library
offers the following features:

* Reading 8SVX files
* Programmatically creating 8SVX files
* Retrieving 8SVX file contents
* Writing 8SVX files
* 8SVX conformance checking

This parser library implements support for all chunks described in the 8SVX
specification, which can be found in: `doc/8SVX.doc` included in this package.

Prerequisites
=============
In order to build and use this package, the following libraries are required:

* `libiff`, in order to parse IFF files

Installation
============
Compilation and installation of this library is straight forward, by using the
standard GNU autotools build instructions:

    $ ./configure
    $ make
    $ make install

More details about the installation process can be found in the `INSTALL` file
included in this package.

Portability
===========
Because this package is implemented in ANSI C (with the small exception that the
command line utilities use `getopt()` ), it should be fairly easy to port this
package to new platforms. So far it has been tested on the following platforms:

* Linux (`i686-linux`, `x86_64-linux`) using GCC
* AmigaOS (`m68k-amigaos`) using EGCS through Geek Gadgets

License
=======
This library is available under the MIT license

Using the 8SVX library API
==========================
The 8SVX parser provdes a convenient interface which can be used to create,
read, write and check 8SVX files. Full API documentation can be found in the
`doc/apidox` directory of this package.

Reading 8SVX files
------------------
To read a 8SVX file, call the `_8SVX_read()` function. An IFF file may contain
multiple 8SVX instruments (however most IFF files represent a single 8SVX file).
The `_8SVX_extractInstruments()` function extracts all the 8SVX instruments from
an IFF file and returns an array of `_8SVX_Instrument` struct instances, which can
be used to convienently access its properties. The length of the array is stored
in the `instrumentsLength` variable:

    #include "8svx.h"
    #include "8svxinstrument.h"
    
    int main(int argc, char *argv[])
    {
        unsigned int instrumentsLength;
        IFF_Chunk *chunk = _8SVX_read("input.8SVX");
        _8SVX_Instrument **instrument = _8SVX_extractInstruments(chunk, &instrumentsLength);
        
        /* Retrieve an instrument from the array and access its properties here */
        
        return 0;
    }

Programmatically creating 8SVX files
------------------------------------
An 8SVX file can be created by creating an instance of an `_8SVX_Instrument`
struct and by setting its sub chunks. The following example defines a 8SVX
instrument with a voice 8 header chunk:

    #include "8svxinstrument.h"
    
    int main(int argc, char *argv[])
    {
        _8SVX_Instrument *instrument = _8SVX_createInstrument();
        
        _8SVX_Voice8Header *voice8Header = _8SVX_createVoice8Header();
        
        /* Create voice 8 header properties */
        
        voice8Header->oneShotHiSamples = SAMPLE_LENGTH;
        voice8Header->repeatHiSamples = 0;
        voice8Header->samplesPerHiCycle = 0;
        voice8Header->samplesPerSec = SAMPLE_LENGTH;
        voice8Header->ctOctave = 1;
        voice8Header->sCompression = _8SVX_CMP_NONE;
        voice8Header->volume = _8SVX_MAX_VOLUME;
        
        /* Attach voice 8 header to the instrument */
        instrument->voice8Header = voice8Header;
        
        return 0;
    }

Retrieving 8SVX file contents
-----------------------------
To retrieve properties of 8SVX instruments inside an IFF file, you must take all
possible 8SVX FORMs into account, which can be retrieved through the
`_8SVX_extractInstruments()` function. By iterating over the resulting array,
you can retrieve the 8SVX instrument properties by accessing members of each
individual `_8SVX_Instrument` struct instance.

    #include "8svxinstrument.h"
    
    int main(int argc, char *argv[])
    {
        _8SVX_Instrument **instruments;
        unsigned int i, instrumentsLength;
        
        /* Open and extract 8SVX instruments here */
        
        for(i = 0; i < instrumentsLength; i++)
        {
            _8SVX_Instrument *instrument = instruments[i];
            _8SVX_Voice8Header *voice8Header = instrument->voice8Header; /* Struct representing voice 8 header properties */
            _8SVX_Copyright *copyright = instrument->copyright; /* Struct containing copyright information */
            _8SVX_Body *body = instrument->body; /* Body chunk containing compressed or uncompressed sample data */
            
            /* Retrieve more properties here */
        }
        
        return 0;
    }

Writing 8SVX files
------------------
To write an `_8SVX_Instrument` struct instance to a file, it must first be
converted to an IFF FORM using the `_8SVX_convertInstrumentToForm()` function.
Then the resulting FORM can written to disk using the `_8SVX_write()` function.

    #include "8svxinstrument.h"
    #include "8svx.h"
    
    int main(int argc, char *argv[])
    {
        _8SVX_Instrument *instrument;
        IFF_Form *form;
        
        /* Create a 8SVX instrument here */
        
        form = _8SVX_convertInstrumentToForm(instrument);
        
        if(_8SVX_write("output.8SVX", (IFF_Chunk*)form))
            return 0; /* File has been successfully written */
        else
            return 1; /* Writing failed */
    }

8SVX conformance checking
-------------------------
Typically when opening an IFF file containing 8SVX instruments, you want to check
whether the file is valid. This can be done by invoking the
`_8SVX_checkInstruments()` function, which checks whether the IFF file is valid
and it checks whether are required 8SVX chunks are present.

    #include "8svxinstrument.h"
    
    int main(int argc, char *argv[])
    {
        IFF_Chunk *chunk;
        _8SVX_Instrument **instruments;
        unsigned int instrumentsLength;

        /* Open an IFF file and extract 8SVX instruments here */

        if(_8SVX_checkInstruments(chunks, instruments, instrumentsLength))
            return 0; /* IFF file including 8SVX instruments are valid */
        else
            return 1; /* IFF file including 8SVX instruments are not valid */
    }


Command-line utilities
======================
Apart from an API to handle 8SVX files, this package also includes a number of
command-line utilities to make usage of 8SVX files more convenient:

* `8svxpp` can be used to pretty print a 8SVX file into a textual representation, so that it can be manually inspected
* `8svxpack` can be used to compress or decompress all 8SVX instruments in an IFF file.

Consult the manual pages of these tools for more information.
