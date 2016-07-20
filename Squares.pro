TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    game/game.cpp \
    managers/fontmanager.cpp \
    utils/directory.cpp \
    utils/file.cpp \
    utils/graphics.cpp \
    utils/timer.cpp \
    models/player.cpp \
    graphics/drawable.cpp \
    models/map.cpp \
    models/mapblock.cpp \
    models/ennemy_block.cpp \
    models/hud.cpp \
    utils/mathematics.cpp \
    models/auto_block.cpp \
    models/life_block.cpp \
    models/shield_block.cpp \
    models/score_block.cpp \
    managers/sound_manager.cpp \
    audio/jukebox.cpp \
    models/menu.cpp \
    utils/key_limitor.cpp \
    game/event_handler.cpp \
    game/engine.cpp \
    game/mouse_texts_focusable.cpp

LIBS += -pthread \
        -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system \
        -lboost_regex -lboost_filesystem -lboost_system

HEADERS += \
    game/game.hpp \
    managers/fontmanager.hpp \
    utils/directory.hpp \
    utils/file.hpp \
    utils/graphics.hpp \
    utils/random.hpp \
    utils/timer.hpp \
    models/player.hpp \
    graphics/drawable.hpp \
    models/map.hpp \
    models/mapblock.hpp \
    models/ennemy_block.hpp \
    models/hud.hpp \
    utils/mathematics.hpp \
    models/auto_block.hpp \
    models/life_block.hpp \
    models/shield_block.hpp \
    models/score_block.hpp \
    managers/sound_manager.hpp \
    audio/jukebox.hpp \
    models/menu.hpp \
    utils/key_limitor.hpp \
    game/event_handler.hpp \
    game/engine.hpp \
    graphics/window.hpp \
    game/mouse_texts_focusable.hpp
