#include "util.h"
#include "wav_file_source.h"
#include "wav_file_sink.h"
#include "fir.h"

#include <stdio.h>
#include <stdlib.h>

/* Open a file. Exit with an error message if the file cannot
   be opened with the specified mode ("r", "w", etc. as in
   coventional fopen). Otherwise return the file pointer of
   the opened file.
*/
FILE *util_fopen(const char *fname, const char *mode) {
  FILE *fp;

  if ((fp=fopen(fname, mode))==NULL) {
        fprintf(stderr, "could not open file named '%s' with mode '%s'", 
                fname, mode);
        exit(1);
  }
  return fp;
}

void *util_malloc(size_t size)
{
   void *p;

   if ((p = malloc(size)) != NULL) {
       return(p);
   } 
   else {
       fprintf(stderr, "util_malloc error: insufficient memory");
       exit(1);
   } 
   return NULL;  /*NOTREACHED*/
}

void util_reset(actor_context_type *context) {
    context->status = ACTOR_NEW_FIRING;
}

void util_execute(actor_context_type *context, char *descriptor) {
    int status = 0;

    context->execute(context);

    /* Print diagnostic information. */
    printf("%s visit complete, status: ", descriptor);
    fflush(NULL);
    status = context->status;
    if (status < 0) {
        printf("error");
    } else if (status == ACTOR_NEW_FIRING) {
        printf("new firing");
    } else if (status == ACTOR_FIRING_DONE) {
        printf("firing done");
    } else {
        printf("partial firing (code = %d)", status);
    }
    printf("\n");
    fflush(NULL);
    if (context->status == ACTOR_FIRING_DONE) {
        util_reset(context);
    } else if (context->status < 0) {
        fprintf(stderr, "error in %s execution", descriptor);
	fflush(NULL);
        exit(1);
    }
}
void util_execute1(actor_context_type *context, char *descriptor, int vector)
{

int i;
for(i=0;i<vector;i++)
{
util_execute(context,descriptor);
}
}
