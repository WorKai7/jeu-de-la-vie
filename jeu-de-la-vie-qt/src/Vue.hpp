#ifndef VUE_HPP
#define VUE_HPP

#include <QMainWindow>
#include "Right.hpp"
#include "GraphicGrid.hpp"

class Vue : public QMainWindow
{
    Q_OBJECT
    
    private:
        QMenuBar *menuBar;
        GraphicGrid *graphicGrid;
        Right *right;

    public:
        // Constructeur par défaut
        Vue();

        // Destructeur
        ~Vue();


        // Getters

        Right* getRight() const;


        // Méthode pour mettre à jour la grille graphique
        void updateGraphicGrid(int** grid, const int width, const int height);


        // Slots
        public slots:
            void sendEmptySignal();
            void sendFullSignal();
            void sendDamier1Signal();
            void sendDamier2Signal();
            void sendListSignal();
            void sendRandomSignal();

        // Signaux
        signals:
            void emptySignal();
            void fullSignal();
            void damier1Signal();
            void damier2Signal();
            void listSignal();
            void randomSignal();
};

#endif
