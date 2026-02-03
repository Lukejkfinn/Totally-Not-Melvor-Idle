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
OBJ_DIR := build\obj
BIN_DIR := .
RES_DIR := assets

# =========================================================
# Raylib / Toolchain
# =========================================================
RAYLIB_PATH    ?= C:/raylib/raylib
COMPILER_PATH  ?= C:/raylib/w64devkit/bin

# =========================================================
# Platform detection
# =========================================================
ifeq ($(OS),Windows_NT)
    PLATFORM_OS := WINDOWS
    EXE := .exe
    MKDIR := mkdir
    RMDIR := rmdir /s /q
    WINDRES := windres
    export PATH := $(COMPILER_PATH):$(PATH)
else
    UNAME := $(shell uname)
    ifeq ($(UNAME),Linux)
        PLATFORM_OS := LINUX
    endif
    EXE :=
    MKDIR := mkdir -p
    RMDIR := rm -rf
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
# Windows resources (ICON)
# =========================================================
RES_RC  := $(RES_DIR)/icon.rc
RES_OBJ := $(OBJ_DIR)/icon.o

# =========================================================
# Compiler flags
# =========================================================
CFLAGS := -Wall -std=c++17 -D_DEFAULT_SOURCE -D$(PLATFORM)

ifeq ($(BUILD_MODE),DEBUG)
    CFLAGS += -g -O0
else
    CFLAGS += -O2 -DNDEBUG
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
    ifneq ($(BUILD_MODE),DEBUG)
        LDFLAGS += -mwindows
    endif
else ifeq ($(PLATFORM_OS),LINUX)
    LDLIBS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

# =========================================================
# Targets
# =========================================================
.PHONY: all clean

all: $(PROJECT_NAME)$(EXE)

# Link executable
$(PROJECT_NAME)$(EXE): $(OBJS) $(RES_OBJ) | $(OBJ_DIR)
	$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)

# Compile C++ sources
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS)

# Compile Windows resource file
$(RES_OBJ): $(RES_RC) | $(OBJ_DIR)
	$(WINDRES) $< $@

# Create object directory
$(OBJ_DIR):
	$(MKDIR) $@

# =========================================================
# Clean (cross-platform)
# =========================================================
clean:
	@echo Cleaning object files...
ifeq ($(PLATFORM_OS),WINDOWS)
	@cmd /c "if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)"
	@cmd /c "mkdir $(OBJ_DIR) 2>nul"
else
	@rm -rf $(OBJ_DIR)/*
	@mkdir -p $(OBJ_DIR)
endif
	@echo Object files cleaned and obj folder recreated.






