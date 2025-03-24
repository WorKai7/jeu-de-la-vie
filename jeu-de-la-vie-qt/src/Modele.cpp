#include "Modele.hpp"
#include <vector>
#include <iostream>

Modele::Modele() {
    width = 10;
    height = 10;
    grid = new Grille();
    simulationSpeed = 500;
    liste = {{0, 0}, {0, 2}, {1, 1}, {1, 2}, {2, 1}};
}

Modele::~Modele() {
    delete grid;
}

Grille* Modele::getGrid() const {
    return grid;
}

int Modele::getSimulationSpeed() const {
    return this->simulationSpeed;
}

void Modele::setSimulationSpeed(const int value) {
    this->simulationSpeed = value;
}

void Modele::newGrid(const int opt) {
    delete grid;

    if (opt == 5) {
        grid = new Grille(width, height, liste);
    } else {
        grid = new Grille(width, height, opt);
    }
}

void Modele::changeGridSize(const int value, const std::string attr) {
    Grille *newGrid;

    // Nouvelle grille avec les bonnes dimensions
    if (attr == "width") {
        newGrid = new Grille(value, this->height);
        this->width = value;
    } else {
        newGrid = new Grille(this->width, value);
        this->height = value;
    }

    // Initialisation vide
    newGrid->initEmpty();

    // Mise à jour
    this->grid = newGrid;
}