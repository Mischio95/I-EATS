#ifndef DRIVER_H
#define DRIVER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gestore_file.h"
#include "driver.h"
#include "utilities.h"

typedef struct driver{
    int src;
    int dest;
    int peso_camion_carico;
}Driver;

bool calcolaPercorso(grafo g, int peso_camion,char** Luoghi);
bool calcolaPercorsoHelper(grafo lg,char** Luoghi);

#endif
