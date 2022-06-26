#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TipoPunto {
    char colore[15];
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
void maxAscissa(TipoLista , int *); /* trova il valore massimo della x fra tutta la lista */
void readFromFile(FILE * , TipoElem *); /* prende gli elementi dal file e li trasferisce nella lista */
void addElemToLista(TipoLista * , TipoElem); /* aggiunge gli elementi alla lista */
void scriviOnFile(TipoLista , char *); /* consente di scrivere sul file tutti gli elementi presenti in lista */
void addNodo(TipoLista *); /* aggiunge un nodo, consenste di fare un test di scrittura */
void eliminaPuntoValMax(TipoLista * , int); /* elimina i nodi che contengono il valore massimo dell'ascisse */

int main() {
    /* ~~ TipoLista || TipoNodo * ~~ */
    TipoLista lista = NULL;
    /* ~~ string || char * || char ~~ */
    char nomeFile[30];
    char condProc = ' '; /* condProceed || opzione di scelta per proseguire con eliminazione o meno */
    char condYes = 's';
    /* int */
    int puntoMaxAscissa = 0; /* assumerà il valore massimo delle ascisse fra tutti gli elementi della lista */
    int condScelta = 0; /* conterrà la risposta alla domanda: 'Scrivere o Leggere da file' */
    int condLoop = 1; /* condizione di ciclo */
    int condSave = 0; /* condizione per decidere che informazione salvare sul file */

    printf("\n\tInserisci nome file: ");
    scanf(" %s" , nomeFile);

    while (condLoop == 1){
        printf("\n\tVuoi leggere, scrivere sul file, stampare la lista oppure uscire dal programma (0 , 1 , 2 , 3) ? \n\t->  ");
        scanf("%d" , &condScelta);

        switch (condScelta) {
            case 0:

                buildFromFile(&lista, nomeFile);
                maxAscissa(lista , &puntoMaxAscissa);
                printf("\n\tIl valore maggiore delle x e' : %d\n" , puntoMaxAscissa);

                printf("\n\tVuoi procedere con l'eliminazione dei punti con questo valore [s/n]?  ->  ");
                scanf(" %c" , &condProc);

                if ( strcmp(&condProc , &condYes) ) {
                    eliminaPuntoValMax(&lista, puntoMaxAscissa);
                }
                else { 
                    printf("\n\tRicevuto!\n");
                }

                break;
            case 1:
                condSave = 0;
                printf("\n\tVuoi salvare la lista attuale o un nuovo nodo [0,1] ? ->  ");
                scanf("%d" , &condSave);
                if ( condSave == 1 ) {
                    addNodo(&lista);
                }
                scriviOnFile(lista, nomeFile);
                break;
            case 2:
                printf("\n\tStampa lista in corso: ");
                stampaLista(lista);
                break;
            case 3:
                condLoop = 0;
                break;
            default:
                printf("\n\t ~~~ Devi aver sbagliato a scrivere!\n");
                condLoop = 1;
        }
    }

} /* fine funzione main */



void addElemToLista(TipoLista *lista , TipoElem elem) {

    TipoNodo *last;
    TipoNodo *newnode = NULL;
    newnode = malloc(sizeof(TipoNodo));

    if (!newnode) { printf("\n\tErrore allocazione memoria\n"); exit(-1); }

    newnode->info = elem;
    newnode->next = NULL;

    if ( !(*lista) ) {
        *lista = newnode;
    }
    else { 
        last = *lista;
        while (last->next != NULL) {
            last = last->next;
        }
        
        last->next = newnode;
    }

}


void eliminaPuntoValMax(TipoLista *lista , int valmax) {
    TipoNodo *prec = malloc(sizeof(TipoNodo));
    TipoNodo *corr;
    int nodeval = 0;

    prec->next = *lista; /* dopo *prec arriverà il primo elemento della lista */
    *lista = prec; /* prec diviene ora il primo elemento */
    corr = prec->next; /* corr punta al secondo elemento della lista (escluso prec) */

    while (corr) {
        nodeval = corr->info.valX;
        if (nodeval == valmax) { prec->next = corr->next; free(corr); }
        else { prec = prec->next; }
        corr = prec->next;
    }

    prec = *lista;
    *lista = prec->next;
    free(prec);

}


void addNodo(TipoLista *lista) {
    TipoNodo *last;
    TipoNodo *newnode = NULL;
    newnode = malloc(sizeof(TipoNodo));
    

    char colore[15];
    int x = 0 , y = 0;

    if (!newnode) { printf("\n\t ~~ Errore allocazione memoria ~~\n"); exit(-1); }
    printf("\n\tInserisci colore x y  -> ");
    scanf(" %s %d %d" , colore , &x , &y);
    
    strcpy(newnode->info.colore , colore);
    newnode->info.valX = x;
    newnode->info.valY = y;
    newnode->next = NULL;
    if (!(*lista)) { *lista = newnode; }
    else {
        last = *lista;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newnode;
    }
}


/* LETTURA DA FILE */
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

    fclose(fin);
}
/* FINE LETTURA DA FILE */


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

void maxAscissa(TipoLista lista , int *val) {
    /* trova il valore massimo della x fra tutta la lista */
    TipoNodo *node = lista;
    int max = 0 , count = 0 ;

    if (!lista) {
        printf("\n\t ~~~ La lista è vuota ~~~");
    }
    else {
        while (node) {
            if (node->info.valX > max) { max = node->info.valX; } 
            node = node->next;
        }
    }
    *val = max;
}


void scriviOnFile(TipoLista lista , char *nomefile) {
    FILE *fout;
    fout = fopen(nomefile , "w");
    TipoNodo *node = lista;
    TipoElem elem;

    if (!fout) {
        printf("\n\t ~~~ Non è stato possibile aprire il file ~~~\n");
        exit(-1);
    }
    
    while (node) { /* finché continuano ad esserci dei nodi all'interno della lista */
        strcpy(elem.colore , node->info.colore);
        elem.valX = node->info.valX;
        elem.valY = node->info.valY;
        fprintf(fout , "%d %d %s\n" , elem.valX , elem.valY , elem.colore);
        
        node = node->next;
    }

    fclose(fout);
} /* fine funzione */

