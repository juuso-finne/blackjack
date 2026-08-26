RAYLIB_PATH = C:/raylib/raylib
SHELL := C:/raylib/w64devkit/bin/sh.exe

INCLUDES = -I$(RAYLIB_PATH)/src
LDFLAGS  = -L$(RAYLIB_PATH)/src

LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

OBJ_DIR = obj/$(BUILD)
SRC_DIR = src

rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

SRCS = $(call rwildcard,$(SRC_DIR)/,*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

BUILD ?= Debug

ifeq ($(BUILD),Debug)
    CFLAGS = -Wall -std=c++17 -g -O0
else ifeq ($(BUILD),Release)
    CFLAGS = -Wall -std=c++17 -O2
else
    $(error Unknown BUILD=$(BUILD))
endif


PROJECT := $(notdir $(CURDIR))

.PHONY: all clean

all:  $(PROJECT).exe

$(PROJECT).exe: $(OBJS)
	g++ -o  $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	g++ -c $< -o $@ $(CFLAGS) $(INCLUDES)

clean:
	rm -rf $(OBJ_DIR) $(PROJECT).exe
