#include "gestore_file.h"

int Login(char* user, char* pass){
    FILE* f;
    char identificativo[MAX_LENGTH_MENU];
    char password[MAX_LENGTH_MENU];
    int peso;

    if ((f = fopen("Database/DBdriver.txt", "r")) != NULL)
    {
        while (fscanf(f, "%s %s %d", identificativo,password,&peso) != EOF)
        {
            if(strcmp(identificativo,user) == 0 && strcmp(pass,password) == 0){
                fclose(f);
                return peso;
            }
        }
        fclose(f);
        return -1;
    }
    else{
        printf("Errore nell'apertura del file\n");
        exit(1);
    }
}

void Registra(char* driver, char* password,int peso){
    FILE *f1;
    if((f1 = fopen("Database/DBdriver.txt", "a"))){
        fprintf(f1, "%s %s %d\n", driver, password, peso);
        fclose(f1);
    }else{
        printf("Errore nell'apertura del file\n");
        exit(1);
    }
}


lista leggiMagazzino(){
    FILE* f;   
    lista lista = NULL;
	Articolo art;
	
	art.nome = (char*)malloc(sizeof(char) * ARTICOLO_MAX_LENGTH);
	assert(art.nome != NULL, "errore nella allocazione della memoria");
	
    f = fopen("Database/DBarticoli.txt", "r");
    assert(f != NULL,"Errore apertura file");

    while(fscanf(f,"%s %d %d",art.nome,&art.peso,&art.quantita) != EOF){
        lista = insert_last(lista,&art);
    }
    fclose(f);
    return lista;
}


void rewriteDBarticoli (lista list) {
    FILE *f_out;

    f_out = fopen("Database/DBarticoli.txt", "w");
    if (f_out == NULL) {
        perror("Errore in apertura del file");
        exit(1);
    } else {
        while (list != NULL) {
            fprintf(f_out, "%s %d %d\n", list->info.nome, list->info.peso, list->info.quantita);
            list = list->next;
        }
    }
    fclose(f_out);
}

grafo leggi_grafo(){
    FILE* f;
    int src, dest, carico_max, n;
    grafo g;


    n = conta_righe();
    g = crea_grafo(n);

    f = fopen("Database/DBgrafo.txt", "r");
    assert(f!= NULL,"Errore apertura file");
  
    while(fscanf(f, "%d %d %d ", &src, &dest, &carico_max) != EOF){
        aggiungi_arco(g,src,dest,carico_max);
    }

    fclose(f);
    return g;
}



char** popolaVettore(){
    int i;
    int index;
    char *nome;
    char** luoghi;
    int n;
    n = conta_righe();

    nome = (char*)malloc(sizeof(char) * ISOLA_MAX_LENGTH);
    assert(nome != NULL, "errore nella allocazione della memoria");

    luoghi = (char**)malloc(n*sizeof(char*));
    assert(luoghi != NULL, "errore nella allocazione della memoria");

    for(i = 0;i<n;i++){
        luoghi[i] = (char*)malloc(ISOLA_MAX_LENGTH*sizeof(char));
        assert(luoghi[i] != NULL, "errore nella allocazione della memoria");
    }

    FILE* f = fopen("Database/DBnodi.txt", "r");
    assert(f != NULL,"Errore apertura file");

    while(fscanf(f,"%d %s",&index,nome) != EOF){
        strcpy(luoghi[index],nome);
    }
    fclose(f);

    return luoghi;
}

int conta_righe(){ 
 int count = 0;

 FILE* f = fopen("Database/DBnodi.txt", "r");
 assert(f != NULL,"Errore apertura file");

 while(fscanf(f,"%*d %*s") != EOF)
     count++;

 fclose(f);
 return count;
}