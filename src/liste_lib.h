#ifndef PROGETTO_2_LISTE_LIB_H
#define PROGETTO_2_LISTE_LIB_H

#include "utilities.h"

#include <string.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Nodo{
    Articolo info;
    struct Nodo* next;
}*lista;


lista newNode(Articolo* art);
lista insert_last(lista l,Articolo* art);
void print_list(lista l);
bool isEmptyList(lista list);
bool esisteInLista(lista list, char* nome);
void decrementa_quantita(lista l, char* nomeArt, int curr_qta);
void clear_list(lista *l);
void svuotaCamionInMagazzino(lista *listaArt,lista *Camion);
void popolaArticolo(lista list,Articolo* art);
void aumenta_quantita(lista l, char* nomeArt, int curr_qta);



#endif
