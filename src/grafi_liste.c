#include "grafi_liste.h"


edge new_node_g(int v,int p){

    edge new = (edge)malloc(sizeof(struct Edge));
    
    new->key = v;
    new->carico_max = p;
    new->next=NULL;

    return new;
}


grafo crea_grafo(int n){
    grafo G;
    G = (grafo)malloc(sizeof(struct Grafo));

    if (G==NULL)
        printf("ERRORE: impossibile allocare memoria per il grafo\n");
    else {
        G->adj = (edge*)malloc(n*sizeof(edge));

        if (G->adj==NULL) {
            printf("ERRORE: imp. allocare mem. per la lista del grafo\n");
            free(G);
            return NULL;
        }else{
            G->nv = n;
            for(int i=0; i<n; i++)
                G->adj[i]=NULL;
        }
    }
    return(G);
}


bool esiste_arco(grafo G, int u, int v){
    edge curr;

    curr = (edge) G->adj[u];
    while(curr != NULL != 0){
        if(curr->key == v)
            return true;
        else
            curr = (edge) curr->next;
    }
    return false;
}


void aggiungi_arco(grafo G, int u, int v,int p){
    assert(!isEmptyGraph(G), "Grafo vuoto");
    assert(u < G->nv && v < G->nv,"Almeno uno dei due vertici non esiste");
    
    if(esiste_arco(G,u,v)){
        return;
    }

    aggiungi_arco_helper(G,u,v,p);
    aggiungi_arco_helper(G,v,u,p);
}


void aggiungi_arco_helper(grafo G, int u, int v,int p){
    edge e, new = new_node_g(v, p);

    if (G->adj[u] == NULL)
        G->adj[u] = (edge) new;
    else {
        e = (edge) G->adj[u];
        while (e->next != NULL)
            e = (edge) e->next;
        e->next = (edge) new;
    }
}


void print_grafo(grafo G,char** Luoghi){
    int i, ne=0;
    edge e;
    if (!isEmptyGraph(G)){    
        for (i=0; i<G->nv; i++){
            printf("Isole adiacenti a %s  \t->\t", Luoghi[i]);

            e= (edge) (edge *) G->adj[i];
            while (e!=NULL){
                printf("%s:(%d)  ", Luoghi[e->key], e->carico_max);
                ne=ne+1; e= (edge) e->next;
            }
            printf("\n");
        }
    }
}


bool isEmptyGraph(grafo G){
    return (G==NULL);
}

int Dijkstra(int src, int *occorrenze, int *path, grafo lg)
{
    int i,k;
    edge aux_edge;
    int *visitati;  //array di interi

    //controlla se la lista di adiacenza della sorgente sia vuota o meno
    if(isEmptyAdj(lg->adj[src]))
        return 0;


    aux_edge = lg->adj[src];    

    assert( !(src<0||src>lg->nv-1), "ERRORE");

    visitati=(int*)malloc(sizeof(int) * lg->nv);           //alloca memoria per l'array di interi
    assert(visitati != NULL, "errore allocazione memoria");

    //INIZIALIZZA I VETTORI
    for(i=0;i<lg->nv ;i++)
    {
        visitati[i]=0;
        path[i]=-1;
        occorrenze[i]=INT_MAX;
    }

    while(aux_edge != NULL){
        occorrenze[aux_edge->key ]= 1;
        if(aux_edge->key != src && occorrenze[aux_edge->key ] < INT_MAX)
            path[aux_edge->key ]=src;

        aux_edge=aux_edge->next;
    }


    visitati[src]=1; // array dei colori
    occorrenze[src]=0; // array con conteggio dei nodi su cui si passa

    //DOPO AVER SCORSO LA LISTA DI ADIACENZA DELLA SORGENTE, FA IL RESTO DEI CONTROLLI

    for(i=1;i<lg->nv ;i++)
    {
        k=Choose(occorrenze, visitati, lg->nv );
        if(k==-1)
            continue;

        //Determina se un nodo valido e' selezionato
        visitati[k]=1;
        aux_edge=lg->adj[k];
        if(aux_edge == NULL)
            continue ;

        while(aux_edge)
        {
            if (!visitati[aux_edge->key] && occorrenze[k] + 1 < occorrenze[aux_edge->key]){ //Aggiorna occorrenze e path
                occorrenze[aux_edge->key] = occorrenze[k] + 1;
                path[aux_edge->key] = k;
            }
            aux_edge = aux_edge->next;
        }
    }
    return 1;
}
bool isEmptyAdj(edge adj){
    return(adj == NULL);
}


