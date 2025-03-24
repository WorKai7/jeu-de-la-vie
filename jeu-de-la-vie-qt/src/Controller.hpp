#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Vue.hpp"
#include "Modele.hpp"
#include <QTimer>

class Controller: public QObject {
    Q_OBJECT
    
    private:
        Vue *vue;
        Modele *modele;
        QTimer *timer;
        bool running;

    public:
        // Constructeur par défaut
        Controller();

        // Destructeur
        ~Controller();


        // Méthode pour mettre à jour la vue
        void updateVue() const;


        // Slots
        public slots:
            // Calcule et affiche la génération suivante
            void nextSlot();

            // Affiche la génération précédente
            void previousSlot();

            // Lance la simulation automatique
            void startSimulationSlot();

            // Arrête la simulation automatique
            void stopSimulationSlot();

            // Met à jour la grille lors de la simulation automatique
            void updateSimulation();

            // Met à jour la vitesse de la simulation automatique
            void speedChangedSlot(const int value);

            // Met à jour la taille de la grille avec la nouvelle largeur
            void widthChangedSlot(const int value);

            // Met à jour la taille de la grille avec la nouvelle longueur
            void heightChangedSlot(const int value);

            // Initialise une grille vide
            void emptySlot();

            // Initialise une grille pleine
            void fullSlot();

            // Initialise une grille avec un damier impair
            void damier1Slot();

            // Initialise une grille avec un damier pair
            void damier2Slot();

            // Initialise une grille personnalisée (voir Modele.cpp)
            void listSlot();

            // Initialise une grille aléatoire
            void randomSlot();
};

#endif