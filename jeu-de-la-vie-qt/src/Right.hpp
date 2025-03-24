#ifndef RIGHT_HPP
#define RIGHT_HPP

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>

class Right: public QWidget {
    Q_OBJECT
    
    private:
        QLabel *title;
        QLabel *sizeLabel;
        QLabel *warningLabel;
        QSpinBox *width;
        QSpinBox *height;
        QLabel *cellsAmount;
        QLabel *aliveCellsAmount;
        QLabel *deadCellsAmount;
        QLabel *generation;
        QPushButton *previousButton;
        QPushButton *nextButton;
        QPushButton *startSimulationButton;
        QPushButton *stopSimulationButton;
        QLabel *speedLabel;
        QSlider *simulationSpeedSlider;

    public:
        // Constructeur par défaut
        Right();

        // Destructeur
        ~Right();


        // Getters
        
        QLabel* getGenLabel() const;
        QSpinBox* getWidthLineEdit() const;
        QSpinBox* getHeightLineEdit() const;
        QLabel* getCellsAmountLabel() const;
        QLabel* getAliveCellsAmountLabel() const;
        QLabel* getDeadCellsAmontLabel() const;
        QPushButton* getPreviousButton() const;
        QPushButton* getNextButton() const;
        QPushButton* getStartButton() const;
        QPushButton* getStopButton() const;
        

        // Slots
        public slots:
            void sendPreviousSignal();
            void sendNextSignal();
            void sendStartSignal();
            void sendStopSignal();
            void sendSpeedChangedSignal();
            void sendWidthChangedSignal();
            void sendHeightChangedSignal();
        
        // Signaux
        signals:
            void nextSignal();
            void previousSignal();
            void startSimulationSignal();
            void stopSimulationSignal();
            void speedChangedSignal(int value);
            void widthChangedSignal(int newWidth);
            void heightChangedSignal(int newHeight);
};

#endif