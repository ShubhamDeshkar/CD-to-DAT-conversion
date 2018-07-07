#ifndef _file_source_float_h
#define _file_source_float_h

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
#define FILE_SOURCE_FLOAT_ERROR_ENTRY -1

/* Partial firing status */
#define FILE_SOURCE_FLOAT_VALUE_READ (ACTOR_STATUS_BASE)

typedef struct {
#include "actor_context_type_common.h"
    int active;
    FILE *file;  
    disps_fifo_pointer out;
} file_source_float_context_type;


file_source_float_context_type *file_source_float_new(FILE *file, disps_fifo_pointer out,int vector);

void file_source_float_reset(file_source_float_context_type *context);

void file_source_float_execute(file_source_float_context_type *context); 

void file_source_float_execute_new(file_source_float_context_type *context);

void file_source_float_terminate(file_source_float_context_type *context);

#endif
