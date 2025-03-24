#include <GraphicGrid.hpp>
#include <QPainter>
#include <QRect>

GraphicGrid::GraphicGrid() {
    this->gridWidth = 10;
    this->gridHeight = 10;

    this->grid = new int *[this->gridHeight];

    for (int i = 0; i < this->gridHeight; i++)
    {
        this->grid[i] = new int[this->gridWidth];
        for (int j = 0; j < this->gridWidth; j++)
        {
            this->grid[i][j] = 0;
        }
    }
}

GraphicGrid::GraphicGrid(int** grid, int width, int height) {
    this->updateGrid(grid, width, height);
}

GraphicGrid::~GraphicGrid() {
    this->clearGrid();
}

void GraphicGrid::updateGrid(int** newGrid, const int width, const int height) {
    this->clearGrid();
    this->setWidth(width);
    this->setHeight(height);
    this->setGrid(newGrid);
    update();
}

void GraphicGrid::paintEvent(QPaintEvent* event) {
    // Initialisation du painter
    QPainter painter(this);

    // Calcul de la largeur et hauteur des cases en forcant leur type
    double cellsWidth = static_cast<double>(width()) / gridWidth;
    double cellsHeight = static_cast<double>(height()) / gridHeight;

    // Determination du côté le plus petit pour l'appliquer au 4 côtés (pour avoir un carré parfait)
    double size = std::min(cellsWidth, cellsHeight);

    // Creation et dessin de chaque rectangle
    for (int i = 0; i < this->gridHeight; i++) {
        for (int j = 0; j < this->gridWidth; j++) {
            QRect rect(j * size, i * size, size, size);

            if (this->grid[i][j]) {
                painter.fillRect(rect, Qt::white);
            } else {
                painter.fillRect(rect, Qt::black);
            }
        }
    }
}

int** GraphicGrid::getGrid() const {
    return this->grid;
}

int GraphicGrid::getWidth() const {
    return this->gridWidth;
}

int GraphicGrid::getHeight() const {
    return this->gridHeight;
}

void GraphicGrid::clearGrid() {
    if (this->grid) {
        for (int i = 0; i < this->gridHeight; i++) {
            delete[] this->grid[i];
        }
        delete[] this->grid;
    }
}

void GraphicGrid::setWidth(int width) {
    this->gridWidth = width;
}

void GraphicGrid::setHeight(int height) {
    this->gridHeight = height;
}

void GraphicGrid::setGrid(int** newGrid) {
    this->grid = new int *[this->gridHeight];

    for (int i = 0; i < this->gridHeight; i++)
    {
        this->grid[i] = new int[this->gridWidth];
        for (int j = 0; j < this->gridWidth; j++)
        {
            this->grid[i][j] = newGrid[i][j];
        }
    }
}