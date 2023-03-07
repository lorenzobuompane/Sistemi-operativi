#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void process_A();
void process_B();
void process_C();
void process_D();

int main() {
    int process;
    printf("Inserisci numero processo:\n\t0 -> A\n\t1 -> B\n\t2 -> C\n\t3 -> D\n");
    scanf("%d", &process);
    printf("--- \n");

    if (process==0) {
        process_A();
    }
    if (process==1) {
        process_B();
    }
    if (process==2) {
        process_C();
    }
    if (process==3) {
        process_D();
    }
    return 0;
}

void process_A() {
    int i;
    for (i=1; i<=2; i++) {
        if (!fork ())
            printf ("%d\n", i);
    }
    //sleep(2);
    printf ("%d\n", i);
}
void process_B() {
    int i;
    for(i=3; i>1; i--) {
        if (fork ())
            printf ("%d\n", i);
    }
    //sleep(2);
    printf ("%d\n", i);
}
void process_C() {
    int i;
    for (i=0; i<2; i++) {
        if (fork ())
            fork ();
    }
    printf ("%d\n", i);
}
void process_D() {
    int i;
    for (i=2; i>=1; i--) {
        if (!fork ()) {
	    //sleep(1);
            printf ("%d\n", -i);
	}
        else {
            printf ("%d\n", i);
	}
	//sleep(5);
    }
}


/*

Esercizio 01
Analisi di programmi concorrenti
--------------------------------

Rappresentare il grafo di controllo del flusso (CFG)
e l'albero di generazione dei processi dei seguenti
tratti di codice.
Indicare inoltre l'output prodotto su video.
Verificare il risultato predetto tramite esecuzione.

A.
for (i=1; i<=2; i++) {
  if (!fork ())
    printf ("%d\n", i);
}
printf ("%d\n", i);

B.
for(i=3; i>1; i--) {
  if (fork ())
    printf ("%d\n", i);
}
printf ("%d\n", i);

C.
for (i=0; i<2; i++) {
  if (fork ())
    fork ();
}
printf ("%d\n", i);

D.
for (i=2; i>=1; i--) {
  if (!fork ())
    printf ("%d\n", -i);
  else
    printf ("%d\n", i);
}

 */