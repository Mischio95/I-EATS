#include "liste_lib.h"


lista newNode(Articolo* art){
    lista temp;
    
    temp = (lista)malloc(sizeof(struct Nodo));
    assert(temp != NULL, "errore nella allocazione della memoria");
    temp->info.nome = (char*)malloc(sizeof(char) * ARTICOLO_MAX_LENGTH);
    assert(temp->info.nome != NULL, "errore nella allocazione della memoria");
    
    temp->next = NULL;
    copia_dati_articolo(art, &temp->info);
    
	return temp;
}

lista insert_last(lista l,Articolo* art){
    if(l == NULL){
        return newNode(art);
    }else{
        l->next = insert_last(l->next,art);
        return l;
    }
}


void print_list(lista l){
    lista curr;

    if(l == NULL){
        printf("Non ci sono articoli!\n");
    }
    curr = l;
    while(curr != NULL){
        printf("Articolo: %s  \tPeso per unita': %d kg\tQuantita' presente: %d\n", curr->info.nome, curr->info.peso, curr->info.quantita);
        curr = curr->next;
    }
}


bool esisteInLista(lista list, char* nome){ 
    if(isEmptyList(list)){
        return false;
    }else if(strcmp(nome, list->info.nome) == 0){
        printf("\nArticolo trovato!\n");
        return true;
    }else{
        return esisteInLista(list->next, nome);
    }
}


void popolaArticolo(lista l,Articolo* art){
    lista curr;
    curr = l;
    while(curr != NULL){
        if(strcmp(art->nome, curr->info.nome) == 0){
            art->peso = curr->info.peso;
            art->quantita = curr->info.quantita;
            return;
        }else{
            curr = curr->next;
        }
    }
}


bool isEmptyList(lista list){
    return (list == NULL);
}

void decrementa_quantita(lista l, char* nomeArt, int curr_qta){
    lista curr;
    curr = l;
    while(curr !=NULL){
        if (strcmp(nomeArt, curr->info.nome)==0)
        {
           curr->info.quantita -= curr_qta;
        }
        curr = curr->next;
    }
}

void aumenta_quantita(lista l, char* nomeArt, int curr_qta){
    lista curr;
    curr = l;
    while(curr !=NULL){
        if (strcmp(nomeArt, curr->info.nome)==0)
        {
            curr->info.quantita += curr_qta;
        }
        curr = curr->next;
    }
}

void svuotaCamionInMagazzino(lista* listaArt, lista* Camion){
    lista currArt,currCam;
    currCam = *Camion;

    if(isEmptyList(*Camion))
        return;

    while(currCam !=NULL){
    currArt = *listaArt;
        while(currArt != NULL) {
            if (strcmp(currCam->info.nome, currArt->info.nome) == 0) {
                currArt->info.quantita += currCam->info.quantita;
            }
            currArt = currArt->next;
        }
        currCam = currCam->next;
    }
    clear_list(Camion);
}


void clear_list(lista *l){
    lista curr, tmp;
    curr = (*l);
    while (curr != NULL){
        tmp = curr;
        curr = curr->next;
        free(tmp->info.nome);
        free(tmp);
    }
    (*l) = NULL;
}

