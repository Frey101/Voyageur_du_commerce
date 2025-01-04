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

void Recursif(int n, int a[8], int cord[8][3], float *min, float somme, float distances[8][8], int visited[8])
{
    if (n == 8) // Si tous les points ont été choisis
    {
        somme = 0;
        for (int i = 0; i < 7; i++)
        {
            somme += distances[a[i]][a[i + 1]]; // Ajoute les distances entre les points
        }
        somme += distance(cord[a[0]][0], cord[a[0]][1], 0, 0); // Distance du départ
        somme += distance(cord[a[7]][0], cord[a[7]][1], 0, 0); // Retour au départ

        if (somme < *min) // Si la somme est inférieure au minimum
        {
            *min = somme;
            for (int i = 0; i < 8; i++)
            {
                cord[i][2] = a[i]; // Met à jour les coordonnées
            }
        }
        return;
    }

    // Exploration des permutations
    for (int i = 0; i < 8; i++)
    {
        if (!visited[i]) // Si le point n'a pas encore été visité
        {
            visited[i] = 1;
            a[n] = i;
            Recursif(n + 1, a, cord, min, somme, distances, visited);
            visited[i] = 0; // Réinitialisation du point pour les autres permutations
        }
    }
}

// Lancement de la recherche de façon récursive :
void Recherche_Itineraire_Recursif(int cord[8][3], float distances[8][8])
{
    int a[8] = {0};       // Tableau pour stocker les indices du chemin
    int visited[8] = {0}; // Tableau pour marquer les points visités
    float min = 2000.0f;
    Recursif(0, a, cord, &min, 0.0f, distances, visited);
    printf("Distance minimale : %.2f\n", min);
    printf("Chemin optimal : ");
    for (int i = 0; i < 8; i++)
    {
        printf("%d ", cord[i][2] + 1); // Affiche l'ordre des indices dans le chemin optimal (1 à 8)
    }
    printf("\n");
}

// *-----------------------------------------------------------------------------------------------------------------------------
// Recherche de l'itinéraire le plus court de façon heuristique (on prend la ville la plus proche à chaque fois) :
void Recherche_Heuristique(int cord[8][3], float distances[8][8])
{
    int visited[8] = {0}; // Tableau pour marquer les villes visitées
    int current_city = -1;
    float min_distance;
    int next_city;

    // Trouver la première ville la plus proche de l'origine (0, 0)
    min_distance = 2000.0f; // Distance initiale très grande
    for (int i = 0; i < 8; i++)
    {
        float dist = distance(0, 0, cord[i][0], cord[i][1]);
        if (dist < min_distance)
        {
            min_distance = dist;
            current_city = i;
        }
    }

    visited[current_city] = 1; // Marquer la première ville comme visitée
    cord[current_city][2] = 1; // Première ville dans l'itinéraire

    // Trouver les autres villes dans l'ordre heuristique
    for (int step = 2; step <= 8; step++)
    {
        min_distance = 2000.0f;
        next_city = -1;

        // Trouver la ville non visitée la plus proche de la ville actuelle
        for (int i = 0; i < 8; i++)
        {
            if (!visited[i] && distances[current_city][i] < min_distance)
            {
                min_distance = distances[current_city][i];
                next_city = i;
            }
        }

        if (next_city != -1)
        {
            visited[next_city] = 1;    // Marquer la ville comme visitée
            cord[next_city][2] = step; // Définir son ordre dans l'itinéraire
            current_city = next_city;  // Passer à la ville suivante
        }
    }
}

void Nettoyer_Carte(char map[49][19])
{
    for (int y = 1; y < 18; y++)
    {
        for (int x = 1; x < 48; x++)
        {
            if (map[x][y] >= '1' && map[x][y] <= '8')
            {
                map[x][y] = ' '; // Remplace les chiffres par des espaces
            }
        }
    }
}
void Ecriture_Itineraire(char map[49][19], int cord[8][3])
{
    Nettoyer_Carte(map); // Supprime les anciens numéros

    for (int a = 0; a < 8; a++)
    {
        int x = cord[a][0];
        int y = cord[a][1];
        char digit = '1' + cord[a][2] - 1; // Convertit l'ordre en caractère

        // Place le chiffre autour de 'X' sans écraser les bordures ou 'X'
        if (map[x + 1][y] == ' ')
            map[x + 1][y] = digit; // À droite
        else if (map[x - 1][y] == ' ')
            map[x - 1][y] = digit; // À gauche
        else if (map[x][y + 1] == ' ')
            map[x][y + 1] = digit; // En bas
        else if (map[x][y - 1] == ' ')
            map[x][y - 1] = digit; // En haut
        else
            map[x][y] = digit; // Si aucune place, écrase le 'X'
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

    // chemin iteratif
    Recherche_ItineraireIteratif(cord, distances);
    Ecriture_Itineraire(map, cord);
    printf("Itineraire en version ITERATIVE :\n");
    Affichage(map);
    printf("\n");

    // chemin recursif
    Recherche_Itineraire_Recursif(cord, distances);
    Ecriture_Itineraire(map, cord);
    printf("Itineraire en version RECURSIVE :\n");
    Affichage(map);
    printf("\n");

    // chemin Heuristique
    // Recherche_Heuristique(cord, distances);

    // printf("Itineraire en version Heuristique :\n");
    // Affichage(map);
    // printf("\n");

    // Après avoir effectué la recherche heuristique
    Recherche_Heuristique(cord, distances); // Utilisation de l'algorithme heuristique
    Ecriture_Itineraire(map, cord);
    // Afficher la carte mise à jour avec l'itinéraire heuristique
    printf("Itineraire en version HEURISTIQUE :\n");
    Affichage(map);
    printf("\n");

    return 0;
}