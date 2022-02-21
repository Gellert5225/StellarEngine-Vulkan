# Directory setup
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
RM = rm -f

# Compiler and flags
CC = g++
CFLAGS = -std=c++17 -Wall -g -O3
INCLUDES = -I../Stellar/src/ -I../Stellar/vendor/spdlog/include -I../Stellar/vendor/glfw/include
LFLAGS = -L./bin
LIBS = -lStellar

# Other
BUILT_MSG = Sandbox has been built to bin
INSTALL_NAME_TOOL_STELLAR =
INSTALL_NAME_TOOL_GLFW =
CP_LIBS =

# OS check
ifeq ($(OS),Windows_NT) # OS is a preexisting environment variable on Windows
	OS = windows
	EXE_EXT = .exe
	INCLUDES += -I "C:\VulkanSDK\1.2.198.1\Include"
else
	UNAME := $(shell uname -s)
	EXPORT = export
	ifeq ($(UNAME),Darwin)
		BIN_DIR = ../macOS/StellarEngine.app/Contents/MacOS
		OS = macos
		LIB_PATH = export DYLD_LIBRARY_PATH=./bin;

		INSTALL_NAME_TOOL_STELLAR = $(shell install_name_tool -change lib/libStellar.dylib  "@executable_path/../Frameworks/libStellar.dylib" ../macOS/StellarEngine.app/Contents/MacOS/Sandbox)
        INSTALL_NAME_TOOL_GLFW = $(shell install_name_tool -add_rpath "@executable_path/../Frameworks" ../macOS/StellarEngine.app/Contents/MacOS/Sandbox)
        CP_LIBS = $(shell cp ./bin/libStellar.dylib ../macOS/StellarEngine.app/Contents/Frameworks && cp ./bin/libglfw.3.dylib ../macOS/StellarEngine.app/Contents/Frameworks)
	else 
		ifeq ($(UNAME),Linux)
			OS = linux
			LIB_PATH = export LD_LIBRARY_PATH=./bin;
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
	$(CP_LIBS)
	$(INSTALL_NAME_TOOL_STELLAR)
	$(INSTALL_NAME_TOOL_GLFW)
	@echo Sandbox has been built to bin

$(BIN_DIR)/$(MAIN): $(OBJS) 
	@mkdir -p '$(@D)'
	@$(call run_and_test,$(CC) $(CFLAGS) $(INCLUDES) -o $(BIN_DIR)/$(MAIN) $(OBJS) $(LFLAGS) $(LIBS))

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p '$(@D)'
	@$(call run_and_test, ($(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@))

run:
	$(EXPORT) $(LIB_PATH) \
	$(BIN_DIR)/Sandbox$(EXE_EXT)

run_mac:
	$(shell open ../macOS/StellarEngine.app)

clean:
	@echo "Cleaning"
	@$(RM) -r bin build lib
	@$(RM) ../macOS/StellarEngine.app/Contents/Frameworks/* ../macOS/StellarEngine.app/Contents/MacOS/*

depend: $(SRCS)
	makedepend $(INCLUDES) $^