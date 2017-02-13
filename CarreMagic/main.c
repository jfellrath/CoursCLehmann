// Nom
//La carré magique

//But
// Afficher un carré dont la somme de chaques lignes / colonnes ainsi que les 2 diagonals est identique.

//Entree
// Un tableau multidimensionnel carré, une structure de type point.x point.y, une structure de type increment
// Une fonction init pour initialiser le tableau
// Une fonction Avancer pour avancer en diagonal N-E ou N-O
// Une fonction qui verifie si la case est libre.

// Sortie:
// Le tableau qui affiche les nombres en carré.


#include <stdio.h>
#include <stdlib.h>

#define TAILLE 7 // Définie la taille du carré.

typedef int increment; // Pour Incrémenter la variable de la boucle principal.

typedef struct Point{ // La structure coordonnee pour se déplacer dans le tableau
    int x;
    int y;
}Point;

void init(int t[][TAILLE]); // Initialise le tableau multi

void affiche(int t[][TAILLE]); // Affiche le tableau en résultat

void avancer(Point *coord,int test); // Cette fonction déplace les coordonnées X et Y

int verif(int t[][TAILLE],Point coord); // Cette fonction verif qu'une case est libre.

int main()
{
    int carre[TAILLE][TAILLE];

    Point mPoint;

    mPoint.x = TAILLE/2-1;
    mPoint.y = (TAILLE/2);

    init(carre);

    carre[mPoint.x][mPoint.y] = 1;

    increment i = 1;

    int test = 0;

    int tableauRempli = 1;

    // Boucle de remplissage du tableau
    while(i<TAILLE*TAILLE){

        avancer(&mPoint,test);

        test = verif(carre,mPoint);

        if(test == 0){
            carre[mPoint.x][mPoint.y] = i+1;
            i++;
        }

    }

    affiche(carre);

    return 0;

}

void init(int t[][TAILLE]){

    increment i,j;

    for(i=0;i<TAILLE;i++){
        for(j=0;j<TAILLE;j++){
            t[i][j] = 0;
        }
    }
}

void affiche(int t[][TAILLE]){

    increment i,j;

    for(i=0;i<TAILLE;i++){
        for(j=0;j<TAILLE;j++){
            printf("%d  ",t[i][j]);
        }
        printf("\n");
    }
}

void avancer(Point *coord,int test){

    coord->x--; // On monte tout le temps

    if(coord->x < 0){ // si on sort du carre on repars en bas
        coord->x = TAILLE-1;
    }

    if (test){ // si la case est pas libre (la fonction verif retourne ce test) on pars vers NORD-OUEST
        coord->y--;
    }else{
        coord->y++; // sinon on part vers NORD-EST
    }

    // test si on sort du cadre NORD-EST ou NORD-OUEST
    if(coord->y < 0){
        coord->y = TAILLE-1;
    }
    if(coord->y > TAILLE-1){
        coord->y = 0;
    }

}

int verif(int t[][TAILLE],Point coord){

    if(t[coord.x][coord.y] == 0){
        return 0; // Retourne 0 si la case est libre
    }else{
        return 1; // 1 si il y a déjà une valeur.
    }

}



