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

#include "wav_file_source.h"
#include "util.h"

/* A wave file reader.
 */
wav_file_source_context_type *wav_file_source_new(FILE *file,
        disps_fifo_pointer out,int vector) {

    wav_file_source_context_type *context = NULL;
    
    context = util_malloc(sizeof(wav_file_source_context_type));
    context->execute = (actor_execution_function_type)wav_file_source_execute_new;    
    context->file = file;
    context->active = 1;
    context->status = ACTOR_NEW_FIRING;
    context->out = out;
    context->vector = vector;

    fread(context->id1, sizeof(char), 4, context->file);
    if (strcmp(context->id1, "RIFF")) {
        context->status = WAV_FILE_SOURCE_ERROR_ENTRY;
        context->active = 0;
    }
    fread(&context->format_size, sizeof(unsigned int), 1, context->file);	
    fread(context->id2, sizeof(char), 4, context->file);
    if (strcmp(context->id2, "WAVE")) {
        context->status = WAV_FILE_SOURCE_ERROR_ENTRY;
        context->active = 0;
    }
    fread(context->id3, sizeof(char), 4, context->file);
    if (strcmp(context->id3, "fmt ")) {
        context->status = WAV_FILE_SOURCE_ERROR_ENTRY;
        context->active = 0;
    }
    fread(&context->format_length, sizeof(unsigned int), 1, context->file);
    fread(&context->format_tag, sizeof(short), 1, context->file);
    fread(&context->channels, sizeof(short), 1, context->file);
    fread(&context->sample_rate, sizeof(unsigned int), 1, context->file);
    fread(&context->avg_bytes_sec, sizeof(unsigned int), 1, context->file);
    fread(&context->block_align, sizeof(short), 1, context->file);
    fread(&context->bits_per_sample, sizeof(short), 1, context->file);
    fread(context->id4, sizeof(char), 4, context->file);
    if (strcmp(context->id4, "data")) {
        context->status = WAV_FILE_SOURCE_ERROR_ENTRY;
        context->active = 0;
    }
    fread(&context->data_size, sizeof(unsigned int), 1, context->file);

    return context;
}

void wav_file_source_execute(wav_file_source_context_type *context) {
    short sample;
    float factor = 32768;
    float value;

    if (!context->active) {
      return;
    }

    switch (context->status) {
    case ACTOR_NEW_FIRING:

      if(fread(&sample, sizeof(short), 1, context->file)<1) {
	    context->active = 0;
    	    return;
        }
    	/* normalization */
	value = (float)sample / factor;

        context->status = WAV_FILE_SOURCE_VALUE_READ;

        /* falls through */      
    case WAV_FILE_SOURCE_VALUE_READ:
        if (disps_fifo_population(context->out) >= 
                disps_fifo_capacity(context->out)) {
            return;
        }

        disps_fifo_write(context->out, &value);

        context->status = ACTOR_FIRING_DONE;
        
        /* falls through */
    case ACTOR_FIRING_DONE:
        break;

    default:
        context->status = WAV_FILE_SOURCE_ERROR_ENTRY;
        break;
    }
}

void wav_file_source_terminate(wav_file_source_context_type *context) {
    fclose(context->file);
    free(context);
}
void wav_file_source_execute_new(wav_file_source_context_type *context){
int i;
for(i=0;i<(context->vector);i++){
context->status=ACTOR_NEW_FIRING;
wav_file_source_execute(context);
}
}

