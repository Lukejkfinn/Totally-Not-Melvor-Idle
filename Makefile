# =========================================================
# Project
# =========================================================
PROJECT_NAME := TotallyNotMelvorIdle
PLATFORM     ?= PLATFORM_DESKTOP
BUILD_MODE   ?= RELEASE

# =========================================================
# Directories
# =========================================================
SRC_DIR := src
INC_DIR := include
OBJ_DIR := build/obj
BIN_DIR := build
DIRS := $(BIN_DIR) $(OBJ_DIR)

# =========================================================
# Raylib
# =========================================================
RAYLIB_PATH ?= C:/raylib/raylib
COMPILER_PATH ?= C:/raylib/w64devkit/bin

# =========================================================
# Platform detection
# =========================================================
ifeq ($(OS),Windows_NT)
    PLATFORM_OS := WINDOWS
    EXE := .exe
    export PATH := $(COMPILER_PATH):$(PATH)
else
    UNAME := $(shell uname)
    ifeq ($(UNAME),Linux)
        PLATFORM_OS := LINUX
    endif
    EXE :=
endif

# =========================================================
# Compiler
# =========================================================
CC := g++

# =========================================================
# Source files
# =========================================================
SRC  := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

# =========================================================
# Compiler flags
# =========================================================
CFLAGS := -Wall -std=c++17 -D_DEFAULT_SOURCE

ifeq ($(BUILD_MODE),DEBUG)
    CFLAGS += -g -O0
else
    CFLAGS += -O2
endif

# =========================================================
# Include paths
# =========================================================
INCLUDE_PATHS := \
	-I$(INC_DIR) \
	-I$(RAYLIB_PATH)/src \
	-I$(RAYLIB_PATH)/src/external

# =========================================================
# Linker flags & libraries
# =========================================================
LDFLAGS := -L$(RAYLIB_PATH)/src

ifeq ($(PLATFORM_OS),WINDOWS)
    LDLIBS := -lraylib -lopengl32 -lgdi32 -lwinmm
else ifeq ($(PLATFORM_OS),LINUX)
    LDLIBS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

# =========================================================
# Targets
# =========================================================
.PHONY: all clean

all: $(BIN_DIR)/$(PROJECT_NAME)$(EXE)

$(BIN_DIR)/$(PROJECT_NAME)$(EXE): $(OBJS) | $(BIN_DIR)
	$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS) -D$(PLATFORM)

$(BIN_DIR) $(OBJ_DIR):
	mkdir $@

# =========================================================
# Clean
# =========================================================
clean:
	rmdir /s /q build 2>nul || true
	@echo Cleaning done
