#ifndef GRAPHICGRID_HPP
#define GRAPHICGRID_HPP

#include <QWidget>

class GraphicGrid: public QWidget 
{
    Q_OBJECT
    
    private:
        int** grid;
        int gridWidth;
        int gridHeight;

        // Méthode pour effacer la grille de la mémoire
        void clearGrid();

        // Setters (utilisation dans updateGrid())

        void setGrid(int** grid);
        void setWidth(int width);
        void setHeight(int height);

    public:
        // Constructeur par défaut (initialise une grille vide de 10x10)
        GraphicGrid();

        // Constructeur prenant en paramètre une grille, une largeur et une hauteur
        GraphicGrid(int** grid, const int width, const int height);

        // Destructeur
        ~GraphicGrid();


        // Getters

        int** getGrid() const;
        int getWidth() const;
        int getHeight() const;


        /*
            Méthode pour mettre à jour la grille graphique
            @param newGrid nouvelle grille à afficher
            @param width largeur de cette nouvelle grille
            @param height hauteur de cette nouvelle grille
        */
        void updateGrid(int** newGrid, const int width, const int height);

    protected:
        // Override de la méthode paintEvent pour dessiner la grille sur la fenêtre
        void paintEvent(QPaintEvent *event) override;
};

#endif
