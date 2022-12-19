#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

#include "Header.h"

/* Il thread padre condivide l'id della coda 
   delle risposte con i figli, tramite una 
   variabile globale */

int id_coda_risposte;

pthread_mutex_t mutex;


void server(int id_c, int id_s){

	int k;
	int ret;

	id_coda_risposte = id_s;

	pthread_mutex_init(&mutex, NULL);


	while(1){

		/* TBD: Ricevere un messaggio di richiesta dal client */

		messaggi_cs * msg_cs = (messaggi_cs *)malloc(sizeof(messaggi_cs));
	
		ret = msgrcv(id_c, &msg_cs, sizeof(messaggi_cs) - sizeof(long), 0, 0);   /* TBD */

		if(ret < 0) {
			perror("Errore ricezione richiesta server");
			exit(1);
		}

		if( /* TBD */ msg_cs->val1== -1 && /* TBD */ msg_cs->val2 == -1){

			/* Il processo esce quando si riceve un messaggio di terminazione,
			   con i valori {-1, -1}
			 */

			
			exit(0);
		}

		/* TBD: Avviare un thread figlio per l'elaborazione del messaggio,
				passandogli una **copia sullo heap** del messaggio ricevuto.
				(ogni thread figlio deve elaborare un messaggio diverso)
		 */

		pthread_t thread;

		pthread_create(&thread, NULL, Prodotto, msg_cs);

	}

}



void* Prodotto(void* v){

	int ret;

	messaggi_cs *c = (messaggi_cs*)malloc(sizeof(messaggi_cs));
	messaggi_sc msg_sc;

	 /* TBD: Calcolare il prodotto */
	int v3 = (c->val1 * c->val2);
	
	msg_sc.risultato = v3;

	/* TBD: Inviare il messaggio di risposta al client.
	        Si chiami la funzione msgsnd() all'interno di una
			sezione critica.
	 */

	pthread_mutex_lock(&mutex);

	printf("\nSono Prodotto di Server. Invio del calcolo: %d\n\n", v3);  

	ret = msgsnd(id_coda_risposte, &msg_sc, sizeof(messaggi_sc) - sizeof(long), 0);/* TBD */

	if(ret < 0) {
		perror("Errore invio risposta server");
		exit(1);
	}

	pthread_mutex_unlock(&mutex);

	pthread_exit(NULL);
}

