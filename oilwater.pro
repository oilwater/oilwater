QT += core
QT += gui
QT += network

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
    src/position.cpp \
    src/terminal.cpp \
    src/network.cpp \
    src/letter_sprite.cpp \
    src/physic.cpp

HEADERS += \
    src/camera.h \
    src/geometry.h \
    src/glmath.hpp \
    src/initbuff.hpp \
    src/kernel.h \
    src/model.h \
    src/position.h \
    src/terminal.h \
    src/network.h \
    src/letter_sprite.h \
    src/physic.h

#LIBS =	-lglfw -lGL -lGLEW -lm -lXrandr -lXi -lX11 -lXxf86vm -lXinerama -lXcursor -lpthread

# OS X PATH
#
#INCLUDEPATH += /usr/local/Cellar/glew/1.13.0/include/
#INCLUDEPATH += /usr/local/Cellar/glfw3/3.1.2/include/
#
# OS X LIBS
#
#LIBS = -L/usr/local/Cellar/glew/1.13.0/lib -L/usr/local/Cellar/glfw3/3.1.2/lib -framework OpenGL -lglfw3 -lGLEW -framework IOKit -framework CoreFoundation -framework CoreVideo -framework Cocoa -v


# FreeBSD LIBS LIBS
#
#LIBS =	-lglfw3 -lGL -lGLEW -lm -lXrandr -lXi -lX11 -lXxf86vm -lXinerama -lXcursor -lpthread

# WIN32 
#
LIBS =  -lglfw3 -lopengl32 -lgdi32 -lglew32 -Wl,--subsystem,windows

DISTFILES += \
    res/maps/cyam_map_test/shaders/vert.glsl \
    res/maps/cyam_map_test/shaders/frag.glsl \
    res/list \
    res/maps/test.map \
    res/maps/default_map.map \
    res/maps/map_test/shaders/frag.glsl \
    res/maps/map_test/shaders/vert.glsl
