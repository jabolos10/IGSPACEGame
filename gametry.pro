TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "C:/SFML-2.5.1/include"

LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}


SOURCES += \
        Bullet.cpp \
        EnemyBullet.cpp \
        EnemyBullet2.cpp \
        EnemyBullet2Reverse.cpp \
        EnemyShip.cpp \
        EnemyShip2.cpp \
        FloatingText.cpp \
        Game.cpp \
        Healthbar.cpp \
        PlayerShip.cpp \
        Ship.cpp \
        main.cpp

HEADERS += \
    Bullet.h \
    EnemyBullet.h \
    EnemyBullet2.h \
    EnemyBullet2Reverse.h \
    EnemyShip.h \
    EnemyShip2.h \
    FloatingText.h \
    Game.h \
    Healthbar.h \
    PlayerShip.h \
    Ship.h
