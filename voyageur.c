#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

// Affichage de la map
void Affichage(char map[49][19])
{
    for (int y = 0; y <= 18; y++)
    {
        for (int x = 0; x <= 48; x++)
        {
            printf("%c", map[x][y]);
        }
        printf("\n");
    }
}

// Fonction pour calculer la distance entre deux points
double distance(int x1, int y1, int x2, int y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// Recherche de l'itinéraire le plus court selon des calculs exhaustifs
void Recherche_ItineraireIteratif(int cord[8][3], float distances[8][8])
{
    float min = 2000, somme;
    int c1, c2, c3, c4, c5, c6, c7, c8;

    for (c1 = 0; c1 < 8; c1++)
    {
        for (c2 = 0; c2 < 8; c2++)
        {
            if (c2 != c1)
            {
                for (c3 = 0; c3 < 8; c3++)
                {
                    if (c3 != c1 && c3 != c2)
                    {
                        for (c4 = 0; c4 < 8; c4++)
                        {
                            if (c4 != c1 && c4 != c2 && c4 != c3)
                            {
                                for (c5 = 0; c5 < 8; c5++)
                                {
                                    if (c5 != c1 && c5 != c2 && c5 != c3 && c5 != c4)
                                    {
                                        for (c6 = 0; c6 < 8; c6++)
                                        {
                                            if (c6 != c1 && c6 != c2 && c6 != c3 && c6 != c4 && c6 != c5)
                                            {
                                                for (c7 = 0; c7 < 8; c7++)
                                                {
                                                    if (c7 != c1 && c7 != c2 && c7 != c3 && c7 != c4 && c7 != c5 && c7 != c6)
                                                    {
                                                        for (c8 = 0; c8 < 8; c8++)
                                                        {
                                                            if (c8 != c1 && c8 != c2 && c8 != c3 && c8 != c4 && c8 != c5 && c8 != c6 && c8 != c7)
                                                            {
                                                                somme = distance(0, 0, cord[c1][0], cord[c1][1]) +
                                                                        distances[c1][c2] + distances[c2][c3] +
                                                                        distances[c3][c4] + distances[c4][c5] +
                                                                        distances[c5][c6] + distances[c6][c7] +
                                                                        distances[c7][c8] + distance(cord[c8][0], cord[c8][1], 0, 0);
                                                                if (somme < min)
                                                                {
                                                                    min = somme;
                                                                    cord[0][2] = c1;
                                                                    cord[1][2] = c2;
                                                                    cord[2][2] = c3;
                                                                    cord[3][2] = c4;
                                                                    cord[4][2] = c5;
                                                                    cord[5][2] = c6;
                                                                    cord[6][2] = c7;
                                                                    cord[7][2] = c8;
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

// Supression des chiffres autour des 'X' :
void Itineraire_Vierge(char map[49][19], int cord[8][3])
{
    for (int a = 0; a <= 7; a++)
    {
        map[cord[a][0]][cord[a][1]] = 'X'; // Remise du point sur la position initiale.
    }
}

// Ecriture de l'itinéraire sur la map en faisant attention à ne pas écraser de bordure, de chiffre ou de 'X' :
void Ecriture_Itineraire(char map[49][19], int cord[8][3])
{
    Itineraire_Vierge(map, cord); // Effacer l'itinéraire précédent

    // Placer les chiffres de 1 à 8 à côté des 'X'
    for (int a = 0; a < 8; a++) // Commence à 0 et termine à 7, soit 8 itérations
    {
        int x = cord[a][0];
        int y = cord[a][1];
        char digit = '1' + a; // Convertir l'index en caractère ASCII, de '1' à '8'

        // Vérifier les cases autour du 'X' pour placer le chiffre
        if (map[x + 1][y] == ' ')
        {
            map[x + 1][y] = digit; // Placer à droite
        }
        else if (map[x - 1][y] == ' ')
        {
            map[x - 1][y] = digit; // Placer à gauche
        }
        else if (map[x][y + 1] == ' ')
        {
            map[x][y + 1] = digit; // Placer en bas
        }
        else if (map[x][y - 1] == ' ')
        {
            map[x][y - 1] = digit; // Placer en haut
        }
        else
        {
            map[x][y] = digit; // Si aucune place n'est trouvée, écraser 'X'
        }
    }
}

int main()
{
    int cord[8][3]; // Tableau pour stocker les coordonnées
    int i = 0, unique, x, y;

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

    // Affichage des coordonnées
    for (i = 0; i < 8; i++)
    {
        printf("Coordonnée %d: (%d, %d)\n", i + 1, cord[i][0], cord[i][1]);
    }

    char map[49][19]; // Taille du tableau en deux dimensions

    // INITIALISATION : on met le caractère "espace" dans chaque case du tableau (de la map) :
    for (int y = 0; y <= 18; y++)
    {
        for (int x = 0; x <= 48; x++)
        {
            map[x][y] = ' ';
        }
    }

    // Mise des bordures de la map
    for (int x = 0; x <= 48; x++)
    {
        map[x][0] = '-';
        map[x][18] = '-';
    }

    for (int y = 0; y <= 18; y++)
    {
        map[0][y] = '|';
        map[48][y] = '|';
    }

    // Placement des 'X' selon les coordonnées générées
    for (i = 0; i <= 7; i++)
    {
        map[cord[i][0]][cord[i][1]] = 'X';
    }
    int A, B;
    float distances[8][8]; // Matrice pour stocker les distances entre les points
    for (A = 0; A <= 7; A++)
    {
        for (B = 0; B <= 7; B++)
        {
            distances[A][B] = sqrt(pow(cord[A][0] - cord[B][0], 2) + pow(cord[A][1] - cord[B][1], 2));
            // pow = calcule de la puissance
            distances[B][A] = distances[A][B];
        }
    }
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

    // ---
    printf("Map de depart:\n");
    Affichage(map);
    printf("\n");

    // printf("Map chemin le plus court (iteratif)\n");
    // Affichage(map);
    // printf("\n");

    Recherche_ItineraireIteratif(cord, distances);
    Ecriture_Itineraire(map, cord);
    printf("Itineraire en version ITERATIVE :\n");
    Affichage(map);
    printf("\n");

    return 0;
}