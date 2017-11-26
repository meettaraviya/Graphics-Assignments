CC=g++

OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw3 -L/usr/local/lib -lXi -lGLEW -lGLU -lm -lGL -lm -lpthread -pthread -ldl -ldrm -lXdamage -lX11-xcb -lxcb-glx -lxcb-dri2 -lglfw3 -lrt -lm -ldl -lXrandr -lXinerama -lXxf86vm -lXext -lXcursor -lXrender -lXfixes -lX11 -lpthread -lxcb -lXau -lXdmcp
GLUTLIB = -lglut
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB) $(GLUTLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I./include/ -g -std=c++11

BIN=assignment4
SRCS=src/*
INCLUDES=include/*

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES)
	$(CC) $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(BIN)
