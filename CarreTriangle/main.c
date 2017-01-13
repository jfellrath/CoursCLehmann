#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i = 0;
    int j = 0; // i et j sont utilisé pour les boucles for
    int hauteur = 0;
    int largeur = 0; // définisse les dimensions du carré ou du trinagle
    int choix = 0;
    char car = ' '; // Retient la saisie du client pour le triangle


    do{
        printf("1: Carre\n2: Croix\n0: Quitter:\n");
        scanf("%d",&choix);

        switch(choix){
            case 1:
                printf("Veuillez saisir une largeur:\n");
                scanf("%d",&largeur);
                printf("Veuillez saisir une hauteur:\n");
                scanf("%d",&hauteur);

                for (i=0;i<hauteur;i++){
                    for (j=0;j<largeur;j++){
                        if (i>0 && i<hauteur-1){
                            if(j>0 && j<largeur-1){
                                printf("*");
                            }else{
                                printf("0");
                            }
                        }else{
                            printf("0");
                        }
                    }
                    printf("\n");
                }
            ;break;
            case 2:
                printf("Veuillez saisir une largeur:\n");
                scanf("%d",&largeur);
                printf("Veuillez saisir une hauteur:\n");
                scanf("%d",&hauteur);
                printf("Quelle signe pour votre croix ?\n");
                fflush(stdin);
                scanf("%c",&car);

                for (i=0;i<=hauteur;i++){
                    for (j=0;j<=largeur;j++){
                        if (j == i || j == largeur-i){
                            printf("%c",car);
                        }else{
                            printf(" ");
                        }
                    }
                    printf("\n");
                }
            ;break;
            case 0:;break;
            default:printf("Mauvais choix");
            break;
        }
    }while (choix != 0);

    return 0;

}
