#include <stdio.h>
#include <niflexrioapi.h>
#include <pthread.h>
#include "getstarted.h" //change to .h
#include "NiFpga_IF_5764_FPGA.h"
#include "NiFpga.h"

char 	*ressourceName = "NI-5674";
char 	*bitfileName = "Bitfile.lvbitx";
int32_t openSessFlags = 0;


int main()
{
    //each thread is for a fetch+write file
    pthread_t th1, th2;
    void *ret;

    //session holder
	NiFpga_Session 	sess = 0;

    //FlexRIO I/O state variables
	int32_t 		timeout = 0;
	uint32_t 		ioReadyFlag = 0;
	int32_t 		ioError = 0;

    FlexRIO_Status  status = 0;

    // FlexRIO Configuration
    uint32_t trig_instance = 0;

	niFlexRIO_OpenSession	(ressourceName, bitfileName, openSessFlags, 
						&sess);
	niFlexRIO_WaitForIoReady(sess, timeout, &ioReadyFlag,
                    	&ioError);
	niFlexRIO_ConfigureForReferenceClock(sess, kFlexRIO_RefClkSrc_PXI_Clk10);
    niFlexRIO_ConfigureImmediateTrigger(sess, trig_instance);
    niFlexRIO_Commit(sess);

    // Acquisition parameters configuration
    int outsideNyquist;
    double centerFreq = 300e6;
    double IQrate = 10e6;
    double actualCenterFreq, actualIQrate;

    if( outsideNyquist = getStarted_AcqConfigureDualChannel(centerFreq, IQrate, &actualCenterFreq, &actualIQrate) ) {
        exit(1);    //redundant ? as exit is already in the getStarted_Acq function
    }

    //writing to FPGA
    NiFpga_MergeStatus(&status, NiFpga_WriteU64(sess,
                                                NiFpga_IF_5764_FPGA_ControlFxp_frequencyshift_Resource,
                                                actualCenterFreq/500e6));       //scaled for Flex
    NiFpga_MergeStatus(&status, NiFpga_WriteU64(sess,
                                                NiFpga_IF_5764_FPGA_ControlFxp_outputsamplerate_Resource,
                                                actualIQrate/1e9));             //scaled for Flex
    
    getStarted_CreateFile();//--------------------------------------------//TO DEVELOP

    getStarted_ConfigureStreams();//----------------------------------------//TO DEVELOP

    /*Clears samples from the stream. Will be based on C_API_Interface communication
    through R/W controls as the functions does not exists in C*/ 
    getStarted_ClearStream();//--------------------------------------------//TO DEVELOP                
    getStarted_StartStream();//--------------------------------------------//TO DEVELOP


    //fetch and write threads creation
    if (pthread_create(&th1, NULL, getStarted_AcquireAndWriteThread, "AI1_AI2") < 0 ){
        fprintf (stderr, "pthread_create error of thread 1\n");
        exit (1);
     }
    if (pthread_create(&th2, NULL, getStarted_AcquireAndWriteThread, "AI3_AI4") < 0 ){
        fprintf (stderr, "pthread_create error of thread 2\n");
        exit (1);
     }
    //starting the threads
    (void)pthread_join (th1, &ret);
    (void)pthread_join (th2, &ret);
    

	return 0;   
}





