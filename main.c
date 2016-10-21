#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define PORTEAVIONID 4
#define TAILLE_PORTEAVION 6
#define CROISEURID 3
#define TAILLE_CROISEUR 4
#define DESTROYERID 2
#define TAILLE_DESTROYER 3
#define CORVETTEID 1
#define TAILLE_CORVETTE 1

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
        return (rand() % ((endVal + startVal -1)) + startVal);
    }

}

void FilerWrite(){
    FILE* ftp = fopen("./test1.txt","a+");
    int i = 0;
    while(i < 1000){
        fprintf(ftp,"Hello world %d",i);
        i++;
    }
    fclose(ftp);
}

void FilerRead(){
    FILE* fptr = fopen("./test1.txt","r");
    char c;
    while(1)
    {
        c = fgetc(fptr);
        if ( feof(fptr) )
        {
            break;
        }
        printf ("%c", c);
    }
    fclose(fptr);
}

int Superposition(int random_position, int taille, int joueur[24][18], int x, int y){ //Fonction pour vérifier s'il y a superposition ou pas

    int i=0;

    switch(random_position){
        case 1:
            for(i=0;i<=taille;i++){
                if(joueur[x+i][y] != 0)
                    return 1;
            }
            break;
        case 2:
            for(i=0;i<=taille;i++){
                if(joueur[x-i][y] != 0)
                    return 1;
            }
            break;
        case 3:
            for(i=0;i<=taille;i++){
                if(joueur[x][y+i] != 0)
                    return 1;
            }
            break;
        case 4:
            for(i=0;i<=taille;i++){
                if(joueur[x][y-i] != 0)
                    return 1;
            }
            break;
    }
    return 0;

}

void PlacementUnBateau(int joueur[24][18], int tailleX, int tailleY, int taillebateau, int idbateau){  //Fonction pour placement des bateaux

    int i=0;
    int j=0;
    int y=0;
    int x=0;
    int random_position=0;
    int superpo=1;

    for(i=idbateau;i<(idbateau+1);i++){
        random_position=doRand(1,4);
        x=doRand(0, tailleX-1);
        y=doRand(0, tailleY-1);
        superpo=1;
        for(j=0;j<taillebateau;j++){
            if(random_position==1){         //Vers le bas
                while(x+taillebateau>=tailleX || superpo==1){
                    x=doRand(0, tailleX-1);
                    y=doRand(0, tailleY-1);
                    superpo=Superposition(random_position, i, joueur, x, y);
                }
                joueur[x][y]=i;
                joueur[x+j][y]=i;
            }else if(random_position==2){   //Vers le haut
                while(x-taillebateau<0 || superpo==1){
                    x=doRand(0, tailleX-1);
                    y=doRand(0, tailleY-1);
                    superpo=Superposition(random_position, i, joueur, x, y);
                }
                joueur[x][y]=i;
                joueur[x-j][y]=i;
            }else if(random_position==3){   //Vers la droite
                while(y+taillebateau>=tailleY || superpo==1){
                    x=doRand(0, tailleX-1);
                    y=doRand(0, tailleY-1);
                    superpo=Superposition(random_position, i, joueur, x, y);
                }
                joueur[x][y]=i;
                joueur[x][y+j]=i;
            }else if(random_position==4){   //Vers la gauche
                while(y-taillebateau<0 || superpo==1){
                    x=doRand(0, tailleX-1);
                    y=doRand(0, tailleY-1);
                    superpo=Superposition(random_position, i, joueur, x, y);
                }
                joueur[x][y]=i;
                joueur[x][y-j]=i;
            }
        }
    }

}

void PlacementBateauJoueur(int joueur[24][18], int tailleX, int tailleY){

    PlacementUnBateau(joueur, tailleX, tailleY, TAILLE_PORTEAVION, PORTEAVIONID);
    PlacementUnBateau(joueur, tailleX, tailleY, TAILLE_CROISEUR, CROISEURID);
    PlacementUnBateau(joueur, tailleX, tailleY, TAILLE_CROISEUR, CROISEURID);
    PlacementUnBateau(joueur, tailleX, tailleY, TAILLE_CORVETTE, CORVETTEID);
    PlacementUnBateau(joueur, tailleX, tailleY, TAILLE_DESTROYER, DESTROYERID);
    PlacementUnBateau(joueur, tailleX, tailleY, TAILLE_DESTROYER, DESTROYERID);

}

void AffichagePlateau(int joueur[24][18], int tailleX, int tailleY){ //Fonction pour afficher le plateau d'un joueur

    int i=0;
    int j=0;
    char lettre[24]={'0','1','2','3','4','5','6','7','8','9'};

    printf("    ");
    for(i=0;i<tailleX;i++){
        printf("%d ", i);
    }
    printf("\n    ");
    for(i=0;i<tailleX;i++){
        printf("- ");
    }
    for(i=0;i<tailleX;i++){
        printf("\n");
        printf("%c | ", lettre[i]);
        for(j=0;j<tailleY;j++){
            printf("%d ", joueur[i][j]);
        }
    }

}

char SerumDeVerite(int joueur[24][18], int tailleX, int tailleY, int x, int y){   //Fonction pour tester

    int i=0;
    int j=0;
    char *toucheroupas={'0'};

    for(i=0;i<tailleX;i++){
        for(j=0;j<tailleY;j++){
            if(joueur[x][y]==2 || joueur[x][y]==3 || joueur[x][y]==4 || joueur[x][y]==5){
                toucheroupas = "Touche-Coule";
            }else{
                toucheroupas = "Touche";
            }
        }
    }
    return toucheroupas;

}

char *ImmaFiringMahLazor(int x, int y, int joueur[24][18], int tirprecedent[3], int tailleX, int tailleY){

    while(joueur[x][y]==9 || joueur[x][y]==7){
        x=doRand(0, tailleX-1);
        y=doRand(0, tailleY-1);
    }
        if(joueur[x][y]==0){
            joueur[x][y]=9;
            printf("L'IA attaque en %d/%d\n\n", x, y);
            return "Plouf!";
        }else if(joueur[x][y]==CORVETTEID || joueur[x][y]==DESTROYERID || joueur[x][y]==CROISEURID || joueur[x][y]==PORTEAVIONID){
            tirprecedent[0]=x; tirprecedent[1]=y; tirprecedent[2]=joueur[x][y];
            joueur[x][y]=7;
            printf("L'IA attaque en %d/%d\n\n", x, y);
            return "Touche!";
            //return SerumDeVerite(joueur, tailleX, tailleY, x, y);
        }
     return "Vous avez deja tire ici";

}



void IAvsIA(int joueur1[24][18], int joueur2[24][18], int x, int y, int tailleX, int tailleY){

    int tirprecedent2[3]={0};
    int tirprecedent1[3]={0};

    printf("IA vs. IA !\n\n");

        do{
            printf("Choisissez la longueur de votre plateau (compris entre 8 et 10) : ");
            scanf("%d[0-9]", &tailleX);
        }while(tailleX<8 || tailleX>24);
        printf("\n");
        fflush(stdin);

        do{
            printf("Choisissez la largeur de votre plateau (compris entre 8 et 10) : ");
            scanf("%d[0-9]", &tailleY);
        }while(tailleY<8 || tailleY>18);
        printf("\n");
        fflush(stdin);
        system("cls");

        //Placement bateau IA1
        PlacementBateauJoueur(joueur1, tailleX, tailleY);
        //Placement bateau IA2
        PlacementBateauJoueur(joueur2, tailleX, tailleY);


        //Affichage du plateau de l'IA 1
        printf("Plateau de l'IA 1 :\n\n");
        AffichagePlateau(joueur1, tailleX, tailleY);
        printf("\n\n");

        //Affichage du plateau de l'IA 2
        printf("Plateau de l'IA 2 :\n\n");
        AffichagePlateau(joueur2, tailleX, tailleY);
        printf("\n");
        getchar();
        system("cls");

        while(getchar()){

            //L'IA 1 tire sur l'IA 2
            printf("Le joueur 1 tire :\n\n");

            x=doRand(0, tailleX-1);
            y=doRand(0, tailleY-1);

            if(tirprecedent1[0]==0 && tirprecedent1[1]==0){
                printf("%s", ImmaFiringMahLazor(x, y, joueur2, tirprecedent1, tailleX, tailleY));
            }else{
                printf("%s", ImmaFiringMahLazor(tirprecedent1[0], tirprecedent1[1], joueur2, tirprecedent1, tailleX, tailleY));
            }printf("\n\n");

            AffichagePlateau(joueur2, tailleX, tailleY);
            printf("\n\n");

            //L'IA 2 tire sur l'IA 1
            printf("Le joueur 2 tire :\n\n");

            x=doRand(0, tailleX-1);
            y=doRand(0, tailleY-1);

            if(tirprecedent2[0]==0 && tirprecedent2[1]==0){
                printf("%s", ImmaFiringMahLazor(x, y, joueur1, tirprecedent2, tailleX, tailleY));
            }else{
                printf("%s", ImmaFiringMahLazor(tirprecedent2[0], tirprecedent2[1], joueur1, tirprecedent2, tailleX, tailleY));
            }printf("\n\n");

            AffichagePlateau(joueur1, tailleX, tailleY);
            printf("\n\n");
            getchar();
            system("cls");
        }

}

void Menu(int joueur1[24][18], int joueur2[24][18],int x,int y,int tailleX, int tailleY){

    int choix=0;
    int mode=0;

    do{
        printf("Bienvenue dans BattleShip!\n\n");
        printf("1. Jouer\n");
        printf("2. Quitter\n\n");
        printf("Votre choix : ");
        scanf("%d[0-9]", &choix);
        fflush(stdin);
        system("cls");
    }while(choix!=1 && choix!=2);

    if(choix==1){
        printf("Choississez votre mode de jeu :\n\n");
        printf("1. IA vs. IA\n");
        printf("2. Joueur vs. IA\n");
        printf("3. Joueur vs. Joueur\n");
        printf("4. Joueur vs. Faker\n\n");
        printf("Votre choix : ");
        scanf("%d", &mode);
        system("cls");

        if(mode==1){
            IAvsIA(joueur1, joueur2, x, y, tailleX, tailleY); //Mode IA vs IA
        }else if(mode==4){

        printf("Joueur vs Faker !\n\n");
        do{
            printf("Choisissez la longueur de votre plateau (compris entre 8 et 10) : ");
            scanf("%d", &tailleX);
        }while(tailleX<8 || tailleX>10);
            printf("\n");
            fflush(stdin);

        do{
            printf("Choisissez la largeur de votre plateau (compris entre 8 et 10) : ");
            scanf("%d", &tailleY);
        }while(tailleX<8 || tailleX>10);
            printf("\n");
            fflush(stdin);
            system("cls");
        }

    }else(choix==2);

}

void JeuBatailleNavale(){

}

int main(){

    while(1){

        int joueur1[100][100]={0};
        int joueur2[100][100]={0};
        int tailleX=0;
        int tailleY=0;
        int x=0;
        int y=0;

        Menu(joueur1, joueur2, x, y, tailleX, tailleY);
        break;
    }



}

int TestMap(int tailleBateau, int placementBateaux, int* tailleX, int* tailleY, int x, int y){

    int j = 0;
    int i = 0;

    if((placementBateaux == 0 && y+tailleBateau>tailleY) || (placementBateaux == 0 && y-tailleBateau<0)){
        return 0;
    }else{
        return 1;
    }

    if((placementBateaux == 1 && x+tailleBateau>tailleX) || (placementBateaux == 1 && x-tailleBateau<0)){
           return 0;
    }else{
        return 1;
    }

}
