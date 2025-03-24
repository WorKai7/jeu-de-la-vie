#include "Controller.hpp"
#include <chrono>
#include <thread>

Controller::Controller() {
    // Attributs
    this->vue = new Vue();
    this->modele = new Modele();
    this->timer = new QTimer(this);
    this->running = false;


    // Connexion de tous les signaux venus de la vue vers les slots qui mènent au modèle (Architecture MVC)
    connect(vue->getRight(), SIGNAL(nextSignal()), this, SLOT(nextSlot()));
    connect(vue->getRight(), SIGNAL(startSimulationSignal()), this, SLOT(startSimulationSlot()));
    connect(vue->getRight(), SIGNAL(stopSimulationSignal()), this, SLOT(stopSimulationSlot()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateSimulation()));
    connect(vue->getRight(), SIGNAL(speedChangedSignal(const int)), this, SLOT(speedChangedSlot(int)));
    connect(vue->getRight(), SIGNAL(widthChangedSignal(const int)), this, SLOT(widthChangedSlot(int)));
    connect(vue->getRight(), SIGNAL(heightChangedSignal(const int)), this, SLOT(heightChangedSlot(int)));
    connect(vue, SIGNAL(emptySignal()), this, SLOT(emptySlot()));
    connect(vue, SIGNAL(fullSignal()), this, SLOT(fullSlot()));
    connect(vue, SIGNAL(damier1Signal()), this, SLOT(damier1Slot()));
    connect(vue, SIGNAL(damier2Signal()), this, SLOT(damier2Slot()));
    connect(vue, SIGNAL(listSignal()), this, SLOT(listSlot()));
    connect(vue, SIGNAL(randomSignal()), this, SLOT(randomSlot()));


    // Mise à jour de la vue
    this->updateVue();

    // Affichage de la fenêtre à l'écran
    this->vue->show();
}

Controller::~Controller() {
    delete this->vue;
    delete this->modele;
    delete this->timer;
}

void Controller::nextSlot() {
    this->modele->getGrid()->nextGeneration();
    this->updateVue();
}

void Controller::startSimulationSlot() {
    this->running = true;
    this->vue->getRight()->getWidthLineEdit()->setDisabled(true);
    this->vue->getRight()->getHeightLineEdit()->setDisabled(true);
    this->vue->getRight()->getNextButton()->setDisabled(true);
    this->vue->getRight()->getStartButton()->setDisabled(true);
    this->vue->getRight()->getStopButton()->setDisabled(false);
    this->timer->start(this->modele->getSimulationSpeed());
}

void Controller::stopSimulationSlot() {
    this->running = false;
    this->vue->getRight()->getWidthLineEdit()->setDisabled(false);
    this->vue->getRight()->getHeightLineEdit()->setDisabled(false);
    this->vue->getRight()->getNextButton()->setDisabled(false);
    this->vue->getRight()->getStartButton()->setDisabled(false);
    this->vue->getRight()->getStopButton()->setDisabled(true);
    this->timer->stop();
}

void Controller::speedChangedSlot(const int value) {
    this->modele->setSimulationSpeed(550 - value);
    if (this->running) {
        this->timer->stop();
        this->timer->start(this->modele->getSimulationSpeed());
    }
}

void Controller::widthChangedSlot(const int value) {
    this->modele->changeGridSize(value, "width");
    this->updateVue();
}

void Controller::heightChangedSlot(const int value) {
    this->modele->changeGridSize(value, "height");
    this->updateVue();
}

void Controller::updateSimulation() {
    if (this->running) {
        this->modele->getGrid()->nextGeneration();
        this->updateVue();
    }
}

void Controller::updateVue() const {
    this->vue->updateGraphicGrid(this->modele->getGrid()->getGrid(), this->modele->getGrid()->getWidth(), this->modele->getGrid()->getHeight());
    this->vue->getRight()->getGenLabel()->setText("Génération: " + QString::number(this->modele->getGrid()->getGeneration()));
    this->vue->getRight()->getWidthLineEdit()->setValue(this->modele->getGrid()->getWidth());
    this->vue->getRight()->getHeightLineEdit()->setValue(this->modele->getGrid()->getHeight());
    this->vue->getRight()->getCellsAmountLabel()->setText("Nombre de cellules: " + QString::number(this->modele->getGrid()->getCellsAmount()));
    this->vue->getRight()->getAliveCellsAmountLabel()->setText("Nombre de cellules vivantes: " + QString::number(this->modele->getGrid()->getAliveCellsAmount()) + " (" + QString::number(this->modele->getGrid()->getAliveCellsPercentage()) + "%)");
    this->vue->getRight()->getDeadCellsAmontLabel()->setText("Nombre de cellules mortes: " + QString::number(this->modele->getGrid()->getDeadCellsAmount()) + " (" + QString::number(this->modele->getGrid()->getDeadCellsPercentage()) + "%)");
}

void Controller::emptySlot() {
    this->modele->newGrid(0);
    this->updateVue();
}

void Controller::fullSlot() {
    this->modele->newGrid(1);
    this->updateVue();
}

void Controller::damier1Slot() {
    this->modele->newGrid(2);
    this->updateVue();
}

void Controller::damier2Slot() {
    this->modele->newGrid(3);
    this->updateVue();
}

void Controller::listSlot() {
    this->modele->newGrid(5);
    this->updateVue();
}

void Controller::randomSlot() {
    this->modele->newGrid(4);
    this->updateVue();
}