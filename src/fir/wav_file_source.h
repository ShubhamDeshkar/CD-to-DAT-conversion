#ifndef _wav_file_source_h
#define _wav_file_source_h

/*******************************************************************************
@ddblock_begin copyright

Copyright (c) 1999-2010
Maryland DSPCAD Research Group, The University of Maryland at College Park 

Permission is hereby granted, without written agreement and without
license or royalty fees, to use, copy, modify, and distribute this
software and its documentation for any purpose, provided that the above
copyright notice and the following two paragraphs appear in all copies
of this software.

IN NO EVENT SHALL THE UNIVERSITY OF MARYLAND BE LIABLE TO ANY PARTY
FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES
ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF
THE UNIVERSITY OF MARYLAND HAS BEEN ADVISED OF THE POSSIBILITY OF
SUCH DAMAGE.

THE UNIVERSITY OF MARYLAND SPECIFICALLY DISCLAIMS ANY WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE SOFTWARE
PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND THE UNIVERSITY OF
MARYLAND HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,
ENHANCEMENTS, OR MODIFICATIONS.

@ddblock_end copyright
*******************************************************************************/

#include "actor.h"
#include "disps_fifo.h"

/* Invalid entry status. */
#define WAV_FILE_SOURCE_ERROR_ENTRY -1

/* Partial firing status */
#define WAV_FILE_SOURCE_VALUE_READ (ACTOR_STATUS_BASE)

typedef struct {
#include "actor_context_type_common.h"
    int active;
    FILE *file;  

    /* Actor interface ports. */
    disps_fifo_pointer out;

    /* WAVE PCM soundfile format */
    /* "RIFF" file description header */
    char id1[5];

    /* Size of file */
    unsigned int format_size;

    /* "WAVE" description header */
    char id2[5];

    /* "fmt " description header */
    char id3[5];

    /* Size of WAVE section chunck */
    unsigned int format_length;    

    /* WAVE type format */
    short format_tag;

    /* Mono or stereo */
    short channels;

    /* Block alignment */
    short block_align;

    /* Bits per sample */
    short bits_per_sample;

    /* "data" description header */
    char id4[5];

    /* Sample rate */
    unsigned int sample_rate;

    /* Bytes per sec */
    unsigned int avg_bytes_sec;

    /* Size of data chunk */ 
    unsigned int data_size;

} wav_file_source_context_type;

wav_file_source_context_type *wav_file_source_new(FILE *wav_file, disps_fifo_pointer out);

void wav_file_source_execute(wav_file_source_context_type *context); 

void wav_file_source_terminate(wav_file_source_context_type *context);

#endif

