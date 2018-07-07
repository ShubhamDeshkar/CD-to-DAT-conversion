#ifndef _util_h
#define _util_h

#include "wav_file_source.h"
#include "wav_file_sink.h"
#include "fir.h"

#include <stdio.h>

/* Open a file. Exit with an error message if the file cannot
   be opened with the specified mode ("r", "w", etc. as in
   coventional fopen). Otherwise return the file pointer of
   the opened file.
*/
FILE *util_fopen(const char *fname, const char *mode);

/* Wrapper for malloc (memory allocation) that prints an error message exits 
if the requested amount of memory is not available.
*/
void *util_malloc(size_t size);

/* Standard wrapper for executing an actor in this library. */
void util_execute(actor_context_type *context, char *descriptor);

void util_execute1(actor_context_type *context, char *descriptor,int vector);

/* Reset the given actor to have "new firing" status. */
void util_reset(actor_context_type *context);

#endif
