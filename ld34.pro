TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network -llua -ldl
QMAKE_CXXFLAGS += -std=c++11 -D DEBUG
#QMAKE_CXXFLAGS += -std=c++11
# These lines are for i386 arch executable. It needs lib32 libraries
#QMAKE_CXXFLAGS += -m32
#QMAKE_LFLAGS += -m32
OBJECTS_DIR = .obj

SOURCES += main.cpp \
    controllers/playercontroller.cpp \
    entities/emitternode.cpp \
    entities/entity.cpp \
    entities/particlenode.cpp \
    entities/quadtree.cpp \
    entities/scenenode.cpp \
    entities/soundnode.cpp \
    entities/spritenode.cpp \
    entities/textnode.cpp \
    events/command.cpp \
    events/commandqueue.cpp \
    GUI/button.cpp \
    GUI/container.cpp \
    GUI/label.cpp \
    GUI/lineedit.cpp \
    GUI/widget.cpp \
    resources/affectors.cpp \
    resources/animation.cpp \
    resources/musicplayer.cpp \
    resources/particle.cpp \
    resources/scriptplayer.cpp \
    resources/soundplayer.cpp \
    states/paralleltask.cpp \
    states/state.cpp \
    states/statestack.cpp \
    states/titlestate.cpp \
    application.cpp \
    datatables.cpp \
    utils.cpp \
    utils.inl \
    world.cpp \
    resources/posteffect.cpp \
    resources/bloomeffect.cpp \
    states/gamestate.cpp \
    entities/player.cpp \
    entities/wall.cpp \
    entities/crate.cpp \
    entities/uiscore.cpp \
    entities/uibonus.cpp \
    entities/doortrigger.cpp \
    states/pausestate.cpp

OTHER_FILES +=

HEADERS += \
    world.hpp \
    utils.hpp \
    datatables.hpp \
    application.hpp \
    states/titlestate.hpp \
    states/statestack.hpp \
    states/stateidentifiers.hpp \
    states/state.hpp \
    states/paralleltask.hpp \
    resources/soundplayer.hpp \
    resources/scriptplayer.hpp \
    resources/resourceidentifiers.hpp \
    resources/resourceholder.hpp \
    resources/particle.hpp \
    resources/musicplayer.hpp \
    resources/animation.hpp \
    resources/affectors.hpp \
    GUI/widget.hpp \
    GUI/lineedit.hpp \
    GUI/label.hpp \
    GUI/container.hpp \
    GUI/button.hpp \
    events/commandqueue.hpp \
    events/command.hpp \
    events/category.hpp \
    entities/textnode.hpp \
    entities/spritenode.hpp \
    entities/soundnode.hpp \
    entities/scenenode.hpp \
    entities/quadtree.hpp \
    entities/particlenode.hpp \
    entities/entity.hpp \
    entities/emitternode.hpp \
    controllers/playercontroller.hpp \
    resources/posteffect.hpp \
    resources/bloomeffect.hpp \
    states/gamestate.hpp \
    entities/player.hpp \
    entities/wall.hpp \
    entities/crate.hpp \
    entities/uiscore.hpp \
    entities/uibonus.hpp \
    entities/doortrigger.hpp \
    states/pausestate.hpp

include(deployment.pri)
qtcAddDeployment()

