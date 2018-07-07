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

test01 - Unvectorized FLAT schedule
test02 - Unvectorized APGAN schedule
test03 - Vectorized FLAT schedule(vector = 10)
test04 - Vectorized APGAN schedule(vector = 10)


Each test folder has following files:
cd.wav - Input
coefs*.txt - coefficient for filters
correct-dat.wav - correct output
out-dat.wav - contains generated output
correct-output.txt - Empty as out-dat.wav and correct-dat.wav are compared using diff and if there is no difference nothing is passed to stdout.
diagnostics.txt - Diagnostic information
expected-errors.txt - expected errors
runme - runs the test(Compares correct-dat.wav and out-dat.wav using diff)
makeme - makes test
