# Directory setup
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
RM = rm -f

# OS check
ifeq ($(OS),Windows_NT) # OS is a preexisting environment variable on Windows
	OS = windows
	EXE_EXT = .exe
else
	UNAME := $(shell uname -s)
	EXPORT = export
	ifeq ($(UNAME),Darwin)
		OS = macos
		LIB_PATH = export DYLD_LIBRARY_PATH=./bin;
	else 
		ifeq ($(UNAME),Linux)
			OS = linux
			LIB_PATH = export LD_LIBRARY_PATH=./bin;
		else
			$(error OS not supported by this Makefile)
		endif
	endif
endif

# Compiler and flags
CC = g++
CFLAGS = -std=c++17 -Wall -g -O3
INCLUDES = -I../Stellar/src/ -I../Stellar/vendor/spdlog/include
LFLAGS = -L./bin
LIBS = -lStellar

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
	$(EXPORT) $(LIB_PATH) \
	./bin/Sandbox$(EXE_EXT)

clean:
	@echo "Cleaning"
	@$(RM) -r bin build lib

depend: $(SRCS)
	makedepend $(INCLUDES) $^
