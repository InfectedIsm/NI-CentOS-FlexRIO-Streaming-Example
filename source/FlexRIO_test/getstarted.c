#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "getstarted.h"


//DONE
void *getStarted_AcquireAndWriteThread(void *arg)
{
    int i;
    FILE *fp;

    char buf[100];
    // each thread have its own file
    snprintf(buf, sizeof(buf), "data_%s.txt",(char*)arg);

    fp = fopen(buf, "w");

    for (i = 0; i < 5 ; i++){
        printf ("writing in file %s: %d\n", (char*)arg, i);
        fprintf (fp, "%d\n", i);
        sleep (1);
    }

    // while (!stop)
    // {
    //     readState = niFlexRIO_Acquire_Read_Region(); //!\\this function does not exists
    //     getStarted_WriteToFile();//----------------------------------------//TO DEVELOP
    // }
    // getStarted_StopStream()
    fclose(fp);
    pthread_exit (0);
}

//Used in getStarted_AcqConfigureDualChannel
int coerce(double value, double min, double max)
{
    double result = 0;
    if (value < min) result = min;
    else if (value > max) result = max;
    else result = value; 

    return result;
}

//DONE
int getStarted_AcqConfigureDualChannel(double centerFreq, double IQrate, 
                                double* actualCenterFreq, double* actualIQrate)
{
    double maximumIQrate           = 500e6;
    double maximumDecimationFactor = 65536;
    double IQrateToHalfIBW         = 0.4;
    double ADCsamplingRate         = 1e9;

    double div, out_a1, out_a2 = 0;
    double integer_part, fractional_part, out_b1, out_b2, out_b3, out_b4, out_b5, out_b6 ;
    int outsideNyquistBand = 0;

    ///a part
    // div still need to be converted to <+,48,1> 
    div = ( coerce(IQrate, maximumIQrate/maximumDecimationFactor, maximumIQrate) / maximumIQrate );

    out_a1 = maximumIQrate * div;
    * actualIQrate = out_a1 ;

    out_a2 = out_a1 * IQrateToHalfIBW;


    ///b part
    integer_part = (double) ((int) ( centerFreq / ADCsamplingRate ));
    fractional_part = ( centerFreq / ADCsamplingRate ) - integer_part;

    //if there's no integer part, out_b1 is negative
    out_b1 = (- fractional_part) * (- ADCsamplingRate);

    out_b2 = integer_part * ADCsamplingRate;

    if ( out_b1 >= 0 )  out_b3 = out_b1;    
    else                out_b3 = out_b1 + ADCsamplingRate;

    out_b4 = out_b2 + out_b3;
    * actualCenterFreq = out_b4;

    out_b5 = ((int) ( out_b4 / (ADCsamplingRate/2) )) * (ADCsamplingRate/2);  

    out_b6 = out_b5 + ADCsamplingRate/2;


    outsideNyquistBand = ( (out_b4 - out_a2) < (out_b5) ) || ( (out_b4 + out_a2) > (out_b6) ) ;

    if (outsideNyquistBand)
    {
        fprintf (stderr, "error : The requested band crosses a Nyquist frequency.\n Program terminated\n");
        exit(1);
    }

return outsideNyquistBand;
}

//is needed ? as the file is already created in getStarted_AcquireAndWriteThread
int getStarted_CreateFile()
{

return 0;
}

int getStarted_ConfigureStreams()
{

return 0;
}

int getStarted_ClearStream()
{

return 0;
}
int getStarted_StartStream()
{

return 0;
}

int getStarted_WriteToFile()
{

return 0;
}

int getStarted_StopStream()
{

return 0;
}

// for testing purpose

// int main()
// {
//     double iq = 0;
//     double freq = 0;
//     int outside = 0;

//     outside = getStarted_AcqConfigureDualChannel(4e8, 1e5, &freq, &iq);
//     printf("iq=%.1f freq=%.1f outside=%d\n", iq, freq, outside);

//     return 0;
// }