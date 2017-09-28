CC=g++

OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
GLUTLIB = -lglut
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB) $(GLUTLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include -I./include/ -g

BIN=assignment2
SRCS=src/main.cpp src/gl_framework.cpp src/shader_util.cpp src/Model.cpp src/Transformation.cpp
INCLUDES=include/Model.hpp include/Transformation.hpp include/gl_framework.hpp include/main.hpp include/shader_util.hpp

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES)
	$(CC) $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(BIN)
