#ifndef Grille_HPP
#define Grille_HPP

#include <vector>

class Grille
{
private:
    int generation;
    int width;
    int height;
    int **grid;
    std::vector<int**> history;

    // Initialisation d'une grille pleine
    void initFull();

    /*
        Initialisation d'une grille en damier selon un choix binaire:

              | 1 | 0 | 1 |   ----   | 0 | 1 | 0 |
              | 0 | 1 | 0 |    ou    | 1 | 0 | 1 |
              | 1 | 0 | 1 |   ----   | 0 | 1 | 0 |

    */
    void initDamier(int choice);

    // Initialisation d'une grille aléatoire
    void initRandom();

    /*
         Initialisation d'une grille à l'aide d'une liste de cases
         - Sous la forme: {{x, y}, {x, y}, {x, y}}
    */
    void initWithList(const std::vector<std::vector<int>> &list);

    // Méthode utile pour récupérer une liste des voisins de la case [x, y] donnée en paramètre
    std::vector<std::vector<int>> getAliveNeighbors(const int y, const int x) const;

    // Méthode utile pour copier une grille de manière profonde
    int **copyGrid() const;

public:
    // Attributs statiques constants pour les options pour construire la grille
    static const int EMPTY = 0;
    static const int FULL = 1;
    static const int DAMIER1 = 2;
    static const int DAMIER2 = 3;
    static const int RANDOM = 4;

    // Constructeur par défaut: initialise une grille vide de 10x10
    Grille();

    // Constructeur par copie
    Grille(const Grille &grille);

    // Constructeur prenant en paramètre une largeur et une hauteur (initialise une grille vide)
    Grille(const int width, const int height);

    /*
        Constructeur prenant en paramètre une largeur et une hauteur et une option d'initialisation
        - Options possibles:
            > Grille::EMPTY
            > Grille::FULL
            > Grille::DAMIER
            > Grille::RANDOM
    */
    Grille(const int width, const int height, const int option);

    /*
        Grille prenant en paramètre une largeur et une hauteur et une liste de cases
        - Sous la forme: {{x, y}, {x, y}, {x, y}}
    */
    Grille(const int width, const int height, const std::vector<std::vector<int>> &list);

    // Destructeur
    ~Grille();

    // Initialisation de la grille vide
    void initEmpty();

    // Getters

    int getGeneration() const;
    int getWidth() const;
    int getHeight() const;
    int **getGrid() const;

    // Setters

    void setCase(const int i, const int j, const int val);

    // Méthode pour afficher la grille en mode texte
    void print() const;

    // Méthode pour avancer d'une génération
    void nextGeneration();

    // Méthode pour reculer d'une génération
    void previousGeneration();

    // Méthodes de statistiques

    int getCellsAmount() const;
    int getAliveCellsAmount() const;
    int getDeadCellsAmount() const;
    float getAliveCellsPercentage() const;
    float getDeadCellsPercentage() const;

    // Affiche un texte qui regroupe chaque statistiques
    void showStatistics() const;

    // Efface la grille de la mémoire
    void freeGrid();
};

#endif