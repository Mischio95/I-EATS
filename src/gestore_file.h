#ifndef GESTORE_FILE_H
#define GESTORE_FILE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "liste_lib.h"
#include "grafi_liste.h"
#include "utilities.h"

#define MAX 50

int Login(char* user, char* pass);
void Registra(char* driver, char* password,int peso);
lista leggiMagazzino();
void rewriteDBarticoli (lista list);
grafo leggi_grafo();
bool occorrenza_gia_presente(int* v, int l, int r, int x);
grafo inizializzaGrafo(grafo G);
char** popolaVettore();
int conta_righe();

#endif
