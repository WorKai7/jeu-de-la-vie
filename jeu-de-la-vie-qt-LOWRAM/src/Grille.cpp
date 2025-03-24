#include <iostream>
#include "Grille.hpp"

Grille::Grille()
{
    this->grid = nullptr;
    this->generation = 1;
    this->width = 10;
    this->height = 10;
    this->initEmpty();
}

Grille::Grille(const Grille &grille)
{
    this->grid = nullptr;
    this->generation = 1;
    this->width = grille.width;
    this->height = grille.height;
    this->grid = grille.grid;
}

Grille::Grille(const int width, const int height)
{
    this->grid = nullptr;
    this->generation = 1;
    this->width = width;
    this->height = height;
    this->initEmpty();
}

Grille::Grille(const int width, const int height, const int option)
{
    this->grid = nullptr;
    this->generation = 1;
    this->width = width;
    this->height = height;

    switch (option)
    {
    case 0:
        this->initEmpty();
        break;

    case 1:
        this->initFull();
        break;

    case 2:
        this->initDamier(0);
        break;

    case 3:
        this->initDamier(1);
        break;

    case 4:
        this->initRandom();
        break;

    default:
        std::cout << "Erreur de valeur pour l'option, initialisation d'une grille vide..." << std::endl;
        this->initEmpty();
        break;
    }
}

Grille::Grille(const int width, const int height, const std::vector<std::vector<int>> &list)
{
    this->grid = nullptr;
    this->generation = 1;
    this->width = width;
    this->height = height;
    this->initWithList(list);
}

Grille::~Grille()
{
    this->freeGrid();
}

void Grille::initEmpty()
{
    this->freeGrid();

    this->grid = new int *[this->height];

    for (int i = 0; i < this->height; i++)
    {
        grid[i] = new int[this->width];
        for (int j = 0; j < this->width; j++)
        {
            grid[i][j] = 0;
        }
    }
}

void Grille::initFull()
{
    this->freeGrid();

    this->grid = new int *[this->height];

    for (int i = 0; i < this->height; i++)
    {
        grid[i] = new int[this->width];
        for (int j = 0; j < this->width; j++)
        {
            grid[i][j] = 1;
        }
    }
}

void Grille::initDamier(int choice)
{
    this->freeGrid();
    
    if (choice != 0 && choice != 1)
    {
        std::cout << "Erreur de saisie, initialisation d'un damier de type:" << std::endl
                  << "| 1 | 0 | 1 |" << std::endl
                  << "| 0 | 1 | 0 |" << std::endl
                  << "| 1 | 0 | 1 |" << std::endl;

        choice = 0;
    }

    this->grid = new int *[this->height];

    for (int i = 0; i < this->height; i++)
    {
        grid[i] = new int[this->width];
        for (int j = 0; j < this->width; j++)
        {
            if ((i + j) % 2 == choice % 2)
            {
                grid[i][j] = 1;
            }
            else
            {
                grid[i][j] = 0;
            }
        }
    }
}

void Grille::initRandom()
{
    this->freeGrid();

    this->grid = new int *[this->height];
    srand(time(0));

    for (int i = 0; i < this->height; i++)
    {
        grid[i] = new int[this->width];
        for (int j = 0; j < this->width; j++)
        {
            grid[i][j] = rand() % 2;
        }
    }
}

void Grille::initWithList(const std::vector<std::vector<int>> &list)
{
    this->initEmpty();

    for (std::vector<int> coord : list)
    {
        this->grid[coord[0]][coord[1]] = 1;
    }
}

std::vector<std::vector<int>> Grille::getAliveNeighbors(const int y, const int x) const
{
    std::vector<std::vector<int>> neighbors;

    // Liste des coordonnées autour de la case entrée en paramètre
    int neighborsCoordinates[8][2] = {
        {y - 1, x - 1},
        {y - 1, x},
        {y - 1, x + 1},
        {y, x - 1},
        {y, x + 1},
        {y + 1, x - 1},
        {y + 1, x},
        {y + 1, x + 1}};

    // Pour chaque coordonnée, si elle ne dépasse pas les limites de la grille et si la case est vivante, on l'ajoute à la liste des voisins
    for (int i = 0; i < 8; i++)
    {
        if (neighborsCoordinates[i][0] >= 0 && neighborsCoordinates[i][0] < this->height &&
            neighborsCoordinates[i][1] >= 0 && neighborsCoordinates[i][1] < this->width)
        {
            if (this->grid[neighborsCoordinates[i][0]][neighborsCoordinates[i][1]])
            {
                neighbors.push_back({neighborsCoordinates[i][0], neighborsCoordinates[i][1]});
            }
        }
    }

    return neighbors;
}

int **Grille::copyGrid() const
{
    int **newGrid = new int *[this->height];
    for (int i = 0; i < this->height; i++)
    {
        newGrid[i] = new int[this->width];
        for (int j = 0; j < this->width; j++)
        {
            newGrid[i][j] = this->grid[i][j];
        }
    }

    return newGrid;
}

int Grille::getGeneration() const
{
    return this->generation;
}

int Grille::getWidth() const
{
    return this->width;
}

int Grille::getHeight() const
{
    return this->height;
}

int **Grille::getGrid() const
{
    return this->grid;
}

void Grille::print() const
{
    std::cout << std::endl;
    for (int i = 0; i < this->height; i++)
    {
        std::cout << "| ";
        for (int j = 0; j < this->width; j++)
        {
            std::cout << this->grid[i][j] << " | ";
        }
        std::cout << std::endl;
    }
}

void Grille::nextGeneration()
{
    int **newGrid = this->copyGrid();

    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            std::vector<std::vector<int>> voisins = this->getAliveNeighbors(i, j);

            if (this->grid[i][j])
            {
                if (voisins.size() < 2 || voisins.size() > 3)
                {
                    newGrid[i][j] = 0;
                }
            }
            else
            {
                if (voisins.size() == 3)
                {
                    newGrid[i][j] = 1;
                }
            }
        }
    }

    this->freeGrid();
    this->grid = newGrid;
    this->generation++;
}

int Grille::getCellsAmount() const
{
    return this->width * this->height;
}

int Grille::getAliveCellsAmount() const
{
    int count = 0;
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            if (this->grid[i][j])
            {
                count++;
            }
        }
    }

    return count;
}

int Grille::getDeadCellsAmount() const
{
    return this->getCellsAmount() - this->getAliveCellsAmount();
}

float Grille::getAliveCellsPercentage() const
{
    return (float)this->getAliveCellsAmount() / this->getCellsAmount() * 100;
}

float Grille::getDeadCellsPercentage() const
{
    return (float)this->getDeadCellsAmount() / this->getCellsAmount() * 100;
}

void Grille::showStatistics() const
{
    std::cout << std::endl
              << "Grille de " << this->width << "x" << this->height << std::endl
              << "Génération n°" << this->generation << std::endl
              << "Nombre de cellules: " << this->getCellsAmount() << std::endl
              << "Nombre de cellules vivantes: " << this->getAliveCellsAmount() << std::endl
              << "Nombre de cellules mortes: " << this->getDeadCellsAmount() << std::endl
              << "Pourcentages de cellules vivantes: " << this->getAliveCellsPercentage() << "%" << std::endl
              << "Pourcentages de cellules mortes: " << this->getDeadCellsPercentage() << "%" << std::endl;
}

void Grille::setCase(const int i, const int j, const int val) {
    this->grid[i][j] = val;
}

void Grille::freeGrid() {
    if (this->grid != nullptr) {
        for (int i = 0; i < this->height; i++) {
            delete[] grid[i];
        }
        delete[] grid;
    }
}