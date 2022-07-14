#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct structInfoAlbero{
    char nome[20] , cognome[20];
    float peso;
    int code; /* codice primario */
} InfoAlbero;

typedef struct structNodoAlbero {
    InfoAlbero info;
    struct structNodoAlbero *sx;
    struct structNodoAlbero *dx;
} TipoNodoAlbero;
typedef TipoNodoAlbero *TipoTestaAlbero;

void stampaAlbero( TipoTestaAlbero ); /* stampa l'albero passato */
void stampaElem( InfoAlbero , int cond ); /* stampa il singolo elemento || cond permette di scegliere cosa visualizzare*/
void addNode( TipoTestaAlbero * , InfoAlbero ); /* aggiunge all'albero il nodo che ha come info InfoAlbero */
TipoTestaAlbero createNode( InfoAlbero ); /* crea il nodo se non ne esiste uno */
TipoTestaAlbero removeNode( TipoTestaAlbero , int ); /* code --> il codice identificativo che useremo per sapere quale nodo rimuovere*/

/* ---FUNZIONE-MAIN---*/
int main() 
{

    TipoTestaAlbero head = NULL;

    InfoAlbero data;

    int condopz = 0 , peso = 0 , code = 0 , condremove = 0;

    char nome[20] , cognome[20];


    printf("\n\tQuanti elementi vuoi inserire? -->   ");
    scanf("%d" , &condopz);

    for (int i = 0 ; i < condopz ; i++)
    {
        printf("\n\t[] Inserisci nome paziente: ");
        scanf( " %s" , nome );

        printf("\n\t  Inserisci cognome paziente: ");
        scanf( " %s" , cognome );

        printf("\n\t  Inserisci peso paziente: ");
        scanf( " %d" , &peso );
        
        printf("\n\t Inserisci codice paziente : ");
        scanf( "%d" , &code );
        //checkEsistenzaCodice()
        printf("\n");

        strcpy( data.nome , nome );
        strcpy( data.cognome , cognome );
        data.peso = peso;
        data.code = code;

        addNode( &head , data );
    }

    printf("\n\t ~~~ Stampa in corso ~~~\n\n");
    stampaAlbero(head);

    printf("\n\tQuale elemento si vuole eliminare? -->  ");
    scanf( "%d" , &condremove );

    head = removeNode( head , data.code );

    printf("\n\t ~~~ Nuova stampa in corso ~~~\n\n");
    stampaAlbero(head); printf("\n");



}
/* ---FINE-FUNZIONE-MAIN--- */


void stampaElem( InfoAlbero info , int cond ) 
{   
    if (cond == 0) { /* se si vuole stampare tutto */
        printf(" Nome : %s " , info.nome);
        printf(" Cognome : %s " , info.cognome);
        printf(" Peso : %f " , info.peso); 
        printf(" Codice : %d " , info.code);
    }
    else if (cond == 1){ /* se si vuole stampare solo il peso */
        printf("%d" , info.code);
    }
}
void stampaAlbero( TipoTestaAlbero root ) 
{
    if (!root) printf("()");
    else 
    {
        printf("( "); /* interno della parentesi */
            stampaElem(root->info , 1);
            stampaAlbero(root->sx); 
            stampaAlbero(root->dx);
        printf(" )"); /* chiusura parentesi */
    } /* fine else */
} /* fine funzione */

TipoTestaAlbero createNode( InfoAlbero data )
{   
    TipoTestaAlbero head = (TipoTestaAlbero) malloc(sizeof(TipoNodoAlbero));

    head->info.code = data.code;
    head->info.peso = data.peso;
    strcpy( head->info.nome , data.nome );
    strcpy( head->info.cognome , data.cognome );
    head->sx = head->dx = NULL;

    return head;
} /* fine funzione createNode() */
void addNode( TipoTestaAlbero *head , InfoAlbero data ) 
{
    if ( !(*head) ) { (*head) = createNode(data); return ; }

    if ( data.peso < (*head)->info.peso ) /* se il valore è più piccolo del nodo già presente allora vai a sx (ricorsivamente) */
    {
        addNode( &((*head)->sx) , data );
    }
    else /* se il valore è più grande del nodo già presente allora vai a dx (ricorsivamente) */
    {
        addNode( &((*head)->dx) , data );
    }
} /* fine funzione addNode() */

TipoTestaAlbero findMin( TipoTestaAlbero root )
{
    TipoTestaAlbero nodetemp = root;
    if (!root) { return 0; }
    while ( nodetemp->sx != NULL )
        nodetemp = nodetemp->sx;
    return nodetemp;
}
TipoTestaAlbero removeNode( TipoTestaAlbero noderoot , int code )
{
    TipoTestaAlbero temp;
    
    if ( !noderoot ) { return noderoot; } /* se non son presenti elementi */
    else if ( code < noderoot->info.code ) { noderoot->sx = removeNode( noderoot->sx , code); }
    else if ( code > noderoot->info.code ) { noderoot->dx = removeNode( noderoot->dx , code); }
    else
    {
        if ( noderoot->sx == NULL && noderoot->dx == NULL ) { /* se non presenta alcun figlio */
            free(noderoot);
            noderoot = NULL;
        }
        else if ( noderoot->sx == NULL && noderoot->dx != NULL ) { /* se presenta solo un figlio destro */
            temp = noderoot;
            noderoot = noderoot->dx;
            free(temp);
        }
        else if ( noderoot->sx != NULL && noderoot->dx == NULL ) { /* se presenta solo un figlio sinistro */
            temp = noderoot;
            noderoot = noderoot->sx;
            free(temp);
        }
        else { /* se presenta due figli */
            temp = findMin( noderoot );
            noderoot->info = temp->info;
            noderoot->dx = removeNode( noderoot->dx , noderoot->info.code );
        }
    }
    return noderoot;
}       
