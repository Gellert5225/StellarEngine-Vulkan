# Directory setup
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
RM = rm -f

# Compiler and flags
CC = export LD_LIBRARY_PATH=:./bin; g++
CFLAGS = -std=c++17 -Wall -g -O3
INCLUDES = -I../Stellar/src/
LFLAGS = -L./bin -Wl,-rpath,./bin
LIBS = -lStellar

ifeq ($(OS),Windows_NT) # OS is a preexisting environment variable on Windows
	OS = windows
	EXE_EXT = .exe
else
	UNAME := $(shell uname -s)
	ifeq ($(UNAME),Darwin)
		OS = macos
	else 
		ifeq ($(UNAME),Linux)
			OS = linux
		else
			$(error OS not supported by this Makefile)
		endif
	endif
endif
# Source files
SRC_DIR = src
SRCS := $(sort $(shell find $(SRC_DIR) -name '*.cpp'))
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

ifeq ($(OS),linux)
	LIBS += -lglfw -lvulkan
endif

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

run:
	./bin/Sandbox$(EXE_EXT)

clean:
	@echo "Cleaning"
	@$(RM) -r bin build lib

depend: $(SRCS)
	makedepend $(INCLUDES) $^
