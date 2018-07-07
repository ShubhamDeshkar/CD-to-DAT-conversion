#ifndef _actor_h
#define _actor_h

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

/*******************************************************************************
Definitions that are common across all actors
*******************************************************************************/

/* Standard status indicators: */
#define ACTOR_NEW_FIRING 0
#define ACTOR_FIRING_DONE 1

/* The starting index for actor-specific status indicators that are
related to correct (error-free) operation.
*/
#define ACTOR_STATUS_BASE 2

struct actor_context_struct;

/*****************************************************************************
A pointer to a "actor_execution_function", which is a function that 
executes an actor with a given context.
*****************************************************************************/
typedef void (*actor_execution_function_type)
        (struct actor_context_struct *context);

typedef struct actor_context_struct {
#include "actor_context_type_common.h"
} actor_context_type;

/*******************************************************************************
This is an "abstract class", so we don't have a constructor or descriptor.
*******************************************************************************/

void add_reset(actor_context_type *context);

void actor_execute(actor_context_type *context); 

#endif
