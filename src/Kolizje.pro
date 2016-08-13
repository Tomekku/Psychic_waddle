TEMPLATE = app
CONFIG += console
CONFIG -= qt





CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

INCLUDEPATH += "/home/SFML/include"
DEPENDPATH += "/home/SFML/include"


SOURCES += main.cpp \
    game.cpp \
    block.cpp \
    randoms.cpp \
    mazegenerator.cpp \
    ai.cpp \
    player.cpp

HEADERS += \
    game.h \
    block.h \
    randoms.h \
    mazegenerator.h \
    ai.h \
    player.h


