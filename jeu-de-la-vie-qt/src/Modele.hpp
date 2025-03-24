#ifndef MODELE_HPP
#define MODELE_HPP

#include "Grille.hpp"
#include <iostream>

class Modele {
    private:
        Grille *grid;
        int width;
        int height;
        int simulationSpeed;
        std::vector<std::vector<int>> liste;

    public:
        // Constructeur par défaut (initialise une grille vide de 10x10)
        Modele();

        // Destructeur
        ~Modele();

        // Getters

        Grille* getGrid() const;
        int getSimulationSpeed() const;

        // Setters

        void setSimulationSpeed(const int value);


        /*
            Méthode pour initialiser une nouvelle grille
            @param opt Option d'initialisation:
            - Options possibles:
            > 0 -> Grille vide
            > 1 -> Grille pleine
            > 2 -> Grille avec damier impair
            > 3 -> Grille avec damier pair
            > 4 -> Grille aléatoire
            > 5 -> Grille personnalisée
        */
        void newGrid(const int opt);

        /*
            Méthode pour changer la taille de la grille
            @param value Nouvelle valeur
            @param attr "width" ou "height" pour choisir quelle valeur changer
        */
        void changeGridSize(const int value, const std::string attr);
};

#endif