## Get from pkgconfig
LIBS=$(shell pkg-config --libs glfw3) -lGL -lm -ldl -lX11 -lXrandr -lXcursor -lXinerama -lXi -lXxf86vm
CXX=g++
CXXFLAGS=-Wall -Wextra -Wfatal-errors -std=c++17
LDFLAGS=

SRC_DIR=modern
OBJ_DIR=build
ABSTR_DIR=abstractions

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.exe,$(SRC_FILES))

ABSTR=$(wildcard $(ABSTR_DIR)/*.cpp)
LIB_OBJ_FILES := $(ABSTR:.cpp=.o)

all: $(OBJ_FILES)

openglib: $(LIB_OBJ_FILES)
	echo "$(ABSTR)"
	echo "$(LIB_OBJ_FILES)"
	ar rcs lib/lib$@.a $^

# all: prepare simple modern glew shader shader2 shader_sq shader_err

abstractions/%.o: abstractions/%.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ -c $^ -pthread $(LIBS) -L/usr/lib64/ -lGLEW -lGLU

build/%.exe: modern/%.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ -pthread $(LIBS) -L/usr/lib64/ -Llib/ -lGLEW -lGLU -lopenglib

prepare:
	mkdir -p build
