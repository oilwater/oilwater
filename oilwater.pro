QT += core
QT += gui

CONFIG += c++11
INCLUDEPATH += /usr/local/Cellar/glew/1.13.0/include/
INCLUDEPATH += /usr/local/Cellar/glfw3/3.1.2/include/
#QMAKE_CXXFLAGS += -std=c++11

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
    src/position.cpp \
    src/terminal.cpp \
    src/network.cpp

HEADERS += \
    src/camera.h \
    src/geometry.h \
    src/glmath.hpp \
    src/initbuff.hpp \
    src/kernel.h \
    src/model.h \
    src/position.h \
    src/terminal.h \
    src/network.h

#LIBS =	-lglfw -lGL -lGLEW -lm -lXrandr -lXi -lX11 -lXxf86vm -lXinerama -lXcursor -lpthread
LIBS = -L/usr/local/Cellar/glew/1.13.0/lib -L/usr/local/Cellar/glfw3/3.1.2/lib -framework OpenGL -lglfw3 -lGLEW -framework IOKit -framework CoreFoundation -framework CoreVideo -framework Cocoa -v


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
    res/box_red/shaders/frag.glsl \
    res/boom_test_sprite/shaders/vert.glsl \
    res/boom_test_sprite/shaders/frag.glsl
