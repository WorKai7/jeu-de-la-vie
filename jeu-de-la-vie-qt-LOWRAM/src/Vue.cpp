#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include "Vue.hpp"

Vue::Vue()
{
    // Propriétées de la fenêtre
    setWindowTitle(tr("Jeu de la vie"));
    resize(900, 600);

    // Barre de menu en haut
    this->menuBar = new QMenuBar();
    QMenu *newMenu = this->menuBar->addMenu("Nouveau");
    QAction *empty = new QAction("Grille vide", this);
    QAction *full = new QAction("Grille pleine", this);
    QAction *list = new QAction("Grille personalisée", this);
    QAction *random = new QAction("Grille aléatoire", this);

    // Sous menu
    QMenu *damier = newMenu->addMenu("Grille en damier");
    QAction *damier1 = new QAction("Damier impair", this);
    QAction *damier2 = new QAction("Damier pair", this);

    newMenu->addAction(empty);
    newMenu->addAction(full);
    newMenu->addMenu(damier);
    damier->addAction(damier1);
    damier->addAction(damier2);
    newMenu->addAction(list);
    newMenu->addAction(random);

    setMenuBar(this->menuBar);
    

    // Création de la zone de travail centrale
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    // Layout horizontal (grille à gauche et menu à droite)
    QHBoxLayout *hlayout = new QHBoxLayout(central);

    // Initialisation des deux parties de la fenêtre
    graphicGrid = new GraphicGrid();
    right = new Right();

    // Ajout au layout
    hlayout->addWidget(graphicGrid);
    hlayout->addWidget(right);

    central->setLayout(hlayout);


    // Connexion des signaux et slots
    connect(empty, SIGNAL(triggered()), this, SLOT(sendEmptySignal()));
    connect(full, SIGNAL(triggered()), this, SLOT(sendFullSignal()));
    connect(damier1, SIGNAL(triggered()), this, SLOT(sendDamier1Signal()));
    connect(damier2, SIGNAL(triggered()), this, SLOT(sendDamier2Signal()));
    connect(list, SIGNAL(triggered()), this, SLOT(sendListSignal()));
    connect(random, SIGNAL(triggered()), this, SLOT(sendRandomSignal()));
}

Vue::~Vue()
{
    delete menuBar;
    delete graphicGrid;
    delete right;
}

void Vue::updateGraphicGrid(int **grid, const int width, const int height)
{
    graphicGrid->updateGrid(grid, width, height);
}

Right *Vue::getRight() const
{
    return this->right;
}

void Vue::sendEmptySignal()
{
    emit emptySignal();
}

void Vue::sendFullSignal()
{
    emit fullSignal();
}

void Vue::sendDamier1Signal()
{
    emit damier1Signal();
}

void Vue::sendDamier2Signal()
{
    emit damier2Signal();
}

void Vue::sendListSignal()
{
    emit listSignal();
}

void Vue::sendRandomSignal()
{
    emit randomSignal();
}