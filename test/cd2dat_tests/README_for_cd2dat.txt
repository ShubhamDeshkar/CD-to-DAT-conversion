-------------------------------------------------------------------------------
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
-------------------------------------------------------------------------------

List of required files for the implementation and tests of the CD2DAT application.

fir.c (Implementation file for the multirate FIR)
fir.h (Header file for the multirate FIR)
util.c (Implementation file for the utility functions)
util.h (Header file for the utility functions)
wav_file_source.c (Implementation file for the wave file reader)
wav_file_source.h (Header file for the wave file reader)
wav_file_sink.c (Implementation file for the wave file writer)
wav_file_sink.h (Header file for the wave file writer)
disps_fifo.c (Implementation file for the FIFO ADT)
disps_fifo.h (Header file for the FIFO ADT)
actor.h (Header file for the actor ADT)
actor_context_type_common.h (Header file for the actor ADT)
coefs1.txt (Tap coefficients for the 1st FIR (i.e. FIR1) in the CD2DAT application)
coefs2.txt (Tap coefficients for the 2nd and the 4th FIRs (FIR2 and FIR4) in the CD2DAT application) 
coefs3.txt (Tap coefficients for the 3rd FIR (i.e. FIR3) in the CD2DAT application)
cd.wav (Input file for your tests of CD2DAT application)
correct-dat.wav (Correct output file for your tests of CD2DAT application)
