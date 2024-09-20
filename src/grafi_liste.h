#ifndef GRAFI_LISTE_CORRETTO_H
#define GRAFI_LISTE_CORRETTO_H

#include <limits.h>
#include <stdlib.h.>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "utilities.h"
#include "liste_lib.h"

typedef struct Edge { //adjlistnode
    int key;
    //char *nome;
    int carico_max;
    struct Edge *next;
}* edge; 				//nodo all'interno del vettore di adiacenza

typedef struct Grafo {
    int nv; 			/* numero di vertici del grafo */
    edge *adj; 		/* vettore con le liste delle adiacenze */
}* grafo;

grafo crea_grafo(int n);
void print_grafo(grafo g,char** Luoghi);
bool esiste_arco(grafo G, int u, int v);
void aggiungi_arco(grafo G, int u, int v,int p);
void aggiungi_arco_helper(grafo G, int u, int v,int p);
bool isEmptyGraph(grafo G);
edge new_node_g(int v,int p);
int Dijkstra(int src, int *occorrenze, int *path, grafo lg);
bool isEmptyAdj(edge adj);
#endif
