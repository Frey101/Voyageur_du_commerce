#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int main()
{
    short int cord[8][2];    // Tableau pour stocker les coordonnées
    int i = 0, unique, x, y; // Variables et coordonnées

    // Initialisation de nombres aléatoires
    srand(time(NULL));
// Génération des 8 coordonnées differentes
    while (i < 8)
    {
        x = rand() % 48 + 1; // Nombre aléatoire entre 1 et 48 pour x
        y = rand() % 18 + 1; // Nombre aléatoire entre 1 et 18 pour y

        // Vérification  des coordonnées
        for (unique = 0; unique < i; unique++)
        {
            if (cord[unique][0] == x && cord[unique][1] == y)
            {
                break; // Si la coordonnée existe déjà, on sort de la boucle
            }
        }

        // Si les coordonnées sont differentes et unique, on les ajoute au tableau
        if (unique == i)
        {
            cord[i][0] = x; // Enregistrer x
            cord[i][1] = y; // Enregistrer y
            i++;            // Passer à la prochaine coordonnée
        }
    }

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

    Affichage(map);
    printf("\n");
    return 0;
}