#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

// gcc test1.c -o t
/*-------------------------------------------------------------------------------------------------------------*/
// Affichage de la map
void Affichage(char map[49][19])
{
    int x, y;
    for (y = 0; y <= 18; y++)
    {
        for (x = 0; x <= 48; x++)
        {
            printf("%c", map[x][y]);
        }
        printf("\n");
    }
}
/*-------------------------------------------------------------------------------------------------------------*/

// Fonction pour calculer la distance entre deux points
double distance(int x1, int y1, int x2, int y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
/*-------------------------------------------------------------------------------------------------------------*/
// (VERSION ITERATIVE) Recherche de l'itinéraire le plus court selon des calculs exhaustifs :
void Recherche_Itineraire_Iteratif(int coordonnee[8][3], float matrice[8][8])
{
    int c1, c2, c3, c4, c5, c6, c7, c8;
    float min = 2000, somme;
    ;
}

/*------------------------------------------------------------------------------------------------------------*/
int main()
{
    short int cord[8][2];   // Tableau pour stocker les coordonnées
    double distances[8][8]; // Matrice pour stocker les distances entre les points

    int i = 0, unique, x, y; // Variables et coordonnées

    /*-------------------------------------------------------------------------------------------------------------*/

    // Initialisation de nombres aléatoires
    srand(time(NULL));

    // Génération des 8 coordonnées différentes sans être sur les bordures
    while (i < 8)
    {
        x = rand() % 46 + 2; // Nombre aléatoire entre 2 et 47 pour x
        y = rand() % 16 + 2; // Nombre aléatoire entre 2 et 17 pour y

        // Vérification des coordonnées pour éviter les doublons
        for (unique = 0; unique < i; unique++)
        {
            if (cord[unique][0] == x && cord[unique][1] == y)
            {
                break; // Si la coordonnée existe déjà, on sort de la boucle
            }
        }

        // Si les coordonnées sont uniques, on les ajoute au tableau
        if (unique == i)
        {
            cord[i][0] = x; // Enregistrer x
            cord[i][1] = y; // Enregistrer y
            i++;            // Passer à la prochaine coordonnée
        }
    }

    /*-------------------------------------------------------------------------------------------------------------*/

    // Affichage des coordonnées
    for (i = 0; i < 8; i++)
    {
        printf("Coordonnée %d: (%d, %d)\n", i + 1, cord[i][0], cord[i][1]);
    }

    char map[49][19]; // Taille du tableau en deux dimensions

    // INITIALISATION : on met le caractère "espace" dans chaque case du tableau (de la map):
    for (y = 0; y <= 18; y++)
    {
        for (x = 0; x <= 48; x++)
        {
            map[x][y] = ' ';
        }
    }

    // on met le caractère "-" sur la première et dernière ligne sur chaque colonne :
    for (x = 0; x <= 48; x++)
    {
        map[x][0] = '-';
        map[x][18] = '-';
    }

    // on met le caractère "|" sur la première et dernière colonne sur chaque ligne :
    for (y = 0; y <= 18; y++)
    {
        map[0][y] = '|';
        map[48][y] = '|';
    }
    // on met 8 "X" dans le tableau en fonction des coordonnées :
    for (i = 0; i <= 7; i++)
    {
        map[cord[i][0]][cord[i][1]] = 'X';
    }

    // Calcul de la matrice des distances
    for (i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (i == j)
            {
                // Distance entre un point et l'origine (0, 0) sur la diagonale
                distances[i][j] = distance(cord[i][0], cord[i][1], 0, 0);
            }
            else
            {
                // Distance entre deux points
                distances[i][j] = distance(cord[i][0], cord[i][1], cord[j][0], cord[j][1]);
            }
        }
    }

    /*-------------------------------------------------------------------------------------------------------------*/

    // Affichage de la matrice des distances
    printf("\nMatrice des distances :\n");
    for (i = 0; i < 8; i++)
    {
        printf("Coordonée %d : ", i + 1);
        for (int j = 0; j < 8; j++)
        {

            printf("%.2f\t", distances[i][j]);
        }
        printf("\n");
    }

    printf("\nMap Basique\n");
    Affichage(map);
    printf("\n");

    return 0;
}
/*-------------------------------------------------------------------------------------------------------------*/