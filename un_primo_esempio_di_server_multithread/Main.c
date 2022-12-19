#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "Header.h"




int main(){

	pid_t pidc, pids;
	int id_c, id_s,i;
	int ret;


	id_c = msgget(IPC_PRIVATE, IPC_CREAT | 0644);/* Ottenere una coda per le richieste dal client al server */

	if(id_c < 0) {
		perror("Errore allocazione coda");
		exit(1);
	}

	id_s = msgget(IPC_PRIVATE, IPC_CREAT | 0644);/* Ottenere una coda per le risposte dal server al client */

	if(id_s < 0) {
		perror("Errore allocazione coda");
		exit(1);
	}



	for(i=0;i<CLIENT;i++){

		/* TBD: Avviare i processi client, chiamando client() */
		pidc = fork();
		
		if(pidc == 0){
			client(id_c, id_s);
			exit(0);
		}
		else if(pidc < 0){
			perror("Errore fork client");
			exit(1);
		}
	}


	pids = fork();

	if(pids<0) {
		perror("Errore fork server");
		exit(1);
	}

	/* TBD: Avviare il processo server, chiamando server() */

	if(pids == 0){
		server(id_c, id_s);
		exit(0);
	}


	/* TBD: Attendere la terminazione dei client */

	for(int i = 0; i < CLIENT; i++){
		wait(NULL);
	}


	/* TBD: Inviare al server il messaggio di terminazione, con i valori {-1, -1} */

	messaggi_cs msg_cs;
	msg_cs.val1 = -1;
	msg_cs.val2 = -1;

	ret = msgsnd(id_c, &msg_cs, sizeof(messaggi_cs) - sizeof(long), 0);   /* TBD */

	if(ret < 0) {
		perror("Errore invio messaggio di terminazione");
		exit(1);
	}

	wait(0);

	/* TBD: Deallocazione code */
	msgctl(id_c, IPC_RMID, NULL);
	msgctl(id_s, IPC_RMID, NULL);

	return 0;

}

