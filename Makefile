CXX = g++ -std=c++11
OBJS = main.o utils.o

LIBS =	-lglfw -lGL -lGLEW -lm -lXrandr -lXi -lX11 -lXxf86vm -lXinerama -lXcursor -lpthread

OBJS = \
    src/camera.o \
    src/initbuff.o \
    src/kernel.o \
    src/main.o \
    src/model.o \
    src/position.o \
    src/terminal.o \
    src/network.o \
    src/letter_sprite.o \
    src/physic.o

TARGET = 	oilwater

$(TARGET):	$(OBJS)
	$(CXX)  $(OBJS) $(LIBS) -o $(TARGET)

all:	$(TARGET)

clean:
	rm $(OBJS) 
	

