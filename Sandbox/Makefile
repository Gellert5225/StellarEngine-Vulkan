# Directory setup
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
RM = rm -f

# Compiler and flags
CC = g++
CFLAGS = -std=c++17 -Wall -g -O3
INCLUDES = -I../Stellar/src/
LFLAGS = -L../Stellar/lib
LIBS = -lStellar -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

# Source files
SRC_DIR = src
SRCS := $(sort $(shell find $(SRC_DIR) -name '*.cpp'))
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

# define the executable file 
MAIN = Sandbox

.SECONDARY:

include $(wildcard ../PrettyPrint.inc)

.PHONY: depend clean

all: $(BIN_DIR)/$(MAIN)
	@echo Sandbox has been built to bin

$(BIN_DIR)/$(MAIN): $(OBJS) 
	@mkdir -p '$(@D)'
	@$(call run_and_test,$(CC) $(CFLAGS) $(INCLUDES) -o $(BIN_DIR)/$(MAIN) $(OBJS) $(LFLAGS) $(LIBS))

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p '$(@D)'
	@$(call run_and_test,$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@)

clean:
	@echo "Cleaning"
	@$(RM) -r bin build lib

depend: $(SRCS)
	makedepend $(INCLUDES) $^
