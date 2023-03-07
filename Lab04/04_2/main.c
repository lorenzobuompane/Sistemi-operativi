#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int i = 0;

    setbuf(stdout,0);
    while (i<=2 && fork()){
        if (!fork()) {
            fprintf (stdout, "Running Exec ...");
            execlp ("echo", "echo", "i*i", (char *) 0);
        }
        i++;
        fprintf (stdout, "Running System ...");
        system ("echo i+i");
    }

    return (0);
}

/*

Esercizio 02
System call fork, exec, system
------------------------------

Si riporti l'albero di generazione dei processi a seguito
dell'esecuzione del seguente tratto di codice C.
Si indichi inoltre che cosa esso produce su video e per quale
motivo.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main () {
  int i = 0;

  setbuf(stdout,0);
  while (i<=2 && fork()){
    if (!fork()) {
      fprintf (stdout, "Running Exec ...");
      execlp ("echo", "echo", "i*i", (char *) 0);
    }
    i++;
    fprintf (stdout, "Running System ...");
    system ("echo i+i");
  }

  return (0);
}

 */