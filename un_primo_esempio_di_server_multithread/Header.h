#include <sys/types.h>

#define RICHIESTE 5
#define CLIENT 3

/* TBD: Definire una struct per i messaggi dal client al server */

typedef struct {
    long type;
    pid_t pid;
    int val1;
    int val2;
}messaggi_cs;


/* TBD: Definire una struct per i messaggi dal server al client */

typedef struct {
    long type;
    int risultato;
}messaggi_sc;

void client(int id_c, int id_s);
void server(int id_c, int id_s);
void* Prodotto(void*);
