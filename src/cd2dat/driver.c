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

#include "disps_fifo.h"
#include "file_source_float.h"
#include "file_sink_float.h"
#include "fir.h"
#include "util.h"

#define BUFFER_CAPACITY 1024

/* An enumeration of the actors in this application. */
#define ACTOR_SOURCE 0
//#define ACTOR_XSOURCE 1
//#define ACTOR_YSOURCE 2
#define ACTOR_FIR 1 
#define ACTOR_SINK 2 

/* The total number of actors in the application. */
#define ACTOR_COUNT 3 


/* 
    Usage: driver.exe in_file taps_file out_file
*/
int main(int argc, char **argv) {
    FILE *in_file = NULL; 
    FILE *taps_file = NULL; 
    //FILE *y_file = NULL; 
    FILE *out_file = NULL; 
    actor_context_type *actors[ACTOR_COUNT];
    actor_context_type *actor = NULL;
    file_source_float_context_type *in_source = NULL;
//    file_source_context_type *x_source = NULL;
 //   file_source_context_type *y_source = NULL;
    
    /* Connectivity: fifo1: (m, product), fifo2: (x, product); 
       fifo3: (y, product); fifo4: (product, out) 
    */
    disps_fifo_pointer fifo1 = NULL, fifo2 = NULL;/* fifo3 = NULL, fifo4 = NULL;i*/

    int token_size = 0;
    int i = 0;
    int arg_count = 4;
    
    /* actor descriptors (for diagnostic output) */
    char *descriptors[ACTOR_COUNT] = {"insource", "fir" , "sink"}; 
   

    /* Check program usage. */
    if (argc != arg_count) {
        fprintf(stderr, "driver.exe error: arg count");
        exit(1);
    }   

    /* Open the input and output file(s). */
    i = 1;
    in_file = util_fopen(argv[i++], "r"); 
    taps_file = util_fopen(argv[i++], "r"); 
  //  x_file = util_fopen(argv[i++], "r"); 
  //  y_file = util_fopen(argv[i++], "r"); 
    out_file = util_fopen(argv[i++], "w"); 

    /* Create the buffers. */
    token_size = sizeof(int);
    fifo1 = disps_fifo_new(BUFFER_CAPACITY, token_size);
    fifo2 = disps_fifo_new(BUFFER_CAPACITY, token_size);
//    fifo3 = disps_fifo_new(BUFFER_CAPACITY, token_size);
//    fifo4 = disps_fifo_new(BUFFER_CAPACITY, token_size);

    /* Create and connect the actors. */
    i = 0;
    int tapslength,decPhase = 0,interpolation = 1,decimation = 3; 
    float taps[100],num;
    int z=0;
    while(fscanf(taps_file, "%f", &num) > 0){
      taps[z] = num;
      z++;
     }
    fclose(taps_file);
    tapslength = z;

    actors[ACTOR_SOURCE] = 
            (actor_context_type *)(file_source_float_new(in_file, fifo1));
   /* actors[ACTOR_XSOURCE] = 
            (actor_context_type *)(file_source_new(x_file, fifo2));*/
   /* actors[ACTOR_YSOURCE] = 
            (actor_context_type *)(file_source_new(y_file, fifo3));*/
    actors[ACTOR_FIR] = 
            (actor_context_type *)(fir_new(fifo1, fifo2, tapslength, taps , interpolation, decimation, decPhase));

    actors[ACTOR_SINK] = (actor_context_type *)(file_sink_float_new(out_file, fifo2,NULL,sizeof(int)));

    in_source = (file_source_float_context_type *)(actors[ACTOR_SOURCE]);
   // x_source = (file_source_context_type *)(actors[ACTOR_XSOURCE]);
   // y_source = (file_source_context_type *)(actors[ACTOR_YSOURCE]);

    /* A simple scheduler: keep executing actors until one of the
       sources has finished, and there are no more result tokens
       waiting to be written to the output file. 
    */
    while ((in_source->active) || 
            (disps_fifo_population(fifo2) > 0)) {
        for (i = 0; i < ACTOR_COUNT; i++) {
            actor = actors[i];
            util_execute(actor, descriptors[i]);
        }
    }

    /* Normal termination. */
    return 0;
}
