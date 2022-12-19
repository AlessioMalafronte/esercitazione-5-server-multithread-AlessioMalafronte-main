#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

#include "Header.h"

void client(int id_c, int id_s){

	int k;
	int ret;

	srand(getpid());



	for(k=0;k<RICHIESTE;k++){

		/* TBD: Inviare un messaggio di richiesta */

		int v1 = rand()%101;
		int v2 = rand()%101;

		messaggi_cs msg_cs;
		msg_cs.val1 = v1;
		msg_cs.val2 = v2;

		printf("Richiesta %d Inviata (%d, %d) [PID=%ld]\n\n", k, v1, v2, getpid());

		/* TBD */

		ret = msgsnd(id_c, &msg_cs, sizeof(messaggi_cs) - sizeof(long), 0); 

		if(ret < 0) {
			perror("Errore invio richiesta client");
			exit(1);
		}


		/* TBD: Ricevere un messaggio di risposta */

		messaggi_sc msg_sc;

		ret = msgrcv(id_s, &msg_sc, sizeof(messaggi_sc) - sizeof(long), getpid(), 0);
		if(ret < 0) {
			perror("Errore ricezione risposta client");
			exit(1);
		}

		int v3 = msg_sc.risultato;

		printf("Risposta %d Ricevuta (%d) [PID=%ld]\n\n", k, v3, getpid());
	}

}

