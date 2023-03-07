#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    char str[100];
    int i;

    setbuf(stdout,0);
    fork();
    for (i=0; i<2; i++){
        if (fork()!=0) {
            sprintf (str, "echo system with i=%d", i);
            system (str);
        } else {
            sprintf (str, "exec with i=%d", i);
            execlp ("echo", "myPgrm", str, NULL);
        }
    }
    return (0);
}


/*

Esercizio 01
System call fork, exec, system
-----------------------------

Si riporti l'albero di generazione dei processi a seguito
dell'esecuzione del seguente tratto di codice C.
Si indichi inoltre che cosa esso produce su video e per quale
motivo.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main () {
  char str[100];
  int i;

  setbuf(stdout,0);
  fork();
  for (i=0; i<2; i++){
    if (fork()!=0) {
      sprintf (str, "echo system with i=%d", i);
      system (str);
    } else {
      sprintf (str, "exec with i=%d", i);
      execlp ("echo", "myPgrm", str, NULL);
    }
  }
  return (0);
}

 */