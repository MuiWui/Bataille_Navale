#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAILLEXMAX 30
#define TAILLEYMAX 30
#define PORTEAVIONID 4
#define TAILLE_PORTEAVION 6
#define CROISEURID 3
#define TAILLE_CROISEUR 4
#define DESTROYERID 2
#define TAILLE_DESTROYER 3
#define CORVETTEID 1
#define TAILLE_CORVETTE 1

/*Prototype de Fonction*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void DemanderNomFichier(char fileName[50]);
void Sauvegarde(int joueur1[TAILLEYMAX][TAILLEXMAX], int joueur2[TAILLEYMAX][TAILLEXMAX], int PlateauFictif1[TAILLEYMAX][TAILLEXMAX], int PlateauFictif2[TAILLEYMAX][TAILLEXMAX], int xy[2], int mode, int diff, int tailleX, int tailleY, int isTouch, int WhoStart, char fileName[50]);
void Chargement(char fileName[50]);
int Superposition(int random_position, int taille, int joueur[TAILLEYMAX][TAILLEXMAX], int x, int y);
void PlacementUnBateauIA(int joueur[TAILLEYMAX][TAILLEXMAX], int tailleX, int tailleY, int taillebateau, int idbateau);
void PlacementBateauxIA(int joueur[TAILLEYMAX][TAILLEXMAX], int tailleX, int tailleY);
void PlacementBateauxIAHardcore(int joueur[TAILLEYMAX][TAILLEXMAX], int tailleX, int tailleY);
void PlacementUnBateauJoueur(int joueur[TAILLEYMAX][TAILLEXMAX], int tailleX, int tailleY, int taillebateau, int idbateau);
void AffichagePlateau(int joueur[TAILLEYMAX][TAILLEXMAX], int tailleX, int tailleY);
char *ImmaFiringMahLazor(int joueur[TAILLEYMAX][TAILLEXMAX], int tailleX, int tailleY);
void Options();
void Menu();
void Choix();
void DemanderTailleTableau(int *tailleX, int *tailleY);
void IAvsIA(int joueur1[TAILLEYMAX][TAILLEXMAX], int joueur2[TAILLEYMAX][TAILLEXMAX], int x, int y, int tailleX, int tailleY);
void JOUEURvsIA(int joueur1[TAILLEYMAX][TAILLEXMAX], int joueur2[TAILLEYMAX][TAILLEXMAX],int tailleX, int tailleY, int mode);
void IAModeFacile(int joueur[TAILLEYMAX][TAILLEXMAX], int tailleX, int tailleY);
int IAModeNormal(int joueur[TAILLEYMAX][TAILLEXMAX], int isTouch, int xy[2], int tailleX, int tailleY);
void IAModeHardcore(int joueur[TAILLEYMAX][TAILLEXMAX], int tailleX, int tailleY);
void PartieJOUEURvsIA(int joueur1[TAILLEYMAX][TAILLEXMAX], int joueur2[TAILLEYMAX][TAILLEXMAX], int tailleX, int tailleY, int PlateauFictif[TAILLEYMAX][TAILLEXMAX], int isTouch, int xy[2], int diff, int mode, char fileName[50]);
void JOUEURvsJOUEUR(int joueur1[TAILLEYMAX][TAILLEXMAX], int joueur2[TAILLEYMAX][TAILLEXMAX],int tailleX, int tailleY, int mode);
void PartieJOUEURvsJOUEUR(int joueur1[TAILLEYMAX][TAILLEXMAX], int joueur2[TAILLEYMAX][TAILLEXMAX], int tailleX, int tailleY, int PlateauFictif1[TAILLEYMAX][TAILLEXMAX], int PlateauFictif2[TAILLEYMAX][TAILLEXMAX], int mode, char fileName[50], int WhoStart);
void TireJoueur(int joueur[TAILLEYMAX][TAILLEXMAX], int PlateauFictif[TAILLEYMAX][TAILLEXMAX], int tailleX, int tailleY);
int FinPartie(int joueur[TAILLEYMAX][TAILLEXMAX], int tailleX, int tailleY);
void JeuBatailleNavale();

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void waitFor(unsigned int secs){

    unsigned int retTime = time(0) + secs;
    while (time(0) < retTime);

}

int doRand(int startVal, int endVal){

    waitFor(0.05);
    srand(time(NULL)*rand());
    if(startVal == 0 && endVal == 1){
        return rand() % 2;
    }else{
        return (rand() % ((endVal - startVal +1)) + startVal);
    }

}

/*Sauvegarde/Chargement*/
//Fonction pour nommer le fichier de sauvegarde
void DemanderNomFichier(char fileName[50]){

    char name[60] = "./";
    printf("Entrez un nom pour le fichier de sauvegarde (sans l\'extension) : ");
    scanf("%s", fileName);
    //Concatenation de deux strings afin de former le nom du fichier de sauvegarde
    strcat(name, fileName);
    strcat(name, ".txt");
    //On recopie la valeur de "name" dans "fileName"
    strcpy(fileName, name);
    printf("\n");

}

//Fonction pour sauvegarder une partie
void Sauvegarde(int joueur1[TAILLEYMAX][TAILLEXMAX], int joueur2[TAILLEYMAX][TAILLEXMAX], int PlateauFictif1[TAILLEYMAX][TAILLEXMAX], int PlateauFictif2[TAILLEYMAX][TAILLEXMAX], int xy[2], int mode, int diff, int tailleX, int tailleY, int isTouch, int WhoStart, char fileName[50]){ //Fonction pour sauvegarder une partie

    printf("Sauvegarde en cours...");
    //On ouvre le fichier avec le nom choisie prédemment dans la fonction
    FILE* ftp = fopen(fileName,"w");
    int x, y;

    fprintf(ftp, "%d %d %d %d %d %d %d %d ", tailleX, tailleY, xy[0], xy[1], mode, diff, isTouch, WhoStart); //On écrit les valeurs des variables dans le fichier

    for(y = 0; y < tailleY; y++){
        for(x = 0; x < tailleX; x++){
            fprintf(ftp, "%d ", joueur1[y][x]);                 //On écrit les valeurs du plateau du JOUEUR1
        }
    }
    fprintf(ftp, " ");
    for(y = 0; y < tailleY; y++){
        for(x = 0; x < tailleX; x++){
            fprintf(ftp, "%d ", joueur2[y][x]);                 //On écrit les valeurs du plateau du JOUEUR2
        }
    }
    fprintf(ftp, " ");
    for(y = 0; y < tailleY; y++){
        for(x = 0; x < tailleX; x++){
            fprintf(ftp, "%d ", PlateauFictif1[y][x]);          //On écrit les valeurs du plateau fictif du JOUEUR1
        }
    }
    if(mode == 3){
        fprintf(ftp, " ");
        for(y = 0; y < tailleY; y++){
            for(x = 0; x < tailleX; x++){
                fprintf(ftp, "%d ", PlateauFictif2[y][x]);      //On écrit les valeurs du plateau fictif du JOUEUR2
            }
        }
    }
    //On referme le fichier
    fclose(ftp);

}

//Fonction pour charger une partie
void Chargement(char fileName[50]){

    char name[60] = "./";
    strcat(name, fileName);
    strcat(name, ".txt");
    FILE* ftpr = fopen(name, "r");
    int joueur1[TAILLEYMAX][TAILLEXMAX], joueur2[TAILLEYMAX][TAILLEXMAX], PlateauFictif1[TAILLEYMAX][TAILLEXMAX], PlateauFictif2[TAILLEYMAX][TAILLEXMAX];
    int xy[2], mode, diff, tailleX, tailleY, x, y, isTouch, WhoStart;

    printf("\nChargement en cours...\n");

    while(!feof(ftpr)){ //On lit les informations jusqu'à la fin du fichier
        fscanf(ftpr, "%d %d %d %d %d %d %d %d ", &tailleX, &tailleY, &xy[0], &xy[1], &mode, &diff, &isTouch, &WhoStart); //On lit les informations stocker dans le fichier de sauvegarde
        for(y = 0; y < tailleY; y++){
            for(x = 0; x < tailleX; x++){
                fscanf(ftpr, "%d ", &joueur1[y][x]);                 //On lit les valeurs du plateau du JOUEUR1
            }
        }
        for(y = 0; y < tailleY; y++){
            for(x = 0; x < tailleX; x++){
                fscanf(ftpr, "%d ", &joueur2[y][x]);                 //On lit les valeurs du plateau du JOUEUR2
            }
        }
        for(y = 0; y < tailleY; y++){
            for(x = 0; x < tailleX; x++){
                fscanf(ftpr, "%d ", &PlateauFictif1[y][x]);          //On lit les valeurs du plateau fictif du JOUEUR1
            }
        }
        if(mode == 3){
            for(y = 0; y < tailleY; y++){
                for(x = 0; x < tailleX; x++){
                    fscanf(ftpr, "%d ", &PlateauFictif2[y][x]);      //On lit les valeurs du plateau fictif du JOUEUR2
                }
            }
        }
    }
    waitFor(3);
    system("cls");

    printf("Chargement termine!\n\nLancement de la partie en cours...\n");
    waitFor(3);
    system("cls");

    //Lancement en fonction du mode de jeu
    if(mode == 2){
        PartieJOUEURvsIA(joueur1, joueur2, tailleX, tailleY, PlateauFictif1, isTouch, xy, diff, mode, name);
    }else if(mode == 3){
        PartieJOUEURvsJOUEUR(joueur1, joueur2, tailleX, tailleY, PlateauFictif1, PlateauFictif2, mode, fileName, WhoStart);
    }else{
        printf("Erreur pendant la phase de chargement.\n"); //Si jamais il y a une erreur
        Choix();
    }
    //On referme le fichier
    fclose(ftpr);

}

/*Fonction pour placer les bateaux des IA ou des JOUEURS*/
//Fonction pour vérifier s'il y a déjà un bateau qui occupe les cases, la fonction renvoie 0 lorsque la case est vide, et elle renvoie 1 lorsqu'il y a un bateau dessus
int Superposition(int random_position, int taille, int joueur[TAILLEYMAX][TAILLEXMAX], int x, int y){

    int i=0;

    switch(random_position){
        case 1:
            for(i=0;i<=taille-1;i++){
                if(joueur[y+i][x] != 0){
                    return 1;
                }
            }
            break;
        case 2:
            for(i=0;i<=taille-1;i++){
                if(joueur[y-i][x] != 0){
                    return 1;
                }
            }
            break;
        case 3:
            for(i=0;i<=taille-1;i++){
                if(joueur[y][x+i] != 0){
                    return 1;
                }
            }
            break;
        case 4:
            for(i=0;i<=taille-1;i++){
                if(joueur[y][x-i] != 0)
                    return 1;
            }
            break;
    }
    return 0;

}

//Fonction qui place un bateau d'une IA,
void PlacementUnBateauIA(int joueur[TAILLEYMAX][TAILLEXMAX], int tailleX, int tailleY, int taillebateau, int idbateau){

    int j=0;
    int y=0;
    int x=0;
    int random_position=0;
    int superpo=1;

    random_position=doRand(1,4);
    x=doRand(0, tailleX-1);
    y=doRand(0, tailleY-1);
    superpo=1;

    //Placement d'un bateau par rapport à random_position
    for(j=0;j<taillebateau;j++){
        //On vérifie que le bateau peut se placer vers le bas sans qu'il n'y ai rien sur son passage et qu'il ne sorte pas du plateau
        if(random_position==1){
            while(y+(taillebateau-1)>(tailleY-1) || superpo==1){
                x=doRand(0, tailleX-1);
                y=doRand(0, tailleY-1);
                superpo=Superposition(random_position, taillebateau, joueur, x, y);
            }
            joueur[y][x]=idbateau;
            joueur[y+j][x]=idbateau;
        //On vérifie que le bateau peut se placer vers le haut sans qu'il n'y ai rien sur son passage et qu'il ne sorte pas du plateau
        }else if(random_position==2){
            while(y-(taillebateau-1)<0 || superpo==1){
                x=doRand(0, tailleX-1);
                y=doRand(0, tailleY-1);
                superpo=Superposition(random_position, taillebateau, joueur, x, y);
            }
            joueur[y][x]=idbateau;
            joueur[y-j][x]=idbateau;
        //On vérifie que le bateau peut se placer vers la droite sans qu'il n'y ai rien sur son passage et qu'il ne sorte pas du plateau
        }else if(random_position==3){
            while(x+(taillebateau-1)>(tailleX-1) || superpo==1){
                x=doRand(0, tailleX-1);
                y=doRand(0, tailleY-1);
                superpo=Superposition(random_position, taillebateau, joueur, x, y);
            }
            joueur[y][x]=idbateau;
            joueur[y][x+j]=idbateau;
        //On vérifie que le bateau peut se placer vers la gauche sans qu'il n'y ai rien sur son passage et qu'il ne sorte pas du plateau
        }else if(random_position==4){
            while(x-(taillebateau-1)<0 || superpo==1){
                x=doRand(0, tailleX-1);
                y=doRand(0, tailleY-1);
                superpo=Superposition(random_position, taillebateau, joueur, x, y);
            }
            joueur[y][x]=idbateau;
            joueur[y][x-j]=idbateau;    //On remplit les cases une par une dans la direction souhaitée à chaque tour de boucle jusqu'à la taille du bateau
        }
    }

}

//Fonction qui place la totalité des bateaux de l'IA en appelant la fonction précédente
void PlacementBateauxIA(int joueur[TAILLEYMAX][TAILLEXMAX], int tailleX, int tailleY){

    PlacementUnBateauIA(joueur, tailleX, tailleY, TAILLE_PORTEAVION, PORTEAVIONID);
    PlacementUnBateauIA(joueur, tailleX, tailleY, TAILLE_CROISEUR, CROISEURID);
    PlacementUnBateauIA(joueur, tailleX, tailleY, TAILLE_CROISEUR, CROISEURID);
    PlacementUnBateauIA(joueur, tailleX, tailleY, TAILLE_CORVETTE, CORVETTEID);
    PlacementUnBateauIA(joueur, tailleX, tailleY, TAILLE_DESTROYER, DESTROYERID);
    PlacementUnBateauIA(joueur, tailleX, tailleY, TAILLE_DESTROYER, DESTROYERID);

}

//Fonction pour le placement des bateaux de l'IA dans le mode Difficile
void PlacementBateauxIAHardcore(int joueur[TAILLEYMAX][TAILLEXMAX], int tailleX, int tailleY){

    PlacementUnBateauIA(joueur, tailleX, tailleY, TAILLE_DESTROYER, DESTROYERID);
    PlacementUnBateauIA(joueur, tailleX, tailleY, TAILLE_CROISEUR, CROISEURID);

}

//Fonction pour le placement d'un bateau d'un joueur
void PlacementUnBateauJoueur(int joueur[TAILLEYMAX][TAILLEXMAX], int tailleX, int tailleY, int taillebateau, int idbateau){

    int i=0;
    int y=0;
    int x=0;
    int isPositionOk[4]={1,1,1,1};
    int superpo=1;
    int PlateauFictif[TAILLEYMAX][TAILLEXMAX];
    int direction;
    int bateauPose=0;

    system("cls");

    for(i=0; i<TAILLEXMAX; i++){
        //Copie un tableau dans un autre
        memcpy(&PlateauFictif[i], &joueur[i], sizeof(joueur[0]));
    }

    do{
        //Réinitialisation de la variable de vérification si le placement échoue
        if(isPositionOk[0] == 0 && isPositionOk[1] == 0 && isPositionOk[2] == 0 && isPositionOk[3] == 0){
            for(i=0;i<4;i++){
                isPositionOk[i]=1;
            }
        }
        printf("Placement du bateau de %d cases de longueur :\n\n", taillebateau);
        AffichagePlateau(joueur, tailleX, tailleY);
        printf("Entrez les coordonnees X et Y du point de depart du bateau :\n\n");
        do{
			do{
                printf("Position X (axe horizontal) : ");
                scanf("%d[0-9]", &x);
                fflush(stdin);
            }while(x<0 || x>=tailleX);
            do{
                printf("Position Y (axe vertital) : ");
                scanf("%d[0-9]", &y);
                fflush(stdin);
            }while(y<0 || y>=tailleY);
        }while(joueur[y][x] != 0);
        system("cls");

        //Positionnement de la première case du bateau sur un plateau fictif pour éviter que la fonction superposition renvoie 1 à chaque fois car celle-ci utilise le tableau joueur
        PlateauFictif[y][x]=idbateau;

        //Pour le bateau de taille 1 on a pas besoin de vérifier la direction, on casse la boucle
        if(taillebateau==TAILLE_CORVETTE){
            joueur[y][x]=CORVETTEID;
            break;
        }

        printf("Voici la position de depart de votre bateau :\n\n");
        AffichagePlateau(PlateauFictif, tailleX, tailleY);

        //Si isPositionOk==0 alors on ne peut pas placer le bateau dans la direction
        for(i=1; i<=4; i++){
            superpo=Superposition(i, taillebateau, joueur, x, y);
            if(i==1){
                if(y+(taillebateau-1)>tailleY-1 || superpo==1){
                   isPositionOk[i-1]=0;     //Vérifie si le placement vers le bas est possible
                }
            }else if(i==2){
                if(y-(taillebateau-1)<0 || superpo==1){
                   isPositionOk[i-1]=0;     //Vérifie si le placement vers le haut est possible
                }
            }else if(i==3){
                if(x+(taillebateau-1)>tailleX-1 || superpo==1){
                    isPositionOk[i-1]=0;    //Vérifie si le placement vers la droite est possible
                }
            }else if(i==4){
                if(x-(taillebateau-1)<0 || superpo==1){
                   isPositionOk[i-1]=0;     //Vérifie si le placement vers la gauche est possible
                }
            }
        }

        //Si isPositionOk==1 alors le bateau peut-être placé dans une ou plusieurs direction
        for(i=0; i<=3; i++){
            if(isPositionOk[i]==1){
                if(i==0){
                    printf("1. Vers le bas\n");
                }else if(i==1){
                    printf("2. Vers le haut\n");
                }else if(i==2){
                    printf("3. Vers la droite\n");
                }else if(i==3){
                    printf("4. Vers la gauche\n");
                }
            }
        }

    }while(isPositionOk[0] == 0 && isPositionOk[1] == 0 && isPositionOk[2] == 0 && isPositionOk[3] == 0);

    do{
        //Si le bateau est de taille 1, on n'a pas besoin de vérifier s'il peut se placer sur les cases alentours
        if(taillebateau==TAILLE_CORVETTE){
            break;
        }

        printf("\nVotre choix : ");
        scanf("%d[0-9]",&direction);
        fflush(stdin);
        //En fonction de la valeur de direction on remplit les cases dans le plateau du joueur par rapport à la taille du bateau
        switch(direction){
            case 1: //Vers le bas
                if(isPositionOk[0]==1){
                    for(i=0; i<taillebateau; i++){
                        joueur[y][x]=idbateau;
                        joueur[y+i][x]=idbateau;
                    }
                    bateauPose=1; //bateauPose prend 1 quand le bateau est posé
                }else{
                    printf("Tu ne peux pas faire cela, recommence\n");
                }
                break;


            case 2: //Vers le haut
                if(isPositionOk[1]==1){
                    for(i=0; i<taillebateau; i++){
                        joueur[y][x]=idbateau;
                        joueur[y-i][x]=idbateau;
                    }
                    bateauPose=1;
                }else{
                    printf("Tu ne peux pas faire cela, recommence\n");
                }
                break;

            case 3: //Vers la droite
                if(isPositionOk[2]==1){
                    for(i=0; i<taillebateau; i++){
                        joueur[y][x]=idbateau;
                        joueur[y][x+i]=idbateau;
                    }
                    bateauPose=1;
                }else{
                    printf("Tu ne peux pas faire cela, recommence\n");
                }
                break;

            case 4: //Vers la gauche
                if(isPositionOk[3]==1){
                    for(i=0; i<taillebateau; i++){
                        joueur[y][x]=idbateau;
                        joueur[y][x-i]=idbateau;
                    }
                    bateauPose=1;
                }else{
                    printf("Tu ne peux pas faire cela, recommence\n");
                }
                break;
        }

    }while(bateauPose==0); //Tant que le bateau n'est pas posé, on réessaye de le poser

}

//Fonction ayant pour but d'afficher un tableau d'un joueur ou d'un IA
void AffichagePlateau(int joueur[TAILLEYMAX][TAILLEXMAX], int tailleX, int tailleY){

    int i=0;
    int j=0;
    int valeur[30]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29};

    printf(" Y \\ X |");

    //On affiche le numéro de la colonne en fonction du nombre de colonne choisie par l'utilisateur (tailleX)
    for(i=0;i<tailleX;i++){
        if(i==0 || i==1 || i==2 || i==3 || i==4 || i==5 || i==6 || i==7 || i==8 || i==9){ //Alignement graphique des valeurs (pour que ça soit plus joli à l'oeil)
            printf("  %d", i);
        }else{
            printf(" %d", i);
        }
    }
    printf("\n--------");
    for(i=0;i<tailleX;i++){
        printf("---");
    }

    //On affiche le numéro de la ligne en fonction du nombre colonne choisie par l'utilisateur (tailleY)
    for(i=0;i<tailleY;i++){
        if(i==0 || i==1 || i==2 || i==3 || i==4 || i==5 || i==6 || i==7 || i==8 || i==9){ //Alignement graphique des valeurs (pour que ça soit plus joli à l'oeil)
            printf("\n");
            printf("   %d   | ", valeur[i]);
        }else{
            printf("\n");
            printf("  %d   | ", valeur[i]);
        }
        for(j=0;j<tailleX;j++){
            printf(" %d ", joueur[i][j]);
        }
    }
    printf("\n\n");

}

//Fonction qui tirer une IA de manière aléatoire sur tout le plateau
char *ImmaFiringMahLazor(int joueur[TAILLEYMAX][TAILLEXMAX], int tailleX, int tailleY){ //Fonction pour faire tirer une IA

    int x, y;

    //On fait tirer une position aléatoire de X et Y pour le tir de l'IA, en vérifiant que l'IA ne retire pas sur une position déjà visée
    do{
        x=doRand(0, tailleX-1);
        y=doRand(0, tailleY-1);
    }while(joueur[y][x]==9 || joueur[y][x]==7);

    if(joueur[y][x]==0){
        joueur[y][x]=9;
        printf("L'IA attaque en %d/%d\n\n", y, x);
        return "L'IA rate! Plouf!\n\n";
    }else if(joueur[y][x]==CORVETTEID || joueur[y][x]==DESTROYERID || joueur[y][x]==CROISEURID || joueur[y][x]==PORTEAVIONID){
        joueur[y][x]=7;
        printf("L'IA attaque en %d/%d\n\n", y, x);
        return "L'IA touche!\n\n";
    }
    return "Vous avez deja tire ici";

}

//Fonction pour régler le jeu de manière optimale
void Options(){

    int i=0;
    int j=0;
    int valeur=0;

    for(i=0;i<=100;i+=5){
        printf("Nous allons maintenant proceder a la detection des performances de votre ordinateur\nafin de vous offrir la meilleur experience de jeu possible!\n\nVeuillez patienter...\n\n");
        printf("   ");
        for(j=1;j<=i/5;j++){
            printf("===");
        }
        printf("  %d%%\n",i);
        waitFor(1);
        system("cls");
    }

    valeur=doRand(0,3);
    printf("OPTIONS GRAPHIQUES\n\n");
    if(valeur==1){
        printf("Les options graphiques sont reglees pour obtenir les meilleures graphismes!\n\n");
        printf("         Resolution  :  3840x2160\n");
        printf("          Affichage  :  Large 16x9\n");
        printf("      Anticrenelage  :  16x\n");
        printf("   Qualite Textures  :  Ultra\n");
        printf("     Qualite Ombres  :  Ultra\n");
        printf(" Occlusion Ambiante  :  HBAO+\n");
        printf("      Anti-Aliasing  :  TXAA\n\n");
    }else{
        printf("Les options graphiques sont reglees pour obtenir les meilleures performances!\n\n");
        printf("         Resolution  :  640x480\n");
        printf("          Affichage  :  Petit 4x3\n");
        printf("      Anticrenelage  :  Off\n");
        printf("   Qualite Textures  :  Faible\n");
        printf("     Qualite Ombres  :  Off\n");
        printf(" Occlusion Ambiante  :  Off\n");
        printf("      Anti-Aliasing  :  Off\n\n");
    }

    Choix();

}

//Menu du jeu permettant de lancer les différents modes de jeu
void Menu(){

	int joueur1[TAILLEYMAX][TAILLEXMAX]={{0}};
	int joueur2[TAILLEYMAX][TAILLEXMAX]={{0}};
	int tailleX=24;	//Taille X par défaut
	int tailleY=18;	//Taille Y par défaut
	int x=0;
	int y=0;
    int choix=0;
    int mode=0;
    char fileName[50];

    system("cls");

    //Lancement des différents menus
    do{
        printf("Bienvenue dans BattleShip!\n\n");
        printf("1. Jouer\n");
        printf("2. Options Graphiques\n");
        printf("3. Charger\n");
        printf("4. Quitter\n\n");
        printf("Votre choix : ");
        scanf("%d[0-9]", &choix);
        fflush(stdin);
        system("cls");
    }while(choix<1 || choix>5);

    //Lancement des différents modes de jeu
    if(choix==1){
        do{
            printf("Choississez votre mode de jeu :\n\n");
            printf("1. IA vs. IA\n");
            printf("2. JOUEUR vs. IA\n");
            printf("3. JOUEUR vs. JOUEUR\n\n");
            printf("Votre choix : ");
            scanf("%d[0-9]", &mode);
            fflush(stdin);
            system("cls");
        }while(mode<1 || mode>3);

            switch(mode){
                case 1:
                        IAvsIA(joueur1, joueur2, x, y, tailleX, tailleY); //Mode IA vs IA
                        break;

                case 2:
                        JOUEURvsIA(joueur1, joueur2, tailleX, tailleY, mode); //Mode JOUEUR vs. IA
                        break;

                case 3:
                        JOUEURvsJOUEUR(joueur1, joueur2, tailleX, tailleY, mode); //Mode JOUEUR vs. JOUEUR
                        break;
            }
    }else if(choix==2){
        Options(); //Menu Options
    }else if(choix==3){
		printf("Entrez le nom du fichier a charger: "); //Chargement de la sauvegarde
		scanf("%s", fileName);
		Chargement(fileName);
	}else if(choix==4){
        exit(0); //Fermeture du programme
    }

}

//Fonction pour permettre de quitter ou de revenir au menu principal
void Choix(){

    int choix;

    printf("Que voulez-vous faire ?\n\n");
    do{
        printf("1. Retour au menu principal\n");
        printf("2. Quitter\n\n");
        printf("Votre choix : ");
        scanf("%d[0-9]", &choix);
        fflush(stdin);
    }while(choix<1 || choix>2);

    if(choix==1){
        Menu();
    }else{
        exit(0);
    }

}

//Fonction pour redimensionner le plateau de jeu
void DemanderTailleTableau(int *tailleX, int *tailleY){

    int choix=0;

    do{
        printf("Souhaitez-vous modifier la taille du plateau de jeu ou garder la valeur par defaut?\n\n     1. Modifier la taille du plateau\n     2. Garder les valeurs par defauts soit X = 24 cases et Y = 18 cases\n\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        printf("\n");
        fflush(stdin);
	}while(choix<1 || choix>2);

    //Réassignation des valeurs de X et Y si le JOUEUR le souhaite
	if(choix==1){
        do{
            printf("Choisissez la longueur de votre plateau (compris entre 10 et %d) : ", TAILLEXMAX);
            scanf("%d[0-9]", tailleX);
            fflush(stdin);
        }while(*tailleX<10 || *tailleX>TAILLEXMAX);

        do{
            printf("Choisissez la largeur de votre plateau (compris entre 10 et %d) : ", TAILLEYMAX);
            scanf("%d[0-9]", tailleY);
        }while(*tailleY<10 || *tailleY>TAILLEYMAX);
        printf("\n");
        fflush(stdin);
	}

}

/*DIFFERENTS MODE DE JEU*/
/*Mode IAvsIA*/
void IAvsIA(int joueur1[TAILLEYMAX][TAILLEXMAX], int joueur2[TAILLEYMAX][TAILLEXMAX], int x, int y, int tailleX, int tailleY){ //Fonction qui regroupe le mode IA vs. IA

    printf("IA vs. IA !\n\n");

	DemanderTailleTableau(&tailleX, &tailleY);
    system("cls");

    //Placement bateau IA1
    PlacementBateauxIA(joueur1, tailleX, tailleY);
    //Placement bateau IA2
    PlacementBateauxIA(joueur2, tailleX, tailleY);

    //Affichage du plateau de l'IA 1
    printf("Plateau de l'IA 1 :\n\n");
    AffichagePlateau(joueur1, tailleX, tailleY);

    //Affichage du plateau de l'IA 2
    printf("Plateau de l'IA 2 :\n\n");
    AffichagePlateau(joueur2, tailleX, tailleY);

    printf("Lorsqu'une IA tire dans l'eau, un 9 apparaitra a l'endroit cible sur le plateau ennemi.\n");
    printf("Lorsqu'une IA tire sur un bateau, un 1 apparaitra a l'endroit cible sur le plateau ennemi.");
    waitFor(15);
    system("cls");

    while(1){

        //L'IA 1 tire sur l'IA 2
        printf("Au tour de l'IA 1 :\n\n");
        printf("%s", ImmaFiringMahLazor(joueur2, tailleX, tailleY));
        printf("Plateau des tirs de l'IA 1 : \n\n");
        AffichagePlateau(joueur2, tailleX, tailleY);

        //On vérifie si l'IA 1 remporte la partie ou non
        if(FinPartie(joueur2, tailleX, tailleY)==1){
            printf("L'IA 1 remporte la partie!\n\n");
            break;
        }
        waitFor(3);
        system("cls");

        //L'IA 2 tire sur l'IA 1
        printf("Au tour de l'IA 2 :\n\n");
        printf("%s", ImmaFiringMahLazor(joueur1, tailleX, tailleY));
        printf("Plateau des tirs de l'IA 2 : \n\n");
        AffichagePlateau(joueur1, tailleX, tailleY);

        //On vérifie si l'IA 2 remporte la partie ou non
        if(FinPartie(joueur1, tailleX, tailleY)==1){
            printf("L'IA 2 remporte la partie!\n\n");
            break;
        }
        waitFor(3);
        system("cls");
    }

    Choix();

}

/*Mode JOUEURvsIA*/
//Sélection du niveau de l'IA et placement des bateaux du JOUEUR et de l'IA
void JOUEURvsIA(int joueur1[TAILLEYMAX][TAILLEXMAX], int joueur2[TAILLEYMAX][TAILLEXMAX],int tailleX, int tailleY, int mode){ //Fonction qui regroupe le mode JOUEUR vs. IA

    int diff, i;
    int tailleBateau[6]={TAILLE_PORTEAVION, TAILLE_CROISEUR, TAILLE_CROISEUR, TAILLE_DESTROYER, TAILLE_DESTROYER, TAILLE_CORVETTE};
    int idBateau[6]={PORTEAVIONID, CROISEURID, CROISEURID, DESTROYERID, DESTROYERID, CORVETTEID};
    int PlateauFictif1[TAILLEYMAX][TAILLEXMAX] = {{0}};
    int xy[2] = {0};
    int isTouch=0;
    char fileName[50];

    //Choix de difficulté de l'IA par le joueur
    do{
        printf("JOUEUR vs. IA !\n\n");
        printf("1. Mode Easy Peasy (IA Facile)\n");
        printf("2. Mode Narmol (IA Normal)\n");
        printf("3. Mode AimBoat (IA Difficile)\n\n");
        printf("Votre choix : ");
        scanf("%d[0-9]", &diff);
        fflush(stdin);
        system("cls");
    }while(diff<1 || diff>3);

	DemanderNomFichier(fileName);
	DemanderTailleTableau(&tailleX, &tailleY);
	system("cls");

    //Placement des bateaux de l'IA en fonction de son niveau
    if(diff==1){
        printf("MODE EASY PEASY (IA FACILE)\n\n");
        PlacementBateauxIA(joueur2, tailleX, tailleY);
    }else if(diff==2){
        printf("MODE NARMOL (IA NORMAL)\n\n");
        PlacementBateauxIA(joueur2, tailleX, tailleY);
    }else if(diff==3){
        printf("MODE AIMBOAT (IA DIFFICILE)\n\n");
        PlacementBateauxIAHardcore(joueur2, tailleX, tailleY);
        printf("Vous allez maintenant affronter l'IA AimBoat, elle ne disposera que de deux bateaux :\n\n    - DESTROYER -> 3 cases\n    - CROISEUR -> 4 cases\n\nBonne chance!\n\n");
        waitFor(10);
    }

    //On demande au JOUEUR de placer ses bateaux
    printf("Vous devez maintenant placer vos bateaux !\n\n");
    waitFor(5);
    for(i=0; i<6; i++){
        PlacementUnBateauJoueur(joueur1, tailleX, tailleY, tailleBateau[i], idBateau[i]);
    }

    system("cls");

    //On montre au JOUEUR la position des ses bateaux pour la partie
    printf("Voici votre plateau pour cette partie :\n\n");
    AffichagePlateau(joueur1, tailleX, tailleY);
    waitFor(3);

    //On lance la suite du mode JOUEURvsIA
    printf("Vous commencez!\n\n");
    PartieJOUEURvsIA(joueur1, joueur2, tailleX, tailleY, PlateauFictif1, isTouch, xy, diff, mode, fileName);

}

//Fonction qui alterne les tirs de l'IA et du JOUEUR
void PartieJOUEURvsIA(int joueur1[TAILLEYMAX][TAILLEXMAX], int joueur2[TAILLEYMAX][TAILLEXMAX], int tailleX, int tailleY, int PlateauFictif1[TAILLEYMAX][TAILLEXMAX], int isTouch, int xy[2], int diff, int mode, char fileName[50]){ //Fonction

	int PlateauFictif2[TAILLEYMAX][TAILLEXMAX] = {{0}};

	while(1){
        waitFor(3);
        system("cls");
        printf("A votre tour de tirer! \n\n");
        printf("Un 7 apparaitra dans la case quand un tir a touché un bateau, sinon un 9 sera mis pour un tir rate!\n\n");
        printf("Voici vos precedents tirs sur le plateau ennemi :\n\n");
        //On affiche le plateau des tirs effectués par le JOUEUR depuis le début de la partie
        AffichagePlateau(PlateauFictif1, tailleX, tailleY);
        //On affiche l'état du plateau du JOUEUR qui tire
        printf("Voici l'etat de votre plateau :\n\n");
        AffichagePlateau(joueur1, tailleX, tailleY);
        //On fait tirer le JOUEUR sur le plateau ennemi
        TireJoueur(joueur2, PlateauFictif1, tailleX, tailleY);
        //On test après chaque tour du JOUEUR s'il a gagné ou pas
        if(FinPartie(joueur2, tailleX, tailleY)==1){
            break;
        }
        //Choix du niveau l'IA en fonction de la difficulté choisie par le JOUEUR
        if(diff==1){
            IAModeFacile(joueur1, tailleX, tailleY);
        }else if(diff==2){
            isTouch=IAModeNormal(joueur1, isTouch, xy, tailleX, tailleY);
        }else if(diff==3){
            IAModeHardcore(joueur1, tailleX, tailleY);
        }
        //On test après chaque tour de l'IA s'il elle a gagné ou pas
        if(FinPartie(joueur1, tailleX, tailleY)==1){
            break;
        }
        waitFor(3);
        system("cls");
        //On sauvegarde la partie automatiquement à chaque fin de tour (un tour correspond aux tirs du JOUEUR puis de l'IA)
        Sauvegarde(joueur1, joueur2, PlateauFictif1, PlateauFictif2, xy, mode, diff, tailleX, tailleY, isTouch, 0, fileName);
    }

    //Affichage du gagnant
    if(FinPartie(joueur1, tailleX, tailleY)==1){
        printf("L'IA remporte la partie! Vous avez perdu\n\n");
    }else{
        printf("Vous remportez la bataille!\n\n");
    }

    Choix();

}

/*Les Différents niveaux de difficulté pour le Mode JOUEURvsIA*/
//IA de difficulté facile
void IAModeFacile(int joueur[TAILLEYMAX][TAILLEXMAX], int tailleX, int tailleY){

    int x, y;

    waitFor(3);
    system("cls");
    printf("Au tour de l'IA :\n\n");

    //On fait tirer une position aléatoire de X et Y pour le tir de l'IA, en vérifiant que l'IA ne retire pas sur une position déjà visée, même si l'IA va toucher un bateau, elle va continuer de tirer de manière aléatoire
    do{
        x=doRand(0, tailleX);
        y=doRand(0, tailleY);
    }while(joueur[y][x]==9 || joueur[y][x]==7);

    //On affiche les positions visées par l'IA
    printf("L'IA attaque en %d/%d\n\n", x, y);
    waitFor(1);

    if(joueur[y][x]==0){
        //On enregistre un 9 quand l'IA tire dans l'eau
        joueur[y][x]=9;
        printf("L'IA rate ! Plouf!\n\n");
    }else if(joueur[y][x]==CORVETTEID || joueur[y][x]==DESTROYERID || joueur[y][x]==CROISEURID || joueur[y][x]==PORTEAVIONID){
        //On enregistre un 7 quand l'IA tire sur un bateau
        joueur[y][x]=7;
        printf("L'IA touche!\n\n");
    }

}

//IA de difficulté normale (après avoir touché un bateau, elle va visée à proximité de ce dernier)
int IAModeNormal(int joueur[TAILLEYMAX][TAILLEXMAX], int isTouch, int xy[2], int tailleX, int tailleY){

    int x, y;

    /*isTouch==0 quand l'IA ne touche pas de bateau
      isTouch==4 quand l'IA vient de toucher un bateau et sa valeur décrémente en négatif (jusqu'à 0) tant qu'elle ne retouche pas le bateau afin de varier la direction des tirs de l'IA*/
    if(isTouch>4)
        isTouch=0;
    printf("Au tour de l'IA :\n\n");

    if(isTouch<=0){
        //On fait tirer une position aléatoire de X et Y pour le tir de l'IA, en vérifiant que l'IA ne retire pas sur une position déjà visée
        do{
            x=doRand(0, tailleX-1);
            y=doRand(0, tailleY-1);
        }while(joueur[y][x]==9 || joueur[y][x]==7);
        xy[0]=x;
        xy[1]=y;
    }else{
        switch(isTouch){ //Variation de la direction en fonction de l'état de isTouch

            case 1:
                x=xy[0]-1;
                y=xy[1];
                break;

            case 2:
                x=xy[0]+1;
                y=xy[1];
                break;

            case 3:
                x=xy[0];
                y=xy[1]-1;
                break;

            case 4:
                x=xy[0];
                y=xy[1]+1;
                break;
        }
    }

    //On affiche les positions visées par l'IA
    printf("L'IA attaque en %d/%d\n\n", x, y);
    waitFor(1);

    if(joueur[y][x]==0){
        //On enregistre un 9 quand l'IA tire dans l'eau
        joueur[y][x]=9;
        printf("L'IA rate ! Plouf!\n");
        isTouch--;
        return isTouch;

    }else if(joueur[y][x]==CORVETTEID || joueur[y][x]==DESTROYERID || joueur[y][x]==CROISEURID || joueur[y][x]==PORTEAVIONID){
        //On enregistre un 7 quand l'IA tire sur un bateau
        joueur[y][x]=7;
        printf("\nL'IA touche!\n\n");
        xy[0]=x;
        xy[1]=y;
        if(isTouch<=0){ //Si isTouch==4, l'IA vient tout juste de trouver un bateau
            return 4;
        }else{
            return isTouch; //Sinon isTouch est sur la bonne direction, donc on garde la même valeur
        }
    }
    return isTouch;
}

//IA de difficulté difficile
void IAModeHardcore(int joueur[TAILLEYMAX][TAILLEXMAX], int tailleX, int tailleY){

    int x, y, i, j;

    waitFor(3);
    system("cls");
    printf("Au tour de l'IA :\n\n");

    //On parcourt le tableau, dès que l'on trouve les coordonnées d'un bateau, l'IA tire
    for(i=0; i<TAILLEYMAX; i++){
        for(j=0; j<TAILLEXMAX; j++){
            if(joueur[i][j]==CORVETTEID || joueur[i][j]==DESTROYERID || joueur[i][j]==CROISEURID || joueur[i][j]==PORTEAVIONID){
                x=j;
                y=i;
            }
        }
    }

    //On affiche les positions visées par l'IA
    printf("L'IA attaque en %d/%d\n\n", x, y);
    waitFor(1);

    if(joueur[y][x]==0){
        //On enregistre un 9 quand l'IA tire dans l'eau
        joueur[y][x]=9;
        printf("L'IA rate ! Plouf!\n\n");
    }else if(joueur[y][x]==1 || joueur[y][x]==2 || joueur[y][x]==3 || joueur[y][x]==4){
        //On enregistre un 7 quand l'IA tire sur un bateau
        joueur[y][x]=7;
        printf("L'IA touche!\n\n");
    }

}

/*Mode JOUEURvsJOUEUR*/
//Placement des bateaux des JOUEURS et sélection du JOUEUR qui commencera
void JOUEURvsJOUEUR(int joueur1[TAILLEYMAX][TAILLEXMAX], int joueur2[TAILLEYMAX][TAILLEXMAX],int tailleX, int tailleY, int mode){

    int diff, i;
    int tailleBateau[6]={TAILLE_PORTEAVION, TAILLE_CROISEUR, TAILLE_CROISEUR, TAILLE_DESTROYER, TAILLE_DESTROYER, TAILLE_CORVETTE};
    int idBateau[6]={PORTEAVIONID, CROISEURID, CROISEURID, DESTROYERID, DESTROYERID, CORVETTEID};
    int PlateauFictif1[TAILLEYMAX][TAILLEXMAX] = {{0}};
    int PlateauFictif2[TAILLEYMAX][TAILLEXMAX] = {{0}};
    int xy[2] = {0};
    int isTouch=0;
    char fileName[50];
    int WhoStart=0;

    DemanderNomFichier(fileName);
    DemanderTailleTableau(&tailleX, &tailleY);
	system("cls");

    //Placement des bateaux du JOUEUR1
    printf("Le JOUEUR1 va maintenant placer ses bateaux !\n\n");
    waitFor(5);
    for(i=0; i<6; i++){
        PlacementUnBateauJoueur(joueur1, tailleX, tailleY, tailleBateau[i], idBateau[i]);
    }
    system("cls");
    printf("Voici votre plateau pour cette partie JOUEUR1 :\n\n");
    AffichagePlateau(joueur1, tailleX, tailleY);
    waitFor(3);
    system("cls");

    //Placement des bateaux du JOUEUR2
    printf("Le JOUEUR2 va maintenant placer ses bateaux !\n\n");
    waitFor(5);
    for(i=0; i<6; i++){
        PlacementUnBateauJoueur(joueur2, tailleX, tailleY, tailleBateau[i], idBateau[i]);
    }
    system("cls");
    printf("Voici votre plateau pour cette partie JOUEUR2 :\n\n");
    AffichagePlateau(joueur2, tailleX, tailleY);
    waitFor(3);
    system("cls");

    printf("La bataille va bientot commencer\n\n");
    waitFor(3);
    printf("De maniere aleatoire nous allons decider le joueur qui commencera la partie");
    waitFor(3);
    //On tire un nombre aléatoire pour faire commencer le JOUEUR1 ou le JOUEUR2 au début
    WhoStart=doRand(0,1);
    if(WhoStart==0){
        //Le JOUEUR1 commencera
        PartieJOUEURvsJOUEUR(joueur1, joueur2, tailleX, tailleY, PlateauFictif1, PlateauFictif2, mode, fileName, WhoStart);
    }else{
        //Le JOUEUR2 commencera
        PartieJOUEURvsJOUEUR(joueur2, joueur1, tailleX, tailleY, PlateauFictif2, PlateauFictif1, mode, fileName, WhoStart);
    }

}

//Déroulement de la partie JOUEURvsJOUEUR avec l'affichage des tirs des joueurs en fonction de celui qui a commencé et l'affichage du gagnant
void PartieJOUEURvsJOUEUR(int joueur1[TAILLEYMAX][TAILLEXMAX], int joueur2[TAILLEYMAX][TAILLEXMAX], int tailleX, int tailleY, int PlateauFictif1[TAILLEYMAX][TAILLEXMAX], int PlateauFictif2[TAILLEYMAX][TAILLEXMAX], int mode, char fileName[50], int WhoStart){

    int xy[2]={0};

    while(1){

        waitFor(3);
        system("cls");

        //En fonction de qui a commencé on rentre dans une des deux boucles
        if(WhoStart==0){

            //Le JOUEUR1 tire
            printf("Au JOUEUR1 de tirer! \n\n");
            printf("Un 7 apparaitra dans la case quand un tir a touche un bateau, sinon un 9 sera mis pour un tir rate!\n\n");
            printf("Voici vos precedents tirs sur le plateau ennemi :\n\n");
            AffichagePlateau(PlateauFictif1, tailleX, tailleY);
            printf("Voici l'etat de votre plateau :\n\n");
            AffichagePlateau(joueur1, tailleX, tailleY);
            TireJoueur(joueur2, PlateauFictif1, tailleX, tailleY);
            waitFor(3);
            //On vérifie si le JOUEUR1 a gagné ou pas à la fin de son tour
            if(FinPartie(joueur1, tailleX, tailleY)==1){
                printf("Le JOUEUR1 remporte la partie!\n\n");
                break;
            }
            printf("Appuyez sur ENTREE pour passer au tour du JOUEUR2");
            getchar();
            system("cls");

            //Le JOUEUR2 tire
            printf("Au JOUEUR2 de tirer! \n\n");
            printf("Un 7 apparaitra dans la case quand un tir a touche un bateau, sinon un 9 sera mis pour un tir rate!\n\n");
            printf("Voici vos precedents tirs sur le plateau ennemi :\n\n");
            AffichagePlateau(PlateauFictif2, tailleX, tailleY);
            printf("Voici l'etat de votre plateau :\n\n");
            AffichagePlateau(joueur2, tailleX, tailleY);
            TireJoueur(joueur1, PlateauFictif2, tailleX, tailleY);
            waitFor(3);
            //On vérifie si le JOUEUR2 a gagné ou pas à la fin de son tour
            if(FinPartie(joueur2, tailleX, tailleY)==1){
                printf("Le JOUEUR2 remporte la partie!\n\n");
                break;
            }
            printf("Appuyez sur ENTREE pour passer au tour du JOUEUR1");
            getchar();
            system("cls");

        }else{

            //Le JOUEUR2 tire
            printf("Au JOUEUR2 de tirer! \n\n");
            printf("Un 7 apparaitra dans la case quand un tir a touche un bateau, sinon un 9 sera mis pour un tir rate!\n\n");
            printf("Voici vos precedents tirs sur le plateau ennemi :\n\n");
            AffichagePlateau(PlateauFictif2, tailleX, tailleY);
            printf("Voici l'etat de votre plateau :\n\n");
            AffichagePlateau(joueur2, tailleX, tailleY);
            TireJoueur(joueur1, PlateauFictif2, tailleX, tailleY);
            waitFor(3);
            //On vérifie si le JOUEUR2 a gagné ou pas à la fin de son tour
            if(FinPartie(joueur2, tailleX, tailleY)==1){
                printf("Le JOUEUR2 remporte la partie!\n\n");
                break;
            }
            printf("Appuyez sur ENTREE pour passer au tour du JOUEUR1");
            getchar();
            system("cls");

            //Le JOUEUR1 tire
            printf("Au JOUEUR1 de tirer! \n\n");
            printf("Un 7 apparaitra dans la case quand un tir a touche un bateau, sinon un 9 sera mis pour un tir rate!\n\n");
            printf("Voici vos precedents tirs sur le plateau ennemi :\n\n");
            AffichagePlateau(PlateauFictif1, tailleX, tailleY);
            printf("Voici l'etat de votre plateau :\n\n");
            AffichagePlateau(joueur1, tailleX, tailleY);
            TireJoueur(joueur2, PlateauFictif1, tailleX, tailleY);
            waitFor(3);
            //On vérifie si le JOUEUR1 a gagné ou pas à la fin de son tour
            if(FinPartie(joueur1, tailleX, tailleY)==1){
                printf("Le JOUEUR1 remporte la partie!\n\n");
                break;
            }
            printf("Appuyez sur ENTREE pour passer au tour du JOUEUR2");
            getchar();
            system("cls");
        }
        //On sauvegarde automatiquement à chaque fin de tour (un tour correspond aux tirs des deux joueurs)
        Sauvegarde(joueur1, joueur2, PlateauFictif1, PlateauFictif2, xy, mode, 0, tailleX, tailleY, 0, WhoStart, fileName);
    }

    Choix();

}

//Fonction qui fait tirer le joueur
void TireJoueur(int joueur[TAILLEYMAX][TAILLEXMAX], int PlateauFictif[TAILLEYMAX][TAILLEXMAX], int tailleX, int tailleY){

    int x=tailleX+1;
    int y=tailleY+1;

    printf("C'est votre tour !\n\n");
    do{
        if(joueur[x][y]==7 || joueur[x][y]==9){
            printf("Vous avez deja tire ici!\n");
        }
        do{
            printf("Entrez la coordonnee X (axe horizontal) : ");
            scanf("%d[0-9]",&x);
        }while(x<0 || x>=tailleX);
            fflush(stdin);
        do{
            printf("\nEntrez la coordonnee Y (axe vertical) : ");
            scanf("%d[0-9]",&y);
            fflush(stdin);
        }while(y<0 || y>=tailleY);
    }while(joueur[y][x]==7 || joueur[y][x]==9);


    if(joueur[y][x]==0){
        //On enregistre les tirs dans les deux tableaux, pour afficher le plateau fictif avec seulement les tirs aux joueurs, sans les bateaux, pour qu'il n'y est pas de triche
        PlateauFictif[y][x]=9;
        joueur[y][x]=9;
        printf("\nVous avez rate ! Plouf!\n\n");
    }else if(joueur[y][x]==1 || joueur[y][x]==2 || joueur[y][x]==3 || joueur[y][x]==4){
        joueur[y][x]=7;
        PlateauFictif[y][x]=7;
        printf("\nVous avez touche!\n\n");
    }else if(joueur[y][x]==7){
        printf("\nTu as deja tire ici recommence!\n");
        TireJoueur(joueur, PlateauFictif, tailleX, tailleY);
    }

}

//Fonction qui test quand la partie se termine
int FinPartie(int joueur[TAILLEYMAX][TAILLEXMAX], int tailleX, int tailleY){

    int x,y;

    for(y=0; y<tailleY; y++){
        for(x=0; x<tailleX; x++){
            if(joueur[y][x]==1 || joueur[y][x]==2 || joueur[y][x]==3 || joueur[y][x]==4){
                return 0;
            }
        }
    }

    return 1; //On parcourt le tableau, et lorsqu'il n'y a plus de bateaux, la fonction renvoie 1, sinon elle renvoie 0 et la partie continue

}

//Fonction principal qui regroupe tout le nécessaire pour faire fonctionner la bataille navale
void JeuBatailleNavale(){

    //Lancement du Menu
    Menu();

}

int main(){

    //Lancement de la bataille navale
    JeuBatailleNavale();

}
