//OpenMP header
#include <omp.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int nthreads, tid;
    
    
    // Begin of parallel region
    #pragma omp parallel private(nthreads, tid) num_threads(4) for
    {
        int channel=0;
        //Getting thread number
        tid = omp_get_thread_num();
        printf( "Welcome to GFG from thread = %d\n",
                tid);
        printf("Channel is equal to = %d\n", channel);
        channel =+ 5;

        if (tid == 0) {

            //Only master thread does this
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n",
                    nthreads);   
        }
    }

}