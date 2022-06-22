/* DESCRIZIONE ESERCIZIO ↓ 
   # Questo programma ci consente di simulare la gestione di un hotel (privo di sistema prenotativo), come ad esempio: 
        1] Nome struttura ,
        2] Numero clienti nella struttura ,
        3] Numero delle stanze occupate ,
        4] Numero di stanze ancora disponibili ,
        5] Numero stanza ,
        X] etc....
    È ovviamente presente la possibilità di caricare/salvare da/su file.

    ~Carlo Persini , 1995178
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/* ~ DICHIARAZIONI STRUTTURE ~ */

struct infoStanza {
   int codiceStanza;
   int pianoStanza; /* indica il piano in cui si trova la stanza */
   int statoStanza; /* indica se la stanza in questo istante è occupata o meno  ::  1 -> occupata | 0 -> libera */
};
typedef struct infoStanza infoStanza;

struct Hotel {
   infoStanza infoStanzaSingola;
   struct Hotel *next;
};
typedef struct Hotel TipoNodo;
typedef TipoNodo *TipoLista;

/* dichiarazione funzioni */

void initLista(TipoLista *);
void stampaMenu();
void addStanzaToHotel(TipoLista * , int *);
void addOccupazione(TipoLista *);
void removeOccupazione(TipoLista *);
void stampaStanze(TipoLista , int);
void modStanza(TipoLista *);

int checkEsisteCodice(TipoLista , int);


/* ~~~ FUNZIONE MAIN ~~~ */
int main() {
 
   /* int */
   int condLoop = 1,
      condScelta = 0,
      numStanzeTot = 0,
      condRisp = 0, /* line:79 - 80 || switch(condScelta) :: case 1 */
      numStanzeOccupate = 0,
      numPianiHotel = 0;

   /* char *var || string */
   char nomeHotel[20];

   /* TipoLista */
   TipoLista lista;
   initLista(&lista); /* inizializzazione della lista a NULL */


   printf("\n\tSalve! Inserisca nome struttura -> ");
   scanf(" %20s" , nomeHotel );

   printf("\n\tDi quanti piani dispone la struttura? -> ");
   scanf("%d" , &numPianiHotel);
   if (numPianiHotel <= 0) { printf("\n\tMi spiace ma non è possibile.\n"); exit(-1); }

   printf("\n\tQuante stanze possiede in tutto? -> ");
   scanf("%d" , &numStanzeTot);
   if  (numStanzeTot <= 0) { printf("\n\tNon è cortese far perdere tempo!\n"); exit(-1); }

   printf("\n\tPerfetto %s! Procediamo . " , nomeHotel);
   sleep(1);
   printf(" .");
   sleep(1);
   printf(" .\n");

   do {
      stampaMenu();
      scanf("%1d" , &condScelta);

      switch (condScelta) 
      {
         case 1: /* aggiorna stato stanza */
            printf("\n\t1] Qualcuno desidera occupare una stanza.\n\t2] Qualcuno desidera lasciare la sua stanza.\n\t-> ");
            scanf("%1d" , &condRisp);
            if (condRisp == 1) {
               addOccupazione(&lista);
            }
            else if (condRisp == 2) {
               removeOccupazione(&lista);
            }
            else { 
               printf("\n\tScusami, non ho capito!\n");
            }
            condLoop = 1;
            break;

         case 2: /* visualizza stanze */
            condRisp = 0;
            printf("\n\tDesideri visualizzare tutte le stanze, solo quelle occupate o solo quelle libere? [0 , 1 , 2]");
            scanf("%d" , &condRisp);
            stampaStanze(lista , condRisp);
            condLoop = 1;
            break;

         case 3: /* modifica informazioni stanza */
            //modStanza(&lista);
            condLoop = 1;
            break;
         
         case 4: /* aggiungi stanza alla struttura */
            addStanzaToHotel(&lista , &numStanzeTot);
            break;
         
         case 5: /* rimuovi stanza dalla struttura */
            break;

         case 6: /* chiudi applicazione */
            condLoop = 0;
            break;
            
         default:
            printf("\n\tDevi aver sbagliato a scrivere! Scegli fra il numero di opzioni presenti per favore!\n");
            sleep(2);
            condLoop = 1;
            break;
      } /* fine switch */

   }while(condLoop == 1);

} /* ~~~ FINE FUNZIONE MAIN ~~~ */



/* ~~ CODICE FUNZIONI ↓ ~~ */

void initLista(TipoLista *lista)
{
   *lista = NULL;
}


void stampaMenu() 
{
   printf("\n\n\t 1- Aggiorna stato stanza\n");
   printf("\n\t 2- Visualizza stanze\n");
   printf("\n\t 3- Modifica informazioni stanza\n");
   printf("\n\t 4- Aggiungi stanza alla tua struttura\n");
   printf("\n\t 5- Rimuovi stanza dalla tua struttura\n");
   printf("\n\t 6- Chiudi applicazione\n\n");
   printf("\t-> ");
}

int checkEsisteCodice(TipoLista lista , int codice) 
{
   int bool = 0;
   TipoNodo *paux = NULL;
   paux = lista;

   while (paux != NULL) {
      if (paux->infoStanzaSingola.codiceStanza == codice ) {
         bool = 1; /* 1 se è stato trovato */
         return bool;
      }
      else {
         paux = paux->next;
      }
   }
   return bool; /* 0 se non è stato trovato */
}

void addStanzaToHotel(TipoLista *lista , int *stanze)
{
   int statostanza = 0; /* 0 -> stanza libera */
   int codstanza = 0;
   int pianostanza = 0;
   int condLoop = 1;


   TipoNodo *ultimo;
   TipoNodo *newnode = NULL;
   newnode = malloc(sizeof(TipoNodo));
   if (newnode == NULL) { printf("\n\tQualcosa è andato storto!\n"); exit(-1); }

   while (condLoop == 1) {
      printf("\n\tInserisci codice nuova stanza: ");
      scanf("%d" , &codstanza);

      if (checkEsisteCodice(*lista , codstanza) == 1) {  /* se il codice stanza esista già */
         printf("\n\tMi spiace ma questo codice esiste gia'! Usane un altro cortesemente ... \n");
         condLoop = 1;
      }
      else { condLoop = 0; }
   }

   condLoop = 1;
   while (condLoop == 1) { 
      printf("\n\tA che piano si trova questa stanza? (Il piano terra vale come 1 ) -> ");
      scanf("%d" , &pianostanza);
      if (pianostanza <= 0) { printf("\n\tMi spiace ma non è possibile! Riprova cortesemente\n"); condLoop = 1; }
      else { condLoop = 0; }
   }

   newnode->infoStanzaSingola.codiceStanza = codstanza;
   newnode->infoStanzaSingola.pianoStanza = pianostanza;
   newnode->infoStanzaSingola.statoStanza = 0;
   newnode->next = NULL;

   if ( *lista == NULL ) { /* se la lista non ha elementi */
      *lista = newnode;
   }
   else { /* se, invece, all'interno della lista son presente >= 1 elementi */
      ultimo = *lista;
      while (ultimo->next != NULL) { ultimo = ultimo->next; } /* scorre la lista sino ad arrivare all'ultimo elemento */
      ultimo->next = newnode;
   }


}

void addOccupazione(TipoLista *lista)
{
   int codStanza = 0 , condLoop = 1;

   stampaStanze(*lista , 0);
   printf("\n\t []Inserisci codice stanza -> ");
   scanf("%d" , &codStanza);

   if (checkEsisteCodice( *lista , codStanza ) == 0 ) {
      printf("\n\tMi spiace ma non risulta alcuna stanza con questo codice!\n");
   }
   else /* se il codice inserito effettivamente esiste e corrisponde ad una camera */
   {
      
      while ( (*lista) != NULL && condLoop == 1) {
         if ( (*lista)->infoStanzaSingola.codiceStanza == codStanza) { (*lista)->infoStanzaSingola.statoStanza = 1; condLoop = 0;}
         else { (*lista) = (*lista)->next; }
      }

   }

}

void removeOccupazione(TipoLista *lista)
{

}


void stampaStanze(TipoLista lista , int condStampa)
{
   TipoNodo *newnode = lista;
   int i = 1 , codStanza = 0;

   if (condStampa == 0) { /* stampa tutte le stanze */
      while (newnode != NULL) {
         codStanza = newnode->infoStanzaSingola.codiceStanza;
         printf("\n\t%d] Stanza [ %d ]" , i , codStanza);     
         i += 1;
         newnode = newnode->next;
      }
   }
   else if (condStampa == 1) { /* stampa SOLO le stanze occupate */
      while (newnode != NULL) {
         codStanza = newnode->infoStanzaSingola.codiceStanza;
         if (newnode->infoStanzaSingola.statoStanza == 1) { printf("\n\t%d] Stanza [ %d ]" , i , codStanza); }
         i += 1;
         newnode = newnode->next;
      }
   }
   else if (condStampa == 2) { /* stampa SOLO le stanze libere */
      while (newnode != NULL) {
         codStanza = newnode->infoStanzaSingola.codiceStanza;
         if (newnode->infoStanzaSingola.statoStanza == 0) { printf("\n\t%d] Stanza [ %d ]" , i , codStanza); }      
         i += 1;
         newnode = newnode->next;
      }
   }
}