#ifndef _fir_h
#define _fir_h

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
#include<stdlib.h>
#include "actor.h"
#include "disps_fifo.h"

#define FIR_ERROR -1

/* Partial firing status indicators. */
#define FIR_IN_AVAILABLE (ACTOR_STATUS_BASE)

typedef struct {
#include "actor_context_type_common.h"
  /* input ports */
  disps_fifo_pointer in;

  /* output port */
  disps_fifo_pointer out;

  /* Persistent local variables */
  int tapsLength;    /*number of taps in FIR*/
  float *taps;       /*pointer to the array of taps*/
  float *feedback;   /*pointer to an array of the past and current inputs, up
						to taplength+decimation samples ago, should be malloced
						and each element initialiazed to zero */
  int mostRecent;    /*the index of the most recent input sample in
				   	    the array feedback, should be initialized in
				   	    the constructor to 0 */
  int interpolation; /*interpolation rate*/
  int decimation;    /*decimation rate*/
  int decPhase;      /*decimation phase, set to zero for the purposes
		   			    of project 1*/  

} fir_context_type;

fir_context_type *fir_new(disps_fifo_pointer in, disps_fifo_pointer out, int tapslength, float *taps, int interpolation, int decimation, int decPhase);


void fir_execute(fir_context_type *context);

void fir_terminate(fir_context_type *context);

/* The reset method is part of util, so it does not need to be implemented */

#endif

