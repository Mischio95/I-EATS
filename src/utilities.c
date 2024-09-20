#include "utilities.h"


int convertiInIndex(char* input,char** Luoghi,int numNodi){
    int i;
    char temp[strlen(input)];
    strcpy(temp, input);
    temp[0] = (char)toupper(temp[0]);
    
    for(i = 0;i<numNodi;i++){
        if((strcmp(Luoghi[i],temp) == 0)){
            return i;
        }
    }
}

char* convertiInNome(int input,char** Luoghi){
    return Luoghi[input];
}

void assert(int condizione,char* mess){
    if(!condizione){
        printf("%s",mess);
        exit(1);
    }
}

bool controllo_quantita(int q1, int q2){
    if(q1>q2){
        printf("\nArticolo non disponibile nella quantita' desiderata.\n");
        return false;
    }
    return true;
}

void copia_dati_articolo(Articolo* art, Articolo* new_art){
    new_art->peso = art->peso;
    new_art->quantita = art->quantita;
	strcpy(new_art->nome, art->nome);
}

//Seleziona un nodo con l'occorrenza minore per essere inserito nell'array visistati[] ogni volta
int Choose(int *occorrenze, int *visitati, int n) 
{
    int i,minpos,min;
    min= INT_MAX;
    minpos=-1;
    for(i=0;i<n;i++)
    {
        if(occorrenze[i] < min && !visitati[i])
        {
            min=occorrenze[i];
            minpos=i;
        }
    }
    return minpos;
}