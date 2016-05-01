#
# Makefile
#
# Created on: Apr 25, 2016
#	Author: rainautumn
#

CXX = g++ -std=c++11

OBJS = src/camera.o src/geometry.o src/initbuff.o src/main.o src/model.o src/position.o src/kernel.o
LIBS =	-lglfw -lGL -lGLEW -lm -lXrandr -lXi -lX11 -lXxf86vm -lXinerama -lXcursor -lpthread

# On FreeBSD glfw it glfw3.
#
#LIBS =	-lglfw3 -lGL -lGLEW -lm -lXrandr -lXi -lX11 -lXxf86vm -lXinerama -lXcursor -lpthread

TARGET = oilwater
$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all: 	$(TARGET)

clean:
	rm -f $(OBJS)
