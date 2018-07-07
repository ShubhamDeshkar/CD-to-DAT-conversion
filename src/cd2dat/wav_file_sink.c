/******************************************************************************
@ddblock_begin copyright

Copyright (c) 1999-2010
Maryland DSPCAD Research Group, The University of Maryland at College Park 
All rights reserved.

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
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav_file_sink.h"
#include "util.h"

/* A wave file writer.
 */
wav_file_sink_context_type *wav_file_sink_new(FILE *file, disps_fifo_pointer
        in) {

    wav_file_sink_context_type *context = NULL;

    context = util_malloc(sizeof(wav_file_sink_context_type));
    context->execute = (actor_execution_function_type)wav_file_sink_execute;
    context->file = file;
    context->status = ACTOR_NEW_FIRING;
    context->in = in;

    strcpy(context->id1, "RIFF");
    context->format_size = 0;
    strcpy(context->id2, "WAVE");    
    strcpy(context->id3, "fmt ");
    context->format_length = 16;    
    context->format_tag = 1;
    context->channels = 1;
    context->block_align = 2;
    context->bits_per_sample = 16;
    strcpy(context->id4, "data");
    context->sample_rate = 48000;
    context->avg_bytes_sec = context->sample_rate*2;
    context->data_size = 0;

    fwrite(context->id1, sizeof(char), 4, context->file);
    fwrite(&context->format_size, sizeof(unsigned int), 1, context->file);
    fwrite(context->id2, sizeof(char), 4, context->file);
    fwrite(context->id3, sizeof(char), 4, context->file);
    fwrite(&context->format_length, sizeof(unsigned int), 1, context->file);
    fwrite(&context->format_tag, sizeof(short), 1, context->file);
    fwrite(&context->channels, sizeof(short), 1, context->file);
    fwrite(&context->sample_rate, sizeof(unsigned int), 1, context->file);
    fwrite(&context->avg_bytes_sec, sizeof(unsigned int), 1, context->file);
    fwrite(&context->block_align, sizeof(short), 1, context->file);
    fwrite(&context->bits_per_sample, sizeof(short), 1, context->file);
    fwrite(context->id4, sizeof(char), 4, context->file);
    fwrite(&context->data_size, sizeof(unsigned int), 1, context->file);

    return context;
}

void wav_file_sink_execute(wav_file_sink_context_type *context) {
    short sample = 0;
    float factor = 32768;
    float value;
    
    switch (context->status) {
    case ACTOR_NEW_FIRING:
        if (disps_fifo_population(context->in) == 0) {
            return;
        }
        disps_fifo_read(context->in, &value);
        sample = (short)(value * factor);
	fwrite(&sample, sizeof(short), 1, context->file);
        context->status = ACTOR_FIRING_DONE;
        /* falls through */
    case ACTOR_FIRING_DONE:
        break;

    default:
        context->status = WAV_FILE_SINK_ERROR_ENTRY;
        break;
    }
}

void wav_file_sink_terminate(wav_file_sink_context_type *context) {
    unsigned int pos = (unsigned int)ftell(context->file);

    context->format_size = pos - 8;
    context->data_size = pos - 44;
    fseek(context->file, 4, SEEK_SET);
    fwrite(&context->format_size, sizeof(unsigned int), 1, context->file);
    fseek(context->file, 40, SEEK_SET);
    fwrite(&context->data_size, sizeof(unsigned int), 1, context->file);

    fclose(context->file);
    free(context);
}

