/*
BUT Jouer à la bataille naval
ENTREE:
    Structure Cellule qui représente (la grille du jeu et une cellule d'un bateau)
    Structure Bateau composé d'un ensemble de cellule.
    Structure composé d'un ensemble de bateau.
    Une fonction de création d'une cellule, elle prend en parametre la ligne et la colonne associé à la cellule
    Une fonction de comparaison de deux cellule, cette fonction renverra vrai ou faux selon le cas
    Une fonction de création de bateau elle renverra une struct bateau correctement rempli
    Une fonction qui vérifie qu'une cellule appartient à un bateau. return vrai/faux
    ATTENTION cette fonction utilisera la fonction de comparaison de cellule.
    Une fonction qui vérifie qu'une céllule appartient à une flotte de bateau.
    ATTENTION cette fonction utilisera la fonction de vérification pour un bateau.
SORTIE:
    Une bataille naval fonctionnel.
*/


#include <stdio.h>
#include <stdlib.h>


#define TAILLE_FLOTTE 5
#define TAILLE_BATEAU 3

typedef enum BOOL{
    FALSE,TRUE
}BOOL;

/*
    chaque cellule contient une coordonnée X et Y, un numero flotte, un numero bateau, un numero cellule, un etat.
    Les valeurs seront comparé au choix de l'utilisateur.
    Le choix de l'utilisateur sera également de type cellule.
    La valeur etat servira à savoir si une cellule d'un bateau à été touché ou non.
*/
typedef struct CELLULE{
    int X;
    int Y;
    int numeroFlotte;
    int numeroBateau;
    int numeroCellule;
    BOOL etat; // Bateau touché ou pas
}CELLULE;

// Chaque bateau possede également un état pour savoir si toutes les cellules d'un bateau ont été touché.
typedef struct BATEAU{
    BOOL etat;
    CELLULE cel[TAILLE_BATEAU];
}BATEAU;

typedef struct FLOTTE{
    BATEAU bateau[TAILLE_FLOTTE];
}FLOTTE;


void Initialisation(FLOTTE *flotte);
void Affichage(FLOTTE *flotte,int numeroFlotte);


CELLULE createCellule(int x,int y,int numeroBateau,int numeroFlotte,int numeroCellule);
BATEAU createBateau(CELLULE cel1,CELLULE cel2,CELLULE cel3);
void createFlotte(FLOTTE *flotte);



BOOL celluleIdentique(CELLULE cel1,CELLULE *cel2); // Renvoie true si les cellules sont identiques
BOOL verifCelFlotte(FLOTTE *flotte,int numeroFlotte,CELLULE *choix);
BOOL verifCelBateau(FLOTTE *flotte,int numeroFlotte,CELLULE *choix);

void verifBateauCoule(FLOTTE *flotte,int numeroFlotte);
BOOL verifFlotteCoule(FLOTTE *flotte, int numeroFlotte);

BOOL verifChoix(FLOTTE *flotte,int numeroFlotte,CELLULE *choix);


int main()
{
    //PLATEAU plateau;
    FLOTTE flotte[2];
    CELLULE choix = {-1,-1,-1,-1,FALSE};
    int tour = 1;
    BOOL terminer = TRUE;


    Initialisation(flotte);

    printf("Bienvenue dans la bataille naval !\nPour jouer, chaque joueur doit donner deux coordonnees X et Y.\n");
    printf("Ces coordonnes doivent etre comprises entre 0 et 9.\n");
    printf("X indique la ligne et Y indique la colonne.\n");
    printf("Pour chaque joueur, le numero des bateaux detruits par l'adversaire vous sont indique.\n");
    printf("Pour gagner, vous devez toucher couler 5 fois votre adversaire.\n");
    printf("Bonne chance !\n\n");



    do{
        if(tour == 1){
            Affichage(flotte,1);
            verifBateauCoule(flotte,0);
            do
            {
                // Initialisation du choix à chaque tour
                choix.etat = FALSE;
                choix.numeroBateau = -1;
                choix.numeroCellule = -1;
                choix.numeroFlotte = -1;
                // Demande au joueur une coordonnée X et Y
                printf("Joueur %d : X: ",tour);
                scanf("%d",&choix.X);
                printf("Joueur %d : Y: ",tour);
                scanf("%d",&choix.Y);

                // Si le choix est ok
            }while(verifChoix(flotte,1,&choix));

            // On passe au joueur 2
            tour = 2;
        }else if(tour == 2){
            Affichage(flotte,0);
            verifBateauCoule(flotte,1);
            do
            {
                choix.etat = FALSE;
                choix.numeroBateau = -1;
                choix.numeroCellule = -1;
                choix.numeroFlotte = -1;
                printf("Joueur %d : X: ",tour);
                scanf("%d",&choix.X);
                printf("Joueur %d : Y: ",tour);
                scanf("%d",&choix.Y);
            }while(verifChoix(flotte,0,&choix));
            tour = 1;
        }

        // Verification de l'état des bateaux de la flotte de chaque joueur.
        if(verifFlotteCoule(flotte,0)){
            terminer = FALSE;
        }else if(verifFlotteCoule(flotte,1)){
            terminer = FALSE;
        }
    }while(terminer);

    // Indication de vainqueur !
    printf("Joueur %d gagne la partie !",tour);
    return 0;
}


// Initialise la flotte des joueurs.
void Initialisation(FLOTTE *flotte){
    createFlotte(flotte);
}

// Affiche aux joueurs les coordonnées de chaque cellule d'un bateau touché.
void Affichage(FLOTTE *flotte,int numeroFlotte){
    int k,l;

    for(k=0;k<TAILLE_FLOTTE;k++){
        for(l=0;l<TAILLE_BATEAU;l++){
            if((flotte[numeroFlotte].bateau[k].cel[l].etat)){
                printf("%d, %d\n",flotte[numeroFlotte].bateau[k].cel[l].X,flotte[numeroFlotte].bateau[k].cel[l].Y);
            }
        }
    }
}

// Remplis une cellule en fonction des paramètres.
CELLULE createCellule(int x,int y,int numeroBateau,int numeroFlotte,int numeroCellule){
    CELLULE cel;
    cel.X = x;
    cel.Y = y;
    cel.etat = FALSE;
    cel.numeroBateau = numeroBateau;
    cel.numeroFlotte = numeroFlotte;
    cel.numeroCellule = numeroCellule;
    return cel;
}

// Remplis un bateau
BATEAU createBateau(CELLULE cel1,CELLULE cel2,CELLULE cel3){
    BATEAU bateau;
    bateau.etat = FALSE;
    bateau.cel[0] = cel1;
    bateau.cel[1] = cel2;
    bateau.cel[2] = cel3;
    return bateau;
}

// Créer la flotte des joueurs.
void createFlotte(FLOTTE *flotte){
    flotte[0].bateau[0] = createBateau(createCellule(0,0,0,0,0),createCellule(0,1,0,0,1),createCellule(0,2,0,0,2));
    flotte[0].bateau[1] = createBateau(createCellule(1,2,1,0,0),createCellule(2,2,1,0,1),createCellule(3,2,1,0,2));
    flotte[0].bateau[2] = createBateau(createCellule(4,2,2,0,0),createCellule(4,3,2,0,1),createCellule(4,4,2,0,2));
    flotte[0].bateau[3] = createBateau(createCellule(1,9,3,0,0),createCellule(2,9,3,0,1),createCellule(3,9,3,0,2));
    flotte[0].bateau[4] = createBateau(createCellule(2,4,4,0,0),createCellule(2,5,4,0,1),createCellule(2,6,4,0,2));

    flotte[1].bateau[0] = createBateau(createCellule(0,4,0,1,0),createCellule(0,5,0,1,1),createCellule(0,6,0,1,2));
    flotte[1].bateau[1] = createBateau(createCellule(1,0,1,1,0),createCellule(2,0,1,1,1),createCellule(3,0,1,1,2));
    flotte[1].bateau[2] = createBateau(createCellule(1,3,2,1,0),createCellule(2,3,2,1,1),createCellule(3,3,2,1,2));
    flotte[1].bateau[3] = createBateau(createCellule(3,8,3,1,0),createCellule(4,8,3,1,1),createCellule(5,8,3,1,2));
    flotte[1].bateau[4] = createBateau(createCellule(7,4,4,1,0),createCellule(7,5,4,1,1),createCellule(7,6,4,1,2));
}

// Retourne vrai si deux cellules sont identiques.
BOOL celluleIdentique(CELLULE cel1,CELLULE *cel2){
    if((cel1.X == cel2->X) && (cel1.Y == cel2->Y)){
        return TRUE;
    }else{
        return FALSE;
    }
}

// Compare le choix avec les cellules de chaque bateau.
// La cellule choix du joueur est complété par la céllule du bateau si il y à correspondance.
// La variable état du choix et setté à vrai et est retourné par la fonction.
BOOL verifCelBateau(FLOTTE *flotte,int numeroFlotte,CELLULE *choix){
    int i,j;
    for(i=0;i<TAILLE_FLOTTE;i++){ // Pour chaque bateau
        for(j=0;j<TAILLE_BATEAU;j++){ // Pour chaque cellule de bateau
            if(celluleIdentique(flotte[numeroFlotte].bateau[i].cel[j],choix)){
                if(!flotte[numeroFlotte].bateau[i].cel[j].etat)
                *choix = flotte[numeroFlotte].bateau[i].cel[j];
                choix->etat = TRUE;
            }
        }
    }

    return choix->etat;
}

// Si il y a un bateau, il y a une flotte. Pour vérifier une flotte on vérifie donc s'il y a un bateau.
BOOL verifCelFlotte(FLOTTE *flotte,int numeroFlotte,CELLULE *choix){
    return verifCelBateau(flotte,numeroFlotte,choix);
}

// Cette procedure incrémente une variable chaque fois qu'une cellule de bateau est touché.
// Chaque bateau possède 3 cellule donc quand cette variable vaut trois c'est que tout le bateau est touché.
// On passe donc l'etat du bateau à vrai
void verifBateauCoule(FLOTTE *flotte,int numeroFlotte){
    int i,j,nbr;
    nbr = 0;
    for(i=0;i<TAILLE_FLOTTE;i++){
        for(j=0;j<TAILLE_BATEAU;j++){
            if(flotte[numeroFlotte].bateau[i].cel[j].etat == TRUE){
                nbr++;
                if(nbr == 3){
                    printf("Bateau %d Touche coule !\n",flotte[numeroFlotte].bateau[i].cel[j].numeroBateau+1);
                    if(flotte[numeroFlotte].bateau[i].etat == FALSE){
                        flotte[numeroFlotte].bateau[i].etat = TRUE;
                    }
                    nbr=0;
                }
            }
        }
    }
}

// Cette fonction incrémente une variable chaque fois qu'un bateau est touché.
// Chaque flotte possède 5 bateau donc lorsque cette variable vaut 5, tous les bateaux sont touché les partie s'arrète !
BOOL verifFlotteCoule(FLOTTE *flotte, int numeroFlotte){
    int i,nbr = 0;
    for(i=0;i<TAILLE_FLOTTE;i++){
        if(flotte[numeroFlotte].bateau[i].etat){
            nbr++;
        }
    }
    if(nbr == 5){
        printf("\n\n%d\n\n",nbr);
        return TRUE;
    }else{
        printf("\n\n%d\n\n",nbr);
        return FALSE;
    }

}

// Vérifie que le choix de l'utilisateur est correcte et qu'il correspond à un bateau si c'est le cas, le fonction set la cellule d'un bateau à true.
BOOL verifChoix(FLOTTE *flotte,int numeroFlotte,CELLULE *choix){
    if((choix->X >=0) && (choix->X <=9) && (choix->Y >= 0) && (choix->Y <=9)){
        verifCelFlotte(flotte,numeroFlotte,choix);

        if(choix->numeroBateau != -1){
             if(choix->etat) {
                flotte[numeroFlotte].bateau[choix->numeroBateau].cel[choix->numeroCellule].etat = TRUE;
                printf("Bateau touche !\n\n");
                return FALSE;
            }else{
                // Cette ligne n'est jamais executé mais si je ne la rajoute pas, le compilateur râle car il manque un return.
                // Et si elle devais quand même ce produire les joueurs en sont informé.
                printf("\n\nUne erreur s'est produite, la partie risque d'être éroné. Nous vous conseillons de recommencer.\n\n");
                return TRUE;
            }
        }else{
            printf("Aucun bateau\n\n");
            return FALSE;
        }
    }else{
        printf("Ce choix n'est pas valide !\n");
        return TRUE;
    }
}




