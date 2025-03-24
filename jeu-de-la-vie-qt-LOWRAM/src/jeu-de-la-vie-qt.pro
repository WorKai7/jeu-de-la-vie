QT += core gui widgets

HEADERS = GraphicGrid.hpp Right.hpp Vue.hpp Grille.hpp Modele.hpp Controller.hpp
                
SOURCES = GraphicGrid.cpp Right.cpp Vue.cpp Grille.cpp Modele.cpp Controller.cpp \
          main.cpp

CONFIG += moc_depends


# install
target.path = $$[QT_INSTALL_EXAMPLES]/miniQt
INSTALLS += target
