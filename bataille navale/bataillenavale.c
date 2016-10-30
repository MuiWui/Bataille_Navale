#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define PORTEAVIONID 4
#define CROISEURID 3
#define TORPILLEURID 2
#define SOUSMARINID 1

int main()
{

    while(1){

        int joueur1[100][100] = {0};
        int joueur2[100][100] = {0};
        int bateau[4];
        int ii = 0;
        int jj = 0;
        int kk = 0;
        int yJ1 = 0;
        int yJ2 = 0;
        int xJ2 = 0;
        int xJ1 = 0;
        int tailleX = 0;
        int tailleY = 0;

        printf("Choisissez la longueur de votre plateau : ");
        scanf("%d", &tailleX);
        printf("\n");
        fflush(stdin);
        printf("Choisissez la largeur de votre plateau : ");
        scanf("%d", &tailleY);
        printf("\n");
        fflush(stdin);

        //Placement bateau JOUEUR1
        for(ii=0;ii<5;ii++){
            xJ1=rand()%(tailleX+1);
            yJ1=rand()%(tailleY+1);
            placementbateau = rand()%(2);
            for(jj=0;jj<ii;jj++){
                if(placementbateau == 0){
                    joueur1[xJ1][yJ1] = ii;
                    joueur1[xJ1+jj][yJ1] = ii;
                }else{
                    joueur1[xJ1][yJ1] = ii;
                    joueur1[xJ1][yJ1+jj] = ii;
                }
            }
        }

        //Placement bateau JOUEUR2
        for(ii=0;ii<5;ii++){
            xJ2=rand()%(tailleX+1);
            yJ2=rand()%(tailleY+1);
            placementbateau = rand()%(2);
            for(jj=0;jj<ii;jj++){
                if(placementbateau=0){
                    joueur2[xJ2][yJ2] = ii;
                    joueur2[xJ2-jj][yJ2] = ii;
                }else if{
                    joueur2[xJ2][yJ2] = ii;
                    joueur2[xJ2][yJ2-jj] = ii;
            }
        }

        printf("Plateau de l'IA 1 :\n");

        //PLATEAU JOUEUR1
        for(ii = 0;ii < tailleX; ii++){
            printf("\n");
            for(jj = 0;jj < tailleY; jj++){
                printf("%d ", joueur1[ii][jj]);
            }
        }

        printf("\n");
        printf("\n");
        printf("Plateau de l'IA 2 :\n");

        //PLATEAU JOUEUR2
        for(ii = 0;ii < tailleX; ii++){
            printf("\n");
            for(jj = 0;jj < tailleY; jj++){
                printf("%d ", joueur2[ii][jj]);
            }
        }

        printf("\n");
        printf("\n");

        //Résultats JOUEUR1
        printf("Resultats Joueur1 :\n");
        for(ii=0;ii<tailleX;ii++){
            printf("\n");
            for(jj=0;jj<tailleY;jj++){
                if(joueur1[ii][jj] == 0){
                    joueur1[ii][jj] = 9;
                }
                printf("%d ", joueur1[ii][jj]);
            }
        }

        printf("\n");
        printf("\n");

        //Résultats JOUEUR2
        printf("Resultats Joueur2 :\n");
        for(ii=0;ii<tailleX;ii++){
            printf("\n");
            for(jj=0;jj<tailleY;jj++){
                if(joueur2[ii][jj] == 0){
                    joueur2[ii][jj] = 9;
                }
                printf("%d ", joueur2[ii][jj]);
            }
        }

        printf("\n");
        printf("\n");

    }

return 0;

}
