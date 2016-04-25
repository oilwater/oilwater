#
# Makefile
#
# Created on: Apr 25, 2016
#	Author: rainautumn
#

CXX = g++ -std=c++11

OBJS = src/camera.o src/geometry.o src/initbuff.o src/main.o src/model.o src/position.o
LIBS = -lglfw -lGL -lGLEW -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread
#LIBS = -lglfw3 -lGL -lGLEW -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread
TARGET = oilwater
OUTFILE = res/oilwater
$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all: 	$(TARGET)
	mv $(TARGET) $(OUTFILE)


clean:
	rm -f $(OBJS)
