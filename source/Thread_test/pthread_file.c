#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *myThreadProcess ( void * arg)
{
    int i;
    FILE *fp;

    char buf[100];
    // each thread have its own file
    snprintf(buf, sizeof(buf), "output_%s.txt",(char*)arg);

    fp = fopen(buf, "w");

    for (i = 0; i < 5 ; i++){
        printf ("writing in file %s: %d\n", (char*)arg, i);
        fprintf (fp, "%d\n", i);
        sleep (1);
    }
    fclose(fp);
    pthread_exit (0);
 }

 void main (int ac, char **av)
 {
     pthread_t th1, th2;
     void *ret;

     printf("%d\n", ( ( (1 - 2) < (-5) ) || ( (1 + 2) > (5) ) ) );

    if (pthread_create(&th1, NULL, myThreadProcess, "1") < 0 ){
        fprintf (stderr, "pthread_create error of thread 1\n");
        exit (1);
     }
    if (pthread_create(&th2, NULL, myThreadProcess, "2") < 0 ){
        fprintf (stderr, "pthread_create error of thread 2\n");
        exit (1);
     }

     (void)pthread_join (th1, &ret);
     (void)pthread_join (th2, &ret);
 }