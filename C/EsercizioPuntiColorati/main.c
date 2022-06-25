#include <stdio.h>
#include <stdlib.h>

struct TipoPunto {
    char colore[10];
    int valX; /* valX -> il valore dell'ascissa in cui si trova il punto  */
    int valY; /* valY -> il valore delle ordinate in cui si trova il punto */
};
typedef struct TipoPunto TipoElem;

typedef struct TipoNodo{
    TipoElem info;
    struct TipoNodo *next;
} TipoNodo;
typedef struct TipoNodo * TipoLista;

void buildFromFile(TipoLista * , char *); /* consente di formare la lista con i dati caricati dal file */
void stampaLista(TipoLista); /* stampa tutti gli elementi della lista */
void maxAscissa(TipoLista); /* trova il valore massimo della x fra tutta la lista */
void readFromFile(FILE * , TipoElem *); /* prende gli elementi dal file e li trasferisce nella lista */
void addElemToLista(TipoLista * , TipoElem); /* aggiunge gli elementi alla lista */


int main() {
    /* ~~ TipoLista || TipoNodo * ~~ */
    TipoLista lista = NULL;
    /* ~~ string || char * ~~ */
    char nomeFile[30];
    /* int */
    int puntoMaxAscissa = 0; /* assumerà il valore massimo delle ascisse fra tutti gli elementi della lista */

    printf("\n\tInserisci nome file: ");
    scanf(" %s" , nomeFile);

    buildFromFile(&lista , nomeFile);

    stampaLista(lista);
} /* fine funzione main */



void addElemToLista(TipoLista *lista , TipoElem elem) {

    TipoNodo *last = NULL;
    TipoNodo *newnode = malloc(sizeof(TipoNodo));
    if (!newnode) { printf("\n\tErrore allocazione memoria\n"); exit(-1); }
    newnode->info = elem;
    newnode->next = NULL;

    if ( !(*lista) ) {
        *lista = newnode;
    }
    else { 
        last = *lista;

        while (last != NULL) {
            last = last->next;
        }
        
        last->next = newnode;
    }

}

void readFromFile(FILE * filetemp, TipoElem *elem) {

    fscanf(filetemp, "%d %d %s\n", &(elem->valX) , &(elem->valY) , elem->colore ); 

}

void buildFromFile(TipoLista *lista , char *nomefile) {
    /* prende i dati dal file e li mette nella lista */
    FILE *fin;
    TipoElem elem;

    fin = fopen(nomefile , "r");
    if (!fin) {
        printf("\n\tErrore apertura file. Chiusura app in corso\n");
        exit(-1);
    }
    
    while ( !feof(fin) ) {
        readFromFile(fin , &elem);
        addElemToLista(lista , elem);
    }

}
void stampaElem(TipoElem elem) {
    printf("%s , ( %d,%d ) \n" , elem.colore , elem.valX , elem.valY);
}

void stampaLista(TipoLista lista) {
    int count = 1;

    while (lista) {
        printf("\n\t%d] " , count);
        stampaElem(lista->info);
        lista = lista->next;
        count += 1;
    }
}

void maxAscissa(TipoLista lista) {
    /* trova il valore massimo della x fra tutta la lista */
}


