#include "sensore.h"
#include "aggregatore.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

void aggregatore(int id_coda_sensore, int id_code_collettori[3]) {

    printf("Avvio processo aggregatore...\n");


    /* TBD: Completare questa funzione, avviando un thread scrittore e 3 thread lettori *
     *
     *      Nota: occorre passare ai thread sia il puntatore ad un oggetto-monitor,
     *      sia l'identificativo della coda di messaggi su cui ricevere/inviare.
     */

}


void * thread_lettore(void * x) {

    for(int i=0; i<10; i++) {

        int valore;

        sleep(1);

        /* TBD: Chiamare il metodo "lettura()" del monitor */

        printf("Aggregatore: Invio valore=%d\n", valore);

        /* TBD: Inviare il messaggio */
    }


    pthread_exit(NULL);
}

void * thread_scrittore(void * x) {

    for(int i=0; i<10; i++) {

        printf("Aggregatore: In attesa di messaggi...\n");

        /* TBD: Ricevere il messaggio */

        int valore = /* TBD */

        printf("Aggregatore: Ricevuto valore=%d\n", valore);

        /* TBD: Chiamare il metodo "scrittura()" del monitor */
    }

    pthread_exit(NULL);
}

void lettura(MonitorLS * m, int * valore) {

    /* TBD: Completare il metodo, con la sincronizzazione */


    *valore = m->variabile;

    printf("Aggregatore: Lettura valore=%d\n", *valore);

}

void scrittura(MonitorLS * m, int valore) {
    
    /* TBD: Completare il metodo, con la sincronizzazione */


    printf("Aggregatore: Scrittura valore=%d\n", valore);

    m->variabile = valore;
}