
@ddblock_begin copyright


@ddblock_end copyright

The project is divided into two parts. 

1) FIR 

The first part is DFG implementation of fir(vectorized and unvectorized)

2)CD2DAT
The second part is DFG implementation of CD2DAT(vectorized and unvectorized) using APGAN and FLAT schedule.




Project 1 Technical Report
Team members: Tianshi Li, Vivek Hemchandra
Project 1 requires an FIR implementation to fulfill the task of up sampling the CD input to DAT output. This paper will first illustrate the FIR implementation and then the CD2DAT conversion. 
1. FIR Implementation
The FIR implementation is developed from the original fir.c template. The structure of fir is first finished according to fir.h header file. The fir.c first implements the fir_new function which returns a new pointer of type fir_context_type structure and initializes the relevant parameters (interpolation, decimation, decPhase, etc). In this way a new fir actor can be created. It should be noted that the contents of feedback array and mostRecent variable should be initialized to 0 for proper functioning of the program.
The fir_execute function is implemented in a LWDF execute manner using switch. Initially, this function calculates value of parameters such as phaseLength, length and phase which are to be used later to calculate the output token of fir. The switch statement checks for the current status of the fir. If the fir is in status ACTOR_NEW_FIRING, it will check whether the number of tokens is 0 (which is an indicator of all tokens are consumed) and if the number of tokens is enough for fir actor to fire, that is, equivalent to the decimation rate, the status of fir is changed to FIR_IN_AVAILABLE. If the status of FIR is FIR_IN_AVAILABLE, then the output of fir is calculated according to the logic implemented under this switch case and written into output buffer provided there is space available in the buffer. Once the tokens are written into output buffer, the fir actor changes status to ACTOR_FIRING_DONE, breaks out of switch and returns to calling program.
The driver.c is implemented to initialize the actors and create a firing schedule. For FIR tests, there are three actors involved: file source, fir and file sink. FILE pointers in_file, taps_file, id_file and out_file are used to read input, read filter coefficients, read interpolation and decimation rate and to write output into file respectively. Since all actors are inherited from actor_context_type structure, these actors are first created in their own functions and then casted into actor_context_type for execution. Only the input file source actor is then casted into file_source_float_context_type because the scheduler needs the value of status of input source. In the final scheduler, file source actor, fir actor and file sink actor are fired in sequence in a while loop. This while loop monitors the value of input source status and the population of tokens in the output buffer. If file source is in new firing state and no tokens left in output buffer, system will terminate the scheduler. 
The scheduler used here is a canonical schedule and at the end all actors are terminated using terminate function of each actor.
2. cd2dat
The implementation of cd2dat using APGAN and FLAT is similar to the one done in FIR test. Differences are the number of actors and schedulers. There are total 6 actors in cd2dat which are: input wav source, FIR1, FIR2, FIR3, FIR4 and output wav sink. Each FIR has its own interpolation and decimation rates as well as filter coefficients. The input and output in this case is .wav file. The flat scheduler is implemented using 6 sequential for loops to fire each actor the required times. While the apgan scheduler is implemented using 4 nested for loops.
Buffer size:
FLAT schedule:
Size of buffer 1: 147
Size of buffer 2: 294
Size of buffer 3: 392
Size of buffer 4: 280
Size of buffer 5 160
Cumulative buffer Size : 1273
APGAN schedule:
Size of buffer 1: 1
Size of buffer 2: 6
Size of buffer 3: 392
Size of buffer 4: 35
Size of buffer 5: 4

Cumulative Buffer Size: 438

3. Vectorization
Vectorization is done, in case of each actor, by defining a new execute function and extending context of each actor to include a new variable vector. So, each time an actor is executed, the newly defined execute function is called which executes the old execute function vector number of times which is done using a for loop. Vectorization reduces number of context switches by factor v(where v is vector value).

