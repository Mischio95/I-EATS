# I-EATS - Gestione Consegne su Isole

### Progetto per il corso di Laboratorio di Algoritmi e Strutture Dati
### Università degli Studi di Napoli Federico II

## Descrizione del Progetto

I-EATS è un'applicazione realizzata in C che simula un sistema di gestione di consegne tra un arcipelago di isole. Il progetto implementa funzionalità per la registrazione e gestione dei driver, la pianificazione di percorsi ottimizzati per le consegne e la gestione dei magazzini. Le isole e i collegamenti sono rappresentati attraverso un grafo non orientato e pesato.

## Funzionalità Principali
* Login e Registrazione Driver: I driver possono registrarsi con un nome utente, password e peso del proprio furgone. Una volta loggati, possono accedere alla propria area personale.
* Gestione Magazzino: I driver possono visualizzare gli articoli disponibili, caricarli sul furgone e aggiornare le quantità nel magazzino.
* Visualizzazione Mappa: La mappa dell'arcipelago con le isole e i ponti viene mostrata attraverso la rappresentazione di un grafo.
* Percorsi Ottimizzati: Utilizzando l'algoritmo di Dijkstra, viene calcolato il percorso minimo tra due isole, tenendo conto del peso del carico e delle limitazioni di peso dei ponti.
* Gestione Articoli sul Furgone: È possibile visualizzare gli articoli caricati e svuotare il furgone riportando gli articoli nel magazzino.

## Strutture Dati Utilizzate

* Liste Concatenate: Utilizzate per la gestione degli articoli nel magazzino e nel furgone.
* Grafo non Orientato e Pesato: Utilizzato per rappresentare le isole e i collegamenti tra esse.
* Algoritmo di Dijkstra: Implementato per il calcolo del percorso minimo tra le isole, basato su un grafo pesato e sulle limitazioni logistiche del carico.

## Esecuzione

All'avvio del programma, il sistema legge i dati relativi alle isole, ai collegamenti e agli articoli disponibili. Il driver può:
* Registrarsi o accedere al sistema.
* Visualizzare e gestire il carico nel furgone.
* Visualizzare la mappa delle isole e calcolare il percorso ottimale tra due punti dell'arcipelago.
* Effettuare consegne e gestire le scorte.

## Algoritmo di Dijkstra
L'algoritmo di Dijkstra viene utilizzato per determinare il percorso minimo tra le isole, ottimizzando il tragitto in base al carico del furgone e ai limiti strutturali dei ponti.

Complessità:
1 Complessità Spaziale: O(|E| + |V|), dove |E| rappresenta il numero di archi e |V| il numero di vertici del grafo.
2 Complessità Temporale:
  2.1 Caso migliore: Ω(|V|)
  2.2 Caso medio e peggiore: O(|V|²)

## Struttura del Progetto
Il progetto è suddiviso nei seguenti file header:
* Strutture Dati: Definizione delle liste e del grafo.
* Gestione Magazzino: Funzioni per la gestione degli articoli e del furgone.
* Algoritmo di Dijkstra: Funzioni per il calcolo dei percorsi minimi.
* Main: Gestione del flusso principale del programma, inclusa l'interazione con l'utente.

## Istruzioni per l'Utilizzo
Compilazione: Il progetto può essere compilato con un compilatore C standard. Ad esempio:
```
gcc main.c -o i-eats
```
Esecuzione:
```
./i-eats
```

## AUTORI

Michele Trombone - Valerio Mosca - Claudio Velotti
