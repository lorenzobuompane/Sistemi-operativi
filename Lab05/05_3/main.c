#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define T 1

void manager(int sig) {
    return;
}

int main() {

    signal(SIGUSR1, manager);
    signal(SIGUSR2, manager);

    pid_t pid = fork();

    while (1) {
        if (pid!=0) {
            sleep(T);
            kill(pid, SIGUSR1);
            pause();
            fprintf(stdout, "Father woke-up\n");
        } else {
            pause();
            fprintf(stdout,"Child woke-up\n");
            sleep(T);
            kill(getppid(), SIGUSR2);
        }
    }

    return 0;
}

/*
Esercizio 03
Utilizzo di segnali
-------------------

Scrivere un programma che mediante l'utilizzo di segnali
sincronizzi due processi (un padre e un figlio) in modo che
stampino alternativamente uno specifico messaggio.
Il seguente e' un esempio di output:

Child Woke-up
Father Woke-up
Child Woke-up
Father Woke-up
Child Woke-up
Father Woke-up
Child Woke-up
Father Woke-up
...

Inserire sleep opportune per evitare corse critiche.
 */