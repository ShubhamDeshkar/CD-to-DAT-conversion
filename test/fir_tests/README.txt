@ddblock_begin copyright
Vivek Hemchandra's Copyright txt 
Copyright (c) 1999-2014
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

Unvectorized FIR:

test01 - fir test with decimation and interpolation rate 1

test02 - fir test with interpolation rate 1 and decimation rate 3

test03 - fir test with interpolation rate 3 and decimation rate 1

Vectorized FIR:

test04 - fir test with interpolation and decimation rate 2 and vector=1

test05 - fir test with interpolation and decimation rate 2 and vector=2

test06 - fir test with interpolation and decimation rate 1 and vector=1


Each test folder contains following files:
coefs_for_fir_tests.txt - tap coefficients of folder
correct-output.txt - correct output
diagnostics.txt- diagnostic inforimation
expected_errors.txt - expected errors
id.txt - contains interpolation and decimation rates
input_for_fir_tests - input for fir
out.txt - output generated 
makeme - make file
runme - run script for test

