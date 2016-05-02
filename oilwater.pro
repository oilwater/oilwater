QT += core
QT += gui

CONFIG += c++11

TARGET = oilwater
CONFIG -= console

TEMPLATE = app

SOURCES += \
    src/camera.cpp \
    src/geometry.cpp \
    src/initbuff.cpp \
    src/kernel.cpp \
    src/main.cpp \
    src/model.cpp \
    src/position.cpp

HEADERS += \
    src/camera.h \
    src/geometry.h \
    src/glmath.hpp \
    src/initbuff.hpp \
    src/kernel.h \
    src/model.h \
    src/position.h

LIBS =	-lglfw -lGL -lGLEW -lm -lXrandr -lXi -lX11 -lXxf86vm -lXinerama -lXcursor -lpthread

# On FreeBSD glfw it glfw3.
#
#LIBS =	-lglfw3 -lGL -lGLEW -lm -lXrandr -lXi -lX11 -lXxf86vm -lXinerama -lXcursor -lpthread

DISTFILES += \
    res/map_test/shaders/vert.glsl \
    res/map_test/shaders/frag.glsl \
    res/load_sprite_inside/shaders/vert.glsl \
    res/load_sprite_inside/shaders/frag.glsl \
    res/load_sprite_outside/shaders/vert.glsl \
    res/load_sprite_outside/shaders/frag.glsl \
    res/box_red/shaders/vert.glsl \
    res/box_red/shaders/frag.glsl
