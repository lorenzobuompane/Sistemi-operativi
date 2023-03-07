#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>

#define T 1
#define MAX_STR 100

void manager(int sig) {
    if (sig==SIGUSR2)
        exit(1);
    else
        return;
}
void produttore (pid_t pid, char* str) {
    FILE *fp = fopen("stringa.txt", "w");
    fprintf(stdout, "\nInserire stringa:\n");
    fgets(str, MAX_STR, stdin);
    fprintf(fp, "%d%s\n", getpid(), str);
    fclose(fp);
    sleep(T);
    kill(pid, SIGUSR1);
    return;
}
void consumatore() {
    FILE *fp = fopen("stringa.txt", "r");
    char str[MAX_STR];
    pid_t pid;
    fscanf(fp, "%d", &pid);
    fgets(str, MAX_STR, fp);
    for (int i=0; i<strlen(str); i++){
        if (isalpha(str[i]))
            printf("%c", toupper(str[i]));
        else
            printf("%c", str[i]);
    }
    printf("\n");
    fclose(fp);
    sleep(T);
    kill(pid, SIGUSR1);
    return;
}
void stampaPid(pid_t father, pid_t child1, pid_t child2) {
    printf("0---%d\n", father);
    sleep(T);
    printf("1---%d\n", child1);
    sleep(T);
    printf("2---%d\n", child2);
    sleep(T);
    printf("-----\n");
    sleep(T);
}

int main() {

    signal(SIGUSR1, manager);
    signal(SIGUSR2, manager);

    char str[MAX_STR];
    char end[MAX_STR];
    strcpy(str, "start");

    pid_t child1=-1;
    pid_t child2=-1;
    if ((child1 = fork())!=0) {
        child2 = fork();
    }

    while (1) {
        if (child1 != 0 && child2 != 0) {
            //sono nel padre e non faccio nulla
            wait((int*) 0);
            wait((int*) 0);
            break;
        } else if (child2 == 0) {
            //sono nel figlio F2 colui che conosce anche il PID di F1
            //quindi faccio PRODUTTORE così posso scrivere anche il mio PID nel file
            //stampaPid(father, child1, child2);
            sleep(T);
            produttore(child1, str);
            sscanf(str, "%s", end);     //AGGIUNTO PERCHÈ CON fgets() NON FUNZIONA L'if
            if (strcmp(end, "end")==0) {
                kill(child1, SIGUSR2);
                exit(2);
            }
            pause();
        } else if (child1 == 0){
            //sono nel figlio F1 e non conosco il PID di F2
            //stampaPid(father, child1, child2);
            pause();
            consumatore();
        }
    }
    printf("SONO USCITO\n");
    return 0;
}

/*
Esercizio 04
Segnali e comunicazione mediante file
-------------------------------------

Implementare un programma C che crea due figli, un produttore
e un consumatore.
Il figlio produttore legge da tastiera delle stringhe e le
trasferisce al consumatore.
Il figlio consumatore converte le stringhe in caratteri maiuscoli
e le visualizza su standard output.
L'introduzione della stringa "end" termina entrambi i processi
figli e quindi il processo padre, in sequenza.
Il trasferimento delle stringhe avvenga attraverso file.

Suggerimenti
1) Derivare la soluzione da quella dell'esercizio precedente
2) I processi che comunicano non sono padre e figlio ma due
   "fratelli"; quindi occorre fare in modo che ciascun
   figlio conosca il PID del processo "fratello".
 */