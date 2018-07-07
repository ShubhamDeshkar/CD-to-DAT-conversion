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

#include "file_source_float.h"
#include "util.h"

file_source_float_context_type *file_source_float_new(FILE *file, disps_fifo_pointer out,int vector) {
    file_source_float_context_type *context = NULL;

    context = util_malloc(sizeof(file_source_float_context_type));
    context->execute = (actor_execution_function_type)file_source_float_execute_new;
    context->file = file;
    context->active = 1;
    context->status = ACTOR_NEW_FIRING;
    context->out = out;
    context->vector=vector;
    return context;
}

void file_source_float_execute(file_source_float_context_type *context) {
    float value = 0;

    if (!context->active) {
        return;
    }
    
    switch (context->status) {
    case ACTOR_NEW_FIRING:
        if (fscanf(context->file, "%f", &value) != 1) { 
            /* End of input */
            context->active = 0;
            return;
        } 
        context->status = FILE_SOURCE_FLOAT_VALUE_READ;
        /* falls through */
    case FILE_SOURCE_FLOAT_VALUE_READ:
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
        context->status = FILE_SOURCE_FLOAT_ERROR_ENTRY;
        break;
    }
}

void file_source_float_terminate(file_source_float_context_type *context) {
    fclose(context->file);
    free(context);
}

void file_source_float_execute_new(file_source_float_context_type *context){
int i;
for(i=0;i<(context->vector);i++){
context->status=ACTOR_NEW_FIRING;
file_source_float_execute(context);
}
}

