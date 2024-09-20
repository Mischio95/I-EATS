#include <stdio.h>
#include "driver.h"
#include <unistd.h>

#if __linux
    #define display_image_command "eog -f Arcipelago.jpg"
    #define clear_command "clear"
#elif defined(_WIN32) || defined(_WIN64)
    #define display_image_command "start Arcipelago.jpg"
    #define clear_command "cls"
#endif

lista ListaArticoli = NULL;
lista Furgone = NULL;
grafo Grafo = NULL;
char** Luoghi;

void areaDriver(char* driver, int peso);

int main(){
    char driver[MAX_LENGTH_MENU];
    char password[MAX_LENGTH_MENU];
    int sceltaMainMenu;
    char sceltaRetry;
    int LoginEffettuato;
    int peso_camion_vuoto;          //Viene aggiornato al momento del Login

    Luoghi = popolaVettore();
    Grafo = leggi_grafo();
    ListaArticoli = leggiMagazzino();

    do{
        system(clear_command);
        printf("\n");
        printf("                          /$$$$$$                                         /$$              \n");
        printf("                         |_  $$_/                                        | $$             \n");
        printf("                           | $$                        /$$$$$$  /$$$$$$ /$$$$$$  /$$$$$$$ \n");
        printf("                           | $$         /$$$$$$       /$$__  $$|____  $|_  $$_/ /$$_____/ \n");
        printf("                           | $$        |______/      | $$$$$$$$ /$$$$$$$ | $$  |  $$$$$$  \n");
        printf("                           | $$                      | $$_____//$$__  $$ | $$ /$\\____  $$ \n");
        printf("                           /$$$$$$                    |  $$$$$$|  $$$$$$$ |  $$$$/$$$$$$$/ \n");
        printf("                          |______/                    \\_______/\\_______/   \\___/|_______/  \n");  
        printf("					____________________________________\n");
        printf("					|                                  |\n");
        printf("					|  1) Login Driver          	   |\n");
        printf("					|__________________________________|\n");
        printf("					|                                  |\n");
        printf("					|  2) Registrazione Driver         |\n");
        printf("					|__________________________________|\n");
        printf("					|                                  |\n");
        printf("					|  3) Uscita                 	   |\n");
        printf("					|__________________________________|\n\n");
        printf("					Inserire scelta : ");
        scanf("%d",&sceltaMainMenu);

        switch(sceltaMainMenu){
            //--------------------------------------------------------------------------------------------- LOGIN CITTADINO
            case 1:
                LoginEffettuato = 0;
                sceltaRetry = 0;
                do{
                    printf("Inserisci codice driver: ");
                    fflush(stdin);
                    scanf("%s",driver);

                    printf("Inserisci password: ");
                    fflush(stdin);
                    scanf("%s",password);

                    if((peso_camion_vuoto = Login(driver, password)) > 0){
                        LoginEffettuato = 1;
                    }else{
                        printf("Driver non registrato!");
                        printf("\nRiprovare? : [S/N] : ");
                        fflush(stdin);
                        scanf("%c", &sceltaRetry);
                    }

                    if(LoginEffettuato == 1){
                        areaDriver(driver, peso_camion_vuoto);
                    }
                }while((sceltaRetry == 'S' || sceltaRetry == 's') || LoginEffettuato == 0);
                break;
//--------------------------------------------------------------------------------------------- REGISTRAZIONE DRIVER
            case 2 :
                printf("Inserisci Campi: \n");

                printf("Inserisci CODICE DRIVER : ");
                fflush(stdin);
                scanf("%s",driver);

                printf("Inserisci Password: ");
                fflush(stdin);
                scanf("%s",password);

                printf("Inserisci Peso Camion: ");
                scanf("%d",&peso_camion_vuoto);

                Registra(driver, password, peso_camion_vuoto);

                printf("\nRegistrazione Effettuata con successo!\n");
                system("PAUSE");
                break;
//--------------------------------------------------------------------------------------------- USCITA
                case 3:
                    rewriteDBarticoli(ListaArticoli);   //riscrive su file la lista degli articoli con le quantita' aggiornate
                    clear_list(&ListaArticoli);
        }

    }while(sceltaMainMenu != 3);

    return 0;
}

void areaDriver(char* driver, int peso){
    int sceltaSubMenuCittadino;
    int quantitaTmp;
    Articolo ArtTmp;
    Driver driverCamion;
    driverCamion.peso_camion_carico = peso;
    char sceltaArticolo, sceltaConsegna;

    ArtTmp.nome = (char*)malloc(sizeof(char) * ARTICOLO_MAX_LENGTH);
    assert(ArtTmp.nome != NULL, "errore nella allocazione della memoria");

    do{
        system(clear_command);
        printf("\n					     ACCESSO ESEGUITO COME: %s",driver);
        printf("\n					     Peso camion attuale :%d kg \n\n",driverCamion.peso_camion_carico);
        printf("					____________________________________\n");
        printf("					|                                  |\n");
        printf("					|  1) Rifornimento Camion          |\n");
        printf("					|__________________________________|\n");
        printf("					|                                  |\n");
        printf("					|  2) Controlla articoli Furgone   |\n");
        printf("					|__________________________________|\n");
        printf("					|                                  |\n");
        printf("					|  3) Visualizza Arcipelago        |\n");
        printf("					|__________________________________|\n");
        printf("					|                                  |\n");
        printf("					|  4) Definisci percorso           |\n");
        printf("					|__________________________________|\n");
        printf("					|                                  |\n");
        printf("					|  5) Svuota Camion in Magazzino   |\n");
        printf("					|__________________________________|\n");
        printf("					|                                  |\n");
        printf("					|  6) Logout                       |\n");
        printf("					|__________________________________|\n\n");
        printf("					Inserire scelta : ");
        scanf("%d",&sceltaSubMenuCittadino);

        switch(sceltaSubMenuCittadino){
//--------------------------------------------------------------------------------------------- RIFORNIMENTO CAMION
            case 1:
                do {
                    system(clear_command);
                    printf("\n\n\nLISTA ARTICOLI:\n\n");
                    print_list(ListaArticoli);
                    printf("\nInserire il nome dell'Articolo da inserire all'interno del furgone: ");
                    fflush(stdin);
                    scanf("%s", ArtTmp.nome);

                    if (esisteInLista(ListaArticoli,ArtTmp.nome)){
                        popolaArticolo(ListaArticoli,&ArtTmp);
                        printf("Quante unita' di %s vuoi ritirare? ", ArtTmp.nome);
                        fflush(stdin);
                        scanf("%d", &quantitaTmp);

                        if (controllo_quantita(quantitaTmp, ArtTmp.quantita)){

                            ArtTmp.quantita = quantitaTmp;

                            if(esisteInLista(Furgone,ArtTmp.nome))
                                aumenta_quantita(Furgone, ArtTmp.nome, quantitaTmp);
                            else
                                Furgone = insert_last(Furgone, &ArtTmp);

                            decrementa_quantita(ListaArticoli, ArtTmp.nome, quantitaTmp);
                            printf("\nArticolo inserito con successo.\n");
                            driverCamion.peso_camion_carico += (ArtTmp.peso * ArtTmp.quantita);
                        }

                        printf("\nInserire altri articoli? [S/N]");
                        fflush(stdin);
                        scanf("%c", &sceltaArticolo);
                    }else
                        printf("\nArticolo non trovato!\n");


                }while(sceltaArticolo == 'S' || sceltaArticolo == 's');
                break;
//--------------------------------------------------------------------------------------------- CONTROLLA ARTICOLI FURGONE
            case 2:
                print_list(Furgone);
                break;

//--------------------------------------------------------------------------------------------- VISUALIZZA ARCIPELAGO
            case 3:
                printf("MAPPA DI I-EATS isola:(portata ponte)\n");
                print_grafo(Grafo,Luoghi);
                system(display_image_command);
                break;
//--------------------------------------------------------------------------------------------- DEFINISCI PERCORSO
            case 4:
                system(clear_command);
                if(calcolaPercorso(Grafo,driverCamion.peso_camion_carico,Luoghi) == true){
                    if(isEmptyList(Furgone)){
                        printf("\nSiamo spiacenti, il camion e' vuoto.\n");
                        printf("Verrai reindirizzato all'area personale.\n\n");
                        break;
                    }
                    printf("Eseguire consegna?[S/N]");
                    fflush(stdin);
                    scanf("%c", &sceltaConsegna);

                    if(sceltaConsegna == 's' || sceltaConsegna == 'S') {
                        printf("\nConsegna effettuata con successo!\n");
                        clear_list(&Furgone);
                        driverCamion.peso_camion_carico = peso;

                    }else{
                        printf("\nConsegna annullata.\n");
                    }
                }
                break;
//--------------------------------------------------------------------------------------------- SVUOTA CAMION IN MAGAZZINO
            case 5: 
                svuotaCamionInMagazzino(&ListaArticoli,&Furgone);
                driverCamion.peso_camion_carico = peso;
                printf("\nCamion svuotato correttamente\n");
                break;
//--------------------------------------------------------------------------------------------- LOGOUT
            case 6:
                svuotaCamionInMagazzino(&ListaArticoli, &Furgone);
                free(ArtTmp.nome);
                break;

            default:
                break;
        }
        system("PAUSE");
    }while(sceltaSubMenuCittadino != 6);
}
