#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("P1: %d\n", getpid());
    if (fork()==0) {        //P3
        sleep(4);
        printf("P3: %d\n", getpid());
        if (fork()==0) {    //P6
            printf("P6: %d\n", getpid());
            exit(6);
        }
        wait(0);
        sleep(1);
        printf("P8: %d\n", getpid());
        exit(3);
    }
    else {                  //P2
        printf("P2: %d\n", getpid());
        if (fork()==0) {    //P5
            sleep(1);
            printf("P5: %d\n", getpid());
            exit(5);
        }
        else {              //P4
            printf("P4: %d\n", getpid());
            sleep(2);
            wait(0);
        }
        printf("P7: %d\n", getpid());
        sleep(7);
        wait(0);
        printf("P9: %d\n", getpid());
    }

    return 0;
}


/*

Esercizio 03
Grafo di precedenza
-------------------

Utilizzando le system call fork e wait, realizzare il seguente
grafo di precedenza.

        P1
       /  \
      /    \
    P2      P3
    /\      /\
   /  \    /  \
 P4   P5  |   P6
   \  /    \  /
    \/      \/
    P7      P8
      \    /
       \  /
        P9

Si osservi che tutti gli archi sono orientati verso il basso.
Ogni processo Pi corrisponda a un messaggio di stampa
(si stampi la stringa "Pi" e il PID del processo).

Verificare le precedenza siano rispettate inserendo delle
system call sleep nei vari rami del programma.

 */