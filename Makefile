# Brazilian Football - Makefile
# Quick build system for development

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -O2
INCLUDES := -Iengine/src -Igame/src -Iexternal/include
LDFLAGS := -lGL -lGLEW -lglfw -lpthread -lm

SRC_DIR := src
ENGINE_DIR := engine/src
GAME_DIR := game/src
BUILD_DIR := build
BIN_DIR := bin

TARGET := $(BIN_DIR)/BrazilianFootball

# Source files (will be expanded as we add modules)
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
ENGINE_SRCS := $(shell find $(ENGINE_DIR) -name '*.cpp')
GAME_SRCS := $(shell find $(GAME_DIR) -name '*.cpp')

ALL_SRCS := $(SRCS) $(ENGINE_SRCS) $(GAME_SRCS)
OBJS := $(ALL_SRCS:%.cpp=$(BUILD_DIR)/%.o)

.PHONY: all clean dirs run

all: dirs $(TARGET)

dirs:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJS)
	@echo "Linking $@..."
	@$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Build complete: $@"

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "Clean complete"

run: all
	@echo "Running Brazilian Football..."
	@./$(TARGET)

.SILENT:
