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
#include "wav_file_source.h"
#include "wav_file_sink.h"
#include "fir.h"
#include "util.h"

#define BUFFER_CAPACITY 40736 

/* An enumeration of the actors in this application. */
#define ACTOR_SOURCE 0
//#define ACTOR_XSOURCE 1
//#define ACTOR_YSOURCE 2
#define ACTOR_FIR_1 1 
#define ACTOR_FIR_2 2 
#define ACTOR_FIR_3 3 
#define ACTOR_FIR_4 4 
#define ACTOR_SINK 5 

/* The total number of actors in the application. */
#define ACTOR_COUNT 6 


/* 
    Usage: driver.exe x_file y_file out_file
*/
int main(int argc, char **argv) {
    FILE *in_file = NULL; 
    FILE *taps_file_f1 = NULL, *taps_file_f24 = NULL, *taps_file_f3 = NULL; 
    //FILE *y_file = NULL; 
    FILE *out_file = NULL; 
    actor_context_type *actors[ACTOR_COUNT];
    actor_context_type *actor = NULL;
    wav_file_source_context_type *in_source = NULL;
    wav_file_sink_context_type *out_source = NULL;
//    file_source_context_type *x_source = NULL;
 //   file_source_context_type *y_source = NULL;
    
    /* Connectivity: fifo1: (m, product), fifo2: (x, product); 
       fifo3: (y, product); fifo4: (product, out) 
    */
    disps_fifo_pointer fifo1 = NULL, fifo2 = NULL, fifo3 = NULL, fifo4 = NULL, fifo5 = NULL;/* fifo3 = NULL, fifo4 = NULL;i*/

    int token_size = 0;
    int i = 0,p;
    int arg_count = 6;
    
    /* actor descriptors (for diagnostic output) */
    char *descriptors[ACTOR_COUNT] = {"insource", "fir1", "fir2", "fir3","fir4" , "sink"}; 
   

    /* Check program usage. */
    if (argc != arg_count) {
        fprintf(stderr, "driver.exe error: arg count");
        exit(1);
    }   

    /* Open the input and output file(s). */
    i = 1;
    in_file = util_fopen(argv[i++], "r"); 
    taps_file_f1 = util_fopen(argv[i++], "r"); 
    taps_file_f24 = util_fopen(argv[i++], "r");
    taps_file_f3 = util_fopen(argv[i++], "r");
  //  x_file = util_fopen(argv[i++], "r"); 
  //  y_file = util_fopen(argv[i++], "r"); 
    out_file = util_fopen(argv[i++], "w"); 

    /* Create the buffers. */
    token_size = sizeof(int);
    fifo1 = disps_fifo_new(BUFFER_CAPACITY, token_size);
    fifo2 = disps_fifo_new(BUFFER_CAPACITY, token_size);
    fifo3 = disps_fifo_new(BUFFER_CAPACITY, token_size);
    fifo4 = disps_fifo_new(BUFFER_CAPACITY, token_size);
    fifo5 = disps_fifo_new(BUFFER_CAPACITY, token_size);

    /* Create and connect the actors. */
    i = 0;
    int interpolation1 = 2,decimation1 = 1, interpolation2 = 4, decimation2 = 3, interpolation3 = 5, decimation3 = 7, interpolation4 = 4, decimation4 = 7,vector1=147*2,vector2=147*2,vector3=98*2,vector4=56*2,vector5=40*2,vector6=160*2; 
    int tapslength1,tapslength2,tapslength3,decPhase = 0; 
    float taps1[500],taps24[500],taps3[500],num;
    int za=0,zb=0,zc=0;
    while(fscanf(taps_file_f1, "%f", &num) == 1){
      taps1[za] = num;
      za++;
     }
    fclose(taps_file_f1);
    tapslength1 = za;
   while(fscanf(taps_file_f24,"%f", &num) == 1){
       taps24[zb] = num;
       zb++;
      }
    fclose(taps_file_f24);
    tapslength2 = zb;
   while(fscanf(taps_file_f3,"%f", &num) == 1){
      taps3[zc] = num;
      zc++;
    }
  fclose(taps_file_f3);
 tapslength3 = zc;

    actors[ACTOR_SOURCE] = 
            (actor_context_type *)(wav_file_source_new(in_file, fifo1,vector1));
    actors[ACTOR_FIR_1] = 
            (actor_context_type *)(fir_new(fifo1, fifo2, tapslength1, taps1 , interpolation1, decimation1, decPhase,vector2));
    actors[ACTOR_FIR_2]= (actor_context_type *)(fir_new(fifo2,fifo3,tapslength2,taps24,interpolation2,decimation2,decPhase,vector3));

    actors[ACTOR_FIR_3]= (actor_context_type *)(fir_new(fifo3,fifo4,tapslength3,taps3,interpolation3,decimation3,decPhase,vector4));

    actors[ACTOR_FIR_4]= (actor_context_type *)(fir_new(fifo4,fifo5,tapslength2,taps24,interpolation4,decimation4,decPhase,vector5));

    actors[ACTOR_SINK] = (actor_context_type *)(wav_file_sink_new(out_file, fifo5,vector6));

    in_source = (wav_file_source_context_type *)(actors[ACTOR_SOURCE]);
    out_source = (wav_file_source_context_type *)(actors[ACTOR_SINK]);

    /* A simple scheduler: keep executing actors until one of the
       sources has finished, and there are no more result tokens
       waiting to be written to the output file. 
    */
    while ((in_source->active) || 
            (disps_fifo_population(fifo5) > 0)) {
        for (i = 0; i < ACTOR_COUNT; i++) {
            actor = actors[i];
            util_execute(actor, descriptors[i]);
        }
    }
  /*while((in_source->active)||(disps_fifo_population(fifo5) > 0)){
//  for(p = 0; p < 147; p++)
 // {
    actor = actors[0];
    util_execute(actor, descriptors[0]);
 //}

 //for(p = 0; p < 147; p++)
//{
  actor = actors[1];
  util_execute(actor, descriptors[1]);
//}

//for(p = 0; p< 98;p++)
//{
actor = actors[2];
util_execute(actor, descriptors[2]);
//}
//for(p = 0; p < 56; p++)
//{
actor = actors[3];
util_execute(actor, descriptors[3]);
//}
//for(p=0;p<40;p++)
//{
actor=actors[4];
util_execute(actor,descriptors[4]);
//}


//for(p=0;p<160;p++)
//{
actor=actors[5];
util_execute(actor,descriptors[5]);


//}
}*/


    /* Normal termination. */
    wav_file_sink_terminate(out_source);
    return 0;
}