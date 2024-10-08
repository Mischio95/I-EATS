#include "driver.h"


bool calcolaPercorso(grafo g, int peso_camion,char** Luoghi){
    int n;
    n= conta_righe();

    grafo aux = crea_grafo(n);
    edge curr;
    int i, flag=0;

    for (i=0; i<g->nv; i++){
        curr= g->adj[i];
        while (curr!=NULL){
            if(curr->carico_max >= peso_camion){
                aggiungi_arco(aux,i,curr->key,curr->carico_max);
                flag=1;
            }
            curr= curr->next;
        }
    }
    if(!flag){
        printf("\nNon esistono percorsi percorribili.\n");
        return false;
    }
    printf("MAPPA DI I-EATS isola:(portata ponte)\n");
    print_grafo(aux,Luoghi);
    return calcolaPercorsoHelper(aux,Luoghi);
}

bool calcolaPercorsoHelper(grafo lg,char** Luoghi)
{   
    char src[ISOLA_MAX_LENGTH];
    char dest[ISOLA_MAX_LENGTH];
    int v,u;
    char *nomeTmp;
    char sceltaRetry;
    int numNodi;
    numNodi = conta_righe();

    do{
    printf("\nInserire punto di partenza: ");
    fflush(stdin);
    scanf("%s",src);

    printf("\nInserire punto di arrivo: ");
    fflush(stdin);
    scanf("%s",dest);
    puts("");
    
   
    u=convertiInIndex(src,Luoghi,numNodi);
    v=convertiInIndex(dest,Luoghi,numNodi);

    if(u == 16 || v == 16){
        printf("\nLuoghi non validi, Riprovare? [S/N] ");
        fflush(stdin);
        scanf("%c",&sceltaRetry);

        if (sceltaRetry != 'S') return false;
        if (sceltaRetry != 's') return false;
    }

    }while(sceltaRetry == 'S' || sceltaRetry == 's');

    int d[lg->nv];
    int path[lg->nv];

    if(Dijkstra(u,d,path,lg)){
        printf("Percorso: ");
        if(path[v]==-1)
        {
            printf("Nessun Percorso disponibile\n");
            return false;
        }

        while (path[v]!=-1)  //ovvero quando arriva alla sorgente si ferma
        {   
            nomeTmp = convertiInNome(v,Luoghi);
            printf("%s <--- ",nomeTmp);
            v=path[v];
        }
        nomeTmp = convertiInNome(u,Luoghi);
        printf("%s\n",nomeTmp);
    }else{
        printf("Non esistono percorsi\n");
        return false;
    }
    return true;
}



