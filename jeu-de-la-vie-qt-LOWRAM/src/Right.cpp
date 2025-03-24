#include <QVBoxLayout>
#include <QHBoxLayout>

#include "Right.hpp"

Right::Right() {
    // Propriétées du widget
    setMaximumWidth(300);

    // Layouts
    QVBoxLayout *vLayout = new QVBoxLayout();
    QHBoxLayout *hLayout1 = new QHBoxLayout();

    // Attributs
    this->title = new QLabel("Bienvenue dans le jeu de la vie !");
    this->sizeLabel = new QLabel("Taille de la grille (largeur, hauteur):");
    this->warningLabel = new QLabel("Attention, changer les dimensions réinitialisera la grille !");
    this->warningLabel->setWordWrap(true);
    this->width = new QSpinBox();
    this->height = new QSpinBox();
    this->width->setMinimum(1);
    this->width->setMaximum(1000);
    this->height->setMinimum(1);
    this->height->setMaximum(1000);
    this->generation = new QLabel("Génération: 0");
    this->cellsAmount = new QLabel("Nombre de cellules: 0");
    this->aliveCellsAmount = new QLabel("Nombre de cellules vivantes: 0 (0%)");
    this->deadCellsAmount = new QLabel("Nombre de cellules mortes: 0 (0%)");
    this->nextButton = new QPushButton("Gen suivante");
    this->startSimulationButton = new QPushButton("Lancer la simulation");
    this->stopSimulationButton = new QPushButton("Arrêter la simulation");
    this->stopSimulationButton->setDisabled(true);
    this->speedLabel = new QLabel("Vitesse de simulation: ");
    this->simulationSpeedSlider = new QSlider(Qt::Horizontal);
    this->simulationSpeedSlider->setRange(50, 500);
    this->simulationSpeedSlider->setValue(100);

    // Ajout des attributs à la fenêtre
    vLayout->addWidget(title);
    vLayout->addSpacing(20);
    vLayout->addWidget(sizeLabel);
    vLayout->addSpacing(10);
    vLayout->addWidget(warningLabel);
    hLayout1->addWidget(width);
    hLayout1->addWidget(height);
    vLayout->addLayout(hLayout1);
    vLayout->addSpacing(20);
    vLayout->addWidget(generation);
    vLayout->addWidget(cellsAmount);
    vLayout->addWidget(aliveCellsAmount);
    vLayout->addWidget(deadCellsAmount);
    vLayout->addSpacing(30);
    vLayout->addWidget(nextButton);
    vLayout->addWidget(startSimulationButton);
    vLayout->addWidget(stopSimulationButton);
    vLayout->addWidget(speedLabel);
    vLayout->addWidget(simulationSpeedSlider);

    // Alignement
    title->setAlignment(Qt::AlignCenter);
    sizeLabel->setAlignment(Qt::AlignCenter);
    warningLabel->setAlignment(Qt::AlignCenter);
    generation->setAlignment(Qt::AlignCenter);
    cellsAmount->setAlignment(Qt::AlignCenter);
    aliveCellsAmount->setAlignment(Qt::AlignCenter);
    deadCellsAmount->setAlignment(Qt::AlignCenter);
    vLayout->setAlignment(Qt::AlignCenter);

    setLayout(vLayout);


    // Connexion des signaux et slots
    connect(nextButton, SIGNAL(clicked(bool)), this, SLOT(sendNextSignal()));
    connect(startSimulationButton, SIGNAL(clicked(bool)), this, SLOT(sendStartSignal()));
    connect(stopSimulationButton, SIGNAL(clicked(bool)), this, SLOT(sendStopSignal()));
    connect(simulationSpeedSlider, SIGNAL(valueChanged(int)), this, SLOT(sendSpeedChangedSignal()));
    connect(width, SIGNAL(valueChanged(int)), this, SLOT(sendWidthChangedSignal()));
    connect(height, SIGNAL(valueChanged(int)), this, SLOT(sendHeightChangedSignal()));
}

Right::~Right() {
    delete title;
    delete sizeLabel;
    delete width;
    delete height;
    delete cellsAmount;
    delete aliveCellsAmount;
    delete deadCellsAmount;
    delete generation;
    delete nextButton;
    delete startSimulationButton;
    delete stopSimulationButton;
    delete speedLabel;
    delete simulationSpeedSlider;
}

void Right::sendNextSignal() {
    emit Right::nextSignal();
}

void Right::sendStartSignal() {
    emit Right::startSimulationSignal();
}

void Right::sendStopSignal() {
    emit Right::stopSimulationSignal();
}

void Right::sendSpeedChangedSignal() {
    emit Right::speedChangedSignal(this->simulationSpeedSlider->value());
}

void Right::sendWidthChangedSignal() {
    emit Right::widthChangedSignal(this->width->value());
}

void Right::sendHeightChangedSignal() {
    emit Right::heightChangedSignal(this->height->value());
}

QLabel* Right::getGenLabel() const {
    return this->generation;
}

QSpinBox* Right::getWidthLineEdit() const {
    return width;
}

QSpinBox* Right::getHeightLineEdit() const {
    return height;
}

QLabel* Right::getCellsAmountLabel() const {
    return cellsAmount;
}

QLabel* Right::getAliveCellsAmountLabel() const {
    return aliveCellsAmount;
}

QLabel* Right::getDeadCellsAmontLabel() const {
   return deadCellsAmount;
}

QPushButton* Right::getNextButton() const {
    return nextButton;
}

QPushButton* Right::getStartButton() const {
    return startSimulationButton;
}

QPushButton* Right::getStopButton() const {
    return stopSimulationButton;
}