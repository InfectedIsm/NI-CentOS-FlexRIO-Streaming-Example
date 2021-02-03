#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int i;

main( int ac, char **av)
{
    int pid;

    i = 1;

    if ((pid=fork()) == 0) {
        // Dans le fils
        printf ("Je suis le fils, pid = %d\n", getpid());
        sleep (2);
        printf ("Fin du fils, i = %d !\n", i);
        exit (0);
    }

    else if (pid > 0) {
        // Dans le père
        printf ("Je suis le père, pid = %d\n", getpid());
        sleep (1);
    // modifie la variable

    i = 2;
    printf ("Le père a modifié la variable a %d !\n", i);
    sleep (3);
    printf ("Le père a modifié la variable a %d\n", i);
    exit (0);
    }

    else {
        //erreur
        perror("fork");
        exit(1);
    }


}
