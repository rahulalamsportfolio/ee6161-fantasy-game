# Qt project file for EE6161 Fantasy Game

QT += core gui widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    src/characters/Character.cpp \
    src/characters/Human.cpp \
    src/characters/Elf.cpp \
    src/characters/Dwarf.cpp \
    src/characters/Hobbit.cpp \
    src/characters/Orc.cpp \
    src/items/Weapon.cpp \
    src/items/Armour.cpp \
    src/items/Shield.cpp \
    src/items/Ring.cpp \
    src/items/Potion.cpp \
    src/items/Spell.cpp \
    src/game/Square.cpp \
    src/game/Board.cpp \
    src/game/Game.cpp \
    src/ui/MainWindow.cpp \
    src/ui/GameWidget.cpp

HEADERS += \
    src/characters/Character.h \
    src/characters/Human.h \
    src/characters/Elf.h \
    src/characters/Dwarf.h \
    src/characters/Hobbit.h \
    src/characters/Orc.h \
    src/items/Item.h \
    src/items/Weapon.h \
    src/items/Armour.h \
    src/items/Shield.h \
    src/items/Ring.h \
    src/items/Potion.h \
    src/items/Spell.h \
    src/game/Square.h \
    src/game/Board.h \
    src/game/Game.h \
    src/ui/MainWindow.h \
    src/ui/GameWidget.h

INCLUDEPATH += src
