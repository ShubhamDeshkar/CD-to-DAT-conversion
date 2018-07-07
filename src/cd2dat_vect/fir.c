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
#include <math.h>
#include "fir.h"
#include "util.h"

/* CREATE implementations for the functions of fir_new and fir_reset. */
fir_context_type *fir_new(disps_fifo_pointer in, disps_fifo_pointer out, int tapslength, float *taps, int interpolation, int decimation, int decPhase,int vector)
{

fir_context_type *context=NULL;


context = util_malloc(sizeof(fir_context_type));
context->execute = (actor_execution_function_type)fir_execute_new;
context->status = ACTOR_NEW_FIRING;
context->in = in; 
context->out = out; 
context->tapsLength = tapslength;
context->interpolation = interpolation;
context->decimation = decimation;
context->decPhase = decPhase; 
context->taps = taps;
context->vector = vector;

context->feedback = util_malloc((context->decimation + context->tapsLength + 50 )*sizeof(float));
context->mostRecent = 0;
int i;
for (i=0 ; i<=(context->decimation + context->tapsLength ) ; i++)
{
context->feedback[i] = 0;
}
return context;
}
/* Modify the function of fir_execute. */
void fir_execute(fir_context_type *context) {
    
    int phaseLength = (int)(context->tapsLength / context->interpolation);
    int length = phaseLength + context->decimation;
    int phase = context->decimation - context->decPhase - 1;
    int i,j;

    if ((context->tapsLength % context->interpolation) != 0) {
      phaseLength++;
    }

    /* CREATE THE FOLLOWING CODE INTO LWDF PHASES - check fir.h and actor.h for
     * phases to be included. */
    /* ADD NEW CODE HERE */
    
    /* check if at least decimation number of tokens are availible on input edge*/
    /* ADD NEW CODE HERE */
    switch(context->status){
    case ACTOR_NEW_FIRING:
        if(disps_fifo_population(context->in) == 0){
          return;
         }
/*        if(disps_fifo_population(context->in) >= context->decimation){
          context->status = FIR_IN_AVAILABLE;
          }*/


          if(disps_fifo_population(context->in) >= disps_fifo_capacity(context->in)){
           return;
               }
            if(disps_fifo_population(context->in) < context->decimation){
               return;
             }
            context->status= FIR_IN_AVAILABLE;


    case FIR_IN_AVAILABLE: 

    for (j=0; j<context->decimation; j++) {
      if (--(context->mostRecent) < 0) {
	(context->mostRecent) = length -1;
      }
      /* 1 token is read into feedback[(context->mostRecent)]. */
      /* ADD NEW CODE HERE */

    disps_fifo_read(context->in,&(context->feedback[context->mostRecent])); 

//    printf("%f\n",context->feedback[0]); 
    
 //   printf("%f\n",context->feedback[1]); 
    
  //  printf("%f\n",context->feedback[2]); 
    
   // printf("%f\n",context->feedback[3]); 

    //printf("%f\n",context->feedback[4]); 

   // printf("%f\n",context->feedback[5]); 
    }    

    for (j=1; j<=context->decimation; j++) {
      while (phase < context->interpolation) {
	float out = 0;
	for (i=0; i<phaseLength; i++) {
	  int tapsIdx = i * context->interpolation + phase;
	  int dataIdx = ((context->mostRecent) + context->decimation - j + i) % (length);
	  if (tapsIdx < context->tapsLength) {
	    out += context->taps[tapsIdx] * context->feedback[dataIdx];
    //        printf("%f\n", out);
	  }
	}
	/* out is pushed onto output edge as 1 token.*/ 
	/* ADD NEW CODE HERE */
        if(disps_fifo_population(context->out) >= disps_fifo_capacity(context->out))
          {
                 return;
          }
        disps_fifo_write(context->out, &out);
	phase += context->decimation;
        }
      phase -=context->interpolation;
}
context->status=ACTOR_FIRING_DONE;

    case ACTOR_FIRING_DONE:
    break;

    default:
    context->status = FIR_ERROR;
    break;
 } 
return;

}

void fir_execute_new(fir_context_type *context){
int i;
for(i=0;i<(context->vector);i++){
context->status=ACTOR_NEW_FIRING;
fir_execute(context);
}
}


void fir_terminate(fir_context_type *context){
free(context);
}




