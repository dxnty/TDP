#include <stdio.h>
#include <stdlib.h>

typedef int TipoElem;
struct node { 
    TipoElem info;
    struct node *next;
};
typedef struct node TipoNodo;
typedef TipoNodo * TipoLista;

float calcolaMedia(TipoLista);
void addNodo(TipoLista * , int);
void insDati(TipoLista , int *som , int *numNodi);

int main() {
    int coundLoop = 0;
    int i = 0;
    TipoLista lista = NULL;

    addNodo(&lista , 10);
    addNodo(&lista , 20);
    addNodo(&lista, 35);
    
}

void addNodo(TipoLista *l , int val_info) {
    TipoNodo *newnode = malloc(sizeof(TipoNodo));
    TipoNodo *ultimo = NULL;

    newnode->info = val_info;
    newnode->next = NULL;

    if (*l == NULL) { *l = newnode; }
    else {
        ultimo = *l;
        while( ultimo->next != NULL ) { ultimo = ultimo->next; }
        ultimo->next = newnode;
    }
}

void insDati(TipoLista l, int *som , int *numNodi) {
    if (l) {
        *som += l->info; /* a somma viene aggiunto il valore contenuto all'interno di l->info */ 
    }
}

float calcolaMedia(TipoLista l) {

    int somma = 0 , numNodi = 0;

    insDati(l, &somma, &numNodi);

    if (numNodi) {
        return (float) somma/numNodi;
    }
    else return 0;
}