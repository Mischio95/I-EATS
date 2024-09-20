#ifndef UTILITIES_H
#define UTILITIES_H
#define MAX_LENGTH_MENU 20
#define ARTICOLO_MAX_LENGTH 30
#define ISOLA_MAX_LENGTH 20

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


typedef struct articolo{
    char* nome;
    int peso;
    int quantita;
}Articolo;


char* convertiInNome(int input,char** Luoghi);
int convertiInIndex(char* input,char** Luoghi,int numNodi);
void assert(int condizione,char* mess);
bool controllo_quantita(int q1, int q2);
void copia_dati_articolo(Articolo* art, Articolo* new_art);
int Choose(int *occorrenze, int *visitati, int n);

#endif
