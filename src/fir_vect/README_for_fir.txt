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

List of required files for the FIR implementation and tests.

fir.c (Implementation file for the multirate FIR)
fir.h (Header file for the multirate FIR)
util.c (Implementation file for the utility functions)
util.h (Header file for the utility functions)
file_source_float.c (Implementation file for the source actor)
file_source_float.h (Header file for the source actor)
file_sink_float.c (Implementation file for the sink actor)
file_sink_float.h (Header file for the sink actor)
disps_fifo.c (Implementation file for the FIFO ADT)
disps_fifo.h (Header file for the FIFO ADT)
actor.h (Header file for the actor ADT)
actor_context_type_common.h (Header file for the actor ADT)
coefs_for_fir_tests.txt (Tap coefficients for the FIR, same for the 3 FIR unit tests)
input_for_fir_tests.txt (Input file for the FIR, same for the 3 FIR unit tests)
correct_output_for_fir_test01.txt (Correct output result for your first unit test of FIR for Interpolation rate: 1, decimation rate: 1)
correct_output_for_fir_test02.txt (Correct output result for your second unit test of FIR for interpolation rate: 1, decimation rate: 3)
correct_output_for_fir_test03.txt (Correct output result for your third unit test of FIR for interpolation rate: 3, decimation rate: 1)
