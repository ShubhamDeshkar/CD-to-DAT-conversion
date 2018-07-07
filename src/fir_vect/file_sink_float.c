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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_sink_float.h"
#include "util.h"

file_sink_float_context_type *file_sink_float_new(FILE *file, disps_fifo_pointer in, char* formatstr, int bytes,int vector) {
    file_sink_float_context_type *context = NULL;

    context = util_malloc(sizeof(file_sink_float_context_type));
    context->execute = (actor_execution_function_type)file_sink_float_execute;
    context->file = file;
    context->status = ACTOR_NEW_FIRING;
    context->in = in;
    context->vector=vector;
    return context;
}

void file_sink_float_execute(file_sink_float_context_type *context) {

  float value = 0;
    switch (context->status) {
    case ACTOR_NEW_FIRING:
        if (disps_fifo_population(context->in) == 0) {
            return;
        }
        disps_fifo_read(context->in, &value);
	fprintf(context->file, "%f\n", value);

	context->status = ACTOR_FIRING_DONE;
        /* falls through */
    case ACTOR_FIRING_DONE:
        break;
    default:
        context->status = FILE_SINK_FLOAT_ERROR_ENTRY;
        break;
    }
}

void file_sink_float_terminate(file_sink_float_context_type *context) {
    fclose(context->file);
    free(context);
}

void file_sink_float_execute_new(file_sink_float_context_type *context){
int i;
for(i=0;i<(context->vector);i++){
context->status=ACTOR_NEW_FIRING;
file_sink_float_execute(context);
}
}
