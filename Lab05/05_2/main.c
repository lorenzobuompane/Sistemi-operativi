#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {

    int fp=open(argv[1], O_RDONLY);

    if (fp<0) {
        fprintf(stderr, "Errore nell'apertura del file\n");
        return -1;
    }
    int  i, j;
    int v[100], val;

    //READ ELEMENT NUMBER
    int n;
    read(fp, &n, sizeof(int));
    fprintf(stdout,"%d", n);
    /*
    pid_t father = getpid();
    for (i=0; i<n-1; i++) {
        for (j=0; j<n-1-i; j++) {
            if (getpid()==father) {
                if (!fork()) {
                    if (v[j] > v[j+1]) {
                        val = v[j];
                        v[j] = v[j+1];
                        v[j+1] = val;
                    }
                 }

            }
        }
    }
     */
    close(fp);
    return 0;
}

/*
Esercizio 02
Exchange-sort concorrente su file
---------------------------------

Premessa numero 1.
L'algoritmo di ordinamento per scambio (exchange-sort o
bubble-sort) ordina un vettore mediante il confronto di
elementi contigui.
La seguente e' una possibile implementazione (con ordinamento
del vettore v di n elementi):

for (i=0; i<n-1; i++) {
  for (j=0; j<n-1-i; j++) {
    if (v[j] > v[j+1]) {
       val = v[j];
       v[j] = v[j+1];
       v[j+1] = val;
    }
  }
}

Premessa numero 2.
Un  file binario puo' essere scritto (funzione UNIX write)
e letto (funzione unix read) in maniera casuale utilizzando
la funzione lseek.

Ad esempio, il programma
lab05ex02.c
una volta ricevuto il nome di un file sulla riga di comando,
- scrive nel file il vettore vet di 12 elementi
- rilegge il file a partire dall'ultima riga.

Specifiche dell'esercizio.
Si implementi in maniera *concorrente* e *multi-processo*
l'algortimo di bubble-sort.
L'algoritmo, utilizzando le system call fork e wait e
condividendo dati su file (i.e., leggendo e scrivendo dati sullo
stesso file) deve effettuare l'ordinamento del file stesso.

Il programma (il padre):
- riceve sulla riga di comando il nome di un file contenente
  un numero predefinito n di interi.
- a ogni iterazione del ciclo esterno "simula" l'azione
  del ciclo interno generando (n-1-i) processi figlio.

Ognuno dei figli
  - legge due elementi adiacenti nel file
  - ne effettua lo scambio qualora necessario
  - li riscrive su file
  - si sincronizza con gli altri processi figli per
    generare l'effetto globale di ordinamento (i.e.,
    a ogni iterazione del ciclo esterno il valore
    maggiore tra quelli rimanenti, viene spostato in
    fondo al file)
  - termina.

Osservazioni
------------

1. Operare su file e' indispensabile in quanto un processo padre
   e uno figlio non condividono lo spazio di indirizzamento (quindi
   ordinando un vettore, ordinerebbero di fatto vettori diversi).
2. Il programma puo' essere generalizzato facendo in modo che
   il primo degli interi memorizzati su file indichi il numero
   di interi successivi presenti nel file.
3. Gestire un file binario semplifica il posizionamento
   sul dato di posizione i.
   Infatti, nel caso di file ASCII, il numero di caratteri occupati
   da un intero non sarebbe costante, come nel caso di file binari,
   ma dipenderebbe dal suo valore:
   - 5 -> codifica ASCII = 1 carattere
       -> codifica binaria = sizeof (int) byte,
   - 12345 -> codifica ASCII = 5 caratteri
           -> codifica binaria = sizeof (int) byte
   Inoltre nel primo caso occorrerebbe contare anche caratteri
   "aggiuntivi", quali il '\n' di fine riga.
 */